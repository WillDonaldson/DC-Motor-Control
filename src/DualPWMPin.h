#ifndef DualPWMPin_h
#define DualPWMPin_h

#include <Arduino.h>
#include "MotorDriver.h"

class DualPWMPin : public MotorDriver {
    public:
        DualPWMPin(char IN1, char IN2);
        void init() override;
        void drivemotor(char direction, unsigned char PWM) override;
    private:
        char _IN1;
        char _IN2;
};

#endif
