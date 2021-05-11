// Code created by Sid Davis for MSD P21311

#define DEBUG 1

// pins
#define SDA A4
#define SCL A5
#define MUX 12
#define LVL_EN 11

// consts
#define ELECTRICAL 0
#define MECHANICAL 1

// state variables
bool sda_state = false;
bool scl_state = false;
bool mux_state = false;
bool lvl_enabled = false;

void setup() {
  // put your setup code here, to run once:
  pinMode(SDA, OUTPUT);
  pinMode(SCL, OUTPUT);
  pinMode(MUX, OUTPUT);
  pinMode(LVL_EN, OUTPUT);

  digitalWrite(SDA, sda_state);
  digitalWrite(SCL, scl_state);
  digitalWrite(MUX, mux_state);
  digitalWrite(LVL_EN, lvl_enabled);

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
      case 'D':
      case 'd':
        toggleSDA();
        break;
      case 'C':
      case 'c':
        toggleSCL();
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

void toggleSDA() {
  if (sda_state == 0) {
    sda_state = 1;
    digitalWrite(SDA, sda_state);
    if (DEBUG) Serial.println("SDA set to 1");
  } else {
    sda_state = 0;
    digitalWrite(SDA, sda_state);
    if (DEBUG) Serial.println("SDA set to 0");
  }
}

void toggleSCL() {
  if (scl_state == 0) {
    scl_state = 1;
    digitalWrite(SCL, scl_state);
    if (DEBUG) Serial.println("SCL set to 1");
  } else {
    scl_state = 0;
    digitalWrite(SCL, scl_state);
    if (DEBUG) Serial.println("SCL set to 0");
  }
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
