#include <Arduino.h>
#include "DualPWMPin.h"

DualPWMPin::DualPWMPin(char IN1, char IN2){
    _IN1 = IN1;
    _IN2 = IN2;
}

void DualPWMPin::init() {
    pinMode(_IN1, OUTPUT);
    pinMode(_IN2, OUTPUT);
}

void DualPWMPin::drivemotor(char  direction, unsigned char PWM){
    if (direction == 1) {
        // clockwise
        analogWrite(_IN1, PWM);
        analogWrite(_IN2, 0);
    } 
    else if (direction == 0) {
        // stationary
        analogWrite(_IN1, 0);
        analogWrite(_IN2, 0);
    } 
    else if (direction == -1) {
        // counterclockwise
        analogWrite(_IN1, 0);
        analogWrite(_IN2, PWM);
    }
}
