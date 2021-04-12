# MSD_wheelchair
MSD-21311 project, Mind-controlled Wheelchair

wheelchair -> main</br>
left_right -> object detection</br>
steering -> steering and acceleration control</br>
path_planning/ -> contains pathing files and map graph, runs Dijkstra shortest path</br>
connection/ -> contains communcation code</br>
build.sh -> compiles system, bypass a makefile to run the command in shell</br>


<h3> code structure of Wheelchair main </h3>

- set global variables
	- next node idx
	- total distnace traveled
	- distnace togo to next node
	- reset flag, boolean
- set start and end nodes from cmd arguments
- setup cameras
- get path through nodes
- set next node and distance to node 
- *loop*
	- get dstance traveled from camera
	- check if at the node -> z distance vs. togo distance
		- adjust total distance traveled
		- set next node and distance togo
		- set reset
	- if reset
		- reset camera pose
		- clear reset
	- check depth camera
		- adjust turn and acceleration signals as needed
	- send message to chair control of forward and turn intensity
- *end loop*


NOTES
=====
Tracking camera MUST have a USB3.0 controller or it throws an error

Several macros are used in debug for object detection
- ABS, prints average distance for each quadrent
- DET, prints quadrents with marks for threshold detection in each
- PDBG, prints signal it would want to send, turn left/turn right

Steering uses a quick and dirty PID of 10 elements to smooth steering, adjust size as needed (PID_SIZE in steering.cpp)

Object detection distance can be adjusted via the THRESH macro in wheelchair.h
