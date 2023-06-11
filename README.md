# DCMotorLib - A Universal Arduino Motor Driver Library

DCMotorLib is a versatile Arduino library for controlling a wide variety of motor drivers. It provides a simple and consistent interface, allowing users to drive motors without worrying about the specifics of their motor driver's pin configuration or control signals.

## Supported Motor Driver Types

DCMotorLib supports three types of motor driver control pin sequences:

1. **MonoPWMPin**: For motor drivers with one direction control pin and one PWM pin (e.g., MD10C).
2. **DualPWMPin**: For motor drivers with two direction/PWM control pins (e.g., L9110N).
3. **EnablePWMPin**: For motor drivers with an enable pin and two direction control pins (e.g., L298N).

## How to Use

To use this library, you'll need to first create an instance of the motor driver type that matches your actual hardware. Pass the relevant pin numbers to the constructor.

Then, create an instance of the MOTOR class, passing the motor driver instance to its constructor.

Use the `init` method to initialize the motor driver, and the `drivemotor` method to control the motor.

See `examples/` for more detailed usage examples.

## Tested/Validated Hardware Configurations

| Pin Sequence | Motor Driver | MCU          | Status | Date Tested |
| ------------ | ------------ | ------------ | ------ | ----------- |
| MonoPWMPin   | MD10C        | Arduino Nano | ✅     | 2023-06-11  |
| DualPWMPin   | L298N        | Arduino Nano | ❌     | N/A         |
| EnablePWMPin | L9110N       | Arduino Nano | ❌     | N/A         |

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
