#include <Arduino.h>
#include "MotorLib.h"
#include "MonoPWMPin.h"
#include "EnablePWMPin.h"
#include "DualPWMPin.h"

#define MONO_PWM_PIN 6
#define MONO_DIR_PIN 7

#define DUAL_IN1_PIN 9
#define DUAL_IN2_PIN 10

#define ENABLE_EN_PIN 11
#define ENABLE_IN1_PIN 12
#define ENABLE_IN2_PIN 13

// Uncomment one of the lines below to choose your motor driver
MonoPWMPin mono(MONO_DIR_PIN, MONO_PWM_PIN);                         // example compatible motor driver: MD10C 
// DualPWMPin dual(DUAL_IN1_PIN, DUAL_IN2_PIN);                         // example compatible motor driver: L9110N
// EnablePWMPin enable(ENABLE_EN_PIN, ENABLE_IN1_PIN, ENABLE_IN2_PIN);  // example compatible motor driver: L298N

// Then use that motor driver to create a MOTOR object
// Uncomment one of the lines below to choose your motor driver
MOTOR motor(&mono);      // example compatible motor driver: MD10C
// MOTOR motor(&dual);      // example compatible motor driver: L9110N
// MOTOR motor(&enable);    // example compatible motor driver: L298N

void setup() {
  motor.init();
}

void loop() {
  // Drive the motor in one direction at half speed
  motor.drivemotor(1, 128);
  delay(2000);

  // Stop the motor
  motor.drivemotor(0, 0);
  delay(2000);

  // Drive the motor in the other direction at full speed
  motor.drivemotor(-1, 255);
  delay(2000);
}