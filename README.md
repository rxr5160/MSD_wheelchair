# MSD_wheelchair
MSD-21311 project, Mind-controlled Wheelchair

<h3> (3/22) code structure of Wheelchair main </h3>
	

- set global variables
	- next node idx
	- total distnace traveled
	- distnace togo to next node
	- reset flag, boolean
- setup cameras
- get path through nodes
- set next node and distance to node -> current always nodes 0->1
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
		- send turn signals as needed
- *end loop*







Note: tracking camera MUST have a USB3.0 controller or it throws an error
Intel_ex/ contains intel example code that may have been modified for prototyping  with the cameras

NOTES
=====

left_right.cpp has object detection via quadrent averages and currently (3/15) prints a left or right direction to be sent to the controller.

In the path-planning folder, there are files for creating a node map as well as path planning that returns the shortest path.

Communication with the BCI and Arduino is being completed by Sid. Creating a library with connect and receive/send information functions. Data is expected to be JSON key/value pairs.



