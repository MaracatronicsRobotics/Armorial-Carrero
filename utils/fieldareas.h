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

#ifndef FIELDAREAS_H
#define FIELDAREAS_H

namespace FieldAreas {
    enum FieldArea {
        Q1 = 1,
        Q2 = 1 << 1,
        Q3 = 1 << 2,
        Q4 = 1 << 3,
        RIGHT = Q1+Q4,
        LEFT = Q2+Q3,
        TOP = Q1+Q2,
        BOTTOM = Q3+Q4,
        ALL = RIGHT+LEFT
    };

    bool hasArea(FieldArea fieldArea, FieldArea hasArea);
    FieldArea addArea(FieldArea fieldArea, FieldArea areaToAdd);
    FieldArea delArea(FieldArea fieldArea, FieldArea areaToDel);
}


#endif // FIELDAREAS_H
