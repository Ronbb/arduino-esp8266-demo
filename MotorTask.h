#ifndef __MOTOR_TASK__
#define __MOTOR_TASK__

#include <Arduino.h>
#include <Scheduler.h>
#include <Task.h>

#include <SoftwareSerial.h>
#include <list>

typedef std::list<byte> MotorPins;

class MotorTask : public Task
{
public:
    explicit MotorTask(MotorPins motorPins) : _motorPins(motorPins), _isSpinning(false) {}
    void start(bool reverse = false);
    void stop();

private:
    void configMotor();
    void spin();

    MotorPins _motorPins;
    volatile bool _isSpinning;
    bool _isReverse;

protected:
    virtual void setup() override;

    virtual void loop() override;
};

#endif