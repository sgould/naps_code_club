/*
 * NAPS Code Club example of controlling a TM1637 4-digit LED display to produce a stopwatch. Make sure
 * you install the TM1637 library by Avishai Orpaz (via Sketch|Include Library|Manage Libraries...).
 * Left button starts and stops. Right button resets.
 * 
 * Stephen Gould, 25 August 2019.
 */

#include "TM1637Display.h"

const int CLK = 2;  // clock pin of TM1637
const int DIO = 3;  // digital i/o pin of TM1637

const int LEFT_BUTTON = A5; // left button pin
const int RIGHT_BUTTON = 4; // right button pin

const int RED_LED = 12;
const int YELLOW_LED = 10;
const int GREEN_LED = 8;
const int BLUE_LED = 6;

TM1637Display display(CLK, DIO);
bool startStop;
int counter;

void setup() 
{
  // setup display
  display.setBrightness(0x0f);

  // setup pins
  pinMode(LEFT_BUTTON, INPUT_PULLUP);
  pinMode(RIGHT_BUTTON, INPUT_PULLUP);
  pinMode(RED_LED, OUTPUT);
  pinMode(YELLOW_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);

  // setup display
  display.setBrightness(0x0f);

  // initialise stopwatch
  startStop = false;
  counter = 0;
  display.showNumberDecEx(counter, 0b00100000, true);

  digitalWrite(RED_LED, HIGH);
  digitalWrite(YELLOW_LED, LOW);
  digitalWrite(GREEN_LED, LOW);
  digitalWrite(BLUE_LED, LOW);  
}

void loop() 
{
  // check left button and toggle start/stop if pressed
  if (digitalRead(LEFT_BUTTON) == LOW) {
    startStop = !startStop;
    digitalWrite(RED_LED, startStop ? LOW : HIGH);
    digitalWrite(GREEN_LED, startStop ? HIGH : LOW);
    while (digitalRead(LEFT_BUTTON) == LOW) {
      delay(10);
    }
  }

  // check right button and reset if pressed
  if (digitalRead(RIGHT_BUTTON) == LOW) {
    if (!startStop) {
      counter = 0;
      display.showNumberDecEx(counter, 0b00100000, true);
    }
    digitalWrite(YELLOW_LED, HIGH);
    while (digitalRead(RIGHT_BUTTON) == LOW) {
      delay(10);
    }
    digitalWrite(YELLOW_LED, LOW);
  }

  // if running increase counter
  if (startStop) {
    counter += 1;
  }
  
  // show current counter value and delay 100ms
  display.showNumberDecEx(counter, 0b00100000, true);
  delay(80);
}
