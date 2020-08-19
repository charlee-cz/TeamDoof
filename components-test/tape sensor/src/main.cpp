#include "Arduino.h"
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET     -1 // This display does not have a reset pin accessible
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define TAPE_SENSOR PA5
#define SWITCH A7
#define MOTOR_1F PA_3
#define MOTOR_1B PA_2
#define MOTOR_2F PB_8
#define MOTOR_2B PB_9
#define MAX_MOTOR 65535
#define FREQ 1000

void disp_setup();

void setup()
{
  // initialize LED digital pin as an output.
  pinMode(TAPE_SENSOR, INPUT);
  disp_setup();
}

volatile double reflectance = 0.0;
volatile double threshold = 500.0;
volatile bool tape = false;

void loop()
{
  while(digitalRead(SWITCH) == HIGH){
    reflectance = analogRead(TAPE_SENSOR);
    
    display.clearDisplay();
    display.setCursor(0,0);
    display.println("On");
    display.display();

    if (!tape){
      pwm_start(MOTOR_1F, FREQ, MAX_MOTOR/2, RESOLUTION_16B_COMPARE_FORMAT);
      pwm_start(MOTOR_2F, FREQ, MAX_MOTOR/2, RESOLUTION_16B_COMPARE_FORMAT);
      pwm_start(MOTOR_1B, FREQ, 0, RESOLUTION_16B_COMPARE_FORMAT);
      pwm_start(MOTOR_2B, FREQ, 0, RESOLUTION_16B_COMPARE_FORMAT);
      display.println("Running");
      display.display();
    }

    if (reflectance > threshold){
      pwm_start(MOTOR_1F, FREQ, 0, RESOLUTION_16B_COMPARE_FORMAT);
      pwm_start(MOTOR_2F, FREQ, 0, RESOLUTION_16B_COMPARE_FORMAT);
      pwm_start(MOTOR_1B, FREQ, 0, RESOLUTION_16B_COMPARE_FORMAT);
      pwm_start(MOTOR_2B, FREQ, 0, RESOLUTION_16B_COMPARE_FORMAT);
      display.println("Tape Detected!");
      display.display();
      tape = true;
    }
  }
  if (digitalRead(SWITCH) == LOW){
    display.clearDisplay();
    display.setCursor(0,0);
    display.println("Off");
    display.display();
    tape = false;
  }
}

void disp_setup(){
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0,0);
}