#define LED1 13
#define LED2 12
#define LED3 11
#define LED4 10

#define SH_CP_DISP 9
#define SER_DISP 8
#define ST_CP_DISP 7

#define SER_MAT 6
#define SH_CP_MAT 5
#define ST_CP_MAT 4

#define SERVO 3
#define BUZZER 2

#define POT1 A0
#define POT2 A1

#define BUTTON1 A2
#define BUTTON2 A3

#include "Buttons.h"
#include "Timer.h"

extern const char numbers[];
extern const char letters[];

class QuickProject
{
  public:
    void Init();
    void WriteNumber(char number, char dot);
    void WriteLetter(char letter, char dot);
};