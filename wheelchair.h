/**
 * wheelchair.h
 * Authored by MSD team P21311, 2021
 * main to stitch pose and distance cameras, communication, and pathing
 * library includes and macros that should not be changed
 *
 * compile with::
 *
 *    g++ -std=c++11 <filename> -lrealsense2
 *      -DABS if you want raw quadrent distance
 *		-DDET if want grid of blockage
 *		-DPDBG if just print directional decision
 *	no macro define will try to send message to control to turn
 * 		-- not included as of 3/29 --
**/
#ifndef WHEELCHAIR_H
#define WHEELCHAIR_H

// distance threshold for object detection
#define THRESH 1.5
//T265 serial number for connection
#define T265_SERIAL "8122110243"

//libraried ustilized
#include <librealsense2/rs.hpp>
#include <limits>
#include <set>
#include <map>
#include <queue>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <math.h>
#include <iostream>
#include <algorithm>            // std::min, std::max
#include <signal.h>
#include <thread>
#include <chrono>
//Extension headers
#include "left_right.h"
#include "path_planning/GraphElements.h"
#include "path_planning/Graph.h"
#include "path_planning/DijkstraShortestPathAlg.h"
#include "connection/arduino_serial.h"
#include "steer.h"

#endif /* WHEELCHAIR_H */
