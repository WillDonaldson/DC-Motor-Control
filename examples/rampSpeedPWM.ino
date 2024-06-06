#include <Arduino.h>

#include "SinglePWM.h"
#include "DualPWM.h"
#include "EnablePWM.h"

// Uncomment one of the lines below to choose your motor driver
//SinglePWM myMotor(11, 12);    // PWM control pin, Direction pin
DualPWM myMotor(9, 10);       // PWM control pin 1, PWM control pin 2
//EnablePWM myMotor(6, 7, 8);   // Enable pin, control pin 1, control pin 2

// Acceleration profile names
const char* profileNames[] = {
  "Undefined",
  "Linear",
  "Quadratic",
  "Exponential",
  "Logarithmic",
  "Cubic",
  "Sine Wave",
  "Cosine Ease-In-Out"
};

void setup(){
  Serial.begin(9600);

  myMotor.init();

  // set PWM thresholds
  myMotor.setMinPWM(15);
  myMotor.setMaxPWM(250);
}

void loop(){
  for(int mode = 1; mode < 8; mode++){
    Serial.print("Mode " + String(mode) + " (" + profileNames[mode] + ") acceleration beginning... ");
    myMotor.initializeRampPWM(250, 3000, mode);
    while(!myMotor.rampPWM());
    Serial.print("maximum speed achieved... ");
    delay(1000);
    Serial.println("stopping motor.");
    myMotor.stop();
    delay(1000);
  }
}