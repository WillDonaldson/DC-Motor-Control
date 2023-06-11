#include <Arduino.h>
#include "MonoPWMPin.h"

MonoPWMPin::MonoPWMPin(char DirPin, char PWMPin){
  _DirPin = DirPin;
  _PWMPin = PWMPin;
}

void MonoPWMPin::init(){
    pinMode(_DirPin, OUTPUT);
    pinMode(_PWMPin, OUTPUT);
}

void MonoPWMPin::drivemotor(char direction, unsigned char PWM){
    if(direction == 1){    
        // clockwise
        digitalWrite(_DirPin, LOW);
        analogWrite(_PWMPin, PWM);
    }
    else if(direction == 0){ 
        // stationary   
        digitalWrite(_DirPin, LOW);
        analogWrite(_PWMPin, LOW);
    }
    else if(direction == -1){    
        // counterclockwise
        digitalWrite(_DirPin, HIGH);
        analogWrite(_PWMPin, PWM);
    }
}
