#include "MotorTask.h"

void MotorTask::setup()
{
    configMotor();
}

void MotorTask::loop()
{
    if (!_isSpinning && !_willRun)
    {
        delay(10);
        return;
    }
    if (!_isSpinning && _willRun)
    {
        delay(100);
        _currentMotor = _willRunMotor;
        _isSpinning = true;
        _willRun = false;
    }

    if (_isSpinning)
    {

        if (_currentMotor == 0)
        {
            pinMode(_motorSelPin, OUTPUT);
            digitalWrite(_motorSelPin, HIGH);

            delay(100);
            int count = 64 * 2;
            while (count-- > 0)
            {
                spin(true);
            }
            delay(2000);
            count = 64 * 2;
            while (count-- > 0)
            {
                spin(false);
            }
        }
        else
        {
            pinMode(_motorSelPin, OUTPUT);
            digitalWrite(_motorSelPin, LOW);

            delay(100);
            int count = 64 * 8 * 3;
            while (count-- > 0)
            {
                spin(false);
            }
            _mcb();
        }

        _isSpinning = false;
        _willRun = false;
    }
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

void MotorTask::spin(bool isReverse)
{
    // digitalWrite(_motorSelPin, _currentMotor == 1 ? HIGH : LOW);

    if (!isReverse)
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

void MotorTask::start(int motor)
{
    _willRun = true;
    _willRunMotor = motor;
}

void MotorTask::stop()
{
    _isSpinning = false;
}
