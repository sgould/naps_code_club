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

/********************************************************************************************************************
 * THE TM1637 LIBRARY HAS INCLUDED HERE FOR CODEBENDER. SCOLL DOWN TO THE BOTTOM OF THE PAGE TO IMPLEMENT YOUR CODE *
 ********************************************************************************************************************/
#if 0
#include "TM1637Display.h"
#else

#define SEG_A   0b00000001
#define SEG_B   0b00000010
#define SEG_C   0b00000100
#define SEG_D   0b00001000
#define SEG_E   0b00010000
#define SEG_F   0b00100000
#define SEG_G   0b01000000

#define DEFAULT_BIT_DELAY  100

const uint8_t DIGIT_TO_SEGMENT[] = {
 // XGFEDCBA
  0b00111111,    // 0
  0b00000110,    // 1
  0b01011011,    // 2
  0b01001111,    // 3
  0b01100110,    // 4
  0b01101101,    // 5
  0b01111101,    // 6
  0b00000111,    // 7
  0b01111111,    // 8
  0b01101111,    // 9
  0b01110111,    // A
  0b01111100,    // b
  0b00111001,    // C
  0b01011110,    // d
  0b01111001,    // E
  0b01110001     // F
};

class TM1637Display {

public:
  TM1637Display(uint8_t pinClk, uint8_t pinDIO, unsigned int bitDelay = DEFAULT_BIT_DELAY);
  void setBrightness(uint8_t brightness, bool on = true) { m_brightness = (brightness & 0x7) | (on? 0x08 : 0x00); }
  void setSegments(const uint8_t segments[], uint8_t length = 4, uint8_t pos = 0);
  void clear() { uint8_t data[] = { 0, 0, 0, 0 }; setSegments(data); }
  void showNumberDec(int num, bool leading_zero = false, uint8_t length = 4, uint8_t pos = 0) { showNumberDecEx(num, 0, leading_zero, length, pos); }
  void showNumberDecEx(int num, uint8_t dots = 0, bool leading_zero = false, uint8_t length = 4, uint8_t pos = 0) { showNumberBaseEx(num < 0? -10 : 10, num < 0? -num : num, dots, leading_zero, length, pos); }
  void showNumberHexEx(uint16_t num, uint8_t dots = 0, bool leading_zero = false, uint8_t length = 4, uint8_t pos = 0) { showNumberBaseEx(16, num, dots, leading_zero, length, pos); }
  uint8_t encodeDigit(uint8_t digit) { return DIGIT_TO_SEGMENT[digit & 0x0f]; }

protected:
   void bitDelay() { delayMicroseconds(m_bitDelay); }
   void start() { pinMode(m_pinDIO, OUTPUT); bitDelay(); }
   void stop() { pinMode(m_pinDIO, OUTPUT); bitDelay(); pinMode(m_pinClk, INPUT); bitDelay(); pinMode(m_pinDIO, INPUT); bitDelay(); }
   bool writeByte(uint8_t b);
   void showDots(uint8_t dots, uint8_t* digits);
   void showNumberBaseEx(int8_t base, uint16_t num, uint8_t dots = 0, bool leading_zero = false, uint8_t length = 4, uint8_t pos = 0);

private:
  uint8_t m_pinClk;
  uint8_t m_pinDIO;
  uint8_t m_brightness;
  unsigned int m_bitDelay;
};

#define TM1637_I2C_COMM1    0x40
#define TM1637_I2C_COMM2    0xC0
#define TM1637_I2C_COMM3    0x80

static const uint8_t minusSegments = 0b01000000;

TM1637Display::TM1637Display(uint8_t pinClk, uint8_t pinDIO, unsigned int bitDelay)
{
  // Copy the pin numbers
  m_pinClk = pinClk;
  m_pinDIO = pinDIO;
  m_bitDelay = bitDelay;

  // Set the pin direction and default value.
  // Both pins are set as inputs, allowing the pull-up resistors to pull them up
  pinMode(m_pinClk, INPUT);
  pinMode(m_pinDIO,INPUT);
  digitalWrite(m_pinClk, LOW);
  digitalWrite(m_pinDIO, LOW);
}

void TM1637Display::setSegments(const uint8_t segments[], uint8_t length, uint8_t pos)
{
    // Write COMM1
  start();
  writeByte(TM1637_I2C_COMM1);
  stop();

  // Write COMM2 + first digit address
  start();
  writeByte(TM1637_I2C_COMM2 + (pos & 0x03));

  // Write the data bytes
  for (uint8_t k=0; k < length; k++)
    writeByte(segments[k]);

  stop();

  // Write COMM3 + brightness
  start();
  writeByte(TM1637_I2C_COMM3 + (m_brightness & 0x0f));
  stop();
}

void TM1637Display::showNumberBaseEx(int8_t base, uint16_t num, uint8_t dots, bool leading_zero, uint8_t length, uint8_t pos)
{
  bool negative = false;
  if (base < 0) {
      base = -base;
    negative = true;
  }

  uint8_t digits[4];

  if (num == 0 && !leading_zero) {
    // Singular case - take care separately
    for(uint8_t i = 0; i < (length-1); i++)
      digits[i] = 0;
    digits[length-1] = encodeDigit(0);
  } else {    
    for(int i = length-1; i >= 0; --i) {
        uint8_t digit = num % base;
      
      if (digit == 0 && num == 0 && leading_zero == false)
          // Leading zero is blank
        digits[i] = 0;
      else
          digits[i] = encodeDigit(digit);
        
      if (digit == 0 && num == 0 && negative) {
          digits[i] = minusSegments;
        negative = false;
      }

      num /= base;
    }

    if (dots != 0) {
      showDots(dots, digits);
    }
    }
    setSegments(digits, length, pos);
}

bool TM1637Display::writeByte(uint8_t b)
{
  uint8_t data = b;

  // 8 Data Bits
  for(uint8_t i = 0; i < 8; i++) {
    // CLK low
    pinMode(m_pinClk, OUTPUT);
    bitDelay();

  // Set data bit
    if (data & 0x01)
      pinMode(m_pinDIO, INPUT);
    else
      pinMode(m_pinDIO, OUTPUT);

    bitDelay();

  // CLK high
    pinMode(m_pinClk, INPUT);
    bitDelay();
    data = data >> 1;
  }

  // Wait for acknowledge
  // CLK to zero
  pinMode(m_pinClk, OUTPUT);
  pinMode(m_pinDIO, INPUT);
  bitDelay();

  // CLK to high
  pinMode(m_pinClk, INPUT);
  bitDelay();
  uint8_t ack = digitalRead(m_pinDIO);
  if (ack == 0)
    pinMode(m_pinDIO, OUTPUT);


  bitDelay();
  pinMode(m_pinClk, OUTPUT);
  bitDelay();

  return ack;
}

void TM1637Display::showDots(uint8_t dots, uint8_t* digits)
{
    for(int i = 0; i < 4; ++i) {
        digits[i] |= (dots & 0x80);
        dots <<= 1;
    }
}
#endif

/********************************************************************************************************************
                                         WRITE YOUR CODE BELOW THIS COMMENT
 ********************************************************************************************************************/

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
