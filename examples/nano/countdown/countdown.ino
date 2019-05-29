/*
 * NAPS Code Club example of controlling a TM1637 4-digit LED display to produce a clock countdown. Make sure
 * you install the TM1637 library by Avishai Orpaz (via Sketch|Include Library|Manage Libraries...).
 * 
 * Stephen Gould, 29 May 2019.
 */

#include "TM1637Display.h"

const int CLK = 2;  // clock pin of TM1637
const int DIO = 3;  // digital i/o pin of TM1637

const uint8_t SEG_DONE[] = {
  SEG_B | SEG_C | SEG_D | SEG_E | SEG_G,           // d
  SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F,   // O
  SEG_C | SEG_E | SEG_G,                           // n
  SEG_A | SEG_D | SEG_E | SEG_F | SEG_G            // E
  };

TM1637Display display(CLK, DIO);
int counter;

void setup() 
{
  // setup display
  display.setBrightness(0x0f);

  // start counter
  counter = 60; 
}

void loop() 
{
  if (counter > 0) {
    display.showNumberDec(counter, true);
    delay(1000);
    counter -= 1;
  } else {
    display.clear();
    delay(1000);
    display.setSegments(SEG_DONE);
    delay(1000);
  }
}
