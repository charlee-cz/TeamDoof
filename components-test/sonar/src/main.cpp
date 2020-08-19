#include <Arduino.h>
#include <NewPing.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET     -1 // This display does not have a reset pin accessible
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define TRIGGER_PIN  PA15  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     PB3  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

void disp_setup();

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

void setup() {
  disp_setup();iiiii
}

void loop() {
  display.clearDisplay();
  display.setCursor(0,0);
  delay(500);                     // Wait 500ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
  display.print("Ping: ");
  display.print(sonar.ping_cm()); // Send ping, get distance in cm and print result (0 = outside set distance range)
  display.println("cm");
  display.display();
}

void disp_setup(){
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0,0);
}
