#ifndef FEEDBACK_H
#define FEEDBACK_H

#include <string>
#include <SimpleFOC.h>

enum class FeedbackMode {
    STEP,
    SWITCH
};

struct MotorConfig {
    int stepNumber;
    int switchAngle;
    bool enable;
    FeedbackMode feedbackMode;
};

class Feedback {
public:
    Feedback() : _sensor(AS5600_I2C), // Assuming AS5600_I2C_ADDRESS is the address constant
                 _driver(4, 5, 6, 7),        // A, B, C, E pins
                 _motor(7) {                // Pin number for the motor
    }
    void init();
    void setFeedbackMode();
    void disable();
    void enable();
    void loop(); 
    //void setStepNumber(int step);
    void setSwitchAngle(int angle);
    void click(boolean e,int strenght);

    //void useAffichageQueue(QueueHandle_t queue); // Function to use the feedBackConfigQueue
    //void processConfig();

private:
    MagneticSensorI2C _sensor;
    BLDCDriver3PWM _driver;

    int _switchAngle;
    boolean _oldTargetAngle;

    float _sP;
    float _sI;
    float _sD;

    int _oldE;
    
public:
    BLDCMotor _motor;
    int _stepValue;
    void setConfig(MotorConfig newConfig);

    MotorConfig configs[1] = {
        {10, 10, false,FeedbackMode::STEP} // Initialize the first element
    };
};

#endif