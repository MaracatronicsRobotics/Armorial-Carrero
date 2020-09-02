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

#ifndef FIELDTYPE_H
#define FIELDTYPE_H
#include <QString>
namespace FieldTypes {
    enum FieldType {
        VISION,
        SSL2012,
        SSL2015,
        SSL2019,
        VSS2008,
        UNDEFINED
    };
    QString toString(FieldType fieldType);
    FieldTypes::FieldType fromString(const QString &fieldTypeStr);
}
#endif // FIELDTYPE_H
