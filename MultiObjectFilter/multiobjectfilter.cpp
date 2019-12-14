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

#include "multiobjectfilter.h"
#include "multiobject.h"
#include <assert.h>
#include <iostream>

MultiObjectFilter::MultiObjectFilter() {

}

MultiObjectFilter::~MultiObjectFilter() {
    reset();
}

void MultiObjectFilter::reset() {
    QList<multiobject*> objects(_objects.values());

    while(objects.empty()==false)
        delete objects.takeFirst();

    _objects.clear();
}

void MultiObjectFilter::addObject(int camId, float confidence, const Position &pos, const Angle &ori) {
    _objects.insertMulti(confidence, new multiobject(pos, ori, camId, confidence));
}

QList<multiobject*> MultiObjectFilter::getFiltered() {
    if(_objects.size() <= 1){
        _noiseFilterTimer.update();

        if(_objects.empty() == false){
            _lastKnowPos = _objects.first()->position();
        }

        return _objects.values();
    }

    QMap<float,multiobject*> unifiedObjects = getUnifiedObjects();

    if(_lastKnowPos.isUnknown()){
        multiobject *retn = unifiedObjects.last();
        _noiseFilterTimer.update();
        return getUnification(retn);
    }
    else{
        float dist = sqrt(pow(unifiedObjects.last()->position().x() - _lastKnowPos.x(), 2) + pow(unifiedObjects.last()->position().y() - _lastKnowPos.y(), 2));
        if(dist <= MERGE_DISTANCE){
            _noiseFilterTimer.update();
            return getUnification(unifiedObjects.last());
        }
        else{
            if(_noiseFilterTimer.getTimeInMilliSeconds() >= MERGE_DISTANCE) { // accept new ball
                _noiseFilterTimer.update();
                return getUnification(unifiedObjects.last());
            } else { // keep old ball
                float minDist = 999;
                multiobject *nearestObject=NULL;
                // Get ball nearest to old position
                for(int i = 0; i < unifiedObjects.size(); i++){
                    multiobject *object = unifiedObjects.values().at(i);
                    float dist = sqrt(pow(object->position().x() - _lastKnowPos.x(), 2) + pow(object->position().y() - _lastKnowPos.y(), 2));
                    if(dist < minDist){
                        minDist = dist;
                        nearestObject = object;
                    }
                }
                return getUnification(nearestObject);
            }
        }
    }
}
QMap<float,multiobject*> MultiObjectFilter::getUnifiedObjects() {
    QMap<float, multiobject*> unifiedObjects(_objects);
    QMap<float, multiobject*>::iterator it = unifiedObjects.begin();

    for(int i = 0; i < unifiedObjects.size()-1; i++){
        multiobject *object1 = unifiedObjects.values().at(i);
        for(int j = i+1; j < unifiedObjects.size(); j++) {
            multiobject *object2 = unifiedObjects.values().at(j);
            // Discard same camera objects
            if(object1->cameraId()==object2->cameraId()){
                continue;
            }
            float dist =  sqrt(pow(object1->position().x() - object2->position().x(), 2) + pow(object1->position().y() - object2->position().y(), 2));
            if(dist <= MERGE_DISTANCE){
                unifiedObjects.erase(it+j);
                j--;
            }
        }
    }

    return unifiedObjects;
}
QList<multiobject*> MultiObjectFilter::getUnification(multiobject *object) {
    QList<multiobject*> unification(_objects.values());

    for(int i=0; i<unification.size(); i++) {
        multiobject *obj = unification.at(i);
        // Keep same
        if(obj == object){
            continue;
        }
        // Discard same camera objects
        if(object->cameraId() == obj->cameraId()) {
            unification.removeAt(i);
            i--;
            continue;
        }
        // Remove objects not nearest enough
        float dist = sqrt(pow(object->position().x() - obj->position().x(), 2) + pow(object->position().y() - obj->position().y(), 2));
        if(dist > MERGE_DISTANCE) {
            unification.removeAt(i);
            i--;
            continue;
        }
    }
    _lastKnowPos = object->position();
    return unification;
}