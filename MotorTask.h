#ifndef __MOTOR_TASK__
#define __MOTOR_TASK__

#include <Arduino.h>
#include <Scheduler.h>
#include <Task.h>

#include <SoftwareSerial.h>
#include <list>

typedef byte MotorSelPin;
typedef std::list<byte> MotorPins;
using MCB = void (*)();

class MotorTask : public Task
{
public:
    /**
     * @brief Construct a MotorTask
     * @param motorPins pins of motor
     */
    explicit MotorTask(MotorPins motorPins, MotorSelPin motorSel, MCB mcb) : _motorPins(motorPins), _motorSelPin(motorSel), _isSpinning(false), _mcb(mcb) {}

    /**
     * @brief Let the motor spin 
     * @param reverse reverse or not, default = false
     */
    void start(int motor);

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
    void spin(bool isReverse);

    MotorSelPin _motorSelPin;
    MotorPins _motorPins;
    int _currentMotor;
    volatile bool _isSpinning;
    volatile bool _willRun;
    volatile int _willRunMotor;
    MCB _mcb;

protected:
    virtual void setup() override;
    virtual void loop() override;
};

#endif
