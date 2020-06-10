#ifndef __HEARTBEAT_TASK__
#define __HEARTBEAT_TASK__

#include <Arduino.h>
#include <Scheduler.h>
#include <Task.h>

#include <SoftwareSerial.h>

class HeartbeatTask : public Task
{
protected:
    virtual void loop() override;
};

#endif