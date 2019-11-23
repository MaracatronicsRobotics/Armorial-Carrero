#include "grsSimulator.h"

grsSimulator::grsSimulator()
{
    _addr.setAddress("127.0.0.1");
    _port = 20011;
}

void grsSimulator::sendPacket(grs_robot robot){
    grSim_Packet packet;
    packet.mutable_commands()->set_isteamyellow(robot.isYellow);
    packet.mutable_commands()->set_timestamp(0.0);

    grSim_Robot_Command *command = packet.mutable_commands()->add_robot_commands();

    command->set_id(robot.id);

    command->set_wheelsspeed(false);
    command->set_wheel1(robot.v1);
    command->set_wheel2(robot.v2);
    command->set_wheel3(robot.v3);
    command->set_wheel4(robot.v4);

    command->set_veltangent(robot.vx);
    command->set_velnormal(robot.vy);
    command->set_velangular(robot.angle);

    command->set_kickspeedx(robot.kickspeedx);
    command->set_kickspeedz(robot.kickspeedz);
    command->set_spinner(robot.spinner);

    QByteArray dgram;
    dgram.resize(packet.ByteSize());
    packet.SerializeToArray(dgram.data(), dgram.size());
    udpsocket.writeDatagram(dgram, _addr, _port);
}
