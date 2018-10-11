#include <Arduino.h>

#include "Buttons.h"

/*****ButtonEvents*****/

ButtonEvents::ButtonEvents(char buttonsCount = 20) : 
  buttonsCount(buttonsCount), buttons(new Button[buttonsCount])
{
  for(int i = 0; i < this->buttonsCount; i++)
  {
    this->buttons[i] = *(new Button());
  }
}

void ButtonEvents::Update()
{
  // buttons
  for(int i = 0; i < this->buttonsCount; i++)// add clear possibility
  {
    this->buttons[i].Update();
  }
  delay(1);// needed to avoid errors
}

char ButtonEvents::RegisterButton(char pin, char event, void(*cb)())
{
  for (int i = 0; i < this->buttonsCount; i++)
  {
    if(this->buttons[i].IsCleared() || this->buttons[i].pin == pin)
    {
      this->buttons[i] = *(new Button(pin));
      this->buttons[i].RegisterCallback(event, cb);
      return i;
    }
  }
}

void ButtonEvents::ClearButton(char id)
{
  this->buttons[id].Clear();
}

/*****Button*****/

Button::Button()
{
  this->cleared = 1;
}
Button::Button(char pin = 0) : pin(pin)
{
  this->cleared = 0;
}

void Button::Update()
{
  char stat = digitalRead(this->pin);
  if(!this->cleared)
  {
    if(stat != this->lastStatus)
    {
      if(stat)
      {
        if(this->defined & 1)
          this->down();
      }
      else
      {
        if(this->defined & 2)
          this->up();
      }
    }
  }
  this->lastStatus = stat;
}

void Button::Clear()
{
  this->cleared = 1;
}

char Button::IsCleared()
{
  return this->cleared;
}

void Button::RegisterCallback(char event, void(*cb)())
{
  switch(event)
  {
    case BUTTON_DOWN:
      this->down = cb;
      this->defined |= 1;
      break;
    case BUTTON_UP:
      this->up = cb;
      this->defined |= 2;
      break;
  }
}
