#ifndef MotorDriver_h
#define MotorDriver_h

#include <Arduino.h>

class MotorDriver {
    public:
        virtual void init() = 0;
        virtual void setSpeedPWM(int speed) = 0;
        virtual ~MotorDriver() {}
};

#endif