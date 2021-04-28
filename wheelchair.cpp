/**
 * wheelchair.cpp
 * Authored by MSD team P21311, 2021
 * Samples taken from Intel library / examples and some open forums.
 * main to stitch pose and distance cameras, communication, and pathing
 *
 *
**/
#include <iostream>
#include <iomanip>

#include "wheelchair.h"

// global variables //
bool reset_pose = false;
int node_num = 1; //starting/current node idx
int distance_traveled = 0; //total distance gone
int distance_togo = 0; //distance to next node
/// start and end positions
int start_node;
int end_node;
//boolean for main while - use to clean exit on destination reached
bool g_running;
// node IDs for turning requirement
int prev_ID;
int curr_ID;
int next_ID;

// private function prototypes
BasePath* get_shortest_path(string map, int start, int end);
void next_dist(BasePath* result);
bool is_number(const std::string& s);


void signalHandler(int signum) {
   //cleanup_arduino(); // is run at end of main function - not needed twice
   g_running = false;
}

///
/// main
///
int main(int argc, char *argv[]) {
	//
	//signal handler to cleanly exit arduino
	//
	signal(SIGINT, signalHandler);

	// get arguments for start and end nodes
	if (argc < 2) {
		cout << "Include a start and end node before running\r\n\tEX: ./wheelchair 0\r\n";
		return 1;
	}
	else {
		if (is_number(argv[1])) {
			start_node = atoi(argv[1]);
		}
	} //end argument collection

    end_node = Init_Headset(start_node);
    if(end_node < 0){
        std::cout << "Headset connection errored\r\n";
        return 1;
    }

    bool moving = false;
    int x_val = 0;
    int y_val = 0;
    if(!Init_Arduino()){
        std::cout << "Failed to connect to arduino\r\n";
        return 1;
    }


	//set up cameras
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

	///
	/// turn stuffs
	///
	int read_ret = read_directions();
	if(read_ret == 1) { //error check
		std::cout << "ERROR reading directions for node turns\n";
	}


	//start running
	g_running = true;
	// set turn ID variables -> get adjusted in turn for each subsequent turn
	prev_ID = start_node;
	curr_ID = result->GetVertex(node_num)->get_ID();
	next_ID = result->GetVertex(node_num+1)->get_ID();
	//
    // main loop that interfaces with cameras and makes decisions
	//
	while(g_running){
		//debug prints
		cout << "prev = " << prev_ID << " curr = " << curr_ID << " next = " << next_ID << "\n";


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
                std::cout << std::fixed;
                std::cout << std::setprecision(5);
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
					//debug prints
					cout << "!! Reached node ID ";
                        cout << result->GetVertex(node_num)->getID();
                        cout << "\r\n";

					// distance_traveled will equal total node wight from graph
					distance_traveled = distance_traveled + distance_togo;
                    //check if at destination
                    if (result->GetVertex(node_num)->getID() == end_node){
                        cout << "You made it!\r\n";
                        send_reached_destination();
                        //return 0;
						g_running = false;
                    }
                    //else continue to next node

                    //next_dist(result);
                    else {
					    reset_pose = true;
                    }
                    moving = false;
				} // end reached
				// still traveling
				else{
                    moving = true;
					//debug print
					cout << "not yet at node ID ";
                        cout << result->GetVertex(node_num)->getID();
                        cout << "\r\n";
					cout << "D: ";
                        cout << -(pose_data.translation.z);
                        cout << " out of ";
                        cout << distance_togo;
                        cout << "\r\n";
				}
				///
				/// end distance check
				///

                // Reset pose when needed @ node
                if(reset_pose){
                    //
                    // send stop signal, waiting on turn
                    //
                    send_arduino_cmd(0, 0);

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
					
					//determine turn
					int turn_direction = get_direction(prev_ID, curr_ID, next_ID);
					// set new node IDs 
					prev_ID = curr_ID;
					curr_ID = next_ID;
					next_ID = result->GetVertex(node_num+1)->getID();

					switch (turn_direction) {
						case -1:
                    		cout << "press any key and then ENTER, once turned LEFT.\n";
							break;
						case 0:
                    		cout << "press any key and then ENTER, going STRAIGHT.\n";
							break;
						case 1:
                    		cout << "press any key and then ENTER, once turned RIGHT";
							break;
						defualt:
							cout << "problem in determining turn.\n";
							break;
					}

					//wait for input to confirm turn completed
                    int waiter;
                    cin >> waiter;
                    pipe.start(t265_config);
                    reset_pose = false;

	                node_num++; //increment path index
					next_dist(result);
                } //end reset pose block
            } //end pose frame block


            auto depth = frames.get_depth_frame();
            // Generate the pointcloud and texture mappings
			// object detection
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
					x_val = steer(0);
					y_val = forward(x_val);
					break;
				case 1:
					//turn right
					x_val = steer(1);
					y_val = forward(x_val);
					break;
				case 2:
					//turn left
					x_val = steer(2);
					y_val = forward(x_val);
					break;
				case 3:
					//turn right, center left
					x_val = steer(3);
					y_val = forward(x_val);
					break;
				case 4:
					//turn left, center right
					x_val = steer(4);
					y_val = forward(x_val);
					break;
				case 5:
					//wall - stop
					x_val = 0;
					y_val = 0;
					break;
				default:
					//stop
					x_val = 0;
					y_val = 0;
					break;
			}
            cout << x_val << " " << y_val << "\n";
            #endif
            #endif
			#endif
            }

        }
        if(!moving){
            x_val = 0;
            y_val = 0;
        }
        send_arduino_cmd(x_val, y_val);
	} //end loop
	cleanup_arduino();
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
	//node_num++; //increment path index
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
