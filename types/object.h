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

#ifndef OBJECT_H
#define OBJECT_H

#include <QReadWriteLock>
#include <QReadWriteLock>
#include <GEARSystem/gearsystem.hh>
#include <NoiseFilter/noise.h>
#include <LossFilter/loss.h>
#include <KalmanFilter/kalman.hpp>




class Object
{

private:
    bool enableKalman = true;
    bool enableLoss = true;
    bool enableNoise = true;
    double _confidence;

    // Thread-safe mutex
    QReadWriteLock *_mutex = new QReadWriteLock();

    // Auxiliary flags
    bool _zero;

    // Filters
    KalmanFilter2D _kalmanFilter = KalmanFilter2D();
    Noise _noiseFilter = Noise();
    Loss _lossFilter = Loss();
    Sensor *_sensor;
    virtual void updateToSensor() = 0;

    // Brute velocity calc

    //ObjectVelocity _objVel;

protected:
    Sensor* sensor() { return _sensor; }
    Position _position = Position();
    Velocity _velocity =  Velocity();
    Angle _orientation = Angle();

public:
    Object(bool enableLossFilter, bool enableKalmanFilter, bool enableNoiseFilter);
    virtual ~Object();
    void update(double confidence, Position pos, Angle ori);
    void setSensor(Sensor *sensor) { _sensor = sensor; }


    bool isValid;

    double getConfidence();
    Position getPosition();
    Velocity getVelocity();
    Angle getOrientation();
    void setFilterTimes(double time);
    void setKalman(bool enable){enableKalman = enable;}
    void setLoss(bool enable){enableLoss = enable;}
    void setNoise(bool enable){enableNoise = enable;}
    void predict();
    void setUnknown();
    bool checkNoise();
    bool checkLoss();
    double confidence();
    void checkFilters();


};

#endif // OBJECT_H
