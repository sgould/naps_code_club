/*
 * NAPS Code Club Week 2 starter code.
 * 
 * Stephen Gould, 17 May 2019.
 */

const int RED_PIN = 12;
const int YELLOW_PIN = 10;
const int GREEN_PIN = 8;
const int BLUE_PIN = 6;

void setup() {
  // set up LEDs as output and turn them off
  pinMode(RED_PIN, OUTPUT);
  pinMode(YELLOW_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);

  digitalWrite(RED_PIN, LOW);
  digitalWrite(YELLOW_PIN, LOW);
  digitalWrite(GREEN_PIN, LOW);
  digitalWrite(BLUE_PIN, LOW);

  // initialize serial port and wait for it to open
  Serial.begin(9600);
  while (!Serial) {
    // do nothing
  }
}

void loop() {
  // print message and wait for reply
  Serial.println("What is your name?");
  while (Serial.available() == 0) {
    // do nothing
  }

  // get the reply
  String name = Serial.readString();
  Serial.println("Hello " + name);

  // flash a light
  digitalWrite(RED_PIN, HIGH);
  delay(1000);
  digitalWrite(RED_PIN, LOW);
}
