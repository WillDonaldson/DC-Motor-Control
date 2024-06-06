#include <Arduino.h>

#include "SinglePWM.h"
#include "DualPWM.h"
#include "EnablePWM.h"

// Uncomment one of the lines below to choose your motor driver
//SinglePWM myMotor(11, 12);    // PWM control pin, Direction pin
DualPWM myMotor(9, 10);       // PWM control pin 1, PWM control pin 2
//EnablePWM myMotor(6, 7, 8);   // Enable pin, control pin 1, control pin 2

void setup() {
  myMotor.init();
}

void loop() {
  myMotor.setSpeedPWM(100);  
  delay(1000);
  myMotor.setSpeedPWM(-180);
  delay(1000);
}