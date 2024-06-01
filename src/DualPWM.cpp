#include "DualPWM.h"
#include <Arduino.h>

// Constructor initializing PWM pins
DualPWM::DualPWM(char PWM1, char PWM2){
    _PWM1 = PWM1;
    _PWM2 = PWM2;
}

// Initialize the motor driver
void DualPWM::init() {
    pinMode(_PWM1, OUTPUT);
    pinMode(_PWM2, OUTPUT);
}

// Set the motor speed and direction using PWM
void DualPWM::updateSpeedPWM(int speed){
    analogWrite(_PWM1, speed >= 0 ? abs(speed) : 0);
    analogWrite(_PWM2, speed >= 0 ? 0 : abs(speed));
}