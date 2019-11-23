
#include "ball.h"

QString Ball::name() {

    return "Ball";

}

Ball::Ball(bool enableLossFilter, bool enableKalmanFilter, bool enableNoiseFilter, bool debugDetection) :  Object(enableLossFilter, enableKalmanFilter, enableNoiseFilter){

    _debugDetection = debugDetection;

}


Position Ball::getBallPosition(){
    if(_debugDetection){
        std::cout << "Ball set at (" << ((_position.x()>0)?" ":"") << _position.x() << ", " << ((_position.y()>0)?" ":"") << _position.y() << "), velocity=" << _velocity.abs() << ".\n";
    }
    return _position;
}

Velocity Ball::getBallVelocity(){
    if(_debugDetection){
        std::cout << "Ball set at (" << ((_position.x()>0)?" ":"") << _position.x() << ", " << ((_position.y()>0)?" ":"") << _position.y() << "), velocity=" << _velocity.abs() << ".\n";
    }
    return _velocity;
}

void Ball::updateToSensor() {

    sensor()->setBallPosition(0, _position);
    sensor()->setBallVelocity(0, _velocity);

    if(_debugDetection)
        std::cout << "Ball set at (" << ((_position.x()>0)?" ":"") << _position.x() << ", " << ((_position.y()>0)?" ":"") << _position.y() << "), velocity=" << _velocity.abs() << ".\n";
}
/* end of Ball methods */
