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

#define BUTTON_DOWN 0
#define BUTTON_UP 1

extern const char numbers[];
extern const char letters[];

class Button;
class Timeout;
class Interval;

class QuickProject
{
  public:
    QuickProject(char buttonsCount = 20);
    void Init();
    void Update();
    char RegisterButton(char pin, char event, void (*cb)());
    void ClearButton(char id);
    void WriteNumber(char number, char dot);
    void WriteLetter(char letter, char dot);
  private:
    Button *buttons;
    char buttonsCount;
};

class Timer
{
  public:
    Timer(char timeoutsCount = 20, char intervalsCount = 20);
    void Update();
    void SetTimeout(int time, void (*cb)());
    char SetInterval(int time, void (*cb)());
    void ClearInterval(char id);
  private:
    Timeout *timeouts;
    Interval *intervals;
    char timeoutsCount;
    char intervalsCount;
};

class Button
{
  public:
    Button();
    Button(char pin);
    char pin;
    void (*down)();
    void (*up)();
    char lastStatus = 0;
    char cleared = 1;
    char defined = 0;
};

class Timeout
{
  public:
    int start;
    int time;
    void (*cb)();
    char done = 1;
};

class Interval
{
  public:
    long last;
    long time;
    void (*cb)();
    char cleared = 1;
};
