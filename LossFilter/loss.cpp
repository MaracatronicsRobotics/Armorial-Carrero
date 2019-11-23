
#include "loss.h"
#include<stdio.h>

/* loss filter methods */

Loss::Loss(){
    filterTime = 300.0;
    temporizer = new MRCTimer(filterTime);
}

void Loss::setFilterTime(double time){
    filterTime = time;
    temporizer = new MRCTimer(filterTime);
}

bool Loss::lossFilter(bool update){
    if(update){
        temporizer->update();
        return false; 
    }

    bool ret = temporizer->checkTimerEnd();

    if(ret){
        temporizer->update();
    }

    return ret;
}

/* end of loss filter methods */
