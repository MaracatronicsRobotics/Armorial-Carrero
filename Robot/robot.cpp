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

#include "robot.h"

/* Robot methods */

int Robot::getBattery() const
{
    return _battery;
}

void Robot::setBattery(int battery)
{
    _battery = battery;
}

Robot::Robot(quint8 color, quint32 teamId, quint32 robotId, bool enableLossFilter, bool enableKalmanFilter, bool enableNoiseFilter, bool debugDetection) :  Object(enableLossFilter, enableKalmanFilter, enableNoiseFilter)
{

    _color = color;
    _teamId = teamId;
    _robotId = robotId;
    _debugDetection = debugDetection;

}

QString Robot::name() {

    QString ss;

    ss = QString(_color==0?"Blue":"Yellow") + " robot, id #" + QString::number(_robotId);

    return QString(ss);

}



void Robot::updateToSensor() {

    sensor()->setPlayerPosition(_teamId, _robotId, _position);

    sensor()->setPlayerVelocity(_teamId, _robotId, _velocity);

    sensor()->setPlayerOrientation(_teamId, _robotId, _orientation);

    if(_debugDetection)

        std::cout << name().toStdString() << ", set at (" << ((_position.x()>0)?" ":"") << _position.x() << ", " << ((_position.y()>0)?" ":"") << _position.y() << "), velocity=" << _velocity.abs() << ", angle=" << GEARSystem::Angle::toDegrees(_orientation.value()) << ".\n";

}

Robot::~Robot() {
    _color = 0;
    _teamId = 0;
    _robotId = 0;
}

/* end of Robot methods */
