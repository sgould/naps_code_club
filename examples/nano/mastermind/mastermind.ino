/*
 * NAPS Code Club Arduino example of a mastermind game. Uses serial communication and
 * assumes that four LEDs are connected to the Arduino.
 * 
 * Stephen Gould, 15 May 2019.
 */

// pin definitions (red, yellow, green, blue)
const int LED_PINS[4] = {12, 10, 8, 6};

// global variables
int secret[4];
int guess[4];

// timer interrupt
int isr_next = 0;
ISR(TIMER2_OVF_vect) {
  for (int i = 0; i < 4; i++) {
    if ((i == isr_next) && (guess[i] == secret[i])) {
      digitalWrite(LED_PINS[i], HIGH);
    } else {
      digitalWrite(LED_PINS[i], LOW);
    }
  }
  isr_next = (isr_next + 1) % 4;
}

void setup() {
  // set up LEDs as output and turn off
  for (int i = 0; i < 4; i++) {
    pinMode(LED_PINS[i], OUTPUT);
    digitalWrite(LED_PINS[i], LOW);
  }

  // startup flash sequence
  for (int j = 0; j < 3; j++) {
    for (int i = 0; i < 4; i++) {
      digitalWrite(LED_PINS[i], HIGH);
      delay(200);
      digitalWrite(LED_PINS[i], LOW);
    }
    for (int i = 2; i > 0; i--) {
      digitalWrite(LED_PINS[i], HIGH);
      delay(200);
      digitalWrite(LED_PINS[i], LOW);
    }
  }

  // set up timer2 interrupts
  TCCR2B = (TCCR2B & B11111000) | 0x04; // ~500us
  TIMSK2 = (TIMSK2 & B11111110) | 0x01;
  
  // choose four random digits
  randomSeed(analogRead(0));
  for (int i = 0; i < 4; i++) {
    secret[i] = random(10);
    guess[i] = -1;
  }

  // initialize serial port and wait for it to open
  Serial.begin(9600);
  while (!Serial) {
    // do nothing
  }
  
  Serial.println("Welcome to NAPS Code Club Mastermind. Guess a combination of four digits (0-9):");
}

void loop() {
  // wait for serial input
  while (Serial.available() == 0) {
    // do nothing
  }
  delay(10);

  // read four digits
  char buffer[4];
  for (int i = 0; i < 4; i++) {
    buffer[i] = Serial.read();
    if (buffer[i] == '\n') {
      Serial.println("Invalid guess. You must enter four digits.");
      return;
    }
  }

  // check that we've read the whole line
  if (Serial.read() != '\n') {
    // clear buffer
    while (Serial.available() > 0) {
      Serial.read();
    }
    Serial.println("Invalid guess. You must enter four digits.");
    return;
  }

  int count = 0;
  for (int i = 0; i < 4; i++) {
    guess[i] = (int)buffer[i] - '0';
    if (guess[i] == secret[i]) {
      count += 1;
    }
  }

  Serial.println("You guessed " + String(count) + " digits correct.");
  if (count == 4) {
    Serial.println("Congratulations!");
  } else {
    Serial.println("Try again.");
  }
}
