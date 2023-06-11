#include "Arduino.h"
#include "MotorLib.h"
#include "MonoPWMPin.h"
#include "EnablePWMPin.h"
#include "DualPWMPin.h"

#define MONO_DIR_PIN 5
#define MONO_PWM_PIN 6

#define ENABLE_EN_PIN 9
#define ENABLE_IN1_PIN 8
#define ENABLE_IN2_PIN 7

#define DUAL_A1A_PIN 10
#define DUAL_A1B_PIN 11

// Uncomment one of the lines below to choose your motor driver
// MonoPWMPin mono(MONO_DIR_PIN, MONO_PWM_PIN);                         // example compatible motor driver: MD10C 
// EnablePWMPin enable(ENABLE_EN_PIN, ENABLE_IN1_PIN, ENABLE_IN2_PIN);  // example compatible motor driver: L298N
DualPWMPin dual(DUAL_A1A_PIN, DUAL_A1B_PIN);                         // example compatible motor driver: L9110N

// Then use that motor driver to create a MOTOR object
// Uncomment one of the lines below to choose your motor driver
// MOTOR motor(&mono);      // example compatible motor driver: MD10C
// MOTOR motor(&enable);    // example compatible motor driver: L298N
MOTOR motor(&dual);      // example compatible motor driver: L9110N

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
