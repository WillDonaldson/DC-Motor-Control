#ifndef MotorDriver_h
#define MotorDriver_h

#include <Arduino.h>

class MotorDriver {
    public:
        virtual void init() = 0;
        virtual void drivemotor(char direction, unsigned char PWM) = 0;
};

#endif