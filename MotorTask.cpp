#include "MotorTask.h"

void MotorTask::setup()
{
    configMotor();
}

void MotorTask::loop()
{
    spin();
}

void MotorTask::configMotor()
{
    for (auto i : std::list<byte>(_motorPins))
    {
        pinMode(i, OUTPUT);
    }
}

void MotorTask::spin()
{
    if (!_isReverse)
    {
        for (auto &&i : _motorPins)
        {
            digitalWrite(i, HIGH);
            delay(2);
            digitalWrite(i, LOW);
        }
    }
    else
    {
        for (auto it = _motorPins.rbegin(); it != _motorPins.rend(); it++)
        {
            digitalWrite(*it, HIGH);
            delay(2);
            digitalWrite(*it, LOW);
        }
    }
}

void MotorTask::start(bool reverse)
{
    _isReverse = reverse;
    _isSpinning = true;
}

void MotorTask::stop()
{
    _isSpinning = false;
}
