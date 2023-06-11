#ifndef EnablePWMPin_h
#define EnablePWMPin_h

#include <Arduino.h>
#include "MotorDriver.h"

class EnablePWMPin : public MotorDriver{
    public:
        EnablePWMPin(char EPin, char In1Pin, char In2Pin);
        void init() override;
        void drivemotor(char direction, unsigned char PWM) override;
    private:
        char _EnPin;
        char _In1Pin;
        char _In2Pin;
};

#endif
