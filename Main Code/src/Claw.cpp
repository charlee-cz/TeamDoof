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
  if(CLOSEPOS < OPENPOS) {
    for (int i = CLOSEPOS; i <= OPENPOS; i+=SPEED_SMALL){
      writeSmall(i);
    }
  } else{
    for (int i = CLOSEPOS; i >= OPENPOS; i-=SPEED_SMALL){
      writeSmall(i);
    }
  }
}

/* Closes the claw
 */
void Claw::close(){
  if(OPENPOS > CLOSEPOS) {
    for (int i = OPENPOS; i >= CLOSEPOS; i-=SPEED_SMALL){
      writeSmall(i);
      delay(15);
    }
  } else{
    for (int i = OPENPOS; i <= CLOSEPOS; i+=SPEED_SMALL){
      writeSmall(i);
      delay(15);
    }
  }
}

/* Raises the claw
 */
void Claw::raise(){
  if(DOWNPOS < UPPOS) {
    for (int i = DOWNPOS; i <= UPPOS; i+=SPEED_BIG){
      writeBig(i);
      delay(15);
    }
  } else{
    for (int i = DOWNPOS; i >= UPPOS; i-=SPEED_BIG){
      writeBig(i);
      delay(15);
    }
  }
}

/* Lowers the claw
 */
void Claw::lower(){
  if(UPPOS > DOWNPOS) {
    for (int i = UPPOS; i >= DOWNPOS; i-=SPEED_BIG){
      writeBig(i);
      delay (25);
    }
  } else{
    for (int i = UPPOS; i <= DOWNPOS; i+=SPEED_BIG){
      writeBig(i);
      delay(15);
    }
  }
}

/** Default pos for search
 */
void Claw::reset(){
  writeSmall(OPENPOS);
  writeBig(DOWNPOS);
}

/* Moves the small servo a specified position
@param int degree, the degree of the position to move the small servo 
 */
void Claw::writeSmall(int degree){
  pwm_start(SMALLSERVO_PIN, SERVO_FREQ, convertSmall(degree), TimerCompareFormat_t::MICROSEC_COMPARE_FORMAT);
}

/*Moves the big servo a specified position
@param int degree, the degree of the position to move the big servo 
 */
void Claw::writeBig(int degree){
  pwm_start(BIGSERVO_PIN, SERVO_FREQ, convertBig(degree), TimerCompareFormat_t::MICROSEC_COMPARE_FORMAT);
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
  if (degree >= MAXANGLE_BIG-1) {
    return MAX_ANGLE_PULSE;
  }
  return degree*(MAX_ANGLE_PULSE - MIN_ANGLE_PULSE)/MAXANGLE_BIG+MIN_ANGLE_PULSE;
}