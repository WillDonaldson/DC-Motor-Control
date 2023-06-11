#include <Arduino.h>
#include "MotorLib.h"

MOTOR::MOTOR(MotorDriver* driver){
  _driver = driver;
}

bool MOTOR::init(){
    _driver->init();
    return true;
}

void MOTOR::drivemotor(char direction, unsigned char PWM){
  _driver->drivemotor(direction, PWM);
}