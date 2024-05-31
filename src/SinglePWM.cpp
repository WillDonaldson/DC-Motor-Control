#include "SinglePWM.h"
#include <Arduino.h>

SinglePWM::SinglePWM(char Dir, char PWM){
    _Dir = Dir;
    _PWM = PWM;
}

void SinglePWM::init(){
    pinMode(_Dir, OUTPUT);
    pinMode(_PWM, OUTPUT);
}

void SinglePWM::setSpeed(int speed){
    speed = constrain(speed, -255, 255);
    digitalWrite(_Dir, speed >= 0 ? HIGH : LOW);
    analogWrite(_PWM, abs(speed));
}