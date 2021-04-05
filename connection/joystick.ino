// Communicate with DigiPOT over SPI
#define DEBUG 1

#define CLK_PIN  13
#define MISO_PIN 12
#define MOSI_PIN 11
#define SS_PIN   10
#define SHDN_PIN 9

#define EN_MUX_PIN 4
#define S_MUX_PIN 3

const int MECHANICAL = 0;
const int ELECTRICAL = 1;
int mux_state = 0;

const int XPOT = 0;
const int YPOT = 1;
int x_pos = 127;
int y_pos = 127;

void digitalPotWrite(int address, int value);
void SPI_transfer(int value, int bits);

void setup() {
  while(!Serial);
  Serial.begin(9600);

  if (DEBUG) Serial.println("Joystick Controller in DEBUG mode. Feedback Enabled");

  // put your setup code here, to run once:
  pinMode(S_MUX_PIN, OUTPUT);
  pinMode(EN_MUX_PIN, OUTPUT);
  pinMode(CLK_PIN, OUTPUT);
  pinMode(MISO_PIN, INPUT);
  pinMode(MOSI_PIN, OUTPUT);
  pinMode(SS_PIN, OUTPUT);
  pinMode(SHDN_PIN, OUTPUT);

  // Mux
  digitalWrite(EN_MUX_PIN, LOW); // enable mux
  digitalWrite(S_MUX_PIN, mux_state);
  // DigiPOT
  digitalWrite(SHDN_PIN, HIGH);

  digitalPotWrite(XPOT, x_pos);
  digitalPotWrite(YPOT, y_pos);

}

void loop() {
  if (Serial.available()) {
    // parse command
    char cmd = Serial.read();
    switch(cmd) {
      case 'X':
      case 'x':
        setX();
        Serial.print('0');
        break;
      case 'Y':
      case 'y':
        setY();
        Serial.print('0');
        break;
      case 'M':
      case 'm':
        toggleMux();
        Serial.print('1');
        break;
      case '\n':
      case '\r':
      case '\t':
      case ' ':
      case ',':
        break;
      default:
        Serial.print('1');
    }
  }
}

void setX() {
  // get Y value
  int input = Serial.parseInt();
  if (DEBUG) {
    Serial.print("Value received: ");
    Serial.println(input);
  }
  // force within bounds
  input = min(max(input, -100), 100);
  if (DEBUG) {
    Serial.print("After Bounding: ");
    Serial.println(input);
  }
  // map [-100, 100] to [0, 255]
  x_pos = map(input, -100, 100, 0, 255);
  if (DEBUG) {
    Serial.print("Mapped Position: ");
    Serial.println(x_pos);
  }
  // commit the value
  digitalPotWrite(XPOT, x_pos);
  if (DEBUG) {
    Serial.print("The X rail has been set to position ");
    Serial.println(x_pos);
  }
}

void setY() {
  // get Y value
  int input = Serial.parseInt();
  if (DEBUG) {
    Serial.print("Value received: ");
    Serial.println(input);
  }
  // force within bounds
  input = min(max(input, -100), 100);
  if (DEBUG) {
    Serial.print("After Bounding: ");
    Serial.println(input);
  }
  // map [-100, 100] to [0, 255]
  y_pos = map(input, -100, 100, 0, 255);
  if (DEBUG) {
    Serial.print("Mapped Position: ");
    Serial.println(y_pos);
  }
  // commit the value
  digitalPotWrite(YPOT, y_pos);
  if (DEBUG) {
    Serial.print("The Y rail has been set to position ");
    Serial.println(y_pos);
  }
}

void toggleMux() {
  if (mux_state == ELECTRICAL) {
    mux_state = MECHANICAL;
    digitalWrite(S_MUX_PIN, MECHANICAL);
    if (DEBUG) Serial.println("Mux Switch set to MECHANICAL");
  } else {
    mux_state = ELECTRICAL;
    digitalWrite(S_MUX_PIN, ELECTRICAL);
    if (DEBUG) Serial.println("Mux Switch set to ELECTRICAL");
  }
}

void digitalPotWrite(int address, int value) {
  digitalWrite(SS_PIN, LOW);
  delay(1);

  SPI_transfer(address, 2);
  SPI_transfer(value, 8);
  delay(1);

  digitalWrite(SS_PIN, HIGH);
}

void SPI_transfer(int value, int bits) {
  const int FREQ = 20; //kHz
  float T = 1/FREQ * 1000.0;
  int quarter_delay = round(T/4);
  for (int i = bits - 1; i >= 0; i--) {
    bool tx_bit = bitRead(value, i);
    digitalWrite(MOSI_PIN, tx_bit);
    delayMicroseconds(quarter_delay);
    digitalWrite(CLK_PIN, HIGH);
    delayMicroseconds(2 * quarter_delay);
    digitalWrite(CLK_PIN, LOW);
    delayMicroseconds(quarter_delay);
  }
}
