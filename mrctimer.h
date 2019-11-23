#ifndef MRCTIMER_H
#define MRCTIMER_H
#include <ctime>
#include <ratio>
#include <chrono>

class MRCTimer
{
public:
    MRCTimer(double time);
    void update();
    bool checkTimerEnd();
    double getTimeInSeconds();
    double getTimeInMilliSeconds();
    double getTimeInMicroSeconds();
    double getTimeInNanoSeconds();
    void setTime(double time);

private:
    std::chrono::steady_clock::time_point start;
    std::chrono::steady_clock::time_point end;

    double time;

};

#endif // MRCTIMER_H
