#ifndef MotorLib_h
#define MotorLib_h

#include <Arduino.h>
#include "MotorDriver.h"

class MOTOR{
    public:
        MOTOR(MotorDriver* driver);
        bool init();  
        void drivemotor(char direction, unsigned char PWM);
    private:
        MotorDriver* _driver;
};

#endif