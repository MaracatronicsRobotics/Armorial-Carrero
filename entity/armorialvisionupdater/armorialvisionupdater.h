#ifndef ARMORIALVISIONUPDATER_H
#define ARMORIALVISIONUPDATER_H

#include <QReadWriteLock>
#include <GEARSystem/gearsystem.hh>
#include <entity/entity.h>
#include <entity/armorialvisionclient/armorialvisionclient.h>
#include <entity/armorialvisionupdater/robottracker.h>
#include <utils/fieldareas.h>
#include <utils/color.h>
#include <types/frame.h>
#include <MultiObjectFilter/multiobjectfilter.h>

#include <Robot/robot.h>
#include <Ball/ball.h>

#include "samico.h"
#include <types/frame.h>

#define MAX_ROBOTS 6
#define FILTER_TIME 300 // ms

#define MM2METER (1/1000.0)

class ArmorialVisionUpdater:public Entity
{
public:
    ArmorialVisionUpdater(ArmorialVisionClient *ArmorialVisionClient, FieldAreas::FieldArea fieldLimit=FieldAreas::ALL, bool enableLossFilter=true, bool enableKalmanFilter=true, bool enableNoiseFilter=true, bool debugDetection=false, bool debugGeometry=false, Samico *samico = new Samico());
    ~ArmorialVisionUpdater();

    QList<Robot*> getRobotObjects() const;
    Ball* getBallObject() const;
    SSL_GeometryFieldSize getFieldGeometry() const;
    bool hasDetectionUpdates(int timeout) const;
    bool hasGeometryUpdates() const;

    void setFieldLimit(FieldAreas::FieldArea fieldLimit) { _fieldLimit = fieldLimit; }
    FieldAreas::FieldArea getfieldLimit() const { return _fieldLimit; }

    QString name();
private:
    void initialization();
    void loop();
    void finalization();

    // Internal
    ArmorialVisionClient *_ArmorialVisionClient;
    void processDetectionData(const QList<SSL_DetectionFrame> &detectionFrames);
    void processGeometryData(const SSL_GeometryData &geometryData);
    QList<std::pair<int,SSL_DetectionBall> > parseCamerasBalls(const QList<SSL_DetectionFrame> &detectionFrames) const;
    QHash<int,std::pair<int,SSL_DetectionRobot> > parseCamerasRobots(const QList<SSL_DetectionFrame> &detectionFrames) const;
    void processBalls(const QList<std::pair<int,SSL_DetectionBall> > &balls);
    void processRobots(const QHash<int, std::pair<int,SSL_DetectionRobot> > &robots);

    // Server index info
    static const quint8 _blueTeamIndex = Colors::BLUE;      // 0
    static const quint8 _yellowTeamIndex = Colors::YELLOW;  // 1

    // Robot tracker (for robots without id)
    RobotTracker _robotTracker;

    // Multi objects filtering
    QHash<int,QHash<int,MultiObjectFilter*> > _multiFilterRobots;
    MultiObjectFilter *_multiFilterBall = new MultiObjectFilter();

    // Objects (final vision objects)
    QHash<int,QHash<int,Robot*> > _objRobots; // color -> id -> robot
    Ball *_objBall;

    // Backbone connection (sensor)
    Sensor *_sensor;

    // Sync
    mutable QSemaphore _newDetectionUpdates;
    mutable QSemaphore _newGeometryUpdates;

    // Internal
    FieldAreas::FieldArea _fieldLimit;
    bool _debugDetection;
    bool _debugGeometry;

    // Samico GUI
    Samico *samico;
    Frame *frameAT = new Frame(MAX_ROBOTS, FILTER_TIME);
};

#endif // ARMORIALVISIONUPDATER_H
