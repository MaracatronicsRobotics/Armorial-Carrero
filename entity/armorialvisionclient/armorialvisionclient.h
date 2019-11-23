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
    ArmorialVisionClient(int visionPort = 10006);
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







