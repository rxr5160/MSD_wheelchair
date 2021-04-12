/**
 * arduino_serial.h
 * Authored by MSD team P21311, 2021
**/

#ifndef ARDUINO_SERIAL_H
#define ARDUINO_SERIAL_H

#include <stdbool.h>

bool Init_Arduino();
void send_arduino_cmd(int x, int y);
void cleanup_arduino();

#endif /* ARDUINO_SERIAL_H */
