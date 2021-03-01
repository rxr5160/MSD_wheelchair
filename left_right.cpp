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
            float left_div = width/3;
            float right_div = (width/3) + left_div;

			// Query the distance from the camera to the object in the
			//		center of the image
			float total_pixel = width * height;
			float left_dist = 0;
            float mid_dist = 0;
            float right_dist = 0;

          // std::cout << "width=" << width << " left=" << left_div << "right=" << right_div << "\n";

            //measure left
			for(int i_w = 0; i_w < left_div; i_w++){
				for(int i_h = 0; i_h < height; i_h++){
					left_dist = left_dist + depth.get_distance(i_w, i_h);
				}
			}
			float avg_ldist = left_dist / (total_pixel/3);

            //measure mid
			for(int i_w = left_div; i_w < right_div; i_w++){
				for(int i_h = 0; i_h < height; i_h++){
					mid_dist = mid_dist + depth.get_distance(i_w, i_h);
				}
			}
			float avg_mdist = mid_dist / (total_pixel/3);

            //measure right
			for(int i_w = right_div; i_w < width; i_w++){
				for(int i_h = 0; i_h < height; i_h++){
					right_dist = right_dist + depth.get_distance(i_w, i_h);
				}
			}
			float avg_rdist = right_dist / (total_pixel/3);

            //print avg dists for sides
            std::cout << "\rLEFT: " << avg_ldist << " MID: " << avg_mdist << " RIGHT: " << avg_rdist;


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



