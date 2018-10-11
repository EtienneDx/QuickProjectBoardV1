#include <Arduino.h>

#include "Timer.h"

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

void Timer::Update()
{
  // timeouts
  for (int i = 0; i < this->timeoutsCount; i++)
  {
    this->timeouts[i].Update();
  }
  // intervals
  for (int i = 0; i < this->intervalsCount; i++)
  {
    this->intervals[i].Update();
  }
}

void Timer::SetTimeout(int time, void (*cb)())
{
  for (int i = 0; i < this->timeoutsCount; i++)
  {
    if(this->timeouts[i].IsDone())
    {
      this->timeouts[i] = *(new Timeout(time, cb));
      return;
    }
  }
}

char Timer::SetInterval(int time, void (*cb)())
{
  for (int i = 0; i < this->intervalsCount; i++)
  {
    if(this->intervals[i].IsCleared())
    {
      this->intervals[i] = *(new Interval(time, cb));
      return i;
    }
  }
}

void Timer::ClearInterval(char id)
{
  this->intervals[id].Clear();
}

/****Timeout****/

Timeout::Timeout()
{
  this->done = 1;
}

Timeout::Timeout(long time, void (*cb)()) : time(time), cb(cb)
{
  this->start = millis();
}

void Timeout::Update()
{
  if(!this->done)
  {
    if(this->start + this->time < millis())
    {
      this->cb();
      this->done = 1;
    }
  }
}

char Timeout::IsDone()
{
  return this->done;
}

/****Interval****/

Interval::Interval()
{
  this->cleared = 1;
}

Interval::Interval(long time, void (*cb)()) : time(time), cb(cb)
{
  this->last = millis();
  this->cleared = 0;
}

void Interval::Update()
{
  if(!this->cleared)
  {
    if(this->last + this->time < millis())
    {
      this->cb();
      while(this->last + this->time < millis())// we don't want to call the cb multiple times if we missed once
      {
        // make sure to be as precise as possible, to keep it steady overtime
        this->last = this->last + this->time;
      }
    }
  }
}

void Interval::Clear()
{
  this->cleared = 1;
}

char Interval::IsCleared()
{
  return this->cleared;
}
