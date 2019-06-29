/*
 * SCOREBOARD: NAPS Code Club starter code for Week 5. Uses the TM1637 4-digit LED display to implement a scoreboard.
 * Press the left or right buttons to increase the score. Hold a button down for more than two seconds to clear the
 * score. Also shows the score on the serial monitor.
 * 
 * https://raw.githubusercontent.com/sgould/naps_code_club/master/lessons/week5/scoreboard/scoreboard.ino
 * https://github.com/sgould/naps_code_club/wiki/Cheatsheet
 * https://edu.codebender.cc/class/.....
 * 
 * Stephen Gould, 30 June 2019.
 */

#include "TM1637Display.h"

const int CLK = 2;  // clock pin of TM1637
const int DIO = 3;  // digital i/o pin of TM1637

const int LEFT_BUTTON = A5; // left button pin
const int RIGHT_BUTTON = 4; // right button pin

TM1637Display display(CLK, DIO);
int teamA;
int teamB;

void setup() 
{
  // setup pins
  pinMode(LEFT_BUTTON, INPUT_PULLUP);
  pinMode(RIGHT_BUTTON, INPUT_PULLUP);

  // setup display
  display.setBrightness(0x0f);

  // setup serial port
  Serial.begin(9600);
  while (!Serial) {
    // do nothing
  }
  
  // initialise scores
  teamA = 0;
  teamB = 0; 
  display.showNumberDec(100 * teamA + teamB, true);
  Serial.println("Team A: " + String(teamA));
  Serial.println("Team B: " + String(teamB));
}

void loop() 
{
  // check if the left button has been pressed
  if (digitalRead(LEFT_BUTTON) == LOW) {
    // increment score for team A
    teamA = teamA + 1;
    
    // start timing in milliseconds
    int t = 0;
    while (digitalRead(LEFT_BUTTON) == LOW) {
      // wait 10ms and increment timer
      delay(10);
      t = t + 10;

      // check if held down for more than 2 seconds
      if (t > 2000) {
        // reset the score for team A and show it
        teamA = 0;
        display.showNumberDec(100 * teamA + teamB, true);
      }
    }

    // display the score
    display.showNumberDec(100 * teamA + teamB, true);
    Serial.println("Team A: " + String(teamA));
    Serial.println("Team B: " + String(teamB));
  }

  // check if the right button has been pressed
  if (digitalRead(RIGHT_BUTTON) == LOW) {
    // increment score for team B
    teamB = teamB + 1;
    
    // start timing in milliseconds
    int t = 0;
    while (digitalRead(RIGHT_BUTTON) == LOW) {
      // wait 10ms and increment timer
      delay(10);
      t = t + 10;

      // check if held down for more than 2 seconds
      if (t > 2000) {
        // reset the score for team B and show it
        teamB = 0;
        display.showNumberDec(100 * teamA + teamB, true);
      }
    }

    // display the score
    display.showNumberDec(100 * teamA + teamB, true);
    Serial.println("Team A: " + String(teamA));
    Serial.println("Team B: " + String(teamB));
  }  
}
