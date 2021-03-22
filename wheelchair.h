
/** compile with::
*
*    g++ -std=c++11 <filename> -lrealsense2
*       -DABS if you want raw quadrent distance
*		-DDET if want grid of blockage
*		-DPDBG if just print directional decision
*
**/




#ifndef WHEELCHAIR_H
#define WHEELCHAIR_H

#define THRESH 1.5
#define T265_SERIAL "8122110243"

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
#include <thread>
#include <chrono>
//Extension headers
#include "left_right.h"
#include "path_planning/GraphElements.h"
#include "path_planning/Graph.h"
#include "path_planning/DijkstraShortestPathAlg.h"

#endif /* WHEELCHAIR_H */
