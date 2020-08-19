#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET     -1 // This display does not have a reset pin accessible
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define IR_leftA PB_1
#define IR_leftB PB0
#define IR_rightA PB1
#define IR_rightB PB0

volatile int threshold = 100;
volatile int left_high = 0;
volatile int left_low = 0;

void disp_setup();
void disp_reset();

void setup() {
  pinMode(IR_leftA, INPUT);
  pinMode(IR_leftB, INPUT);
  disp_setup();
  Serial.begin(9600);
}

void loop() {
  disp_reset();
  left_high = analogRead(IR_leftA);
  left_low = analogRead(IR_leftB);
  
  display.print("High: ");
  display.println(left_high);
  display.print("Low: ");
  display.println(left_low);
  display.display();
}


void disp_setup(){
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0,0);
}

void disp_reset(){
  delay(300);
  display.clearDisplay();
  display.setCursor(0,0);
}