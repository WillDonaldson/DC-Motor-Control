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

## Future Features

Encoder class: initially only handle a quadrature encoder, but potentially expand to single channel encoder (assuming the motor direction is always known), and an option for a Z-channel input

Velocity PID controller: merging encoder and motors to maintain setpoint speeds

Positional PID Controller

setMinPWM(): By default, min PWM is zero, but some most motors will stall out below a certain threshold. The function could set the minimum PWM speed.

setMaxPWM(): Similar to setMinPWM()

brake(): short motor terminals - dependent on motor driver hardware features, may be hard to introduce generally

smoothTimeStop(int timeSeconds): come to a stop in a set amount of seconds. Requires knowing the current speed of the motor

accelerateToSpeed(int setpointSpeed, int accelerationRate, bool useEncoder = False): accelerate (or decelerate) to a setpoint speed. If useEncoder == False, use PWM values for setpointSpeedand accelerationRate. If useEncoder == True, use RPM values for setpointSpeedand accelerationRate to send a moving setpoint value to setSpeedPID().

setSpeedPID(int setpointSpeed): requires encoder, use a PID loop to reach and maintain a desired setPoint

getPWM(): read current PWM value of motor

getRPM(): read current RPM value of motor

getPulses()

getAngle()

getDir(): assuming quadrature encoder is attached, use it to check rotation direction

movePulses(int pulseCount): rotate forward/backwards a set number of encoder pulses from the current position. Optionally utilize a positional PID loop

zeroEncoder(): zero the encoder pulse count based on current motor position (may require external limit switch/Z-channel encoder to trigger in desired location)

homeEncoder(): move to zero position. Optionally utilize a positional PID loop

moveAngle(): assuming zeroEncoder() has set a home position, move to a given angle relative to home. Optionally utilize a positional PID loop

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
