// Testing DAC from PWM conversions using a RC LP filter

/*
 * Uno PWM pins:
 * 490 Hz on Pin {3, 9, 10, 11}
 * 980 Hz on Pin {5, 6}
 * 
 * Leonardo PWM pins:
 * 490 Hz on Pin {5, 6, 9, 10, 13}
 * 980 Hz on Pin {3, 11}
 */

 #define pwm_pin_490 10
 #define pwm_pin_980 11
 int pwm_val = 0;

 #define pot_pin 0
 int pot_val = 0;

void setup() {
  // set PWM freq on UNO pins 3&11 to 31372.55Hz
  TCCR2B = TCCR2B & B11111000 | B00000001;
  
  // put your setup code here, to run once:
  pinMode(pwm_pin_490, OUTPUT);
  pinMode(pwm_pin_980, OUTPUT);

  analogWrite(pwm_pin_490, 0);
  analogWrite(pwm_pin_980, 0);

//  while(!Serial);
//  Serial.begin(9600);
//  Serial.println("Hello Mr. MSD");
}

void loop() {
  // put your main code here, to run repeatedly:

  pot_val = analogRead(pot_pin);
//  Serial.print("\npot val: ");
//  Serial.println(pot_val);

  pwm_val = map(pot_val, 0, 1023, 0, 255);
//  Serial.print("PWM val: ");
//  Serial.println(pwm_val);

//  analogWrite(pwm_pin_490, pwm_val);
  analogWrite(pwm_pin_980, pwm_val);

  delay(100);
}
