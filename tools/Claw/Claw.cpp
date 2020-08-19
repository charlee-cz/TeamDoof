#include <Claw.h>

/* empty constructor
 */
Claw::Claw(){}

void Claw::setup(){
  pinMode(SMALLSERVO_PIN,OUTPUT);
  pinMode(BIGSERVO_PIN,OUTPUT);
}

/* Opens the claw
 */
void Claw::open(){
  if(closepos < openpos) {
    for (int i = closepos; i <= openpos; i+=speedsmall){
      writeSmall(i);
    }
  } else{
    for (int i = closepos; i >= openpos; i-=speedsmall){
      writeSmall(i);
    }
  }
}

/* Closes the claw
 */
void Claw::close(){
  if(openpos > closepos) {
    for (int i = openpos; i >= closepos; i-=speedsmall){
      writeSmall(i);
    }
  } else{
    for (int i = openpos; i <= closepos; i+=speedsmall){
      writeSmall(i);
    }
  }
}

/* Raises the claw
 */
void Claw::raise(){
  if(downpos < uppos) {
    for (int i = downpos; i <= uppos; i+=speedbig){
      writeBig(i);
    }
  } else{
    for (int i = downpos; i >= uppos; i-=speedbig){
      writeBig(i);
    }
  }
}

/* Lowers the claw
 */
void Claw::lower(){
  if(uppos > downpos) {
    for (int i = uppos; i >= downpos; i-=speedbig){
      writeBig(i);
    }
  } else{
    for (int i = uppos; i <= downpos; i+=speedbig){
      writeBig(i);
    }
  }
}

/* Moves the small servo a specified position
@param int degree, the degree of the position to move the small servo 
 */
void Claw::writeSmall(int degree){
  pwm_start(SMALLSERVO_PIN, SERVO_FREQ, 0, TimerCompareFormat_t::MICROSEC_COMPARE_FORMAT);
}

/*Moves the big servo a specified position
@param int degree, the degree of the position to move the big servo 
 */
void Claw::writeBig(int degree){
  pwm_start(BIGSERVO_PIN, SERVO_FREQ, 0, TimerCompareFormat_t::MICROSEC_COMPARE_FORMAT);
}

/* Converts the input degree into the pulse width in microseconds to use in pwm_start for the small servo
@param int degree, the degree to be converted
 */
int Claw::convertSmall(int degree){
  if (degree <= 0) {
    return MIN_ANGLE_PULSE;
  }
  if (degree >= MAXANGLE_SMALL) {
    return MAX_ANGLE_PULSE;
  }
  return degree*(MAX_ANGLE_PULSE - MIN_ANGLE_PULSE)/MAXANGLE_SMALL+MIN_ANGLE_PULSE;
}

/* Converts the input degree into the pulse width in microseconds to use in pwm_start for the big servo
@param int degree, the degree to be converted
 */
int Claw::convertBig(int degree){
  if (degree <= 0) {
    return MIN_ANGLE_PULSE;
  }
  if (degree >= MAXANGLE_BIG) {
    return MAX_ANGLE_PULSE;
  }
  return degree*(MAX_ANGLE_PULSE - MIN_ANGLE_PULSE)/MAXANGLE_BIG+MIN_ANGLE_PULSE;
}