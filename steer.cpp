/**
 * steer.cpp
 * Authored by MSD team P21311, 2021
 * steering control for once an object has been found in front fo chair
 * 
 *
**/

#define MAXTURN 100
#define MAX_FORWARD 100


// start turn based on direction from main control
// full steer.
// once side near object is clear
// base off center to steer other way until center is clear
// then continue forward

// I think our speeds will be slow enough that a gradual reduction of 
//	steering isnt really needed


//averge turns to straighten out - PID light
int last_turns[10] = {0};
int curt = 0;


// @param: 0 stright :: 1 right :: 2 left :: 3 hard right :: 4 hard left
// @return: x value for turn: 100 is max
int steer(int direction) {
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
			curt -MAXTURN;
			break;
		defualt:
			curt 0;
			break;
	} // end switch

	//quick and dirty PID
	for(int i=1; i=<10; i++){
		last_turns[i-1] = last_turns[i];
	}
	last_turns[10] = curt;
	int pid = 0;
	for(int x : last_turns) {
		pid = pid + x;
	}
	pid = pid/10;
	return pid;
}

int forward(int turn){
	//max turn = half speed
	//small turn = 3/4 speed
	if (turn > 50){
		return MAX_FORWARD/2;
	}
	else if (turn > 25) {
		return (MAX_FORWARD/4)+(MAX_FORWARD/2);
	else { //<25
		return MAX_FORWARD;
	}
}





