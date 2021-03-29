/**
 * wheelchair.cpp
 * Authored by MSD team P21311, 2021
 * Samples taken from Intel library / examples and some open forums.
 * main to stitch pose and distance cameras, communication, and pathing
 * 
 *
**/

#include "wheelchair.h"

// global variables //
bool reset_pose = false;
int node_num = 0; //starting/current node idx
int distance_traveled = 0; //total distance gone
int distance_togo = 0; //distance to next node
/// start and end positions
int start_node;// = 0;
int end_node;// = 6;

// private function prototypes
BasePath* get_shortest_path(string map, int start, int end);
void next_dist(BasePath* result);
bool is_number(const std::string& s);

///
/// main
///
int main(int argc, char *argv[]) {
	// get arguments for start and end nodes
	if (argc < 3) {
		cout << "Include a start and end node before running\r\n
				\tEX: ./wheelchair 0 6\r\n";
		return 1;
	}
	else {
		if (is_number(argv[1]) && is_number(argv[2])) {
			start_node = atoi(argv[1];
			end_node = atoi(argv[2];
		}
	} //end argument collection

    rs2::pose_frame pose_frame(nullptr);
    std::vector<rs2_vector> trajectory;
	// Create librealsense context for managing devices
    rs2::context                          ctx;
    std::vector<rs2::pipeline>            pipelines;
    rs2::config                           t265_config;

    // Capture serial numbers before opening streaming
    std::vector<std::string>              serials;
    for (auto&& dev : ctx.query_devices())
        serials.push_back(dev.get_info(RS2_CAMERA_INFO_SERIAL_NUMBER));

    // Start a streaming pipe per each connected device
    for (auto&& serial : serials) {
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

	// get the path to travel
    BasePath* result = get_shortest_path("path_planning/map_v2", 
			start_node, end_node);
	//result->PrintOut(cout); // debug statment
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

                // Print the x, y, z values of the translation, 
				//   relative to initial position
                auto pose_data = pose.get_pose_data();
                std::cout << "\r" << "Device Position: " 
					<< pose_data.translation.x << " : " 
					<< pose_data.translation.y << " : " 
					<< pose_data.translation.z << " (meters)\n\n";

                // add new point in the trajectory 
				// (if motion large enough to reduce size of traj. vector)
                if (trajectory.size() == 0)
                    trajectory.push_back(pose_data.translation);
                else {
                    rs2_vector prev = trajectory.back();
                    rs2_vector curr = pose_data.translation;
                    if(sqrt(pow((curr.x - prev.x),2) + pow((curr.y - prev.y),2) 
							+ pow((curr.z - prev.z),2)) > 0.002){
                        trajectory.push_back(pose_data.translation);
                    }
                }

				///
				/// check distance traveled
				///
				// reached node
				if (-(pose_data.translation.z) >= distance_togo) {
					cout << "!! Reached node ID ";
                        cout << result->GetVertex(node_num)->getID();
                        cout << "\r\n";
					// distance_traveled will equal total node wight from graph
					distance_traveled = distance_traveled + distance_togo; 
                    //check if at destination
                    if (result->GetVertex(node_num)->getID() == end_node){
                        cout << "You made it!\r\n";
                        return 0;
                    }
                    //else continue to next node
					next_dist(result);
					reset_pose = true;
					//TODO communication - stop chair?
				} // end reached
				// still traveling
				else{
					//TODO communication - start chair?
					//debug print
					cout << "not yet at node idx ";
                        cout << node_num;
                        cout << "\r\n";
					cout << "D: ";
                        cout << -(pose_data.translation.z);
                        cout << "out of ";
                        cout << distance_togo;
                        cout << "\r\n";
				}
				///
				/// end distance check
				///

                // Reset pose when needed
                if(reset_pose){
					//TODO
					// Turn check on angle - reach goal so not a high priority
					// comment is example for reading from gyro
					// more reading motion ex from: 
					// https://github.com/IntelRealSense/librealsense/blob/master/doc/t265.md
					/*
					if (rs2::motion_frame gyro_frame = 
							frameset.first_or_default(RS2_STREAM_GYRO)){
					   rs2_vector gyro_sample = gyro_frame.get_motion_data();
						//std::cout << "Gyro:" << gyro_sample.x << ", " 
						<< gyro_sample.y << ", " 
						<< gyro_sample.z << std::endl;
						//...
					}
					*/

                    pipe.stop();
                    std::this_thread::sleep_for(std::chrono::seconds(1));
                    /// wait for turn
                    cout << "press any key and then ENTER once 
								turned to face node ID ";
                        cout << (node_num + 1);
                        cout << "\r\n";
                    int waiter;
                    cin >> waiter;
                    pipe.start(t265_config);
                    reset_pose = false;
					next_dist(result);
                } //end reset pose block
            } //end pose frame block

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

	} //end loop
    return 0;
} //end main

//check if string is number for argument parsing to get start/end nodes
bool is_number(const std::string& s) {
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}

//check distance to next node in pathing
void next_dist(BasePath* result) {
	node_num++; //increment path index
	int d = result->GetVertex(node_num)->Weight(); //distance to next node
	distance_togo = d - distance_traveled;
}

//get pathing from starting node to ending node 
BasePath* get_shortest_path(string map, int start, int end){
	Graph* my_graph_pt = new Graph(map);
	DijkstraShortestPathAlg shortest_path_alg(my_graph_pt);
	BasePath* result =
		shortest_path_alg.get_shortest_path(
			my_graph_pt->get_vertex(start), my_graph_pt->get_vertex(end));
    return result;
}
