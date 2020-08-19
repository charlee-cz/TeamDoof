#include <Arduino.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET     -1 // This display does not have a reset pin accessible
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define SWITCH A7
#define POT_IN PA_5
#define MOTOR_1F PA_3
#define MOTOR_1B PA_2
#define MOTOR_2F PB_8
#define MOTOR_2B PB_9
#define MAX_MOTOR 65535
#define FREQ 1000
#define OFFSET 10

#define DEFAULT_DUTY 50

void disp_setup();
void motor_duty(PinName pin, double percent);
int change_speed();

volatile int pot_percent;
volatile double pot_val;
volatile int speed;
volatile double percent;

void setup() {
  // put your setup code here, to run once:
  pinMode(POT_IN, INPUT);
  pinMode(MOTOR_1F, OUTPUT);
  pinMode(MOTOR_1B, OUTPUT);
  pinMode(MOTOR_2F, OUTPUT);
  pinMode(MOTOR_2B, OUTPUT);
  pinMode(SWITCH, INPUT_PULLDOWN);

  disp_setup();
  Serial.begin(9600);
}

//not working with display lol

void loop() {
  while(digitalRead(SWITCH) == HIGH){
    speed = change_speed();
    percent = (double)speed/100.0;
    pwm_start(MOTOR_1F, FREQ, percent*MAX_MOTOR, RESOLUTION_16B_COMPARE_FORMAT);
    pwm_start(MOTOR_2F, FREQ, percent*MAX_MOTOR, RESOLUTION_16B_COMPARE_FORMAT);
    display.print("Forward...");
    display.display();
    delay(10000);
    motor_duty(MOTOR_1F, 0);
    motor_duty(MOTOR_2F, 0);

    if (digitalRead(SWITCH)== LOW){
      break;
    }

    speed = change_speed();
    percent = (double)speed/100.0;
    pwm_start(MOTOR_1B, FREQ, percent*MAX_MOTOR, RESOLUTION_16B_COMPARE_FORMAT);
    pwm_start(MOTOR_2B, FREQ, percent*MAX_MOTOR, RESOLUTION_16B_COMPARE_FORMAT);
    display.print("Backward...");
    display.display();
    delay(10000);
    motor_duty(MOTOR_1B, 0);
    motor_duty(MOTOR_2B, 0);
  }

  if(digitalRead(SWITCH) == LOW){
    display.clearDisplay();
    display.setCursor(0,0);
    display.print("OFF");
    display.display();
    delay(500);
  }

}

void disp_setup(){
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0,0);
}

void motor_duty(PinName pin, double percent){
  percent = percent/100;
  Serial.println(percent);
  Serial.println(percent*MAX_MOTOR);
  pwm_start(pin, FREQ, percent*MAX_MOTOR, RESOLUTION_16B_COMPARE_FORMAT);
}

int change_speed(){
  display.clearDisplay();
  display.setCursor(0,0);
  pot_val = analogRead(POT_IN);
  pot_percent = (pot_val/1024*100)-OFFSET;

  display.println("Speed (in duty %): ");
  display.println(pot_percent);
  return pot_percent;
}


/* 
if (digitalRead(SWITCH)== LOW){
    Serial.println("OFF");
    delay(1000);
  } else if (digitalRead(SWITCH)== HIGH) {
    display.clearDisplay();
    display.print("Pot Value: ");
    display.println(pot_val);
    display.print("MOTOR 1 DUTY: ");
    display.println(DEFAULT_DUTY);
    display.print("MOTOR 2 DUTY: ");
    display.println(pot_percent);
    display.display();
  }
*/