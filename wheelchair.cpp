
#include "wheelchair.h"

bool reset_pose = false;
int node_num = 0; //starting/current node idx
int distance_traveled = 0; //total distance gone
int distance_togo = 0; //distance to next node

BasePath* get_shortest_path(string map, int start, int end);
void next_dist(BasePath* result);

int main(){

    rs2::pose_frame pose_frame(nullptr);
    std::vector<rs2_vector> trajectory;
    rs2::context                          ctx;        // Create librealsense context for managing devices
    std::vector<rs2::pipeline>            pipelines;
    rs2::config                           t265_config;


    // Capture serial numbers before opening streaming
    std::vector<std::string>              serials;
    for (auto&& dev : ctx.query_devices())
        serials.push_back(dev.get_info(RS2_CAMERA_INFO_SERIAL_NUMBER));


    // Start a streaming pipe per each connected device
    for (auto&& serial : serials)
    {
        rs2::pipeline pipe(ctx);
        rs2::config cfg;
        cfg.enable_device(serial);
        pipe.start(cfg);
        pipelines.emplace_back(pipe);

        //Save T265 config for reset later
        if(serial.compare(T265_SERIAL) == 0){
            t265_config = cfg;
        }
    }

    BasePath* result = get_shortest_path("path_planning/map_v2", 0, 6);
	//result->PrintOut(cout);
	next_dist(result); // get distance to check against for next node distance

    //Test grid system
	while(1){
        for (auto &&pipe : pipelines){ // loop over pipelines
            // Wait for the next set of frames from the camera
            auto frames = pipe.wait_for_frames();

            // pose - T265
            auto pose = frames.get_pose_frame();
            if (pose) {
                pose_frame = pose;

                // Print the x, y, z values of the translation, relative to initial position
                auto pose_data = pose.get_pose_data();
                std::cout << "\r" << "Device Position: " << pose_data.translation.x << " : " << pose_data.translation.y << " : " << pose_data.translation.z << " (meters)\n\n";

                // add new point in the trajectory (if motion large enough to reduce size of traj. vector)
                if (trajectory.size() == 0)
                    trajectory.push_back(pose_data.translation);
                else {
                    rs2_vector prev = trajectory.back();
                    rs2_vector curr = pose_data.translation;
                    if (sqrt(pow((curr.x - prev.x), 2) + pow((curr.y - prev.y), 2) + pow((curr.z - prev.z), 2)) > 0.002){
                        trajectory.push_back(pose_data.translation);
                    }
                }

				///
				/// check distance traveled
				if (pose_data.translation.z >= distance_togo) {
					cout << "!! Reached node ID ";
                        cout << result->GetVertex(node_num)->getID();
                        cout << "\r\n";
					distance_traveled = distance_traveled + distance_togo; //will equal node wight
					next_dist(result);
					reset_pose = true;
					//TODO communication - stop chair?
				}
				else{
					//TODO communication - start chair?
					//debug print
					cout << "not yet at node idx " + node_num + "\r\n";
					cout << "D: " + pose_data.translation.z + "out of " + 
												distance_togo + "\r\n";
				}
				///
				///

                // Reset pose when needed
                if(reset_pose){
                    pipe.stop();
                    std::this_thread::sleep_for(std::chrono::seconds(1));
                    pipe.start(t265_config);
                    reset_pose = false;
					next_dist(result);
                }
            }

            auto depth = frames.get_depth_frame();

            // Generate the pointcloud and texture mappings
            if (depth){
               quadrant_distance(pipe);

            #ifdef ABS
                print_distances();
            #endif

            #ifdef DET
                print_marked_quadrents();
            #endif

			#ifdef PDBG
                print_direction();
			#endif

            #ifndef ABS
            #ifndef DET
			#ifndef PDBG
			switch (turn_direction()) {
				case 0:
					//forward
					//TODO communication add message here
					break;
				case 1:
					//turn right
					//TODO communication add message here
					break;
				case 2:
					//turn left
					//TODO communication add message here
					break;
				default:
					//forward again
					//TODO communication add message here
					break;
			}
            #endif
            #endif
			#endif
            }

        }

	}
    return 0;
}


void next_dist(BasePath* result) {
	node_num++; //increment path index
	int d = result->GetVertex(node_num)->Weight(); //distance to next node
	distance_togo = d - distance_traveled;
}


BasePath* get_shortest_path(string map, int start, int end){

	Graph* my_graph_pt = new Graph(map);
	DijkstraShortestPathAlg shortest_path_alg(my_graph_pt);
	BasePath* result =
		shortest_path_alg.get_shortest_path(
			my_graph_pt->get_vertex(start), my_graph_pt->get_vertex(end));

    return result;
}
