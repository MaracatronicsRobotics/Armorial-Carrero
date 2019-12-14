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

#include "armorialvisionclient.h"
#include <iostream>

QString ArmorialVisionClient::name() {
    return "ArmorialVisionClient";
}

ArmorialVisionClient::ArmorialVisionClient(int visionPort) {
    _visionPort = visionPort;

    // Create RoboCupSSLClient to listen to vision packets
    _vision = new RoboCupSSLClient(_visionPort);

    // Loop time, disabled
    this->setLoopTime(0);

    _hasDetectionUpdate = false;
    _hasGeometryUpdate = false;

    _geometryPacket.Clear();
    _freqDetectionTimer.start();
}

ArmorialVisionClient::~ArmorialVisionClient() {
    delete _vision;
}

void ArmorialVisionClient::initialization() {
    _portMutex.lock();

    // Vision system connection (grSim / ssl-vision)
    if(_vision->open(true))
        std::cout << ">> ArmorialVisionClient: Listening to vision system on port " << _visionPort << ".\n";
    else {
        cout << ">> ArmorialVisionClient: [ERROR] Cannot listen to vision system on port " << _visionPort << ".\n";
        this->stopRunning();
        _portMutex.unlock();
        return;
    }

    _portMutex.unlock();
}

void ArmorialVisionClient::loop() {
    SSL_WrapperPacket packet;

    // Wait for packet
    if(_vision->receive(packet)) {

        // Check if packet contains detection data
        if(packet.has_detection()) {

            // Calc detection FPS
            _fpsMutex.lock();
            _freqDetectionTimer.stop();
            _fpsDetection.append(1000/_freqDetectionTimer.timemsec());
            if(_fpsDetection.size()>MAX_FPS_COUNT)
                _fpsDetection.takeAt(0);
            _freqDetectionTimer.start();
            _fpsMutex.unlock();

            // Get detection data
            SSL_DetectionFrame currDetection = packet.detection();

            // Store detection packet for camera
            const int currCam = currDetection.camera_id();
            _packetsMutex.lockForWrite();
            _detectionPackets.insert(currCam, currDetection);
            _packetsMutex.unlock();

            // Flag
            _hasDetectionUpdate = true;
        }

        // Check if packet contains geometry data
        if(packet.has_geometry()) {

            // Calc geometry FPS
            _fpsMutex.lock();
            _freqGeometryTimer.stop();
            _fpsGeometry.append(1000/_freqGeometryTimer.timemsec());
            if(_fpsGeometry.size()>MAX_FPS_COUNT)
                _fpsGeometry.takeAt(0);
            _freqGeometryTimer.start();
            _fpsMutex.unlock();

            // Store geometry data
            _packetsMutex.lockForWrite();
            _geometryPacket = packet.geometry();
            _packetsMutex.unlock();

            // Flag
            _hasGeometryUpdate = true;
        }
    }
}

void ArmorialVisionClient::finalization() {
    _vision->close();
}

bool ArmorialVisionClient::hasDetectionUpdate() {
    bool retn = _hasDetectionUpdate;
    _hasDetectionUpdate = false;
    return retn;
}

bool ArmorialVisionClient::hasGeometryUpdate() {
    bool retn = _hasGeometryUpdate;
    _hasGeometryUpdate = false;
    return retn;
}

QList<SSL_DetectionFrame> ArmorialVisionClient::getDetectionData() {
    _packetsMutex.lockForRead();
    QList<SSL_DetectionFrame> retn = _detectionPackets.values();
    _packetsMutex.unlock();
    return retn;
}

SSL_GeometryData ArmorialVisionClient::getGeometryData() {
    _packetsMutex.lockForRead();
    SSL_GeometryData retn = _geometryPacket;
    _packetsMutex.unlock();
    return retn;
}

void ArmorialVisionClient::setVisionPort(int visionPort) {
    _portMutex.lock();
    _visionPort = visionPort;

    // Stop thread
    this->terminate();
    this->wait();

    // Delete old
    _vision->close();
    delete _vision;
    _vision = NULL;

    // Create new
    _vision = new RoboCupSSLClient(_visionPort);

    // Restart thread
    this->start();
    _portMutex.unlock();
}

int ArmorialVisionClient::numCameras() {
    _fpsMutex.lock();

    // Check last packet reception time
    _freqDetectionTimer.stop();
    if(_freqDetectionTimer.timemsec()>CLIENT_DISCONNECTED_TIME)
        _detectionPackets.clear();

    _fpsMutex.unlock();

    return _detectionPackets.size();
}

float ArmorialVisionClient::fpsDetection() {
    float fps=0;

    _fpsMutex.lock();

    // Check last packet reception time
    _freqDetectionTimer.stop();
    if(_freqDetectionTimer.timemsec()>CLIENT_DISCONNECTED_TIME) {
        _fpsDetection.clear();
        _fpsGeometry.clear();
    }

    // Calc frequency
    int size = _fpsDetection.size();
    for(int i=0; i<size; i++)
        fps += _fpsDetection.at(i);

    _fpsMutex.unlock();

    return (size==0)? 0 : fps/size;
}

float ArmorialVisionClient::fpsGeometry() {
    float fps=0;

    _fpsMutex.lock();

    // Check last packet reception time
    _freqDetectionTimer.stop();
    if(_freqDetectionTimer.timemsec()>CLIENT_DISCONNECTED_TIME) {
        _fpsDetection.clear();
        _fpsGeometry.clear();
    }

    // Calc frequency
    int size = _fpsGeometry.size();
    for(int i=0; i<size; i++)
        fps += _fpsGeometry.at(i);

    _fpsMutex.unlock();

    return (size==0)? 0 : fps/size;
}
