#include "INIT.h"
#include <Motor.h>
#include <Display.h>

Motor robotMotor;
Display disp;

// CONSTANTS FOR INIT.h
#define SPEED_SMALL 5
#define SPEED_BIG 1

// CONSTANTS FOR Claw.h
#define SERVO_FREQ 50
#define MIN_ANGLE_PULSE 500
#define MAX_ANGLE_PULSE 2500

const int closepos = CLOSEPOS;
const int openpos = OPENPOS;
const int speedsmall = SPEED_SMALL;
const int downpos = DOWNPOS;
const int uppos = UPPOS;
const int speedbig = SPEED_BIG;

// PUBLIC
void openClaw();
void closeClaw();
void raiseClaw();
void lowerClaw();

void writeSmall(int degree);
void writeBig(int degree);

void stopSmallPWM();
void stopBigPWM();

// PRIVATE
int convertSmall(int degree);
int convertBig(int degree);

// void writeUp(int start, int end, int interval, int big); // end is inclusive, 0 is small, 1 is big 
// void writeDown(int start, int end, int interval, int big); // end is inclusive, 0 is small, 1 is big


void setup() {
  disp.setup();
  pinMode(SMALLSERVO_PIN,OUTPUT); // small servo
  pinMode(BIGSERVO_PIN,OUTPUT); // big servo
  disp.println("Starting in 2...");
  delay(2000);
  disp.clear();
}

void loop() {
  // disp.clear();
  // disp.println("testing motors...");
  // robotMotor.drive_ccw();
  // delay(1000);
  // robotMotor.stop();
  // disp.clear();

  // for (int i = downpos; i <= uppos; i+=speedbig){
  //   writeBig(i);
  // }
  // //stopBigPWM();
  // delay(5000);
  // for (int i = uppos; i >= downpos; i-=speedbig){
  //   writeBig(i);
  // }
  // //stopBigPWM();
  // delay(3000);

  disp.println("Closing");
  closeClaw();
  delay(1000);
  disp.clear();

  disp.println("Raising");
  raiseClaw();
  delay(1000);
  disp.clear();

  disp.println("Lowering");
  lowerClaw();
  delay(1000);
  disp.clear();  

  disp.println("Opening");
  openClaw();
  delay(1000);
  disp.clear();
}

void openClaw(){
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

void closeClaw(){
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

void raiseClaw(){
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

void lowerClaw(){
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

void writeSmall(int degree){
  pwm_start(SMALLSERVO_PIN, SERVO_FREQ, convertSmall(degree), TimerCompareFormat_t::MICROSEC_COMPARE_FORMAT);
}
void writeBig(int degree){ 
  pwm_start(BIGSERVO_PIN, SERVO_FREQ, convertBig(degree), TimerCompareFormat_t::MICROSEC_COMPARE_FORMAT);
}

void stopSmallPWM(){
  pwm_start(SMALLSERVO_PIN, SERVO_FREQ, 0, TimerCompareFormat_t::MICROSEC_COMPARE_FORMAT);
}

void stopBigPWM(){
  pwm_start(BIGSERVO_PIN, SERVO_FREQ, 0, TimerCompareFormat_t::MICROSEC_COMPARE_FORMAT);
}

// end is inclusive
// void writeUp(int start, int end, int interval, int big){
//   for(int i = start; i <= end; i+=interval){
//     if(big == 0){
//       disp.clear();
//       writeSmall(i);
//       delay(100);
      
//     } else{
//       writeBig(i);
//     }
//   }
// }

// void writeDown(int start, int end, int interval, int big){
//   for(int i = start; i >= end; i-=interval){
//     if(big==0){
//       writeSmall(i);
//     } else{
//       writeBig(i);
//     }
//   }
// }

// these assume linear angle and pulse time relationship across the range
int convertSmall(int degree){
  if (degree <= 0) {
    return MIN_ANGLE_PULSE;
  }
  if (degree >= 179) {
    return MAX_ANGLE_PULSE;
  }
  return degree*(MAX_ANGLE_PULSE - MIN_ANGLE_PULSE)/180+MIN_ANGLE_PULSE;
}

int convertBig(int degree){
  if (degree <= 0) {
    return MIN_ANGLE_PULSE;
  }
  if (degree >= 119) {
    return MAX_ANGLE_PULSE;
  }
  return degree*(MAX_ANGLE_PULSE - MIN_ANGLE_PULSE)/120+MIN_ANGLE_PULSE;
}


