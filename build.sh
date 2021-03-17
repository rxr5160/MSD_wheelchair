#!/bin/sh

#g++ -std=c++11 wheelchair.cpp left_right.cpp -lrealsense2
g++ -std=c++17 wheelchair.cpp left_right.cpp path_planning/DijkstraShortestPathAlg.cpp path_planning/Graph.cpp -lrealsense2


