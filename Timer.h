class Timeout;
class Interval;

class Timer
{
  public:
    Timer(char timeoutsCount = 20, char intervalsCount = 20);
    void Update();
    char SetTimeout(int time, void (*cb)());
    void CancelTimeout(char id);
    char SetInterval(int time, void (*cb)());
    void ClearInterval(char id);
  private:
    Timeout *timeouts;
    Interval *intervals;
    char timeoutsCount;
    char intervalsCount;
};

class Timeout
{
  public:
    Timeout();
    Timeout(long time, void (*cb)());
    void Update();
    char IsDone();
    void Cancel();
  private:
    long start;
    long time;
    void (*cb)();
    char done = 1;
};

class Interval
{
  public:
    Interval();
    Interval(long time, void (*cb)());
    void Clear();
    void Update();
    char IsCleared();
  private:
    long last;
    long time;
    void (*cb)();
    char cleared = 1;
};
