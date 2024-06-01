#include "SinglePWM.h"
#include <Arduino.h>

// Constructor initializing PWM and direction pins
SinglePWM::SinglePWM(char Dir, char PWM){
    _Dir = Dir;
    _PWM = PWM;
}

// Initialize the motor driver
void SinglePWM::init(){
    pinMode(_Dir, OUTPUT);
    pinMode(_PWM, OUTPUT);
}

// Set the motor speed and direction using PWM
void SinglePWM::updateSpeedPWM(int speed){
    digitalWrite(_Dir, speed >= 0 ? HIGH : LOW);
    analogWrite(_PWM, abs(speed));
}