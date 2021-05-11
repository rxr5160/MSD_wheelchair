// Code created by Sid Davis for MSD P21311

#define DEBUG 1

// pins & addresses
#define MUX     12
#define LVL_EN  11
#define DIGIPOT 0b00101100
#define X_POT   0x00
#define Y_POT   0x80

// libraries
#include <Wire.h>

// consts
#define ELECTRICAL 0
#define MECHANICAL 1
#define RAMP_DELAY 10
#define MIN_SET 50
#define MAX_SET 205

// state variables
bool mux_state = MECHANICAL;
bool lvl_enabled = false;
byte x_pos = 128;
byte y_pos = 128;
byte x_goal = 128;
byte y_goal = 128;

void setup() {
  // put your setup code here, to run once:
  pinMode(MUX, OUTPUT);
  pinMode(LVL_EN, OUTPUT);
  digitalWrite(MUX, mux_state);
  digitalWrite(LVL_EN, lvl_enabled);

  // prep comms with DigiPOT
  Wire.begin();

  // Wait for the Serial Connection
  while(!Serial);
  Serial.begin(9600);
  if (DEBUG) Serial.println("Joystick Controller in DEBUG mode. Feedback Enabled");

  // Arduino is properly powered, enable the level shifter
  toggleLvlOut();
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available()) {
    // parse command
    char cmd = Serial.read();
    switch(cmd) {
      case 'X':
      case 'x':
        Serial.print(setX());
        break;
      case 'Y':
      case 'y':
        Serial.print(setY());
        break;
      case 'M':
      case 'm':
        Serial.print(toggleMux());
        break;
      case 'O':
      case 'o':
        //Serial.print(toggleLvlOut());
        Serial.print(1);
        break;
      case '\n':
      case '\r':
      case '\t':
      case ' ':
      case ',':
        break;
      default:
        Serial.print(1);
    }
  }

  if (x_goal > x_pos) {
    x_pos++;
    digitalPotWrite(X_POT, x_pos);
    delay(RAMP_DELAY);
  } else if (x_goal < x_pos) {
    x_pos--;
    digitalPotWrite(X_POT, x_pos);
    delay(RAMP_DELAY);
  }

  if (y_goal > y_pos) {
    y_pos++;
    digitalPotWrite(Y_POT, y_pos);
    delay(RAMP_DELAY);
  } else if (y_goal < y_pos) {
    y_pos--;
    digitalPotWrite(Y_POT, y_pos);
    delay(RAMP_DELAY);
  }
}

void digitalPotWrite(int address, byte value) {
  Wire.beginTransmission(DIGIPOT);
  Wire.write(byte(address));
  Wire.write(value);
  Wire.endTransmission();
}

int setX() {
  int error = 0;
  // grab the value to set
  int input = Serial.parseInt();
//  if (!length(input)) {
//    if (DEBUG) Serial.println("No integer value found for 'SET X' cmd");
//    error = 1;
//    return error;
//  }

  // check for bounding
  if ((input > 100) || (input < -100)) {
    if (DEBUG) Serial.println("Received value for 'SET X' is out of range, but has been clipped");
    error = 1;
  }
  input = min(max(input, -100), 100);

  // map to a byte and commit
  x_goal = byte(map(input, -100, 100, MIN_SET, MAX_SET));
  if (DEBUG) {
    Serial.print("X has been set to ");
    Serial.println(x_goal);
  }
  return error;
}

int setY() {
  int error = 0;
  // grab the value to set
  int input = Serial.parseInt();
//  if (length(input) == 0) {
//    if (DEBUG) Serial.println("No integer value found for 'SET Y' cmd");
//    error = 1;
//    return error;
//  }

  // check for bounding
  if ((input > 100) || (input < -100)) {
    if (DEBUG) Serial.println("Received value for 'SET Y' is out of range, but has been clipped");
    error = 1;
  }
  input = min(max(input, -100), 100);

  // map to a byte and commit
  y_goal = byte(map(input, -100, 100, MIN_SET, MAX_SET));
  if (DEBUG) {
    Serial.print("Y has been set to ");
    Serial.println(y_goal);
  }return error;
}

int toggleMux() {
  if (mux_state == ELECTRICAL) {
    mux_state = MECHANICAL;
    digitalWrite(MUX, mux_state);
    if (DEBUG) Serial.println("Mux set to MECHANICAL");
  } else {
    mux_state = ELECTRICAL;
    digitalWrite(MUX, mux_state);
    if (DEBUG) Serial.println("Mux set to ELECTRICAL");
  }
  return 0;
}

int toggleLvlOut() {
  if (lvl_enabled == 1) {
    lvl_enabled = 0;
    digitalWrite(LVL_EN, lvl_enabled);
    if (DEBUG) Serial.println("Lvl Shft set OFF");
  } else {
    lvl_enabled = 1;
    digitalWrite(LVL_EN, lvl_enabled);
    if (DEBUG) Serial.println("Lvl Shft set ON");
  }
  return 0;
}

/* DEPRECATED
void rampX() {
  if (DEBUG) Serial.println("Starting X Ramping");
  for (byte i = 128; i < 255; i++) {
    Wire.beginTransmission(DIGIPOT);
    Wire.write(byte(X_POT));
    Wire.write(i);
    Wire.endTransmission();
    delay(50);
  }
  if (DEBUG) Serial.println("Midpoint X Ramping");
  for (byte i = 255; i > 0; i--) {
    Wire.beginTransmission(DIGIPOT);
    Wire.write(byte(X_POT));
    Wire.write(i);
    Wire.endTransmission();
    delay(50);
  }
  if (DEBUG) Serial.println("Finish X Ramping");
  for (byte i = 0; i < 128; i++) {
    Wire.beginTransmission(DIGIPOT);
    Wire.write(byte(X_POT));
    Wire.write(i);
    Wire.endTransmission();
    delay(50);
  }
  if (DEBUG) Serial.println("Done with X Ramping");  
}

void rampY() {
  if (DEBUG) Serial.println("Starting Y Ramping");
  for (byte i = 128; i < 255; i++) {
    Wire.beginTransmission(DIGIPOT);
    Wire.write(byte(Y_POT));
    Wire.write(i);
    Wire.endTransmission();
    delay(50);
  }
  if (DEBUG) Serial.println("Midpoint Y Ramping");
  for (byte i = 255; i > 0; i--) {
    Wire.beginTransmission(DIGIPOT);
    Wire.write(byte(Y_POT));
    Wire.write(i);
    Wire.endTransmission();
    delay(50);
  }
  if (DEBUG) Serial.println("Finish Y Ramping");
  for (byte i = 0; i < 128; i++) {
    Wire.beginTransmission(DIGIPOT);
    Wire.write(byte(Y_POT));
    Wire.write(i);
    Wire.endTransmission();
    delay(50);
  }
  if (DEBUG) Serial.println("Done with Y Ramping");  
}
*/
