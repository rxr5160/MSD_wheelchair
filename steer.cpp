/**
 * steer.cpp
 * Authored by MSD team P21311, 2021
 * steering control for once an object has been found in front fo chair
 *
 *
**/

// ** Thoughts on including float/math/floor functions **
//using floor function to get to 0 steering rather than possibly get stuck at 1
// might not be needed because of int injection
//	if bunch of zeros are injected becuase it's clear in front it would be fine
//	0, 50, or 100 values -> would not be an issue
//	will leave for saftey
//#include <cmath>
//#include <ctgmath>

#include <iostream>

#define MAXTURN 100
#define MAX_FORWARD 100
#define PID_SIZE 25


// start turn based on direction from main control
// full steer.
// once side near object is clear
// base off center to steer other way until center is clear
// then continue forward

// I think our speeds will be slow enough that a gradual reduction of
//	steering isnt really needed

//averge turns to straighten out - PID light
static int last_turns[PID_SIZE] = {0};

// @param: 0 stright :: 1 right :: 2 left :: 3 hard right :: 4 hard left
// @return: x value for turn: 100 is max
int steer(int direction) {
	int curt = 0;
	switch (direction) {
		case 0:
			// no turn bias
			// zero x in control
			curt = 0;
			break;
		case 1:
			// slight right
			curt = MAXTURN/2;
			break;
		case 2:
			// slight left
			curt = -MAXTURN/2;
			break;
		case 3:
			// hard right
			curt = MAXTURN;
			break;
		case 4:
			// hard left
			curt = -MAXTURN;
			break;
		defualt:
			curt = 0;
			break;
	} // end switch

    //return curt;

	//quick and dirty PID
	// 10 element shift register and average
	//shift left
	for(int i=1; i<(PID_SIZE); i++){
		last_turns[i-1] = last_turns[i];
	}
	//assign last element
	last_turns[PID_SIZE-1] = curt;
	//average and get pid value
	int pid = 0;
	for(int x : last_turns) {
        //std::cout << x << "\n";
		pid = pid + x;
	}
    //std::cout << pid << "\n";
	pid = pid/PID_SIZE;
	return pid;
}

int forward(int turn){
	//max turn = half speed
	//small turn = 3/4 speed
	if (abs(turn) > 50){
		//half speed
		return MAX_FORWARD/2;
	}
	else if (abs(turn) > 25) {
		//3/4 speed
		return (MAX_FORWARD * (3.0/4));
    }
	else { //<25
		//full speed
		return MAX_FORWARD;
	}
}





