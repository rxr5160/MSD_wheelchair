# MSD_wheelchair
MSD-21311 project, Mind-controlled Wheelchair

Note: tracking camera MUST have a USB3.0 controller or it throws an error

Intel_ex/ contains intel example code that may have been modified for prototyping  with the cameras


left_right.cpp has object detection via quadrent averages and currently (3/15) prints a left or right direction to be sent to the controller. 
The graph.cpp and traversal.cpp work together to create map and find a path to travrse it. As of 3/15 it finds a path but not the optimal path. Optimal is being worked on.



