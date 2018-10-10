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

QuickProject::QuickProject(char buttonsCount = 20) : 
  buttonsCount(buttonsCount), buttons(new Button[buttonsCount])
{}

Timer::Timer(char timeoutsCount = 20, char intervalsCount = 20) : 
  timeoutsCount(timeoutsCount), intervalsCount(intervalsCount), timeouts(new Timeout[timeoutsCount]), intervals(new Interval[intervalsCount])
{
  for(int i = 0; i < this->timeoutsCount; i++)
  {
    this->timeouts[i] = *(new Timeout());
  }

  for(int i = 0; i < this->intervalsCount; i++)
  {
    this->intervals[i] = *(new Interval());
  }
}

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

  for(int i = 0; i < this->buttonsCount; i++)
  {
    this->buttons[i] = *(new Button());
  }
}

void QuickProject::Update()
{
  // buttons
  char stat;
  for(int i = 0; i < this->buttonsCount; i++)// add clear possibility
  {
    if(!this->buttons[i].cleared)
    {
      stat = digitalRead(this->buttons[i].pin);
      if(stat != this->buttons[i].lastStatus)
      {
        if(stat)
        {
          if(this->buttons[i].defined & 1)
            this->buttons[i].down();
        }
        else
        {
          if(this->buttons[i].defined & 2)
            this->buttons[i].up();
        }
      }
    }
    this->buttons[i].lastStatus = stat;
  }
  delay(1);
}

void Timer::Update()
{
  // timeouts
  for (int i = 0; i < this->timeoutsCount; i++)
  {
    if(!this->timeouts[i].done)
    {
      if(this->timeouts[i].start + this->timeouts[i].time < millis())
      {
        this->timeouts[i].cb();
        this->timeouts[i].done = 1;
      }
    }
  }
  // intervals
  for (int i = 0; i < this->intervalsCount; i++)
  {
    if(!this->intervals[i].cleared)
    {
      Serial.println(i);
      if(this->intervals[i].last + this->intervals[i].time < millis())
      {
        this->intervals[i].cb();
        // make sure to be as precise as possible, to keep it steady overtime
        this->intervals[i].last = this->intervals[i].last + this->intervals[i].time;
      }
    }
  }
}

char QuickProject::RegisterButton(char pin, char event, void(*cb)())
{
  for (int i = 0; i < this->buttonsCount; i++)
  {
    if(this->buttons[i].cleared || this->buttons[i].pin == pin)
    {
      this->buttons[i] = *(new Button(pin));
      this->buttons[i].cleared = 0;
      switch(event)
      {
        case BUTTON_DOWN:
          this->buttons[i].down = cb;
          this->buttons[i].defined |= 1;
          break;
        case BUTTON_UP:
          this->buttons[i].up = cb;
          this->buttons[i].defined |= 2;
          break;
      }
      return i;
    }
  }
}

void QuickProject::ClearButton(char id)
{
  this->buttons[id].cleared = 1;
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

void Timer::SetTimeout(int time, void (*cb)())
{
  for (int i = 0; i < this->timeoutsCount; i++)
  {
    if(this->timeouts[i].done)
    {
      this->timeouts[i].start = millis();
      this->timeouts[i].time = time;
      this->timeouts[i].cb = cb;
      this->timeouts[i].done = 0;
      return;
    }
  }
}

char Timer::SetInterval(int time, void (*cb)())
{
  for (int i = 0; i < this->intervalsCount; i++)
  {
    if(this->intervals[i].cleared)
    {
      this->intervals[i].last = millis();
      this->intervals[i].time = time;
      this->intervals[i].cb = cb;
      this->intervals[i].cleared = 0;
      return i;
    }
  }
}

void Timer::ClearInterval(char id)
{
  this->intervals[id].cleared = 1;
}

Button::Button(){}
Button::Button(char pin = 0) : pin(pin){}
