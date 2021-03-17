#include <librealsense2/rs.hpp>
#include <stdio.h>
#include <math.h>
#include <iostream>
#include <algorithm>            // std::min, std::max
#include <thread>
#include <chrono>

#include "wheelchair.h"

/** compile with::
*
*    g++ -std=c++11 <filename> -lrealsense2
*       -DABS if you want raw quadrent distance
*		-DDET if want grid of blockage
*
**/

float quadrents[16] = {0};

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

void print_pose(auto pose_data){

    std::cout << "\r" << "Device Position: " << pose_data.translation.x << " : " << pose_data.translation.y << " : " << pose_data.translation.z << " (meters)\n\n";

}
