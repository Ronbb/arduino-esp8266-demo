#include "SensorTask.h"

void SensorTask::setup()
{
    configSensor();
}

void SensorTask::loop()
{
    delay(1000);
}

void SensorTask::configSensor()
{
    pinMode(_pin, INPUT_PULLUP);
    attachInterrupt(_pin, _isr, RISING);
}
