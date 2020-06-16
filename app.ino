#include <Arduino.h>
#include <Scheduler.h>
#include <Task.h>

#include <SoftwareSerial.h>

#include "MotorTask.h"
#include "HeartbeatTask.h"
#include "SensorTask.h"
#include "MusicTask.h"


#define SENSOR_0 13
#define SENSOR_1 15

#define MOTOR       \
    {                 \
        12, 5, 14, 4 \
    }

#define MOTOR_SEL 16

void ICACHE_RAM_ATTR sensorISR_0();
void ICACHE_RAM_ATTR sensorISR_1();

void mcb();

auto heartbeat_task = new HeartbeatTask();
auto motor_task = new MotorTask(MOTOR, MOTOR_SEL, mcb);
auto sensor_task0 = new SensorTask(SENSOR_0, sensorISR_0);
auto sensor_task1 = new SensorTask(SENSOR_1, sensorISR_1);
auto music_task = new MusicTask();

void mcb() {
    music_task->Run();
}

void ICACHE_RAM_ATTR sensorISR_0()
{
    motor_task->start(0);
}

void ICACHE_RAM_ATTR sensorISR_1()
{
    motor_task->start(1);
}

void setup()
{
    Serial.begin(115200);
    Serial.println("Main Setup");

    delay(1000);

    Scheduler.start(heartbeat_task);
    Scheduler.start(motor_task);
    Scheduler.start(sensor_task0);
    Scheduler.start(sensor_task1);
    Scheduler.start(music_task);
    Scheduler.begin();
}

void loop() {}
