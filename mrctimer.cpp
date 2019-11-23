#include "mrctimer.h"
#include <chrono>

MRCTimer::MRCTimer(double time){
    this->time = time;
    this->start = std::chrono::steady_clock::now();
}

void MRCTimer::update(){
    this->start = std::chrono::steady_clock::now();
}

void MRCTimer::setTime(double time){
    this->time = time;
}

bool MRCTimer::checkTimerEnd(){
    return (getTimeInMilliSeconds() > time);
}

double MRCTimer::getTimeInSeconds(){
    this->end = std::chrono::steady_clock::now();
    return std::chrono::duration_cast<std::chrono::seconds>(end - start).count();
}

double MRCTimer::getTimeInMilliSeconds(){
    this->end = std::chrono::steady_clock::now();
    return std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
}

double MRCTimer::getTimeInMicroSeconds(){
    this->end = std::chrono::steady_clock::now();
    return std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
}

double MRCTimer::getTimeInNanoSeconds(){
    this->end = std::chrono::steady_clock::now();
    return std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
}
