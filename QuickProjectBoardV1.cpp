#include <Arduino.h>
#include <ctype.h>

#include "QuickProjectBoardV1.h"

const char numbers[] = {
  0b01111110,
  0b00110000,
  0b01101101,
  0b01111001,
  0b00110011,
  0b01011011,
  0b01011111,
  0b01110000,
  0b01111111,
  0b01111011
};

const char letters[] = {
  0b01110111,
  0b00011111,
  0b01001110,
  0b00111101,
  0b01001111,
  0b01000111,
  0b01011110,
  0b00010111,
  0b00000110,
  0b00111100,
  0b01010111,//k
  0b00001110,
  0b01010100,
  0b01110110,
  0b01111110,
  0b01100111,
  0b01110011,
  0b01100110,
  0b01011101,//s
  0b00001111,
  0b00111110,
  0b00111010,
  0b00100010,
  0b00110111,//x
  0b00111011,
  0b01101001
};

void QuickProject::Init()
{
  for(char i = 2; i < 14; i++)
  {
    pinMode(i, OUTPUT);
  }
  pinMode(POT1, INPUT);
  pinMode(POT2, INPUT);
  pinMode(BUTTON1, INPUT);
  pinMode(BUTTON2, INPUT);
  this->WriteNumber(0, 0);
}

void QuickProject::WriteNumber(char number, char dot)
{
  number = number > 9 ? 9 : number;
  digitalWrite(ST_CP_DISP, LOW);

  shiftOut(SER_DISP, SH_CP_DISP, LSBFIRST, numbers[number] | (dot ? 0b10000000 : 0));
  
  digitalWrite(ST_CP_DISP, HIGH);
}

void QuickProject::WriteLetter(char letter, char dot)
{
  letter = toupper(letter);
  letter = letter < 'A' ? 'A' : letter > 'Z' ? 'Z' : letter;
  letter -= 'A';
  digitalWrite(ST_CP_DISP, LOW);

  shiftOut(SER_DISP, SH_CP_DISP, LSBFIRST, letters[letter] | (dot ? 0b10000000 : 0));
  
  digitalWrite(ST_CP_DISP, HIGH);
}
