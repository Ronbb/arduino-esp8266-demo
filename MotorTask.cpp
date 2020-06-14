#include "MotorTask.h"

void MotorTask::setup()
{
    configMotor();
}

void MotorTask::loop()
{
    if (!_isSpinning)
    {
        delay(10);
        return;
    }
    spin();
}

void MotorTask::configMotor()
{
    for (auto i : std::list<byte>(_motorPins))
    {
        pinMode(i, OUTPUT);
    }
    pinMode(_motorSelPin, OUTPUT);
    digitalWrite(_motorSelPin, HIGH);
}

void MotorTask::spin()
{
    // digitalWrite(_motorSelPin, _currentMotor == 1 ? HIGH : LOW);

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

void MotorTask::start(int motor, bool reverse)
{
    _isReverse = reverse;
    _isSpinning = true;
    _currentMotor = motor;
    Serial.println(motor);
}

void MotorTask::stop()
{
    _isSpinning = false;
}
