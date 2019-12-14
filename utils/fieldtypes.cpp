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

#include "fieldtypes.h"
namespace FieldTypes {
QString toString(FieldType fieldType) {
    switch(fieldType) {
        case VISION:  return "Vision data";
        case SSL2012: return "SSL 2012";
        case SSL2015: return "SSL 2015";
        case SSL2019: return "SSL 2019";
        case VSS2008: return "VSS 2008";
        default:      return "undefined";
    }
}
FieldType fromString(const QString &fieldTypeStr) {
    if(fieldTypeStr=="Vision data") return VISION;
    if(fieldTypeStr=="SSL 2012") return SSL2012;
    if(fieldTypeStr=="SSL 2015") return SSL2015;
    if(fieldTypeStr=="SSL 2019") return SSL2019;
    if(fieldTypeStr=="VSS 2008") return VSS2008;
    return UNDEFINED;
}
}