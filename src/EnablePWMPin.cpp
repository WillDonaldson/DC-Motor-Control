#include <Arduino.h>
#include "EnablePWMPin.h"

EnablePWMPin::EnablePWMPin(char EnPin, char In1Pin, char In2Pin){
    _EnPin = EnPin;
    _In1Pin = In1Pin;
    _In2Pin = In2Pin;
}

void EnablePWMPin::init(){
    pinMode(_EnPin, OUTPUT);
    pinMode(_In1Pin, OUTPUT);
    pinMode(_In2Pin, OUTPUT);
}

void EnablePWMPin::drivemotor(char direction, unsigned char PWM){
    analogWrite(_EnPin, PWM);               // send PWM speed command
    if (direction == 1) {
        // clockwise
        digitalWrite(_In1Pin, HIGH);
        digitalWrite(_In2Pin, LOW);
    } 
    else if (direction == 0) {
        // stationary
        digitalWrite(_In1Pin, LOW);
        digitalWrite(_In2Pin, LOW);
    } 
    else if (direction == -1) {
        // counterclockwise
        digitalWrite(_In1Pin, LOW);
        digitalWrite(_In2Pin, HIGH);
    }
}
