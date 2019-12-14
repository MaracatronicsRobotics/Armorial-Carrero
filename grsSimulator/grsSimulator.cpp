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
