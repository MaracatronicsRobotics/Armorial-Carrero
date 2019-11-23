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









