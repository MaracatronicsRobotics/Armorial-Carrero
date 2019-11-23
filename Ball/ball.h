#ifndef BALL_H
#define BALL_H


#include <types/object.h>


class Ball : public Object {

private:

    bool _debugDetection;

public:

    Ball(bool enableLossFilter=true, bool enableKalmanFilter=true, bool enableNoiseFilter=true, bool debugDetection=false);

    QString name();

    Position getBallPosition();
    Velocity getBallVelocity();
    void updateToSensor();


};


#endif
