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

/* noise filter methods */

#include "noise.h"
#include <stdio.h>

Noise::Noise(){
    filterTime = 300.0;
    temporizer = new MRCTimer(filterTime);
}

void Noise::setFilterTime(double time){
    filterTime = time;
    temporizer = new MRCTimer(filterTime);
}

void Noise::setOff(){
    initialized = false;
}

bool Noise::isInitialized(){
    return initialized;
}

void Noise::initCounter(){
    temporizer->update();
	this->initialized = true;
}

bool Noise::noiseFilter(){
    bool ret = temporizer->checkTimerEnd();

    if(ret){
        return true;
    }
    return false;
}

/* end of noise filter methods */
