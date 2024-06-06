#include "MotorDriver.h"
#include <Arduino.h>

// Declarations for ramp profiles
float linearRamp(float t);
float quadraticRamp(float t);
float exponentialRamp(float t);
float logarithmicRamp(float t);
float cubicRamp(float t);
float sineWaveRamp(float t);
float cosineSmoothRamp(float t);

/**
 * @brief Sets the motor speed using PWM values.
 *
 * This function sets the motor speed to the specified value using PWM. If the speed is outside the
 * valid range, it is constrained to be within the range defined by minPWM and maxPWM.
 *
 * @param speed The desired speed to set. The value is constrained between -maxPWM and maxPWM.
 * @return Nothing, errors and warnings are handled internally.
 */
void MotorDriver::setSpeedPWM(int speed){
    // Ensure requested speed is within valid range
    if(abs(speed) < minPWM || abs(speed) > maxPWM){
        handleError(WARNING_INVALID_PWM_SETPOINT);
        speed = constrain(speed, -maxPWM, maxPWM);  
        speed = abs(speed) > minPWM ? speed : 0;    
    }

    // Write filtered speed command to motors
    updateSpeedPWM(speed);      

    // Log current speed for other functions to reference          
    currentSpeedPWM = speed;                    
    return;
}

/**
 * @brief Stop the motor immediately by setting speed to 0
 */
void MotorDriver::stop(){
    setSpeedPWM(0);
}

/**
 * @brief Gets the current PWM value of the motor.
 *
 * @return The current PWM value of the motor.
 */
int MotorDriver::getPWM(){
    return currentSpeedPWM;
}

/**
 * @brief Sets the minimum PWM value for the motor.
 *
 * This function sets the minimum PWM value below which the motor will not run. 
 * If the specified value is invalid, an error is returned.
 *
 * @param PWM The minimum PWM value to set. Must be between 0 and maxPWM.
 * @return MotorDriverError indicating success or type of error.
 */
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

/**
 * @brief Sets the maximum PWM value for the motor.
 *
 * This function sets the maximum PWM value below which the motor will not run. 
 * If the specified value is invalid, an error is returned.
 *
 * @param PWM The maximum PWM value to set. Must be between minPWM and 255.
 * @return MotorDriverError indicating success or type of error.
 */
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

/**
 * @brief Initializes a PWM ramp to smoothly transition the motor speed from the current speed to the specified end speed over a given duration.
 *
 * This function sets up the parameters for a PWM ramp, ensuring that the ramp starts smoothly from the current speed
 * and transitions to the specified end speed within the constraints of minPWM and maxPWM. 
 *
 * @param endSpeed The target speed at the end of the ramp. The value is constrained between -maxPWM and maxPWM.
 *                 If the absolute value of endSpeed is below minPWM (and not zero), it is adjusted to minPWM or -minPWM.
 * @param duration The duration of the ramp in milliseconds. If the duration is zero or negative, the speed is updated immediately to endSpeed.
 * @param accelerationProfile The profile to use for ramping the speed. This determines the shape of the ramp curve (e.g., linear, quadratic).
 */
void MotorDriver::initializeRampPWM(int endSpeed, long duration, char accelerationProfile){
    // Constrain endSpeed within the valid range
    endSpeed = constrain(endSpeed, -maxPWM, maxPWM);

    // Ensure endSpeed is not below minPWM unless it's zero
    if(endSpeed != 0 && abs(endSpeed) < minPWM){
        endSpeed = (endSpeed < 0) ? -minPWM : minPWM;
    }

    // Handle case where duration is zero or negative
    if(duration <= 0){
        // Update to max setpoint speed immediately
        setSpeedPWM(endSpeed);
        rampComplete = true;
        delay(1000);
        return;
    }

    // Initialize ramp parameters
    rampComplete = false;
    rampRuntime = duration;
    rampStartTime = millis();
    rampEndSpeed = endSpeed;
    rampStartSpeed = getPWM();
    setAccelerationProfile(accelerationProfile);
}

/**
 * @brief Executes the PWM ramp operation to gradually change the motor speed based on the initialized ramp parameters.
 *
 * This function calculates the progress of the ramp based on the elapsed time and updates the motor speed accordingly.
 * If the ramp is complete (i.e., the target end speed is reached), it sets the motor speed to endSpeed and marks the ramp as complete.
 * If the ramp is still in progress, it calculates the new speed using the specified acceleration profile and updates the motor speed.
 *
 * @return true if the ramp is complete, false if the ramp is still in progress.
 */
bool MotorDriver::rampPWM(){
    // Ramp already complete or was not initialized by initializeRampPWM()
    if(rampComplete){
        return rampComplete; 
    }

    // Track time as the ramp function progresses 
    unsigned long currentMillis = millis();
    unsigned long rampElapsedTime = currentMillis - rampStartTime;
    float progress = float(rampElapsedTime) / rampRuntime;

    // If ramp has completed, set rampEndSpeed and flag ramp completed
    if(progress >= 1.0f){
        setSpeedPWM(rampEndSpeed);
        rampComplete = true;
        return rampComplete;
    }

    // Accelerate the motor towards the end setpoint
    int newSpeed = rampStartSpeed + (rampEndSpeed - rampStartSpeed) * rampFunction(progress);
    setSpeedPWM(newSpeed);
    return rampComplete; // Return incomplete ramp 
}

/**
 * @brief Sets the acceleration profile for the ramp operation.
 *
 * This function sets the acceleration profile to be used for ramping the motor speed. 
 * The profile determines the shape of the ramp curve (e.g., linear, quadratic, exponential, etc.).
 *
 * @param profile The acceleration profile to set. Each profile corresponds to a different ramp function.
 */
void MotorDriver::setAccelerationProfile(char profile){
    switch (profile){
        case 1: // Linear ramp
            rampFunction = linearRamp;
            break;
        case 2: // Quadratic ramp
            rampFunction = quadraticRamp;
            break;
        case 3: // Exponential ramp
            rampFunction = exponentialRamp;
            break;
        case 4: // Logarithmic ramp
            rampFunction = logarithmicRamp;
            break;
        case 5: // Cubic ramp
            rampFunction = cubicRamp;
            break;
        case 6: // Sine wave ramp
            rampFunction = sineWaveRamp;
            break;
        case 7: // Cosine wave ease in and out ramp
            rampFunction = cosineSmoothRamp;
            break;
        default: // Default to linear if unknown profile
            rampFunction = linearRamp; 
            break;
    }
}

/**
 * @brief Handles errors and warnings related to motor driver operations.
 *
 * This function processes and handles errors and warnings encountered during motor driver operations.
 *
 * @param error The error or warning to handle.
 * @return MotorDriverError indicating the handled error or warning.
 */
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

// All ramp equations ensure for inputs in range [0, 1], the outputs are also in range [0, 1].
float linearRamp(float t){
    return t;
}

float quadraticRamp(float t){
    return t * t;
}

float exponentialRamp(float t){
    return (exp(t) - 1) / (exp(1) - 1);
}

float logarithmicRamp(float t){
    return 1 - (exp(1 - t) - 1) / (exp(1) - 1);
}

float cubicRamp(float t){
    return t * t * t;
}

float sineWaveRamp(float t){
    return sin(t * PI / 2);
}

float cosineSmoothRamp(float t) {
    return 0.5 - cos(t * PI) / 2;
}