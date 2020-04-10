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

#ifndef ROBOT_H
#define ROBOT_H

#include <types/object.h>
#include <include/timer.h>

class Robot: public Object{

private:

    // Robot info

    quint32 _teamId;
    quint32 _robotId;
    bool _debugDetection;
    int _battery;



public:
    enum Color
    {
        YELLOW,
        BLUE
    };

    quint8 _color;

    Robot(quint8 color, quint32 teamId, quint32 robotId, bool enableLossFilter=true, bool enableKalmanFilter=true, bool enableNoiseFilter=true, bool debugDetection=true);
    virtual ~Robot();

    quint8 color() const { return _color; }
    quint32 teamId() const { return _teamId; }
    void setTeamId(quint8 team_id) { _teamId=team_id; }
    quint32 robotId() const { return _robotId; }
    void setRobotId(quint32 robot_id)  { _robotId=robot_id;}
    Velocity getRobotVelocity();

    QString name();

    // angularSpeed
    bool hasLastAngle;
    double lastAngle;
    MRCTimer *timer;

    void updateToSensor();

    int getBattery() const;
    void setBattery(int battery);
};

#endif // ROBOT_H
