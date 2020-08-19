#ifndef INIT_h
#define INIT_h
#endif

/* MAIN HEADER FILE
** - Includes ALL pin variables
** - Includes all other header files
** - 
*/

#include "Wire.h"
#include "Arduino.h"
#include <Ultrasonic.h>
#include <Adafruit_SSD1306.h>
// #include <Servo.h>
// #include <NewPing.h>

/* NOTE
** Pin notation:
** Use underscore for analog (?)
*/

// Motor Pins
#define MOTOR_LF PB_8 //left
#define MOTOR_LB PB_9 //left
#define MOTOR_RF PA_3 //right
#define MOTOR_RB PA_2 //right

// Motor Parameters
#define MAX_MOTOR 65535
#define MOTOR_RATIO 1  // RIGHT/LEFT
#define FREQUENCY 500

// Sonar Parameters
#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

// For Claw Servo
#define SMALLSERVO_PIN PA_7

// For Arm Servo
#define BIGSERVO_PIN PA_8

// Servo Parameters
#define MAXANGLE_SMALL 120
#define MAXANGLE_BIG 180
#define CLOSEPOS (MAXANGLE_SMALL-1) // check that your servo is oriented this way - it may be the opposite
#define OPENPOS 0
#define DOWNPOS 75
#define UPPOS 115

// Display Settings
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET     -1 // This display does not have a reset pin accessible


//BLUEPILL INPUTS//////////////////////////////////////////////////////////////////////////////////////////////////////////

// For Sonar
#define TRIGGER_PIN PB5
#define ECHO_PIN PB4
#define TIMEOUT 15000UL // 15000UL has range of approx. 105 inches, 20000UL is default and range of ~3m; maxed at 40 ms for 6.8m

// IR Sensors
#define IR_LA PB1
#define IR_LB PB0
#define IR_RA PA1
#define IR_RB PA0

// Tape Sensors
#define TAPE_L PA5
#define TAPE_R PA4

// Control
#define SWITCH PB14
#define BUTTON PB13