#ifndef DUALPWM_H
#define DUALPWM_H

#include "MotorDriver.h"

class DualPWM : public MotorDriver {
    public:
        DualPWM(char PWM1, char PWM2);
        void init() override;
        void setSpeed(int speed) override;
    private:
        char _PWM1;
        char _PWM2;
};

#endif
