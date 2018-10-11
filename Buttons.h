#define BUTTON_DOWN 0
#define BUTTON_UP 1

class Button;

class ButtonEvents
{
  public:
    ButtonEvents(char buttonsCount = 20);
    void Update();
    char RegisterButton(char pin, char event, void (*cb)());
    void ClearButton(char id);
  private:
    Button *buttons;
    char buttonsCount;
};

class Button
{
  public:
    Button();
    Button(char pin);
    void Update();
    void Clear();
    char IsCleared();
    void RegisterCallback(char event, void (*cb)());
    char pin;
  private:
    void (*down)();
    void (*up)();
    char lastStatus = 0;
    char cleared;
    char defined = 0;
};
