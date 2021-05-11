// Code created by Sid Davis for MSD P21311

#define DEBUG 1

// pins & addresses
#define MUX 12
#define LVL_EN 11
#define DIGIPOT 0b00101100
#define X_POT 0x00
#define Y_POT 0x80

// libraries
#include <Wire.h>

// consts
#define ELECTRICAL 0
#define MECHANICAL 1

// state variables
bool mux_state = false;
bool lvl_enabled = false;

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
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available()) {
    // parse command
    char cmd = Serial.read();
    switch(cmd) {
      case 'X':
      case 'x':
        rampX();
        break;
      case 'Y':
      case 'y':
        rampY();
        break;
      case 'M':
      case 'm':
        toggleMux();
        break;
      case 'O':
      case 'o':
        toggleLvlOut();
        break;
      case '\n':
      case '\r':
      case '\t':
      case ' ':
      case ',':
        break;
    }
  }
}

//void rampX() {
//  byte buf[2];
//  buf[0] = X_POT;
//  buf[1] = 255;
//  Serial.println("Starting X Rise");
//  Wire.beginTransmission(DIGIPOT);
//  Serial.println("Transmission started");
//  Wire.write(buf, 2);
//  Serial.println("255 sent");
//  Wire.endTransmission();
//  Serial.println("Transmission Complete");
//  Serial.println("5 sec pause...");
//  delay(5000);
//  buf[1] = 0;
//  Serial.println("Starting X Fall");
//  Wire.beginTransmission(DIGIPOT);
//  Serial.println("Transmission started");
//  Wire.write(buf, 2);
//  Serial.println("0 sent");
//  Wire.endTransmission();
//  Serial.println("Transmission Complete");
//}

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
  if (DEBUG) Serial.println("Done with X Ramping");  
}

void toggleMux() {
  if (mux_state == ELECTRICAL) {
    mux_state = MECHANICAL;
    digitalWrite(MUX, mux_state);
    if (DEBUG) Serial.println("Mux set to MECHANICAL");
  } else {
    mux_state = ELECTRICAL;
    digitalWrite(MUX, mux_state);
    if (DEBUG) Serial.println("Mux set to ELECTRICAL");
  }
}

void toggleLvlOut() {
  if (lvl_enabled == 1) {
    lvl_enabled = 0;
    digitalWrite(LVL_EN, lvl_enabled);
    if (DEBUG) Serial.println("Lvl Shft set OFF");
  } else {
    lvl_enabled = 1;
    digitalWrite(LVL_EN, lvl_enabled);
    if (DEBUG) Serial.println("Lvl Shft set ON");
  }
}
