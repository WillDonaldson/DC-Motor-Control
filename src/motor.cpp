#include "Arduino.h"
#include "motor.h"

MOTOR::MOTOR(char DirPin, char PWMPin){
  _DirPin = DirPin;
  _PWMPin = PWMPin;
}

bool MOTOR::init(){
    pinMode(_DirPin, OUTPUT);
    pinMode(_PWMPin, OUTPUT);
    return true;
}

void MOTOR::drivemotor(int Direction, unsigned char PWM){
  if(Direction == 1){    
    // clockwise
    digitalWrite(_DirPin, LOW);
    analogWrite(_PWMPin, PWM);
  }
  else if(Direction == 0){ 
    // stationary   
    digitalWrite(_DirPin, LOW);
    analogWrite(_PWMPin, LOW);
  }
  else if(Direction == -1){    
    // counterclockwise
    digitalWrite(_DirPin, HIGH);
    analogWrite(_PWMPin, PWM);
  }
}