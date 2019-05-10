/*
 * NAPS Code Club Guessing Game. Assumes Arduino with three LEDs wired. Change pin
 * definitions below depending on wiring. Demonstrates random number generation,
 * serial I/O, and digital output.
 * 
 * Stephen Gould, 10 May 2019.
 */

const int RED_PIN = 12;
const int YELLOW_PIN = 10;
const int GREEN_PIN = 7;

int secret_number;

void setup() {
  // set up LEDs as output and turn them off
  pinMode(RED_PIN, OUTPUT);
  pinMode(YELLOW_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);

  digitalWrite(RED_PIN, LOW);
  digitalWrite(YELLOW_PIN, LOW);
  digitalWrite(GREEN_PIN, LOW);

  // initialize serial port and wait for it to open
  Serial.begin(9600);
  while (!Serial) {
    // do nothing
  }

  // choose a random number
  randomSeed(analogRead(0));
  secret_number = random(10) + 1;
  Serial.println("Guess a number between 1 and 10.");
}

void loop() {
  // wait for serial input
  while (Serial.available() == 0) {
    // do nothing
  }

  // get the guess
  int guess = Serial.parseInt();
  // clear buffer
  while (Serial.available() > 0) {
    Serial.read();
  }

  // compare to the secret number
  if (guess > secret_number) {
    digitalWrite(RED_PIN, HIGH);
    digitalWrite(YELLOW_PIN, LOW);
    digitalWrite(GREEN_PIN, LOW);
    Serial.println(String(guess) + " is too high. Guess again.");
    Serial.flush();
  } else if (guess < secret_number) {
    digitalWrite(RED_PIN, LOW);
    digitalWrite(YELLOW_PIN, LOW);
    digitalWrite(GREEN_PIN, HIGH);    
    Serial.println(String(guess) + " is too low. Guess again.");
    Serial.flush();
  } else {
    digitalWrite(RED_PIN, LOW);
    digitalWrite(YELLOW_PIN, HIGH);
    digitalWrite(GREEN_PIN, LOW);    
    Serial.println(String(guess) + " is right!");
    Serial.flush();
    exit(0);
  }
}
