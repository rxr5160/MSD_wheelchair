/* reads in directions from file and creates listing */
int read_directions();
/* given node IDs will determine turin direction for path
 * -1 = left :: 0 = forward :: 1 = right */
int get_direction(int prev, int curr, int next);

