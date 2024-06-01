# DCMotorLib - A Universal Arduino Motor Driver Library

DCMotorLib is a versatile Arduino library for controlling a wide variety of motor drivers. It provides a simple and consistent interface, allowing users to drive motors without worrying about the specifics of their motor driver's pin configuration or control signals.

## Supported Motor Driver Types

DCMotorLib supports three types of motor driver control pin sequences:

1. **SinglePWM**: For motor drivers with one direction control pin and one PWM pin (e.g., MD10C).
2. **DualPWM**: For motor drivers with two direction/PWM control pins (e.g., L9110N).
3. **EnablePWM**: For motor drivers with an enable pin and two direction control pins (e.g., L298N).

## How to Use

To use this library, you'll need to first create an instance of the motor driver type that matches your actual hardware. Pass the relevant pin numbers to the constructor.

Then, create an instance of the MOTOR class, passing the motor driver instance to its constructor.

Use the `init` method to initialize the motor driver, and the `setSpeed` method to control the motor.

See `examples/` for more detailed usage examples.

## Tested/Validated Hardware Configurations

| Pin Sequence | Motor Driver | MCU          | Status | Date Tested |
| ------------ | ------------ | ------------ | ------ | ----------- |
| SinglePWM    | MD10C        | Arduino Nano | ❌     | Not tested  |
| DualPWM      | L9110N       | Arduino Nano | ✅     | 31-05-2024  |
| DualPWM      | DBH-12V      | Arduino Nano | ✅     | 31-05-2024  |
| EnablePWM    | L298N        | Arduino Nano | ✅     | 31-05-2024  |

## Development Plan

Following outlines the planned functionality of this library as it is developed

#### Motor Class:

* **setSpeedPWM(int speed)**: Set the motor speed using PWM values.
* **stop()**: Immediately stop motors.
* **getPWM()**: Read the current PWM value of the motor.
* **setMinPWM(int PWM)**: Set the minimum PWM speed.
* **setMaxPWM(int PWM)**: Set the maximum PWM speed.
* **rampSpeedPWM(int startSpeed, int endSpeed, int duration=-1)**: Ramp motor speed from `startSpeed` to `endSpeed` over `duration` milliseconds. If `duration` is -1, move as fast as possible.
* **setAccelerationProfile(int profile)**: Set different acceleration profiles such as linear, exponential, logarithmic, etc.

#### Encoder Class*:

* **getPulses()**: Get the current count of pulses from the encoder.
* **getRPM()**: Get the current RPM of the motor.
* **getAngle(bool absolute = false)**: Get the current angle of the motor. If `absolute` is false, the angle is measured relative to the home position within the range (-180, 180] degrees. If `absolute` is true, the angle is measured from the absolute home position, and the range is unbounded.
* **getDir()**: Get the direction of rotation.
* **zeroEncoder()**: Set the current pulse and angle as zero.

**initially will only handle a quadrature encoders, but can potentially be expanded to single channel encoder (assuming the motor direction is always known), and Z-channel input encoders.*

#### Velocity PID Contoller:

* **setMinVelocity(int minRPM)**: Set the minimum RPM.
* **setMaxVelocity(int maxRPM)**: Set the maximum RPM.
* **setVelocityPID(int setpointRPM)**: Set the desired RPM using a PID controller.
* **rampVelocityPID(int startRPM, int endRPM, int duration=-1)**: Ramp motor velocity from `startRPM` to `endRPM` over `duration` milliseconds. If `duration` is -1, move as fast as possible.
* **setVelocityPID(float Kp, float Ki, float Kd)**: Set PID constants for velocity control.
* **getVelocityPID()**: Get the current PID settings for velocity control.
* **isStalled()**: Detect if the motor is stalled when it has been commanded to move.
* **findStallPWM()**: Automatically cycle through low PWM setpoints to find the threshold at which the motor stalls.
* **findStallVelocity()**: Automatically cycle through low RPM setpoints to find the threshold at which the motor stalls.

#### Positional PID Controller:

* **moveHome(bool absolute = false)**: Move to the zero position. If `absolute` is false, the movement is within the range (-180, 180] degrees relative to the home position. If `absolute` is true, the movement is unbounded and moves to the absolute home position.
* **moveAngle(int startAngle, int endAngle, int duration=-1, bool absolute = false)**: Rotate to a given angle from `startAngle` to `endAngle` over `duration` milliseconds. If `duration` is -1, move as fast as possible. If `absolute` is false, the movement is within the range (-180, 180] degrees relative to the home position. If `absolute` is true, the movement is unbounded and moves to the absolute home position.
* **movePulses(int pulseCount, int duration=-1)**: Rotate forward/backward by a set number of encoder pulses over `duration` milliseconds. If `duration` is -1, move as fast as possible.
* **setPositionalPID(float Kp, float Ki, float Kd)**: Set the PID constants for positional control.
* **getPositionalPID()**: Get the current PID settings for positional control.

#### Functionality Not Currently Under Development

* **autoTuneVelocityPID() and autoTunePositionalPID()**: These functions may be developed after completing the core library.
* **autoCalibrateEncoder()**: Library assumes pulses/revolution are known from the manufacturer.
* **Hardware-Specific Functionality**: Including motor braking and coasting, which is only available on certain motor driver configurations.
* **Current Monitoring and Control**: Not currently planned for development.

## License

MIT License

Copyright (c) 2023 Will Donaldson

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
