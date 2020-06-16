#include "HeartbeatTask.h"

// Print a message containing the current time every once in a while
void HeartbeatTask::loop()
{
    //Serial.printf("[Heartbeat] %u\n", millis() / 1000); // seconds
    delay(1000);                                       // milliseconds
}
