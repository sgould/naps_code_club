/*
 * NAPS Code Club Elegoo Nano Arduino flashing LED example.
 * 
 * Stephen Gould, 5 May 2019.
 */

const int RED_PIN = 12;
const int YELLOW_PIN = 10;
const int GREEN_PIN = 7;
 
 void setup() {
  // set up LEDs as output and turn off
  pinMode(RED_PIN, OUTPUT);
  pinMode(YELLOW_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);

  digitalWrite(RED_PIN, LOW);
  digitalWrite(YELLOW_PIN, LOW);
  digitalWrite(GREEN_PIN, LOW);
}

void loop() {
  // flash red then yellow then green
  digitalWrite(RED_PIN, HIGH);
  delay(1000);
  digitalWrite(RED_PIN, LOW);

  digitalWrite(YELLOW_PIN, HIGH);
  delay(1000);
  digitalWrite(YELLOW_PIN, LOW);

  digitalWrite(GREEN_PIN, HIGH);
  delay(1000);
  digitalWrite(GREEN_PIN, LOW);
}
