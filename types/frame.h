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

#ifndef FRAME_H
#define FRAME_H

#include <vector>
#include "Ball/ball.h"
#include "Robot/robot.h"



class Frame
{
public:
    Frame(int qt_robosTime, int tempoFiltros);
    int _qt_blue;
    int _qt_yellow;
    int _qt_robosTime;
    int _tempoFiltros;
    quint32 _camera_id;
    std::vector<Robot> _blueRobots;
    std::vector<Robot> _yellowRobots;
    Ball _ball;

private:
    Robot *aux;

};

#endif // FRAME_H
