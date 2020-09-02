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

#ifndef MULTIOBJECT_H
#define MULTIOBJECT_H

#include <types/object.h>

class multiobject {

public:
    multiobject(const Position &pos, const Angle &ori, int camId, float confidence);


    Position position() const { return _pos; }
    Angle orientation() const { return _ori; }
    int cameraId() const { return _camId; }
    float confidence() const { return _confidence; }

private:
    Position _pos;
    Angle _ori;
    int _camId;
    float _confidence;
};

#endif // MULTIOBJECT_H
