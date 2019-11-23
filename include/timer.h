#ifndef TIMER_HH_
#define TIMER_HH_

#include <ctime>

class Timer {

public:
    Timer() { }

    void start() {
        clock_gettime(CLOCK_REALTIME, &time1);
    }
    void stop() {
        clock_gettime(CLOCK_REALTIME, &time2);
    }
    double timesec() {
        return timensec()/1E9;
    }
    double timemsec()    {
        return timensec()/1E6;
    }
    double timeusec()    {
        return timensec()/1E3;
    }
    double timensec()    {
        return (time2.tv_sec*1E9 + time2.tv_nsec) - (time1.tv_sec*1E9 + time1.tv_nsec);
    }
private:
    timespec time1, time2;
};

#endif // TIMER_HH_
