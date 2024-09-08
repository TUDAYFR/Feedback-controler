#include "feedback.h"

void Feedback::init(){
    _sensor = MagneticSensorI2C(AS5600_I2C);
    _motor = BLDCMotor(7);
    _driver = BLDCDriver3PWM(4, 5, 6, 7); // A, B, C, E

    _sensor.init();
    _motor.linkSensor(&_sensor);
    _driver.voltage_power_supply = 12;
    _driver.voltage_limit = 4;
    _driver.init();
    _motor.linkDriver(&_driver);
    _motor.foc_modulation = FOCModulationType::SpaceVectorPWM;
    _motor.controller = MotionControlType::angle;
    _motor.P_angle.P = 20;
    _motor.velocity_limit = 20;
    _motor.init();
    _motor.initFOC();
    _stepValue = 0;
}

void Feedback::setFeedbackMode() {

    if (configs[1].feedbackMode == FeedbackMode::STEP) {
        // Configure settings for step mode
        _motor.PID_velocity.P = 0.10f;
        _motor.PID_velocity.I = 0;
        //_motor.PID_velocity.D = 0.00008f;
        _motor.PID_velocity.D = 0;

        _sP = 0.10f;
        _sI = 0;
        _sD = 0;

    } else if (configs[1].feedbackMode == FeedbackMode::SWITCH) {
        // Configure settings for switch mode
        _motor.PID_velocity.P = 0.2f;
        _motor.PID_velocity.I = 0;
        _motor.PID_velocity.D = 0.00005f;

        _sP = 0.2f;
        _sI = 0;
        _sD = 0.00005f;
    }
}


void Feedback::disable(){
    _motor.velocity_limit = 0;
}

void Feedback::enable(){
    _motor.velocity_limit = 20;
}

void Feedback::loop(){

    //processConfig();

    if (configs[1].feedbackMode == FeedbackMode::STEP) {

        _motor.loopFOC();
        float angleStep = 360.0/configs[1].stepNumber ;
        int targetAngle = round((_motor.shaft_angle*180)/(angleStep*PI))*angleStep ;
        //Serial.println(targetAngle);
        _motor.move((targetAngle*PI)/180);
        _oldTargetAngle = targetAngle;
        _stepValue = round((_motor.shaft_angle*180)/(angleStep*PI));

    } else if (configs[1].feedbackMode == FeedbackMode::SWITCH) {

        _motor.loopFOC();
        int targetAngle = round((_motor.shaft_angle*180)/(configs[1].switchAngle*PI))*configs[1].switchAngle ;
        if(targetAngle > configs[1].switchAngle){targetAngle = configs[1].switchAngle;}
        if(targetAngle < 0){targetAngle = 0;}
        //Serial.println(targetAngle);
        _motor.move((targetAngle*PI)/180);
        _oldTargetAngle = targetAngle;

    }
}


void Feedback::setSwitchAngle(int angle){
    _switchAngle = angle;
}


void Feedback::click(boolean e,int strenght){ // e is a boolean in = 1 out  = 0
    int currentpos = _motor.shaft_angle;
    if(e != _oldE){
        if(e == true){
            
            for(int i=0 ; i< 3 ; i++){
                _motor.move(strenght);
                _motor.loopFOC();
            }
        }else{
            
            for(int i=0 ; i< 4 ; i++){
                _motor.move(-strenght);
                _motor.loopFOC();
            }
        }
    }
    _oldE = e ;
}

void Feedback::setConfig(MotorConfig newConfig){
    configs[1] = newConfig;
}


/*void Feedback::useAffichageQueue(QueueHandle_t queue) {
    feedbackQueue = queue;
    MotorConfig config;
    if (xQueueReceive(feedbackQueue, &config, portMAX_DELAY) != pdPASS) {
        // Queue receive failed, handle the situation
        Serial.println(" Queue receive failed"); 
       }else{
        Serial.println(" Queue receive"); 
       }
    // Use the received MotorConfig...
}*/

/*void Feedback::processConfig() {
    MotorConfig receivedConfig;

    // Try to receive the first item from the queue
    if (uxQueueMessagesWaiting(feedbackQueue) > 0) {
        // If there are items in the queue, receive the first one
        if (xQueueReceive(feedbackQueue, &receivedConfig, 0) == pdPASS) {
            // Set the motorConfig to the received config
            configs[1] = receivedConfig;
            // Optionally, process or perform operations with the received config here
        } else {
            // Queue receive failed, handle the situation
        }
    }
}*/