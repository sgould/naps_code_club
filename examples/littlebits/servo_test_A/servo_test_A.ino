/*
 * NAPS Code Club motor and servo example. Connect the motor to pin 9 and the servo to pin 5. Make sure switches are set to 'analog'.
 * Set motor to 'cw' or 'ccw'. servo switch to 'turn'.
 * 
 * Marnie Shaw, 13 May 2019.
 * Stephen Gould, 30 May 2019.
 */

const int MOTOR_PIN = 9;
const int SERVO_PIN = 5;

void setup() 
{
  pinMode(MOTOR_PIN, OUTPUT);
  analogWrite(MOTOR_PIN, 0);
  pinMode(SERVO_PIN, OUTPUT);
  analogWrite(SERVO_PIN, 0);
}

void loop() {
  // 0 degrees and stop motor
  analogWrite(SERVO_PIN, 0);
  analogWrite(MOTOR_PIN, 0);
  delay(5000);

  // 45 degrees
  analogWrite(SERVO_PIN, 64);
  delay(5000);

  // 90 degrees
  analogWrite(SERVO_PIN, 128);
  delay(5000);

  // 180 degrees
  analogWrite(SERVO_PIN, 255);
  delay(5000);

  // slow speed
  analogWrite(MOTOR_PIN, 64);
  delay(5000);

  // medium speed
  analogWrite(MOTOR_PIN, 128);
  delay(5000);

  // full speed
  analogWrite(MOTOR_PIN, 255);
  delay(5000);
}
