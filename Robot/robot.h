#ifndef ROBOT_H
#define ROBOT_H


#include <types/object.h>

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

    void updateToSensor();

    int getBattery() const;
    void setBattery(int battery);
};

#endif // ROBOT_H
