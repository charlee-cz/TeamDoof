#ifndef Claw_h
#define Claw_h

#include "Arduino.h"
#include "Servo.h"
#include "NewPing.h"

// For Sonar on Claw
#define TRIGGER_PIN PB5
#define ECHO_PIN PB4
#define MAX_DISTANCE 320

// For Claw Servo
#define servoClawPin PA7
#define clawMaxAngle 120
#define clawSpeed 2

// For Arm Servo
#define servoArmPin PA8
#define armMaxAngle 100

Class Claw(){
    public:
        void open(int speed);
        void close(int speed);
        void open();
        void close();
        int read_sonar();
    private:
        NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);
        Servo clawServo;
        Servo armServo;
        volatile int position;
}