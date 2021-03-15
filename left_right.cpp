#include <librealsense2/rs.hpp>
#include <stdio.h>
#include <math.h>
#include <iostream>
#include <algorithm>            // std::min, std::max
#include <thread>
#include <chrono>

/** compile with::
*
*    g++ -std=c++11 <filename> -lrealsense2
*       -DABS if you want raw quadrent distance
*		-DDET if want grid of blockage
*
**/


#define THRESH 0.5
#define T265_SERIAL "8122110243"

float quadrents[16] = {0};
bool  reset_pose = false;

void quadrant_distance(rs2::pipeline p){
    // Block program until frames arrive
	rs2::frameset frames = p.wait_for_frames();

	// Try to get a frame of a depth image
	rs2::depth_frame depth = frames.get_depth_frame();

	// Get the depth frame's dimensions
	float width = depth.get_width();
	float height = depth.get_height();

    //get 4 sections
    float wdiv = width/4;
    float hdiv = height/4;

	// Query the distance from the camera to the object in the
	//		center of the image
	float total_pixel = width * height;

    //measure Q0
	for(int i_w = 0; i_w < wdiv; i_w++){
		for(int i_h = 0; i_h < hdiv; i_h++){
			quadrents[0] = quadrents[0] + depth.get_distance(i_w, i_h);
		}
	}
	quadrents[0] = quadrents[0] / (total_pixel/16);

    //measure Q1
	for(int i_w = wdiv; i_w < (wdiv*2); i_w++){
		for(int i_h = 0; i_h < hdiv; i_h++){
			quadrents[1] = quadrents[1] + depth.get_distance(i_w, i_h);
		}
	}
	quadrents[1] = quadrents[1] / (total_pixel/16);

    //measure Q2
	for(int i_w = (wdiv*2); i_w < (wdiv*3); i_w++){
		for(int i_h = 0; i_h < hdiv; i_h++){
			quadrents[2] = quadrents[2] + depth.get_distance(i_w, i_h);
		}
	}
	quadrents[2] = quadrents[2] / (total_pixel/16);

    //measure Q3
	for(int i_w = (wdiv*3); i_w < width; i_w++){
		for(int i_h = 0; i_h < hdiv; i_h++){
			quadrents[3] = quadrents[3] + depth.get_distance(i_w, i_h);
		}
	}
	quadrents[3] = quadrents[3] / (total_pixel/16);

    //measure Q4
	for(int i_w = 0; i_w < wdiv; i_w++){
		for(int i_h = hdiv; i_h < (hdiv*2); i_h++){
			quadrents[4] = quadrents[4] + depth.get_distance(i_w, i_h);
		}
	}
	quadrents[4] = quadrents[4] / (total_pixel/16);

    //measure Q5
	for(int i_w = wdiv; i_w < (wdiv*2); i_w++){
		for(int i_h = hdiv; i_h < (hdiv*2); i_h++){
			quadrents[5] = quadrents[5] + depth.get_distance(i_w, i_h);
	    }
	}
	quadrents[5] = quadrents[5] / (total_pixel/16);

    //measure Q6
	for(int i_w = (wdiv*2); i_w < (wdiv*3); i_w++){
		for(int i_h = hdiv; i_h < (hdiv*2); i_h++){
			quadrents[6] = quadrents[6] + depth.get_distance(i_w, i_h);
		}
	}
	quadrents[6] = quadrents[6] / (total_pixel/16);

    //measure Q7
	for(int i_w = (wdiv*3); i_w < width; i_w++){
		for(int i_h = hdiv; i_h < (hdiv*2); i_h++){
			quadrents[7] = quadrents[7] + depth.get_distance(i_w, i_h);
		}
	}
	quadrents[7] = quadrents[7] / (total_pixel/16);

    //measure Q8
	for(int i_w = 0; i_w < wdiv; i_w++){
		for(int i_h = (hdiv*2); i_h < (hdiv*3); i_h++){
			quadrents[8] = quadrents[8] + depth.get_distance(i_w, i_h);
		}
	}
	quadrents[8] = quadrents[8] / (total_pixel/16);

    //measure Q9
	for(int i_w = wdiv; i_w < (wdiv*2); i_w++){
		for(int i_h = (hdiv*2); i_h < (hdiv*3); i_h++){
			quadrents[9] = quadrents[9] + depth.get_distance(i_w, i_h);
		}
	}
	quadrents[9] = quadrents[9] / (total_pixel/16);

    //measure Q10
	for(int i_w = (wdiv*2); i_w < (wdiv*3); i_w++){
		for(int i_h = (hdiv*2); i_h < (hdiv*3); i_h++){
			quadrents[10] = quadrents[10] + depth.get_distance(i_w, i_h);
		}
	}
	quadrents[10] = quadrents[10] / (total_pixel/16);

    //measure Q11
	for(int i_w = (wdiv*3); i_w < width; i_w++){
		for(int i_h = (hdiv*2); i_h < (hdiv*3); i_h++){
			quadrents[11] = quadrents[11] + depth.get_distance(i_w, i_h);
		}
	}
	quadrents[11] = quadrents[11] / (total_pixel/16);

    //measure Q12
	for(int i_w = 0; i_w < wdiv; i_w++){
		for(int i_h = (hdiv*3); i_h < height; i_h++){
			quadrents[12] = quadrents[12] + depth.get_distance(i_w, i_h);
		}
	}
    quadrents[12] = quadrents[12] / (total_pixel/16);

    //measure Q13
	for(int i_w = wdiv; i_w < (wdiv*2); i_w++){
		for(int i_h = (hdiv*3); i_h < height; i_h++){
			quadrents[13] = quadrents[13] + depth.get_distance(i_w, i_h);
		}
	}
	quadrents[13] = quadrents[13] / (total_pixel/16);

    //measure Q14
	for(int i_w = (wdiv*2); i_w < (wdiv*3); i_w++){
		for(int i_h = (hdiv*3); i_h < height; i_h++){
			quadrents[14] = quadrents[14] + depth.get_distance(i_w, i_h);
		}
	}
	quadrents[14] = quadrents[14] / (total_pixel/16);

    //measure Q15
	for(int i_w = (wdiv*3); i_w < width; i_w++){
		for(int i_h = (hdiv*3); i_h < height; i_h++){
			quadrents[15] = quadrents[15] + depth.get_distance(i_w, i_h);
		}
	}
	quadrents[15] = quadrents[15] / (total_pixel/16);
}

void print_distances(){
    std::cout << "============================\n\n";
    std::cout << quadrents[0] << " " << quadrents[1] << " " << quadrents[2] << " " << quadrents[3] << "\n";
	std::cout << quadrents[4] << " " << quadrents[5] << " " << quadrents[6] << " " << quadrents[7] << "\n";
	std::cout << quadrents[8] << " " << quadrents[9] << " " << quadrents[10] << " " << quadrents[11] << "\n";
	std::cout << quadrents[12] << " " << quadrents[13] << " " << quadrents[14] << " " << quadrents[15] << "\n";
}

void print_marked_quadrents(){
    //determine blockage in quadrents
	char fill[16] = {'O'};
    for (int c=0; c < 16; c++){
        if (quadrents[c] < THRESH) {
           	fill[c] = 'X';
		}
		else {
			fill[c] = 'O';
		}
    }

    //print filled quadents
	for (int v=0; v < 16; v++) {
		std::cout << fill[0] << " | " << fill[1] << " | " << fill[2] << " | " << fill[3] << "\n";
		std::cout << "--------------\n";
		std::cout << fill[4] << " | " << fill[5] << " | " << fill[6] << " | " << fill[7] << "\n";
		std::cout << "--------------\n";
		std::cout << fill[8] << " | " << fill[9] << " | " << fill[10] << " | " << fill[11] << "\n";
		std::cout << "--------------\n";
		std::cout << fill[12] << " | " << fill[13] << " | " << fill[14] << " | " << fill[15] << "\n";
		std::cout << "--------------\n\n";
	}
}

void print_direction(){
	//left
    for (int c=0; c < 16; c+=4){
        if (quadrents[c] < THRESH) {
            std::cout << "somethig close on left side" << c << "\n";
			std::cout << "==turn to the right==\n";
        }
    }
	//right
	for (int c=3; c < 16; c+=4){
        if (quadrents[c] < THRESH) {
            std::cout << "somethig close on right side" << c << "\n";
		    std::cout << "==turn to the left==\n";
        }
    }
	//center left
    for (int c=1; c < 16; c+=4){
        if (quadrents[c] < THRESH) {
            std::cout << "somethig close on lcenter" << c << "\n";
			std::cout << "==turn to the right==\n";
        }
    }
	//center right
	for (int c=2; c < 16; c+=4){
        if (quadrents[c] < THRESH) {
            std::cout << "somethig close on rcenter" << c << "\n";
	    	std::cout << "==turn to the left==\n";
        }
    }

}

int main(){

	// Create a Pipeline - this serves as a top-level API for streaming and processing frames
	//rs2::pipeline p;
	//rs2::config cfg;
	//cfg.enable_stream(RS2_STREAM_DEPTH);
	//p.start(cfg);

    rs2::pose_frame pose_frame(nullptr);
    std::vector<rs2_vector> trajectory;
    rs2::context                          ctx;        // Create librealsense context for managing devices
    //std::map<std::string, rs2::colorizer> colorizers; // Declare map from device serial number to colorizer
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

        if(serial.compare(T265_SERIAL) == 0){
            std::cout << "Serial Found " << serial << "\n";
            t265_config = cfg;
        }
    }

    //Test grid system
	while(1){
        for (auto &&pipe : pipelines){ // loop over pipelines
            // Wait for the next set of frames from the camera
            auto frames = pipe.wait_for_frames();

            // pose
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

                // Reset pose when needed
                if(reset_pose){
                    pipe.stop();
                    std::this_thread::sleep_for(std::chrono::seconds(1));
                    pipe.start(t265_config);
                    reset_pose = false;
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

            #ifndef ABS
                #ifndef DET
                //print_direction();
                #endif
            #endif

            }

        }

	}
    return 0;
}



