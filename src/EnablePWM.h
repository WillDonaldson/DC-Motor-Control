#ifndef ENABLEPWM_H
#define ENABLEPWM_H

#include "MotorDriver.h"

class EnablePWM : public MotorDriver{
    public:
        EnablePWM(char en, char in1, char in2);
        void init() override;
    private:
        void updateSpeedPWM(int speed) override;    // implement the protected virtual function
    private:
        char _en;
        char _in1;
        char _in2;
};

#endif
