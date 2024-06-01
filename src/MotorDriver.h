#ifndef MotorDriver_h
#define MotorDriver_h

class MotorDriver {
    public:
        virtual void init() = 0;
        void setSpeedPWM(int speed);            // non-virtual interface
        void stop();
        int getPWM();
        bool setMinPWM(int PWM);
        bool setMaxPWM(int PWM);
        virtual ~MotorDriver() {}
    protected:
        virtual void updateSpeedPWM(int speed) = 0; // protected virtual function
        int currentSpeedPWM = 0;   // variable updated each time setSpeedPWM is called
    private:
        int minPWM = 0;         
        int maxPWM = 255;
};

#endif