#ifndef MotorDriver_h
#define MotorDriver_h

// Base class for motor drivers
class MotorDriver {
    public:
        virtual ~MotorDriver() {}       // virtual destructor for cleanup
        virtual void init() = 0;        // virtual function to initialize the motor driver
        void setSpeedPWM(int speed);    // non-virtual interface to set the motor speed using PWM values
        void stop();
        int getPWM();
        bool setMinPWM(int PWM);
        bool setMaxPWM(int PWM);
    protected:
        virtual void updateSpeedPWM(int speed) = 0; // protected virtual function to be implemented by derived classes
        int currentSpeedPWM = 0;        // variable updated each time setSpeedPWM is called
    private:
        int minPWM = 0;         
        int maxPWM = 255;
};

#endif