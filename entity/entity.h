#ifndef ENTITY_H
#define ENTITY_H

#include <QThread>
#include <QMutex>
#include <iostream>
#include "./include/timer.h"

class Entity : public QThread {
public:
    explicit Entity(QObject *parent = 0);

    // Loop time
    void setLoopTime(int t);
    void setLoopFrequency(int hz);
    int getLoopTime();
    int getLoopFrequency();

    // Run control
    void restart();
    bool isRunning();
    void stopRunning();

    // Entity name
    virtual QString name() = 0;
private:
    void run();

    // Thread methods-> this methods are not implemented and must be implemented by the inherited class
    virtual void initialization() = 0;
    virtual void loop() = 0;
    virtual void finalization() = 0;

    bool _running;
    int _loopTime;

    QMutex _mutexRunning;
    QMutex _mutexLoopTime;
};

#endif // ENTITY_H
