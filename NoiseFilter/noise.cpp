/* noise filter methods */

#include "noise.h"
#include <stdio.h>

Noise::Noise(){
    filterTime = 300.0;
    temporizer = new MRCTimer(filterTime);
}

void Noise::setFilterTime(double time){
    filterTime = time;
    temporizer = new MRCTimer(filterTime);
}

void Noise::setOff(){
    initialized = false;
}

bool Noise::isInitialized(){
    return initialized;
}

void Noise::initCounter(){
    temporizer->update();
	this->initialized = true;
}

bool Noise::noiseFilter(){
    bool ret = temporizer->checkTimerEnd();

    if(ret){
        return true;
    }
    return false;
}

/* end of noise filter methods */
