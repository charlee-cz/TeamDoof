#include <Claw.h>

Claw::Claw(){
  clawServo.attach(servoClawPin);
  armServo.attach(servoArmPin);
}

/* Opens the claw at a given angle per 15 ms.
 * @param: speed is an integer providing the increment of servo rotation
 */
void Claw::open(int speed){
    position = clawServo.read();
    if (position <= clawMaxAngle - 6){
        for (int i = position; i < clawMaxAngle-1; i+= speed ){
            clawServo.write(i);
            delay(15);
        }
    }
}

/* Closes the claw at a given angle per 15 ms.
 * @param: speed is an integer providing the increment of servo rotation
 */
void Claw::close(int speed){
  position = clawServo.read();
  if (position >= 6) {
    for (int i = position; i > 0; i-=speed){
      clawServo.write(i);
      delay(15);
    }
  }
}

/* Opens the claw at a predetermined speed
 */
void Claw::open(){
    position = clawServo.read();
    if (position <= clawMaxAngle - 6){
        for (int i = position; i < clawMaxAngle-1; i+= clawSpeed ){
            clawServo.write(i);
            delay(15);
        }
    }
}

/* Closes the claw at a predetermined speed
 */
void Claw::close(){
  position = clawServo.read();
  if (position >= 6) {
    for (int i = position; i > 0; i-=clawSpeed){
      clawServo.write(i);
      delay(15);
    }
  }
}