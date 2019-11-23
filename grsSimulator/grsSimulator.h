#include "include/3rd_party/grSim_Packet.pb.h"
#include "include/3rd_party/grSim_Commands.pb.h"
#include "include/3rd_party/grSim_Replacement.pb.h"
#include <QByteArray>
#include <QUdpSocket>

typedef struct{
    bool isYellow;
    int id;
    double v1, v2, v3, v4;
    double vx ,vy, angle;
    double kickspeedx, kickspeedz;
    bool spinner;
} grs_robot;

class grsSimulator{

public:
    grsSimulator();
    void sendPacket(grs_robot robot);
private:
    QUdpSocket udpsocket;
    QHostAddress _addr;
    quint16 _port;
};
