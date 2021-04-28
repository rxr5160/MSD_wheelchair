/**
 * read direction the chair must move from the list.
 * determine what direction the chair must move at current node
**/

#include <iostream>
#include <fstream>
#include <sstream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

typedef struct direct_t {
	int prev;
	int curr;
	int next;
	int dir;  //1 right, -1 left, 0 straight
} direct_t;

static direct_t* dir_list[36];

int read_directions() {
	int idx = 0;
	ifstream dir_file;
	dir_file.open("path_planning/directions",ios::in);
	if (dir_file.is_open()) {
		string line;
        string header;
		getline(dir_file, header); //burn header line
        //cout << line;
		char *c;
		char *s = (char*)malloc (12);
        //cout << s;
		while(getline(dir_file, line)) {
		    strcpy(s, line.c_str());//, sizeof(line.c_str()));
            //cout << line;
			direct_t *a = (direct_t*)malloc(sizeof(direct_t));
			c = strtok(s, " ");
            //cout << c;
			a->prev = atoi(c);
			c = strtok(NULL, " ");
            //cout << c;
			a->curr = atoi(c);
			c = strtok(NULL, " ");
			//cout << c;
            a->next = atoi(c);
			c = strtok(NULL, "\n");
			switch (*c) {
				case 'L':
					a->dir = -1;
					break;
				case 'R':
					a->dir = 1;
					break;
				case 'S':
					a->dir = 0;
					break;
				default:
					// unknown direction - shouldnt reach here
					a->dir = 2;
					break;
			} //end switch
			dir_list[idx] = a;
			idx++;
		}// end file read
		dir_file.close();
	} //end file
	else {
		return 1;
		//error
	}
	return 0; //direction list creation complete
}



int get_direction(int prev, int curr, int next) {
	for (int idx = 0; idx < 36; idx++) {
		if (dir_list[idx]->curr == curr) {
			if(dir_list[idx]->prev == prev) {
				if(dir_list[idx]->next == next) {
					return dir_list[idx]->dir;
				} //end next
			} //end prev
		} //end curr
	} //end list
	return 2; //error - unknown direction
}

//test main
/*
int main(){
	int r = read_directions();
	if (r != 0) {
		cout << "ERROR reading\n";
	}
	else {
		cout << "read success\n";
		r = get_direction(0, 1, 2);
		if (r == -1) {
			cout << "left turn\n";
		}
		else if (r == 1) {
			cout << "right turn\n";
		}
        else if(r == 0){
            cout << "straight\n";
        }
		else {
			cout << "ERROR turn\n";
		}
	}
}
*/
