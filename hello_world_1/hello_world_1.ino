/*
 * NAPS Code Club LittleBits Arduino Board Hello World Example. Make sure
 * to open the serial communications window (Tools|Serial Monitor) after
 * uploading.
 * 
 * Stephen Gould, 4 May 2019.
 */

void setup() {
  // initialize serial port and wait for it to open
  Serial.begin(9600);
  while (!Serial) {
    // do nothing
  }

  // print message and wait for reply
  Serial.println("What is your name?");
  while (Serial.available() == 0) {
    // do nothing
  }

  // get the reply
  String name = Serial.readString();

  // print hello and goodbye
  Serial.print("Hello ");
  Serial.println(name);
  Serial.print("Goodbye ");
  Serial.println(name);
}

void loop() {
  // do nothing
}
