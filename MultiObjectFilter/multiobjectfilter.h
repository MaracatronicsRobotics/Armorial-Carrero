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
