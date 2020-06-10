#include "HeartbeatTask.h"

void HeartbeatTask::loop()
{
    Serial.printf("Heartbeat %u\n", millis() / 1000);
    delay(10000);
}