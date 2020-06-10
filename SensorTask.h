#ifndef __SENSOR_TASK__
#define __SENSOR_TASK__

#include <Arduino.h>
#include <Scheduler.h>
#include <Task.h>

#include <SoftwareSerial.h>

using SensorPin = byte;
using SensorISR = void (*)();

class SensorTask : public Task
{
public:
    explicit SensorTask(SensorPin pin, SensorISR isr) : _pin(pin), _isr(isr) {}

protected:
    virtual void setup() override;
    virtual void loop() override;

private:
    void configSensor();
    SensorPin _pin;
    SensorISR _isr;
};

#endif
