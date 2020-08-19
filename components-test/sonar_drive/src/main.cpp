#include <Arduino.h>
#include <NewPing.h>
#include <Adafruit_SSD1306.h>
#include <Motor.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET     -1 // This display does not have a reset pin accessible
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define TRIGGER_PIN  PA15  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     PB3  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.
#define CLAWDISTANCE 12  // The ideal distance for the claw to be away from the sonar.

#define CONSTANT1 0.5
#define CONSTANT2 0.5

Motor robotMotor;

void disp_setup();
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.


void setup() {
  disp_setup();
}

int last_error = 0;
void loop() {

  int set_number = 12; //value for ur ur sonar to pick up can (cm)
  int sonar_reading = sonar.ping_cm();
  int error = set_number - sonar_reading;  //-ve if too far from can, +ve if too close
  int P = CONSTANT1 * error;
  int D = CONSTANT2 * (error-last_error);

  if (set_number == sonar_reading) {
    robotMotor.stop();
  }

  last_error = error;
  int gain = P + D; //somehow make sure gain is an int from 1-100

  if (gain > 1) {
    robotMotor.drive_backward(gain);
  }
  if (gain < -2) {
    robotMotor.drive_forward(-gain);
  }

  display.clearDisplay();
  display.setCursor(0,0);
  delay(500);
  display.print("distance: ");
  display.println(sonar.ping_cm());
  display.display();

}

void disp_setup(){
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0,0);
}
