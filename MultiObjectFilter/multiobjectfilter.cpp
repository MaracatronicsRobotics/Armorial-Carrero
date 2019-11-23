#include "multiobjectfilter.h"
#include <assert.h>
#include <iostream>

MultiObjectFilter::MultiObjectFilter(){

}

MultiObjectFilter::~MultiObjectFilter(){
    reset();
}

void MultiObjectFilter::reset(){
    QList<multiobject *> objects(_objects.values());

    while(objects.empty() == false){
        delete objects.takeFirst();
    }

    _objects.clear();
}

void MultiObjectFilter::addObject(int camId, float confidence, const Position &pos, const Angle &ori){
    _objects.insertMulti(confidence, new multiobject(pos, ori, camId, confidence));
}

QList<multiobject *> MultiObjectFilter::getFiltered(){
    if(_objects.size() <= 1){
        _noiseFilterTimer.update();
        if(_objects.empty() == false){
            _lastKnowPos = _objects.first()->position();
        }
        return _objects.values();
    }

    QMap<float, multiobject *> unifiedObjects = getUnifiedObjects();

    // checando last position
    if(_lastKnowPos.isUnknown()){
        multiobject *retn = unifiedObjects.last();

        _noiseFilterTimer.update();
        return getUnification(retn);
    }else{
        float dist = sqrt(pow((_lastKnowPos.x() - unifiedObjects.last()->position().x()), 2) + pow((_lastKnowPos.y() - unifiedObjects.last()->position().y()), 2));
        if(dist <= MERGE_DISTANCE){
            _noiseFilterTimer.update();
            return getUnification(unifiedObjects.last());
        }else{
            if(_noiseFilterTimer.getTimeInMilliSeconds() >= THRESHOLD_TIME){
                _noiseFilterTimer.update();
                return getUnification(unifiedObjects.last());
            }else{
                float minDist = 999;
                multiobject *nearestObject = NULL;

                for(int i = 0; i < unifiedObjects.size(); i++){
                    multiobject *object = unifiedObjects.values().at(i);

                    float dist2 = sqrt(pow((_lastKnowPos.x() - object->position().x()), 2) + pow((_lastKnowPos.y() - object->position().y()), 2));
                    if(dist2 < minDist){
                        minDist = dist;
                        nearestObject = object;
                    }
                }

                return getUnification(nearestObject);
            }
        }
    }
}

QMap<float, multiobject *> MultiObjectFilter::getUnifiedObjects(){
    QMap<float, multiobject *> unifiedObjects(_objects);

    QMap<float, multiobject *>::iterator it = unifiedObjects.begin();

    for(int i = 0; i < unifiedObjects.size() - 1; i++){
        multiobject *object1 = unifiedObjects.values().at(i);

        for(int j = i + 1; j < unifiedObjects.size(); j++){
            multiobject *object2 = unifiedObjects.values().at(j);

            if(object1->cameraId() == object2->cameraId()){
                continue;
            }

            float dist = sqrt(pow((object1->position().x() - object2->position().x()), 2) + pow((object1->position().y() - object2->position().y()), 2));
            if(dist <= MERGE_DISTANCE){
                unifiedObjects.erase(it + j);
                j--;
            }
        }
    }

    return unifiedObjects;
}

QList<multiobject *> MultiObjectFilter::getUnification(multiobject *object){
    QList<multiobject *> unification(_objects.values());

    for(int i = 0; i < unification.size(); i++){
        multiobject *obj = unification.at(i);

        if(obj == object){
            continue;
        }

        if(object->cameraId() == obj->cameraId()){
            unification.removeAt(i);
            i--;
            continue;
        }

        float dist = sqrt(pow((object->position().x() - obj->position().x()), 2) + pow((object->position().y() - obj->position().y()), 2));
        if(dist > MERGE_DISTANCE){
            unification.removeAt(i);
            i--;
            continue;
        }
    }

    _lastKnowPos = object->position();
    return unification;
}
