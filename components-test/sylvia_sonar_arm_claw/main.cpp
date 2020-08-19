#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <NewPing.h>
#include <servo.h>
#include <Arduino.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET     -1 // This display does not have a reset pin accessible
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define TRIGGER_PIN  PB5  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     PB4  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

#define servoPinBlue PA7
#define maxAngleBlue 180

#define servoPinGrey PA8
#define maxAngleGrey 120

#define closePos 0 // check that your servo is oriented this way - it may be the opposite
#define openPos (maxAngleBlue-1)
#define downPos 0
#define upPos 90

void disp_setup();
void disp_dist(long dist);
void openClaw(int blueServoPos);
void closeClaw(int blueServoPos);
void lowerClaw(int greyServoPos);
void raiseClaw(int greyServoPos);

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.
Servo blueServo;
Servo greyServo;

long distance = -1;
int blueServoPos = -1;
int greyServoPos = -1;

void setup() {
  blueServo.attach(servoPinBlue);
  greyServo.attach(servoPinGrey);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  // Displays Adafruit logo by default. call clearDisplay immediately if you don't want this.
  display.display();
  delay(2000);
}

void loop() {
  disp_setup();
  delay(500);                     // Wait 500ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
  distance = sonar.ping_cm();
  disp_dist(distance);

  blueServoPos = blueServo.read();
  greyServoPos = greyServo.read();
  display.println(blueServoPos);
  display.println(greyServoPos);
  display.display();

  // claw should always be open and arm should always be down unless it is grabbing can
  if (blueServoPos != openPos) {
    openClaw(blueServoPos);
    blueServoPos = openPos;
  }
  if (greyServoPos != downPos) {
    lowerClaw(greyServoPos);
    greyServoPos = downPos;
  }

  // if can is in range, grab can and raise arm and hold on to it for 3 seconds, then release
  if(distance<8 && distance>3) {
    display.println("Can detected!\n Claw closing...");
    display.display();
    closeClaw(blueServoPos);
    blueServoPos = closePos;
    raiseClaw(greyServoPos);
    greyServoPos = upPos;
    delay(3000);
    display.println("releasing claw...");
    display.display();
    lowerClaw(greyServoPos);
    openClaw(blueServoPos);
  }
}


// FUNCTIONS // 

void openClaw(int blueServoPos){
  for (int pos = blueServoPos; pos <= openPos; pos++){
    blueServo.write(pos);
    delay(5);
  }
  return;
}

void closeClaw(int blueServoPos){
  if (blueServoPos!=openPos) {
    openClaw(blueServoPos);
  }
  for (int pos = openPos; pos >= closePos; pos--) {
    blueServo.write(pos);
    delay(5);
  }
  return;
}

void lowerClaw(int greyServoPos) { 
  for (int pos = greyServoPos; pos >= downPos; pos--) {
    greyServo.write(pos);
    delay(15);
  }
  return;
}

void raiseClaw(int greyServoPos) {
  for (int pos = greyServoPos; pos <= upPos; pos++){
    greyServo.write(pos);
    delay(15);
  }
}

void disp_setup() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0,0);
}

void disp_dist(long dist){
  display.print("Ping distance: ");
  display.print(dist); // Send ping, get distance in cm and print result (0 = outside set distance range)
  display.println("cm");
  display.display();
}





