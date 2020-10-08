#include <librealsense2/rs.hpp>
#include <stdio.h>
#include <iostream>

int main(){

	// Create a Pipeline - this serves as a top-level API for streaming and processing frames
	rs2::pipeline p;
	p.start();
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

			// Query the distance from the camera to the object in the 
			//		center of the image
			float total_pixel = width * height;
			float total_dist = 0;
			for(int i_w = 0; i_w < width; i_w++){
				for(int i_h = 0; i_h < height; i_h++){
					total_dist = depth.get_distance(i_w, i_h);
				}
			}
			float avg_dist = total_dist / total_pixel;

			// Print if wall
			if (avg_dist <= 1){
				std::cout << "\rWALL" << avg_dist << " meters away!";
			}
	}
return 0;
}



