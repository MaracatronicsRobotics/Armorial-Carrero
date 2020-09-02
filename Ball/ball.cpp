/***
 * Maracatronics Robotics
 * Federal University of Pernambuco (UFPE) at Recife
 * http://www.maracatronics.com/
 *
 * This file is part of Armorial project.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 ***/

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
