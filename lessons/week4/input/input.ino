const int BUTTON_PIN = 4;

void setup() {
  Serial.begin(9600);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
}

void loop() {
  int x;
  x = digitalRead(BUTTON_PIN);
  Serial.println(x);
}
