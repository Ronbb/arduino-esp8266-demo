#ifndef __MOTOR_TASK__
#define __MOTOR_TASK__

#include <Arduino.h>
#include <Scheduler.h>
#include <Task.h>

#include <SoftwareSerial.h>
#include <list>

typedef byte MotorSelPin;
typedef std::list<byte> MotorPins;

class MotorTask : public Task
{
public:
    /**
     * @brief Construct a MotorTask
     * @param motorPins pins of motor
     */
    explicit MotorTask(MotorPins motorPins, MotorSelPin motorSel) : _motorPins(motorPins), _motorSelPin(motorSel), _isSpinning(false), _isReverse(false) {}

    /**
     * @brief Let the motor spin 
     * @param reverse reverse or not, default = false
     */
    void start(int motor, bool reverse = false);

    /**
     * @brief Let the motor stop spinning 
     */
    void stop();

private:
    /**
     * @brief Configure pins of motor
     */
    void configMotor();

    /**
     * @brief Motor spins once
     */
    void spin();

    MotorSelPin _motorSelPin;
    MotorPins _motorPins;
    int _currentMotor;
    volatile bool _isSpinning;
    volatile bool _isReverse;

protected:
    virtual void setup() override;
    virtual void loop() override;
};

#endif
