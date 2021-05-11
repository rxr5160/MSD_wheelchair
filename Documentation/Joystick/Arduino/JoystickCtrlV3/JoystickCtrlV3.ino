// control joystick using servos & potentiometers

#define DEBUG 0

// Libraries
#include <Servo.h>

// pins
#define SERVO_X 3
#define SERVO_Y 5

// consts
#define ELECTRICAL 0
#define MECHANICAL 1
#define RAMP_DELAY 10
#define MIN_SET 0
#define MAX_SET 180

// state variables
bool ctrl_state = MECHANICAL;
byte x_goal = 90;
byte y_goal = 90;
byte x_pos = 90;
byte y_pos = 90;

// servo objects
Servo servo_x;  
Servo servo_y;  

void setup() {
  // put your setup code here, to run once:

  // initialize the servos
  servo_x.attach(SERVO_X);
  servo_y.attach(SERVO_Y);
  servo_x.write(x_pos);
  servo_y.write(y_pos);
  
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
        Serial.print(setX());
        break;
      case 'Y':
      case 'y':
        Serial.print(setY());
        break;
      case 'M':
      case 'm':
//        Serial.print(toggleMux());
        Serial.print(1);
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
    servo_x.write(x_pos);
    delay(RAMP_DELAY);
  } else if (x_goal < x_pos) {
    x_pos--;
    servo_x.write(x_pos);
    delay(RAMP_DELAY);
  }

  if (y_goal > y_pos) {
    y_pos++;
    servo_y.write(y_pos);
    delay(RAMP_DELAY);
  } else if (y_goal < y_pos) {
    y_pos--;
    servo_y.write(y_pos);
    delay(RAMP_DELAY);
  }
}

int setX() {
  int error = 0;
  // grab the value to set
  int input = Serial.parseInt();

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
  }
  return error;
}
