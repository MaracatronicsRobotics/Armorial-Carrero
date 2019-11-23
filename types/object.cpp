#include "object.h"

Object::Object(bool enableLossFilter, bool enableKalmanFilter, bool enableNoiseFilter) {

//    _lossFilter.setEnabled(enableLossFilter);
    _kalmanFilter.setEnabled(enableKalmanFilter);
//    _noiseFilter.setEnabled(enableNoiseFilter);

    _zero = false;
    _position.setUnknown();
    _velocity.setUnknown();
    _orientation.setUnknown();

    _confidence = 0.0;
    isValid = true;
}

Object::~Object() {

}

Position Object::getPosition() {
    _mutex->lockForRead();

    Position retn = _position;

    _mutex->unlock();

    return retn;
}

Velocity Object::getVelocity() {
    _mutex->lockForRead();

    Velocity retn = _velocity;

    _mutex->unlock();

    return retn;
}

Angle Object::getOrientation() {
    _mutex->lockForRead();

    Angle retn = _orientation;

    _mutex->unlock();

    return retn;
}

void Object::setFilterTimes(double time){
    _lossFilter.setFilterTime(time);
    _noiseFilter.setFilterTime(time);
}

double Object::getConfidence() {

    _mutex->lockForRead();

    double retn = _confidence;

    _mutex->unlock();

    return retn;

}

bool Object::checkNoise(){
    bool ret = _noiseFilter.noiseFilter();
    return ret;
}

bool Object::checkLoss(){
    bool ret = _lossFilter.lossFilter(false);

    if(ret == false && isValid){ // se n deu perda pode ser validado

    }else{
        isValid = false;
        _position.setInvalid();
    }

    return ret;
}

void Object::update(double confidence, Position pos, Angle ori) {
    _mutex->lockForWrite();

    isValid = true;

    if(!_noiseFilter.isInitialized()){
        _noiseFilter.initCounter();
        _position.setInvalid(); // como o filtro de ruido ainda nao terminou
                                // é necessário invalidar a posição até que ele acabe
    }else{
        if(_noiseFilter.noiseFilter()){ // caso o filtro tenha terminado o tempo
            _zero = false;
            isValid = true;
            _lossFilter.lossFilter(true); // dou update no filtro de perda

            _kalmanFilter.iterate(pos); // inicializa mais uma iteração no kalman
            _position.setPosition(_kalmanFilter.getPosition().x(), _kalmanFilter.getPosition().y(), 0.0); // pega a posição retornada pelo kalman
            _velocity = _kalmanFilter.getVelocity();
            _orientation.setValue(ori.value()); // dou update no angulo do robo
            updateToSensor();
        }else{
            predict(); // quando estou em noise, tento fazer predições da movimentação do robô
            updateToSensor();
        }
    }

    _mutex->unlock();
}

void Object::checkFilters(){
    if(checkLoss()){
        _noiseFilter.setOff();
        setUnknown();
    }
}

void Object::predict(){
    _kalmanFilter.predict();
}

void Object::setUnknown() {

    if(_zero == false) {
        _confidence = 0.0;
        _position = Position(false, 0.0, 0.0,0.0);
        _velocity = Velocity(false, 0, 0);
        _orientation = Angle(false, 0);
        _zero = true;
        updateToSensor();
    }

}
