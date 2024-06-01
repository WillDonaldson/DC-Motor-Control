#ifndef SINGLEPWM_H
#define SINGLEPWM_H

#include "MotorDriver.h"

class SinglePWM : public MotorDriver{
    public:
        SinglePWM(char Dir, char PWM);
        void init() override;  
    private:
        void updateSpeedPWM(int speed) override;    // implement the protected virtual function
    private:
        char _Dir;
        char _PWM;
};

#endif