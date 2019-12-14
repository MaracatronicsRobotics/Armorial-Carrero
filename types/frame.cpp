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

#include "frame.h"

Frame::Frame(int qt_robosTime, int tempoFiltros)
{
       aux = new Robot(0, 1, 1, true, true,true,true);

        for(uint8_t x = 0; x < qt_robosTime; x++){

            _blueRobots.push_back(*aux);
            _blueRobots[x].setKalman(true);
            _blueRobots[x].setLoss(true);
            _blueRobots[x].setNoise(true);
            _blueRobots[x].setFilterTimes(tempoFiltros);
            _blueRobots[x].getPosition().setUnknown();
            _blueRobots[x].isValid = true;

            _yellowRobots.push_back(*aux);
            _yellowRobots[x].setKalman(true);
            _yellowRobots[x].setLoss(true);
            _yellowRobots[x].setNoise(true);
            _yellowRobots[x].setFilterTimes(tempoFiltros);
            _yellowRobots[x].getPosition().setUnknown();
            _yellowRobots[x].isValid = true;
    }
        _ball = new Ball();
        _ball.setKalman(true);
        _ball.setLoss(true);
        _ball.setNoise(true);
        _ball.setFilterTimes(tempoFiltros);
    this->_qt_robosTime = qt_robosTime;
    this->_tempoFiltros = tempoFiltros;
}









