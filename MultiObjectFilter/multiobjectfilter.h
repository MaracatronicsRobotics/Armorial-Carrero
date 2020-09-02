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

#ifndef MULTIOBJECTFILTER_H
#define MULTIOBJECTFILTER_H

#include <QMap>
#include "multiobject.h"
#include <mrctimer.h>

#define MERGE_DISTANCE 0.20f
#define THRESHOLD_TIME 500 // ms

class MultiObjectFilter{
public:
    MultiObjectFilter();
    ~MultiObjectFilter();

    void reset();
    void addObject(int camId, float confidence, const Position &pos, const Angle &ori = Angle(false, 0));
    QList<multiobject *> getFiltered();

private:
    QMap<float, multiobject *> _objects;

    Position _lastKnowPos;
    MRCTimer _noiseFilterTimer = MRCTimer(THRESHOLD_TIME);

    QMap<float, multiobject *> getUnifiedObjects();
    QList<multiobject *> getUnification(multiobject *object);
};

#endif // MULTIOBJECTFILTER_H
