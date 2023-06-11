#ifndef MonoPWMPin_h
#define MonoPWMPin_h

#include <Arduino.h>
#include "MotorDriver.h"

class MonoPWMPin : public MotorDriver{
    public:
        MonoPWMPin(char DirPin, char PWMPin);
        void init() override;  
        void drivemotor(char direction, unsigned char PWM) override;
    private:
        char _DirPin;
        char _PWMPin;
};

#endif