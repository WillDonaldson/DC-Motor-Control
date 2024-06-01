#include "DualPWM.h"
#include <Arduino.h>

DualPWM::DualPWM(char PWM1, char PWM2){
    _PWM1 = PWM1;
    _PWM2 = PWM2;
}

void DualPWM::init() {
    pinMode(_PWM1, OUTPUT);
    pinMode(_PWM2, OUTPUT);
}

void DualPWM::setSpeedPWM(int speed){
    speed = constrain(speed, -255, 255);
    analogWrite(_PWM1, speed >= 0 ? abs(speed) : 0);
    analogWrite(_PWM2, speed >= 0 ? 0 : abs(speed));
}