#ifndef SINGLEPWM_H
#define SINGLEPWM_H

#include "MotorDriver.h"

class SinglePWM : public MotorDriver{
    public:
        SinglePWM(char Dir, char PWM);
        void init() override;  
        void setSpeedPWM(int speed) override;
    private:
        char _Dir;
        char _PWM;
};

#endif