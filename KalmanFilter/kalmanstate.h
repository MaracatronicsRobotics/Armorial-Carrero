#ifndef KALMANSTATE_H
#define KALMANSTATE_H


#include "matrix.h"
class KalmanState {

public:

    KalmanState();

    void setPosition(float value);

    void setVelocity(float value);

    void setAcceleration(float value);

    float getPosition() const;

    float getVelocity() const;

    float getAcceleration() const;

    Matrix& matrix();

private:

    Matrix _state;

};

#endif // KALMANSTATE_H
