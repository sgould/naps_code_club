// Car Crash
//
// A game using button inputs to move a car left and right along a randomly curving road,
// with display output on the serial terminal and status outputs on LEDs.
//
// Fill in the sections marked with TODO below

const int RED = 12;
const int YELLOW = 10;
const int GREEN = 8;
const int BLUE = 6;

const int LEFT = A5;
const int RIGHT = 4;

void allLeds(int val) {
  digitalWrite(RED, val); 
  digitalWrite(YELLOW, val); 
  digitalWrite(GREEN, val); 
  digitalWrite(BLUE, val); 
}

void setup() {
  Serial.begin(9600);

  pinMode(LEFT, INPUT_PULLUP);
  pinMode(RIGHT, INPUT_PULLUP);

  pinMode(RED, OUTPUT);
  pinMode(YELLOW, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);

  allLeds(HIGH);
  delay(1000);
  allLeds(LOW);
}

void loop() {
  allLeds(LOW);
  
  Serial.println("Ready...");
  digitalWrite(RED, HIGH);
  delay(1000);
  Serial.println("Set...");
  digitalWrite(RED, LOW);
  digitalWrite(YELLOW, HIGH);
  delay(1000);
  Serial.println("GO!");
  digitalWrite(YELLOW, LOW);
  digitalWrite(GREEN, HIGH);

  int left = 30;
  int width = 20;
  int car = 40;

  while (true) {
  	// TODO If the left button is pressed, move the car left

  	// TODO If the right button is pressed, move the car left

    int r = random(100);
    if (r < 50 && left > 1) {
      left = left - 1;
    } else if (left + width < 80) {
      left = left + 1;
    }
    if (width > 5 && r < 2) {
      width -= 1;
    }

    char road[81];
    for (int x = 0; x < 80; x++) {
      road[x] = '#';
    }
    for (int x = left; x < left + width; x++) {
      road[x] = ' ';
    }
    road[left] = '|';
    road[left + width] = '|';
    road[car] = 'U';
    road[80] = 0;
    Serial.println(road);

    if (car <= left || car >= left + width) {
      allLeds(LOW);
      digitalWrite(RED, HIGH);
      Serial.println("------------------");
      Serial.println("     CRASH!!!");
      Serial.println("------------------");
      delay(3000);
      return;
    }
  }
}

