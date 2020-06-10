#include <Arduino.h>
#include <Scheduler.h>
#include <Task.h>

#include <SoftwareSerial.h>
#include <list>

#include "MotorTask.h"
#include "HeartbeatTask.h"
#include "SensorTask.h"

// #include "AudioFileSourceSPIFFS.h"
// #include "AudioGeneratorMP3.h"
// #include "AudioOutputI2SNoDAC.h"

#define SENSOR_1 13
#define SENSOR_2 10
#define MOTOR_1       \
    {                 \
        12, 15, 14, 4 \
    }

volatile bool mentorState_1;
volatile bool mentorState_2;

void ICACHE_RAM_ATTR sensorISR_1();

void ICACHE_RAM_ATTR sensorISR_2();

auto motor_task = new MotorTask(MOTOR_1);
auto heartbeat_task = new HeartbeatTask();
auto sensor_task1 = new SensorTask(SENSOR_1, sensorISR_1);
auto sensor_task2 = new SensorTask(SENSOR_2, sensorISR_2);

void ICACHE_RAM_ATTR sensorISR_1()
{
    motor_task->start(false);
}

void ICACHE_RAM_ATTR sensorISR_2()
{
    motor_task->start(true);
}

void setup()
{
    Serial.begin(115200);
    Serial.println("setup");

    delay(1000);

    Scheduler.start(heartbeat_task);
    Scheduler.start(motor_task);
    Scheduler.start(sensor_task1);
    Scheduler.start(sensor_task2);
    Scheduler.begin();
}

void loop() {}