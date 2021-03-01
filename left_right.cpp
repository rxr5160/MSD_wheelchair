#include <librealsense2/rs.hpp>
#include <stdio.h>
#include <iostream>


/** compile with::
*
*    g++ -std=c++11 -lrealsense2
*
**/

int main(){

	// Create a Pipeline - this serves as a top-level API for streaming and processing frames
	rs2::pipeline p;
	rs2::config cfg;
	cfg.enable_stream(RS2_STREAM_DEPTH);
	p.start(cfg);
	//replace p.start()
	//allows capture from pre-recorded image
	//	rs2::config cfg;
	//	cfg.enable_device_from_file("/home/radicello/Downloads/stairs.bag");
	//	p.start(cfg);

	while(1){
			// Block program until frames arrive
			rs2::frameset frames = p.wait_for_frames();

			// Try to get a frame of a depth image
			rs2::depth_frame depth = frames.get_depth_frame();

			// Get the depth frame's dimensions
			float width = depth.get_width();
			float height = depth.get_height();

            //get thirds
            float div = width/4;

			// Query the distance from the camera to the object in the
			//		center of the image
			float total_pixel = width * height;
			float quadrents[16] = {0};

          // std::cout << "width=" << width << " left=" << left_div << "right=" << right_div << "\n";

            //measure Q0
			for(int i_w = 0; i_w < div; i_w++){
				for(int i_h = 0; i_h < div; i_h++){
					quadrents[0] = quadrents[0] + depth.get_distance(i_w, i_h);
				}
			}
			quadrents[0] = quadrents[0] / (total_pixel/16);

            //measure Q1
			for(int i_w = div; i_w < (div*2); i_w++){
				for(int i_h = 0; i_h < div; i_h++){
					quadrents[1] = quadrents[1] + depth.get_distance(i_w, i_h);
				}
			}
			quadrents[1] = quadrents[1] / (total_pixel/16);

            //measure Q2
			for(int i_w = (div*2); i_w < (div*3); i_w++){
				for(int i_h = 0; i_h < div; i_h++){
					quadrents[2] = quadrents[2] + depth.get_distance(i_w, i_h);
				}
			}
			quadrents[2] = quadrents[2] / (total_pixel/16);

            //measure Q3
			for(int i_w = (div*3); i_w < width; i_w++){
				for(int i_h = 0; i_h < div; i_h++){
					quadrents[3] = quadrents[3] + depth.get_distance(i_w, i_h);
				}
			}
			quadrents[3] = quadrents[3] / (total_pixel/16);

            //measure Q4
			for(int i_w = 0; i_w < div; i_w++){
				for(int i_h = div; i_h < (div*2); i_h++){
					quadrents[4] = quadrents[4] + depth.get_distance(i_w, i_h);
				}
			}
			quadrents[4] = quadrents[4] / (total_pixel/16);

            //measure Q5
			for(int i_w = div; i_w < (div*2); i_w++){
				for(int i_h = div; i_h < (div*2); i_h++){
					quadrents[5] = quadrents[5] + depth.get_distance(i_w, i_h);
				}
			}
			quadrents[5] = quadrents[5] / (total_pixel/16);

            //measure Q6
			for(int i_w = (div*2); i_w < (div*3); i_w++){
				for(int i_h = div; i_h < (div*2); i_h++){
					quadrents[6] = quadrents[6] + depth.get_distance(i_w, i_h);
				}
			}
			quadrents[6] = quadrents[6] / (total_pixel/16);

            //measure Q7
			for(int i_w = (div*3); i_w < width; i_w++){
				for(int i_h = div; i_h < (div*2); i_h++){
					quadrents[7] = quadrents[7] + depth.get_distance(i_w, i_h);
				}
			}
			quadrents[7] = quadrents[7] / (total_pixel/16);

            //measure Q8
			for(int i_w = 0; i_w < div; i_w++){
				for(int i_h = (div*2); i_h < (div*3); i_h++){
					quadrents[8] = quadrents[8] + depth.get_distance(i_w, i_h);
				}
			}
			quadrents[8] = quadrents[8] / (total_pixel/16);

            //measure Q9
			for(int i_w = div; i_w < (div*2); i_w++){
				for(int i_h = (div*2); i_h < (div*3); i_h++){
					quadrents[9] = quadrents[9] + depth.get_distance(i_w, i_h);
				}
			}
			quadrents[9] = quadrents[9] / (total_pixel/16);

            //measure Q10
			for(int i_w = (div*2); i_w < (div*3); i_w++){
				for(int i_h = (div*2); i_h < (div*3); i_h++){
					quadrents[10] = quadrents[10] + depth.get_distance(i_w, i_h);
				}
			}
			quadrents[10] = quadrents[10] / (total_pixel/16);

            //measure Q11
			for(int i_w = (div*3); i_w < width; i_w++){
				for(int i_h = (div*2); i_h < (div*3); i_h++){
					quadrents[11] = quadrents[11] + depth.get_distance(i_w, i_h);
				}
			}
			quadrents[11] = quadrents[11] / (total_pixel/16);

            //measure Q12
			for(int i_w = 0; i_w < div; i_w++){
				for(int i_h = (div*3); i_h < height; i_h++){
					quadrents[12] = quadrents[12] + depth.get_distance(i_w, i_h);
				}
			}
			quadrents[12] = quadrents[12] / (total_pixel/16);

            //measure Q13
			for(int i_w = div; i_w < (div*2); i_w++){
				for(int i_h = (div*3); i_h < height; i_h++){
					quadrents[13] = quadrents[13] + depth.get_distance(i_w, i_h);
				}
			}
			quadrents[13] = quadrents[13] / (total_pixel/16);

            //measure Q14
			for(int i_w = (div*2); i_w < (div*3); i_w++){
				for(int i_h = (div*3); i_h < height; i_h++){
					quadrents[14] = quadrents[14] + depth.get_distance(i_w, i_h);
				}
			}
			quadrents[14] = quadrents[14] / (total_pixel/16);

            //measure Q15
			for(int i_w = (div*3); i_w < width; i_w++){
				for(int i_h = (div*3); i_h < height; i_h++){
					quadrents[15] = quadrents[15] + depth.get_distance(i_w, i_h);
				}
			}
			quadrents[15] = quadrents[15] / (total_pixel/16);


            //print avg dists for sides
            //std::cout << "\rLEFT: " << avg_ldist << " MID: " << avg_mdist << " RIGHT: " << avg_rdist;
			std::cout << quadrents;

/*
			// Print if wall
			if (avg_dist <= 1){
				std::cout << "\rWALL" << avg_dist << " meters away!\n";
			}
            else{
                std::cout << "\rAvg Dist" << avg_dist << " meters\n";
            }
*/
	}
return 0;
}



