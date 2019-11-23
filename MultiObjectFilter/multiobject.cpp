#include "multiobject.h"

multiobject::multiobject(const Position &pos, const Angle &ori, int camId, float confidence){
    _pos = pos;
    _ori = ori;
    _camId = camId;
    _confidence = confidence;
}
