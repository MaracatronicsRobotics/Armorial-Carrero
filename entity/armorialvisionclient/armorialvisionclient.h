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

#ifndef ARMORIALVISIONCLIENT_H
#define ARMORIALVISIONCLIENT_H
#include <QHash>
#include <QReadWriteLock>
#include <entity/entity.h>
#include <include/timer.h>
#include <include/3rd_party/robocup_ssl_client.h>


#define CLIENT_DISCONNECTED_TIME 500 // ms

class ArmorialVisionClient:public Entity
{
public:
    ArmorialVisionClient(int visionPort = 10006, string visionAddress = "224.5.23.2");
    ~ArmorialVisionClient();

    bool hasDetectionUpdate();
    bool hasGeometryUpdate();
    QList<SSL_DetectionFrame> getDetectionData();
    SSL_GeometryData getGeometryData();

    float fpsDetection();
    float fpsGeometry();
    int numCameras();
    int visionPort() { return _visionPort; }
    void setVisionPort(int visionPort);

    QString name();
private:
    void initialization();
    void loop();
    void finalization();

    // Vision system client (to receive camera data)
    RoboCupSSLClient *_vision;
    int _visionPort;
    string _visionAddress;
    QMutex _portMutex;

    // Camera and packets info
    QReadWriteLock _packetsMutex;
    QHash<int,SSL_DetectionFrame> _detectionPackets;
    SSL_GeometryData _geometryPacket;

    // FPS calc
    QMutex _fpsMutex;
    Timer _freqDetectionTimer;
    QList<float> _fpsDetection;
    Timer _freqGeometryTimer;
    QList<float> _fpsGeometry;
    static const int MAX_FPS_COUNT = 15;

    // Flags
    bool _hasDetectionUpdate;
    bool _hasGeometryUpdate;
};

#endif // ARMORIALVISIONCLIENT_H







