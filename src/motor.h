#ifndef motor_h
#define motor_h

#include "Arduino.h"

class MOTOR{
    public:
        MOTOR(char DirPin, char PWMPin);
        bool init();  
        void drivemotor(int Direction, unsigned char PWM);
    private:
        char _DirPin;
        char _PWMPin;
};

extern MOTOR motor;

#endif