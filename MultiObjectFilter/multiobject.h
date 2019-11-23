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
