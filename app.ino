#include <Arduino.h>
#include <Scheduler.h>
#include <Task.h>

#include <SoftwareSerial.h>

#include "MotorTask.h"
#include "HeartbeatTask.h"
#include "SensorTask.h"

// #include "AudioFileSourceSPIFFS.h"
// #include "AudioGeneratorMP3.h"
// #include "AudioOutputI2SNoDAC.h"

#define SENSOR_0 13
#define SENSOR_1 10
#define MOTOR_1       \
    {                 \
        12, 15, 14, 4 \
    }

void ICACHE_RAM_ATTR sensorISR_0();
void ICACHE_RAM_ATTR sensorISR_1();

auto heartbeat_task = new HeartbeatTask();
auto motor_task0 = new MotorTask(MOTOR_1);
auto sensor_task0 = new SensorTask(SENSOR_0, sensorISR_0);
auto sensor_task1 = new SensorTask(SENSOR_1, sensorISR_1);

void ICACHE_RAM_ATTR sensorISR_0()
{
    motor_task0->start(false);
}

void ICACHE_RAM_ATTR sensorISR_1()
{
    motor_task0->start(true);
}

void setup()
{
    Serial.begin(115200);
    Serial.println("Main Setup");

    delay(1000);

    Scheduler.start(heartbeat_task);
    Scheduler.start(motor_task0);
    Scheduler.start(sensor_task0);
    Scheduler.start(sensor_task1);

    Scheduler.begin();
}

void loop() {}
