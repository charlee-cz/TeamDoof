#include <Motor.h>
#include <INIT.h>

/* Empty Constructor for Motor class that sets up the defined pins for output. */
Motor::Motor(){
    pinMode(MOTOR_LF, OUTPUT);
    pinMode(MOTOR_LB, OUTPUT);
    pinMode(MOTOR_RF, OUTPUT);
    pinMode(MOTOR_RB, OUTPUT);
}

/* Makes robot drive forward at a speed 
 * @param: int speed, from 1-10, speed of motor is MAX_MOTOR*speed
 */
void Motor::drive_forward(int speed){
  this->stop();
  delay(50);
  pwm_start(MOTOR_LF, FREQUENCY, MOTOR_RATIO * (4.0+(speed*0.6))/11.0*MAX_MOTOR, RESOLUTION_16B_COMPARE_FORMAT);
  pwm_start(MOTOR_RF, FREQUENCY, (4.0+(speed*0.6))/11.0*MAX_MOTOR, RESOLUTION_16B_COMPARE_FORMAT);
  }

/* Makes robot drive backward at a speed 
 * @param: int speed, from 1-10, speed of motor is MAX_MOTOR*speed/11
 */
void Motor::drive_backward(int speed){
  this->stop();
  delay(50);
  pwm_start(MOTOR_LB, FREQUENCY, MOTOR_RATIO * (4.0+(speed*0.6))/11.0*MAX_MOTOR, RESOLUTION_16B_COMPARE_FORMAT);
  pwm_start(MOTOR_RB, FREQUENCY, (4.0+(speed*0.6))/11.0*MAX_MOTOR, RESOLUTION_16B_COMPARE_FORMAT);
}

/* Makes robot rotate clockwise (right)*/
void Motor::drive_cw(){
  this->stop();
  delay(50);
  pwm_start(MOTOR_LF, FREQUENCY, MAX_MOTOR*TURN_SPEED*MOTOR_RATIO, RESOLUTION_16B_COMPARE_FORMAT);
  pwm_start(MOTOR_RB, FREQUENCY, MAX_MOTOR*TURN_SPEED, RESOLUTION_16B_COMPARE_FORMAT);
}

/* Makes robot rotate counter-clockwise (left)*/
void Motor::drive_ccw(){
  this->stop();
  delay(50);
  pwm_start(MOTOR_LB, FREQUENCY, MAX_MOTOR*TURN_SPEED*MOTOR_RATIO, RESOLUTION_16B_COMPARE_FORMAT);
  pwm_start(MOTOR_RF, FREQUENCY, MAX_MOTOR*TURN_SPEED, RESOLUTION_16B_COMPARE_FORMAT);
}

/* Makes robot rotate clockwise (right) SLOWLY*/
void Motor::drive_cw_slow(){
  this->stop();
  delay(50);
  pwm_start(MOTOR_RB, FREQUENCY, MAX_MOTOR* TURN_SPEED, RESOLUTION_16B_COMPARE_FORMAT);
}

/* Makes robot rotate counter-clockwise (left) with set speed*/
void Motor::drive_ccw_slow(){
  this->stop();
  delay(50);
  pwm_start(MOTOR_LB, FREQUENCY, MAX_MOTOR* TURN_SPEED * MOTOR_RATIO, RESOLUTION_16B_COMPARE_FORMAT);
}


/* Stops both motors*/
void Motor::stop(){
    pwm_start(MOTOR_LF, FREQUENCY,0,RESOLUTION_16B_COMPARE_FORMAT);
    pwm_start(MOTOR_LB, FREQUENCY,0,RESOLUTION_16B_COMPARE_FORMAT);
    pwm_start(MOTOR_RF, FREQUENCY,0,RESOLUTION_16B_COMPARE_FORMAT);
    pwm_start(MOTOR_RB, FREQUENCY,0,RESOLUTION_16B_COMPARE_FORMAT);
}

// Stops motor from moving backwards
void Motor::stop_back(){
  pwm_start(MOTOR_LB, FREQUENCY,0,RESOLUTION_16B_COMPARE_FORMAT);
  pwm_start(MOTOR_RB, FREQUENCY,0,RESOLUTION_16B_COMPARE_FORMAT);
}