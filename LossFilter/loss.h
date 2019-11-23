#ifndef LOSS_H
#define LOSS_H
#include <mrctimer.h>

class Loss{
    public:
        Loss();
        bool lossFilter(bool update);
        void setFilterTime(double time);
    private:
        MRCTimer *temporizer;
        double filterTime = 300.0;
};
#endif
