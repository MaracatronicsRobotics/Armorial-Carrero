#include "armorialvisionupdater.h"

QString ArmorialVisionUpdater::name() {
    return "ArmorialVisionUpdater";
}

ArmorialVisionUpdater::ArmorialVisionUpdater(ArmorialVisionClient *ArmorialVisionClient, FieldAreas::FieldArea fieldLimit, bool enableLossFilter, bool enableKalmanFilter, bool enableNoiseFilter,  bool debugDetection, bool debugGeometry, Samico *samico) {
    _ArmorialVisionClient = ArmorialVisionClient;
    _fieldLimit = fieldLimit;
    _debugDetection = debugDetection;
    _debugGeometry = debugGeometry;

    // Create Sensor (GEARSystem)
    _sensor = new Sensor();

    // Initialize robot objects
    QHash<int,Robot*> yellowRobots;
    QHash<int,Robot*> blueRobots;
    for(int id=0; id<MAX_ROBOTS; id++) {
        Robot *yellowRobot = new Robot(Colors::YELLOW, _yellowTeamIndex, id, enableLossFilter, enableKalmanFilter, enableNoiseFilter, debugDetection);
        yellowRobot->setSensor(_sensor);
        yellowRobots.insert(id, yellowRobot);

        Robot* blueRobot = new Robot(Colors::BLUE, _blueTeamIndex, id, enableLossFilter, enableKalmanFilter, enableNoiseFilter, debugDetection);
        blueRobot->setSensor(_sensor);
        blueRobots.insert(id, blueRobot);
    }
    _objRobots.insert(Colors::YELLOW, yellowRobots);
    _objRobots.insert(Colors::BLUE, blueRobots);

    // Initialize ball object
    _objBall = new Ball(enableLossFilter, enableKalmanFilter, enableNoiseFilter, debugDetection);
    _objBall->setSensor(_sensor);

    // Initialize robot multi object filters
    QHash<int,MultiObjectFilter*> yellowRobotsFilter;
    QHash<int,MultiObjectFilter*> blueRobotsFilter;
    for(int id=0; id<MAX_ROBOTS; id++) {
        MultiObjectFilter* yellowRobotFilter = new MultiObjectFilter();
        yellowRobotsFilter.insert(id, yellowRobotFilter);
        MultiObjectFilter* blueRobotFilter = new MultiObjectFilter();
        blueRobotsFilter.insert(id, blueRobotFilter);
    }
    _multiFilterRobots.insert(Colors::YELLOW, yellowRobotsFilter);
    _multiFilterRobots.insert(Colors::BLUE, blueRobotsFilter);
    // Initialize ball multi object filtering
    _multiFilterBall = new MultiObjectFilter();

    // Frequency
    this->setLoopFrequency(60); // Hz

    // Samico GUI
    this->samico = samico;
}

ArmorialVisionUpdater::~ArmorialVisionUpdater() {
    // Sensor
    delete _sensor;

    // Robot objects
    QList<QHash<int,Robot*> > robots = _objRobots.values();
    for(int i=0; i<robots.size(); i++) {
        QList<Robot*> colorRobots = robots.at(i).values();

        for(int id=0; id<colorRobots.size(); id++)
            delete colorRobots.at(id);
    }

    // Ball object
    delete _objBall;

    // Robots multi object filtering
    QList<QHash<int,MultiObjectFilter*> > robotsFilter = _multiFilterRobots.values();
    for(int i=0; i<robotsFilter.size(); i++) {
        QList<MultiObjectFilter*> colorRobots = robotsFilter.at(i).values();
        for(int id=0; id<colorRobots.size(); id++)
            delete colorRobots.at(id);
    }
    // Ball multi object filtering
    delete _multiFilterBall;
}

QList<Robot*> ArmorialVisionUpdater::getRobotObjects() const {
    // Generate robots list
    QList<Robot*> yellowRobots = _objRobots.value(Colors::YELLOW).values();
    QList<Robot*> blueRobots = _objRobots.value(Colors::BLUE).values();

    return QList<Robot*>(yellowRobots+blueRobots);
}

Ball* ArmorialVisionUpdater::getBallObject() const {
    return _objBall;
}

SSL_GeometryFieldSize ArmorialVisionUpdater::getFieldGeometry() const {
    return _ArmorialVisionClient->getGeometryData().field();
}

bool ArmorialVisionUpdater::hasDetectionUpdates(int timeout) const {
    return _newDetectionUpdates.tryAcquire(1, timeout);
}

bool ArmorialVisionUpdater::hasGeometryUpdates() const {
    return _newGeometryUpdates.tryAcquire();
}

//************************Começo dos métodos abstratos de Entity*********************

void ArmorialVisionUpdater::initialization() {

    // WRBackbone connect (as Sensor)
    _sensor->connect("127.0.0.1", 0);
    if(_sensor->isConnected())
        cout << ">> ArmorialVision: Connected to WRBackbone.\n";
    else {
        cout << ">> ArmorialVision: [ERROR] Cannot connect to WRBackbone.\n";
        this->stopRunning();
        return;
    }

    // Sensor configuration
    _sensor->addBall(0);
    _sensor->addTeam(0, "Maracatronics");
    _sensor->addTeam(1, "Opponent");
    std::cout << ">> ArmorialVision: Teams #0 (yellow) and #1 (blue) created.\n";
    for(int i=0; i<MAX_ROBOTS; i++) {
        _sensor->addPlayer(0, i);
        _sensor->addPlayer(1, i);
        std::cout << ">> ArmorialVision: Player #" << i << " created.\n";
    }

    // Debug config
    cout.setf(ios::fixed,ios::floatfield);
    cout.precision(2);
}

void ArmorialVisionUpdater::loop() {

    // Detection data
    if(_ArmorialVisionClient->hasDetectionUpdate()) {

        // Request data to EyeClient
        QList<SSL_DetectionFrame> detectionFrames = _ArmorialVisionClient->getDetectionData();

        // Process
        processDetectionData(detectionFrames);
        
        // Release update
        if(_newDetectionUpdates.available()==0)
            _newDetectionUpdates.release();

        // UPDATE Samico
        samico->setFrame(frameAT);
    }

    // Geometry data
    if(_ArmorialVisionClient->hasGeometryUpdate()) {

        // Request data to EyeClient
        SSL_GeometryData geometryData = _ArmorialVisionClient->getGeometryData();

        // Process
        processGeometryData(geometryData);

        // Release update
        if(_newGeometryUpdates.available()==0)
            _newGeometryUpdates.release();
    }
}

void ArmorialVisionUpdater::finalization() {
    _sensor->disconnect();
}

void ArmorialVisionUpdater::processDetectionData(const QList<SSL_DetectionFrame> &detectionFrames) {

    // Parse camera data
    QList<std::pair<int,SSL_DetectionBall> > balls = parseCamerasBalls(detectionFrames);
    QHash<int,std::pair<int,SSL_DetectionRobot> > robots = parseCamerasRobots(detectionFrames);

    // Process data
    processBalls(balls);
    processRobots(robots);

    // Setting frame to samico
    //frameAT->_ball = new Ball();
    //frameAT->_blueRobots.clear();
    //frameAT->_yellowRobots.clear();

    frameAT->_qt_blue = MAX_ROBOTS;
    frameAT->_qt_yellow = MAX_ROBOTS;
    
    for(int color=Colors::YELLOW; color<=Colors::BLUE; color++) {
        for(int i = 0; i < MAX_ROBOTS; i++){
            if(color == Colors::YELLOW) frameAT->_yellowRobots[i] = (*(_objRobots.value(color).value(i)));
            else if(color == Colors::BLUE) frameAT->_blueRobots[i] = (*(_objRobots.value(color).value(i)));
        }
    }

    frameAT->_ball = *(_objBall);
 }

QList<std::pair<int,SSL_DetectionBall> > ArmorialVisionUpdater::parseCamerasBalls(const QList<SSL_DetectionFrame> &detectionFrames) const {
    QList<std::pair<int,SSL_DetectionBall> > retn;

    // Run on detection frames
    QList<SSL_DetectionFrame>::const_iterator it;
    for(it=detectionFrames.constBegin(); it!=detectionFrames.constEnd(); it++) {
        SSL_DetectionFrame frame = *it;

        // Add to retn list
        for(int i=0; i<frame.balls_size(); i++)
            retn.append(std::make_pair(frame.camera_id(), frame.balls(i)));
    }

    return retn;
}

QHash<int,std::pair<int,SSL_DetectionRobot> > ArmorialVisionUpdater::parseCamerasRobots(const QList<SSL_DetectionFrame> &detectionFrames) const {
    QHash<int,std::pair<int,SSL_DetectionRobot> > retn;

    // Run on detection frames
    QList<SSL_DetectionFrame>::const_iterator it;
    for(it=detectionFrames.constBegin(); it!=detectionFrames.constEnd(); it++) {
        SSL_DetectionFrame frame = *it;

        // Add yellow to retn list
        for(int i=0; i<frame.robots_yellow_size(); i++)
            retn.insertMulti(Colors::YELLOW, std::make_pair(frame.camera_id(), frame.robots_yellow(i)));

        // Add blue to retn list
        for(int i=0; i<frame.robots_blue_size(); i++)
            retn.insertMulti(Colors::BLUE, std::make_pair(frame.camera_id(), frame.robots_blue(i)));
    }

    return retn;
}

void ArmorialVisionUpdater::processBalls(const QList<std::pair<int,SSL_DetectionBall> > &balls) {
    // Reset multi object filtering
    _multiFilterBall->reset();
    // Add objects to multi object filtering

    QList<std::pair<int,SSL_DetectionBall> >::const_iterator it;
    for(it=balls.constBegin(); it!=balls.constEnd(); it++) {
        const int camId = it->first;
        const SSL_DetectionBall ball = it->second;

        float realX = ball.x()*MM2METER;
        float realY = ball.y()*MM2METER;
        // Field area limit
        if(FieldAreas::hasArea(_fieldLimit, FieldAreas::Q1)==false) {
            if(realX>-0.10 && realY>-0.10)
                continue;
        }
        if(FieldAreas::hasArea(_fieldLimit, FieldAreas::Q2)==false) {
            if(realX<0.10 && realY>-0.10)
                continue;
        }
        if(FieldAreas::hasArea(_fieldLimit, FieldAreas::Q3)==false) {
            if(realX<0.10 && realY<0.10)
                continue;
        }
        if(FieldAreas::hasArea(_fieldLimit, FieldAreas::Q4)==false) {
            if(realX>-0.10 && realY<0.10)
                continue;
        }
        // Confidence
        if(ball.has_confidence()==false)
            continue;
        // Add to multi robot filtering
        Position pos(ball.has_x()&&ball.has_y(), realX, realY, 0.0);
        _multiFilterBall->addObject(camId, ball.confidence(), pos);
    }

    // Get return from multi object filtering
    QList<multiobject *> multiFiltered = _multiFilterBall->getFiltered();
    // Update object
    if(multiFiltered.empty()){
        _objBall->checkFilters();
    }else{
        // Update all list
        for(int i=0; i<multiFiltered.size(); i++) {
            multiobject *object = multiFiltered.at(i);
            _objBall->update(object->confidence(), object->position(), Angle(false, 0));

        }
    }
}

void ArmorialVisionUpdater::processRobots(const QHash<int,std::pair<int,SSL_DetectionRobot> > &robots) {
    // Start tracker for unkwnown id robots
    _robotTracker.startAssociations();
    // Check both yellow and blue
    for(int color=Colors::YELLOW; color<=Colors::BLUE; color++) {
        QList<std::pair<int,SSL_DetectionRobot> > colorRobots = robots.values(color);

        // Check robots without id
        for(int i=0; i<colorRobots.size(); i++) {
            SSL_DetectionRobot &robot = colorRobots[i].second;
            if(robot.has_robot_id()==false) {
                Position robotPos(true, robot.x()*MM2METER, robot.y()*MM2METER, 0.0);
                robot.set_robot_id(_robotTracker.getId(robotPos, (Colors::Color)color));
            }
        }

        // Check all robot ids
        for(unsigned id=0; id<MAX_ROBOTS; id++) {
            // Reset multi object filtering
            _multiFilterRobots.value(color).value(id)->reset();
            // Run on colorRobots
            QList<std::pair<int,SSL_DetectionRobot> >::iterator it;
            for(it=colorRobots.begin(); it!=colorRobots.end(); it++) {
                const int camId = it->first;
                const SSL_DetectionRobot robot = it->second;

                // Discard robots with wrong id
                if(robot.robot_id()!=id)
                    continue;

                float realX = robot.x()*MM2METER;
                float realY = robot.y()*MM2METER;

                // Field area limit
                if(FieldAreas::hasArea(_fieldLimit, FieldAreas::Q1)==false) {
                    if(realX>-0.10 && realY>-0.10)
                        continue;
                }
                if(FieldAreas::hasArea(_fieldLimit, FieldAreas::Q2)==false) {
                    if(realX<0.10 && realY>-0.10)
                        continue;
                }
                if(FieldAreas::hasArea(_fieldLimit, FieldAreas::Q3)==false) {
                    if(realX<0.10 && realY<0.10)
                        continue;
                }
                if(FieldAreas::hasArea(_fieldLimit, FieldAreas::Q4)==false) {
                    if(realX>-0.10 && realY<0.10)
                        continue;
                }

                // Confidence
                if(robot.has_confidence()==false)
                    continue;
                
                // Add to multi robot filtering
                Position pos(robot.has_x()&&robot.has_y(), realX, realY, 0.0);
                Angle ori(robot.has_orientation(), robot.orientation());
                _multiFilterRobots.value(color).value(id)->addObject(camId, robot.confidence(), pos, ori);
            }
            // Get return from multi object filtering
            QList<multiobject *> multiFiltered = _multiFilterRobots.value(color).value(id)->getFiltered();
            // Update object
            if(multiFiltered.empty()){
                _objRobots.value(color).value(id)->checkFilters();
            }else{
                // Update all list
                for(int i=0; i<multiFiltered.size(); i++) {
                    multiobject *object = multiFiltered.at(i);
                    _objRobots.value(color).value(id)->update(object->confidence(), object->position(), object->orientation());
                }
            }
        }
    }

    // End tracker
    _robotTracker.endAssociations();
}

void ArmorialVisionUpdater::processGeometryData(const SSL_GeometryData &geometryData) {

    // Get field data
    const SSL_GeometryFieldSize &field = geometryData.field();

    // Calc centerRadius and areaRadius
    float centerRadius = 0.0;
    float areaRadius = 0.0;
    for(int i=0; i<field.field_arcs_size(); i++) {
        const SSL_FieldCicularArc arc = field.field_arcs(i);
        if(arc.name()=="CenterCircle") // SSL/VSS
            centerRadius = arc.radius() + arc.thickness()/2;
        if(arc.name()=="LeftFieldLeftPenaltyArc") // SSL only
            areaRadius = arc.radius() + arc.thickness()/2;
    }

    // Calc areaWidth and areaStretch
    float areaWidth = 0.0;
    float areaStretch = 0.0;
    for(int i=0; i<field.field_lines_size(); i++) {
        const SSL_FieldLineSegment line = field.field_lines(i);

        // Defense width
        if(line.name()=="RightPenaltyStretch") { // SSL/VSS
            areaWidth = field.field_length()/2 - line.p1().x() - line.thickness()/2;
            areaStretch = 2*fabs(line.p1().y());
            break;
        }
    }

    // Calc goalDepth and areaLength
    float goalDepth = field.goal_depth();
    float areaLength = areaStretch + 2*areaRadius; // SSL/VSS

    // Update to system
    _sensor->setFieldCenter(Position(true, 0.0, 0.0, 0.0));
    _sensor->setFieldTopRightCorner(Position(true, (field.field_length()/2.0)*MM2METER, (field.field_width()/2.0)*MM2METER, 0.0));
    _sensor->setFieldTopLeftCorner(Position(true, (-field.field_length()/2.0)*MM2METER, (field.field_width()/2.0)*MM2METER, 0.0));
    _sensor->setFieldBottomLeftCorner(Position(true, (-field.field_length()/2.0)*MM2METER, (-field.field_width()/2.0)*MM2METER, 0.0));
    _sensor->setFieldBottomRightCorner(Position(true, (field.field_length()/2.0)*MM2METER, (-field.field_width()/2.0)*MM2METER, 0.0));
    _sensor->setRightPenaltyMark(Position(true, (field.field_length()/2.0 - areaRadius)*MM2METER, 0.0, 0.0));
    _sensor->setLeftPenaltyMark(Position(true, (-field.field_length()/2.0 + areaRadius)*MM2METER, 0.0, 0.0));
    _sensor->setLeftGoalPosts(Position(true, (-field.field_length()/2.0)*MM2METER, (-field.goal_width()/2.0)*MM2METER, 0.0), Position(true, (-field.field_length()/2.0)*MM2METER, (field.goal_width()/2.0)*MM2METER, 0.0));
    _sensor->setRightGoalPosts(Position(true, (field.field_length()/2.0)*MM2METER, (field.goal_width()/2.0)*MM2METER, 0.0), Position(true, (field.field_length()/2.0)*MM2METER, (-field.goal_width()/2.0)*MM2METER, 0.0));
    _sensor->setFieldCenterRadius(centerRadius*MM2METER);
    _sensor->setGoalArea(areaLength*MM2METER, areaWidth*MM2METER, areaRadius*MM2METER);
    _sensor->setGoalDepth(goalDepth*MM2METER);

    if(_debugGeometry) {
        printf("[Geometry Data]\n");
        printf("Field Dimensions:\n");
        printf("  -field_length=%d (mm)\n",field.field_length());
        printf("  -field_width=%d (mm)\n",field.field_width());
        printf("  -boundary_width=%d (mm)\n",field.boundary_width());
        printf("  -goal_width=%d (mm)\n",field.goal_width());
        printf("  -goal_depth=%d (mm)\n",field.goal_depth());
    }
}
