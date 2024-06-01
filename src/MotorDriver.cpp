#include "MotorDriver.h"
#include <Arduino.h>

// Set the motor speed using PWM values
// Does not return an error code. Errors and warnings are handled internally.
void MotorDriver::setSpeedPWM(int speed){
    if(abs(speed) < minPWM || abs(speed) > maxPWM){
        handleError(WARNING_INVALID_PWM_SETPOINT);
        speed = constrain(speed, -maxPWM, maxPWM);  // ensure speed is within valid range
        speed = abs(speed) > minPWM ? speed : 0;    // apply minimum PWM threshold
    }
    updateSpeedPWM(speed);                      // write filtered speed command to motors
    currentSpeedPWM = speed;                    // log current speed, for other functions to reference
}

// Stop the motor immediately by setting speed to 0
// Does not return an error code. Errors and warnings are handled internally.
void MotorDriver::stop(){
    setSpeedPWM(0);
}

int MotorDriver::getPWM(){
    return currentSpeedPWM;
}

// Set the minimum PWM value
// Returns error code or success
MotorDriverError MotorDriver::setMinPWM(int PWM){
    if(PWM < 0 || PWM >= maxPWM){
        return handleError(ERROR_INVALID_PWM_CUTOFF);      
    }
    minPWM = PWM;
    if(getPWM() < minPWM){
        return handleError(WARNING_CURRENT_PWM_SPEED_INVALID); // after update, the current PWM speed is now invalid
    }
    return handleError(SUCCESS);
}

// Set the maximum PWM value
// Returns error code or success
MotorDriverError MotorDriver::setMaxPWM(int PWM){
    if(PWM > 255 || PWM <= minPWM){
        return handleError(ERROR_INVALID_PWM_CUTOFF);   
    }
    maxPWM = PWM;
    if(getPWM() > maxPWM){
        return handleError(WARNING_CURRENT_PWM_SPEED_INVALID); // after update, the current PWM speed is now invalid
    }
    return handleError(SUCCESS);
}

MotorDriverError MotorDriver::handleError(MotorDriverError error){
    lastError = error;
    switch(error){
        case SUCCESS:
            // TO DO: Handle success
            break;
        case ERROR_INVALID_PWM_CUTOFF:
            // TO DO: Handle error of invalid request to update minPWM or maxPWM 
            break;
        case WARNING_INVALID_PWM_SETPOINT:
            // TO DO: Handle warning of invalid requested PWM setpoint beyond maxPWM 
            break;
        case WARNING_CURRENT_PWM_SPEED_INVALID:
            // Handle warning that current PWM speed is out of allowed range
            if(currentSpeedPWM < minPWM){
                // stop motor
                setSpeedPWM(0);
            }
            else if(currentSpeedPWM > maxPWM){
                // restrict motor to maxPWM
                setSpeedPWM(maxPWM);
            }
            break;
        default:
            // TO DO: Handle unknown error
            break;
    }
    return error;
}