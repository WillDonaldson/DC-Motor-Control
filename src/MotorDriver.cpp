#include "MotorDriver.h"
#include <Arduino.h>

void MotorDriver::setSpeedPWM(int speed){
    // enforce that the PWM speed command falls within accepted range
    speed = constrain(speed, -maxPWM, maxPWM);
    speed = abs(speed) > minPWM ? speed : 0;

    // write filtered speed command to motors
    updateSpeedPWM(speed);

    // log current speed, for other functions to reference
    currentSpeedPWM = speed;  
}

void MotorDriver::stop(){
    setSpeedPWM(0);
}

int MotorDriver::getPWM(){
    return currentSpeedPWM;
}

bool MotorDriver::setMinPWM(int PWM){
    if(PWM < 0 || PWM >= maxPWM){
        // requested PWM update is not valid
        return false;
    }
    // update PWM cutoff 
    minPWM = PWM;
    return true;
}

bool MotorDriver::setMaxPWM(int PWM){
    if(PWM > 255 || PWM <= minPWM){
        // requested PWM update is not valid
        return false;
    }
    // update PWM cutoff
    maxPWM = PWM;
    return true;
} 



