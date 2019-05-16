/*
 * NAPS Code Club LittleBits Arduino Board motor control example. Attach motor to bottom most output
 * port on Arduino board (d9) and set output to PWM. Set motor to var.
 * 
 * Stephen Gould, 5 May 2019.
 */

const int MOTOR_PIN = 9;

void setup() {
  pinMode(MOTOR_PIN, OUTPUT);
}

void loop() {
  // forward
  digitalWrite(MOTOR_PIN, HIGH);
  delay(2000);

  // stop
  for (int i = 0; i < 500; i++) {
    digitalWrite(MOTOR_PIN, LOW);
    delay(1);
    digitalWrite(MOTOR_PIN, HIGH);
    delay(1);    
  }

   // reverse
  digitalWrite(MOTOR_PIN, LOW);
  delay(2000);  

  // stop
  for (int i = 0; i < 500; i++) {
    digitalWrite(MOTOR_PIN, LOW);
    delay(1);
    digitalWrite(MOTOR_PIN, HIGH);
    delay(1);    
  }
}
