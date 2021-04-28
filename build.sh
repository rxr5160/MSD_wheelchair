#!/bin/sh

#g++ -std=c++11 wheelchair.cpp left_right.cpp -lrealsense2
#g++ -std=c++17 wheelchair.cpp left_right.cpp path_planning/DijkstraShortestPathAlg.cpp path_planning/Graph.cpp connection/arduino_serial.c -lrealsense2 -o wheelchair -DPDBG
g++ -std=c++17 wheelchair.cpp left_right.cpp path_planning/DijkstraShortestPathAlg.cpp path_planning/Graph.cpp path_planning/turn.cpp connection/arduino_serial.c connection/headset_server.cpp steer.cpp -lrealsense2 -lzmq -ljsoncpp -o wheelchair


