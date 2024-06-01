#include "EnablePWM.h"
#include <Arduino.h>

// Constructor initializing enable and direction pins
EnablePWM::EnablePWM(char en, char in1, char in2){
    _en = en;
    _in1 = in1;
    _in2 = in2;
}

// Initialize the motor driver
void EnablePWM::init(){
    pinMode(_en, OUTPUT);
    pinMode(_in1, OUTPUT);
    pinMode(_in2, OUTPUT);
}

// Set the motor speed and direction using PWM
void EnablePWM::updateSpeedPWM(int speed){
    analogWrite(_en, abs(speed));
    digitalWrite(_in1, speed >= 0 ? HIGH : LOW);
    digitalWrite(_in2, speed >= 0 ? LOW : HIGH);
}
