#include <Display.h>
#include <INIT.h>

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

/* Empty Constructor for Display class that initializes the Adafruit SSD1306 */
Display::Display() {
    // Empty constructor because it is not necessary.
}

/* Clears the Adafruit Display and resets the cursor postiion
 */
void Display::setup() {
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
} 

/* Clears the Adafruit Display and resets the cursor postiion
 */
void Display::clear() {
  display.clearDisplay();
  display.setCursor(0, 0);
} 

/* Writes a given string on the display and enters a new line
 * @param: const char *s, the character array that is to be printed on the display
 */
void Display::println(const char *s) {
    display.println(s);
    display.display();
}

/* Writes a given integer on the display and enters a new line
 * @param: int num, the integer that is to be printed on the display
 */
void Display::println(int num) {
    display.println(num);
    display.display();
}

/* Writes a given double on the display and enters a new line
 * @param: double num, the double that is to be printed on the display
 */
void Display::println(double num) {
    display.println(num);
    display.display();
}

/* Writes a given string on the display
 * @param: const char *s, the character array that is to be printed on the display
 */
void Display::print(const char *s) {
    display.print(s);
    display.display();
}

/* Writes a given integer on the display
 * @param: int num, the integer that is to be printed on the display
 */
void Display::print(int num) {
    display.print(num);
    display.display();
}

/* Writes a given double on the display
 * @param: double num, the double that is to be printed on the display
 */
void Display::print(double num) {
    display.print(num);
    display.display();
}

/* Writes a tag and its value on the display
 * @param: const char *tag, a character array to print on the display.display.
 *         int value, the value corresponding to the given label
 */
void Display::taggedValue(const char *tag, int value) {
    display.print(tag);
    display.println(value);
    display.display();
}
