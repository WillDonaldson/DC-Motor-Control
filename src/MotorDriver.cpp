#include "MotorDriver.h"
#include <Arduino.h>

// Set the motor speed using PWM values
void MotorDriver::setSpeedPWM(int speed){
    speed = constrain(speed, -maxPWM, maxPWM);  // ensure speed is within valid range
    speed = abs(speed) > minPWM ? speed : 0;    // apply minimum PWM threshold
    updateSpeedPWM(speed);                      // write filtered speed command to motors
    currentSpeedPWM = speed;                    // log current speed, for other functions to reference
}

// Stop the motor immediately by setting speed to 0
void MotorDriver::stop(){
    setSpeedPWM(0);
}

int MotorDriver::getPWM(){
    return currentSpeedPWM;
}

// Set the minimum PWM value
bool MotorDriver::setMinPWM(int PWM){
    if(PWM < 0 || PWM >= maxPWM){
        return false;       // invalid PWM value
    }
    minPWM = PWM;
    return true;
}

// Set the maximum PWM value
bool MotorDriver::setMaxPWM(int PWM){
    if(PWM > 255 || PWM <= minPWM){
        return false;       // invalid PWM value
    }
    maxPWM = PWM;
    return true;
} 