#ifndef MotorDriver_h
#define MotorDriver_h

enum MotorDriverError{
    SUCCESS = 0,
    ERROR_INVALID_PWM_CUTOFF = 1,
    WARNING_INVALID_PWM_SETPOINT = 2,
    WARNING_CURRENT_PWM_SPEED_INVALID = 3
};

// Base class for motor drivers
class MotorDriver {
    public:
        virtual ~MotorDriver() {}                   // virtual destructor for cleanup
        virtual void init() = 0;                    // virtual function to initialize the motor driver
        void setSpeedPWM(int speed);    // non-virtual interface to set the motor speed using PWM values
        void stop();
        MotorDriverError setMinPWM(int PWM);
        MotorDriverError setMaxPWM(int PWM);
        int getPWM();
    protected:
        virtual void updateSpeedPWM(int speed) = 0; // protected virtual function to be implemented by derived classes
        int currentSpeedPWM = 0;                    // variable updated each time setSpeedPWM is called
        MotorDriverError handleError(MotorDriverError error);
    private:
        int minPWM = 0;         
        int maxPWM = 255;
        MotorDriverError lastError = SUCCESS;      // for logging last error
};

#endif