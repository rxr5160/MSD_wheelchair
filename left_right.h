#ifndef LEFT_RIGHT_H
#define LEFT_RIGHT_H

extern float quadrants[16];

void quadrant_distance(rs2::pipeline p);
void print_distances();
void print_marked_quadrents();
void print_direction();
int turn_direction();

#endif /* LEFT_RIGHT_H */
