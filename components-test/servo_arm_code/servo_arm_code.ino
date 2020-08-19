/* Sweep
 by BARRAGAN <http://barraganstudio.com>
 This example code is in the public domain.

 modified 8 Nov 2013
 by Scott Fitzgerald
 http://www.arduino.cc/en/Tutorial/Sweep
*/

#include <Servo.h>

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int pos = 0;    // variable to store the servo position
int start = 0;
int last = 60;
int increment = 5;

const int pullPin = 2;
int pullButton = 0;
const int pushPin = 3;
int pushButton =0;

void setup() {
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  pinMode(pullPin, INPUT);
  pinMode(pushPin, INPUT);
}

void loop() {
  pullButton = digitalRead(pullPin);
  Serial.println(pullButton);
  if(pullButton==HIGH){
    for (pos = start; pos <= last; pos += increment) { // goes from 0 degrees to 180 degrees
      // in steps of 1 degree
      myservo.write(pos);              // tell servo to go to position in variable 'pos'
      delay(15);                       // waits 15ms for the servo to reach the position
    }
  }
  pushButton = digitalRead(pushPin);
  if(pushButton==HIGH){
    for (pos = last; pos >= start; pos -= increment) { // goes from 0 degrees to 180 degrees
      // in steps of 1 degree
      myservo.write(pos);              // tell servo to go to position in variable 'pos'
      delay(15);                       // waits 15ms for the servo to reach the position
    }
  }
}
