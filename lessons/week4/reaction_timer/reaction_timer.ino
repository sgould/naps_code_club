// Reaction Timer

const int RED_PIN = 12;
const int YELLOW_PIN = 10;
const int GREEN_PIN = 8;
const int BLUE_PIN = 6;

const int BUTTON_PIN = 4;

void allLeds(int val) {
  digitalWrite(RED_PIN, val); 
  digitalWrite(YELLOW_PIN, val); 
  digitalWrite(GREEN_PIN, val); 
  digitalWrite(BLUE_PIN, val); 
}

void setup() {
  Serial.begin(9600);

  pinMode(BUTTON_PIN, INPUT_PULLUP);

  pinMode(RED_PIN, OUTPUT);
  pinMode(YELLOW_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);

  allLeds(HIGH);
  delay(1000);
  allLeds(LOW);
}

void loop() {
  int t;

  Serial.println("Hold down the red button to start a reaction test");

  // TODO: Wait for the button to be pressed

  allLeds(LOW);

  digitalWrite(YELLOW_PIN, HIGH);
  Serial.println("Starting. When the yellow LED turns off, let go of the button.");

  // TODO: t = a random number between 0 and 5000

  t = t + 2000;

  while (t > 0) {
    // TODO: Delay for 1 millisecond
    
    // TODO: Decrement t by 1
    
    // TODO: 
    // if (the button has been released) {
    //     Turn on the red LED
    //     Print "Oops! You let go too soon."
    //     return;
    // }
  }

  digitalWrite(YELLOW_PIN, LOW);

  // TODO: While the button is still pressed, increment t each millisecond 

  digitalWrite(GREEN_PIN, HIGH);
  Serial.println("Done! Your reaction time, in milliseconds:");
  Serial.println(t);
}

