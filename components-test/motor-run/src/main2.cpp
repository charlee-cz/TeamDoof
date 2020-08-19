#include <Arduino.h>
#include <NewPing.h>
#include <Adafruit_SSD1306.h>
#include <Motor.h>
#include <algorithm>
using namespace std;

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


void disp_setup(); // sets up the display
void disp_dist(int distance); // prints to the display the distance

int search(); // 1st stage: searches for and returns the distance of closest can
void orient(int min); // 2nd stage: orients the robot to point to the closest can
void approach(); // 3rd stage: approaches the can 

Motor robotMotor;
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

void setup() {
  disp_setup();
}

void loop() {
    display.println("STARTING SEARCH...");
    display.display();
    delay(2000);
    display.clearDisplay();

    int min = search();
    orient(min);
    display.clearDisplay();
    display.println("CAN LOCATED. STARTING APPROACH...");
    display.display();
    delay(2000);

    approach();
    display.clearDisplay();
    display.println("ROBOT IS AT THE CAN.");
    display.display();
    delay(5000);
}


// FUNCTIONS //
int search(){
    int distances[50];
    robotMotor.drive_ccw();
    delay(1000);
    robotMotor.stop(); // positions the robot to start the sweep
    for (int i = 0; i < 50; i++){
        distances[i] = sonar.ping_cm();
        robotMotor.drive_cw();
        delay(30);
        robotMotor.stop();
        delay(10);
    }
    // finds the minimum distance
    std::pair<int*,int*>minmax = std::minmax_element(std::begin(distances), std::end(distances));
    int min = *minmax.first;
    return min;
}

void orient(int min){
    int distance = sonar.ping_cm();
    while (distance > min){
        disp_dist(distance);
        robotMotor.drive_ccw();
        delay(30);
        robotMotor.stop();
        delay(10);
        distance = sonar.ping_cm();
    }
    return;
}

void approach(){
    int distance = sonar.ping_cm();
    while (distance > 25) {
        robotMotor.drive_forward(8);
        delay(100);
        distance = sonar.ping_cm();
        disp_dist(distance);
    }
    robotMotor.stop();
    while (distance > 12) {
        robotMotor.drive_forward(1);
        delay(100);
        distance = sonar.ping_cm();
        disp_dist(distance);
    }
    robotMotor.stop();
    return;
}

void disp_setup(){
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0,0);
}

void disp_dist(int distance){
    display.clearDisplay();
    display.print("Distance: ");
    display.print(distance);
    display.println(" cm");
    display.display();
}