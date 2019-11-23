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
