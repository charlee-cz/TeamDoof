#include "INIT.h"
#include "Motor.h"
#include "Claw.h"
#include "Sensors.h"

Sensors sensors;
Ultrasonic ultrasonic(TRIGGER_PIN, ECHO_PIN,15000UL);
Motor robotMotor;
Claw claw;
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
// NewPing sonar(TRIGGER_PIN,ECHO_PIN,MAX_DISTANCE);
volatile short int prev = 0;

void disp_setup();
void disp_label_value(const char *label, int value);
void disp_msg(const char *msg);
void disp_clear();
void motorRawStop();

/* TEST FUNCTIONS */
void testDrive(); // (Uses Motor.h) Tests: driving forwards, backwards, turning ccw and cw
void testDriveRaw(); // (Uses PWM) Tests: driving forwards, backwards, turning ccw and cw
void testGrabber(); // Tests //Claw opening and closing
void testArm(); // Tests arm lifting and lowering
void testClawFunctions(); // Uses //Claw.h
void testDriveAndServos(); // (Uses Motor.h)
void testDriveAndServosRaw(); // (Uses PWM)
void testSonar();
void testSonarClawArm();
void testIRreadingRaw();
void testIRreading();
void testTapeReadingRaw();
void testTapeReading();
void tapeRejectionTest();
void tapeRejectionTestSylvia();
void tapeRejectionAndPID();
void PIDtest();
void tapeRejectionAndPIDSylvia();

void setup() {
  // put your setup code here, to run once:
  pinMode(IR_LA,INPUT);
  pinMode(IR_LB,INPUT);
  pinMode(IR_RA,INPUT);
  pinMode(IR_RB,INPUT);
  pinMode(TAPE_L, INPUT_PULLUP);
  pinMode(TAPE_R, INPUT_PULLUP);

  disp_setup();
  claw.setup();
  sensors.setup();
}

void loop() {
  // CHOOSE WHICH TEST FUNCTION TO RUN:
  // NOTE: if running the raw motor test files, make sure to comment out lines 2 and 7

  disp_clear();
  // disp_msg("starting");
  
  testSonar();
}

/* COMPONENTS TEST FUNCTIONS */

// (Uses Motor.h) Tests: driving forwards, backwards, turning ccw and cw
void testDrive(){
  robotMotor.drive_forward(5);
  disp_msg("Driving forward...");
  delay(5000);
  robotMotor.drive_backward(5);
  disp_msg("Driving backward...");
  delay(3000);
  robotMotor.drive_ccw();
  disp_msg("Turning ccw...");
  delay(2000);
  robotMotor.drive_cw();
  disp_msg("Turning cw...");
  delay(2000);
} 

// (Uses PWM) Tests: driving forwards, backwards, turning ccw and cw
void testDriveRaw(){
  disp_msg("Driving forward...");
  motorRawStop();
  pwm_start(MOTOR_LF, FREQUENCY, MOTOR_RATIO*0.5*MAX_MOTOR, RESOLUTION_16B_COMPARE_FORMAT);
  pwm_start(MOTOR_RF, FREQUENCY, MOTOR_RATIO*0.5*MAX_MOTOR, RESOLUTION_16B_COMPARE_FORMAT);
  delay(5000);
  disp_msg("Driving backward...");
  motorRawStop();
  pwm_start(MOTOR_LB, FREQUENCY, MOTOR_RATIO*0.5*MAX_MOTOR, RESOLUTION_16B_COMPARE_FORMAT);
  pwm_start(MOTOR_RB, FREQUENCY, MOTOR_RATIO*0.5*MAX_MOTOR, RESOLUTION_16B_COMPARE_FORMAT);
  delay(3000);
  disp_msg("Turning ccw...");
  motorRawStop();
  pwm_start(MOTOR_LB, FREQUENCY, MOTOR_RATIO*0.7*MAX_MOTOR, RESOLUTION_16B_COMPARE_FORMAT);
  pwm_start(MOTOR_RF, FREQUENCY, 0.7*MAX_MOTOR, RESOLUTION_16B_COMPARE_FORMAT);
  delay(2000);
  disp_msg("Turning cw...");
  motorRawStop();
  pwm_start(MOTOR_LF, FREQUENCY, MOTOR_RATIO*0.7*MAX_MOTOR, RESOLUTION_16B_COMPARE_FORMAT);
  pwm_start(MOTOR_RB, FREQUENCY, 0.7*MAX_MOTOR, RESOLUTION_16B_COMPARE_FORMAT);
  delay(2000);
}

// Tests Claw opening and closing
void testGrabber(){
  claw.open();
  delay(1000);
  claw.close();
  delay(1000);
}

// // Tests arm lifting and lowering
void testArm(){
  claw.raise();
  delay(1000);
  claw.lower();
  delay(1000);
}

// (Uses Motor.h) Drives, stops, moves servos
void testDriveAndServos(){
  disp_clear();
  disp_msg("Driving...");
  robotMotor.drive_forward(4);
  delay(2000);
  robotMotor.stop();
  delay(300);
  disp_clear();
  disp_msg("Moving servos...");
  claw.close();
  claw.raise();
  claw.lower();
  claw.open();
}

// (Uses PWM) Drives, stops, moves servos
void testDriveAndServosRaw(){
  disp_clear();
  disp_msg("Driving...");
  pwm_start(MOTOR_LF, FREQUENCY, MOTOR_RATIO*0.5*MAX_MOTOR, RESOLUTION_16B_COMPARE_FORMAT);
  pwm_start(MOTOR_RF, FREQUENCY, MOTOR_RATIO*0.5*MAX_MOTOR, RESOLUTION_16B_COMPARE_FORMAT);
  delay(5000);
  motorRawStop();
  delay(300);

  disp_clear();
  disp_msg("Moving servos...");
  for (int i = 0; i < 90; i++) {
    //Claw.writeSmallServo(i);
    //Claw.writeBigServo(i);
    delay(15);
  }
  for (int i = 90; i >= 0; i--) {
    //Claw.writeSmallServo(i);
    //Claw.writeBigServo(i);
    delay(15);
  }
}

// Reads the sonar reading
void testSonar(){
  // disp_clear();
  // disp_label_value("Distance (cm): ",sonar.ping_cm());
  disp_label_value("Distance (cm): ", ultrasonic.read());
  delay(50);
  disp_label_value("Dist (in): ", ultrasonic.read(INC));
}

// Tests if servo can actuate based on servo readings
void testSonarClawArm(){
  disp_clear();
  // int distance = sonar.ping_cm();
  int distance = ultrasonic.read();
  disp_label_value("Dist (cm): ", distance);
  claw.open();
  claw.lower();

  if(distance<8 && distance>3) {
    disp_msg("Can detected!\n //Claw closing...");
    //Claw.closeClaw();
    //Claw.raiseClaw();
    delay(2000);
    disp_msg("releasing //Claw...");
    //Claw.lowerClaw();
    //Claw.openClaw();
  }
}

void testIRreadingRaw(){
  disp_clear();
  disp_label_value("LEFT IR HI: ", analogRead(IR_LA));
  disp_label_value("LEFT IR LO: ", analogRead(IR_LB));
  disp_label_value("RIGHT IR HI: ", analogRead(IR_RA));
  disp_label_value("RIGHT IR LO: ", analogRead(IR_RB));
  delay(500);
}

void testIRreading()
{
  disp_clear();
  disp_label_value("Left:", sensors.ir_l());
  disp_label_value("Right:", sensors.ir_r());
  delay(200);
}

void testTapeReadingRaw(){
  disp_clear();
  disp_label_value("Left Sensor: ",analogRead(TAPE_L));
  disp_label_value("Right Sensor: ",analogRead(TAPE_R));
  delay(500);
}

void testTapeReading()
{
  disp_clear();
  disp_label_value("Tape status:", sensors.on_tape());
  disp_label_value("Left Sensor: ",sensors.tape_l());
  disp_label_value("Right Sensor: ",sensors.tape_r());
  delay(200);
}

void tapeRejectionTest(){
  int left_reflection = sensors.tape_l();
  int right_reflection = sensors.tape_r();
  disp_label_value("left: ", left_reflection);
  disp_label_value("right: ", right_reflection);
  disp_label_value("threshold: ", TAPE_THRES);

  if (left_reflection > TAPE_THRES && right_reflection > TAPE_THRES) {
    robotMotor.drive_backward(5);
  } else if (left_reflection > TAPE_THRES){
    robotMotor.drive_cw();
  } else if (right_reflection > TAPE_THRES){
    robotMotor.drive_ccw();
  } else {
    robotMotor.drive_forward(5);
  }
}

void tapeRejectionTestSylvia(){
  int left_reflection = sensors.tape_l();
  int right_reflection = sensors.tape_r();
  disp_label_value("left: ", left_reflection);
  disp_label_value("right: ", right_reflection);
  disp_label_value("threshold: ", TAPE_THRES);

  if (left_reflection < TAPE_THRES && right_reflection < TAPE_THRES) {
    robotMotor.drive_backward(5);
  } else if (left_reflection < TAPE_THRES){
    robotMotor.drive_cw();
  } else if (right_reflection < TAPE_THRES){
    robotMotor.drive_ccw();
  } else {
    robotMotor.drive_forward(5);
  }
}

void PIDtest()
{
  int kp = 30;
  int kd = 100;
  int ki = 0;

  int P = 0;
  int D = 0;
  int I = 0;
  int G = 0;

  int err = sensors.ir_error();

  disp_clear();
  
  if (sensors.ir_nearbin()){
    // robotMotor.stop();
    disp_msg("near!");
  }
  else if (!sensors.ir_noise()) { //if not reading noise
    pwm_start(MOTOR_LB, FREQUENCY, 0, RESOLUTION_16B_COMPARE_FORMAT);

    P = kp * err;
    D = kd * (err - prev);
    I = (ki * err) + I;
    if (I > MAX_I)
      I = MAX_I;
    if (I < -MAX_I)
      I = -MAX_I;
    G = P + D + I;

    disp_label_value("gain = ",G);
    disp_label_value("Left:", sensors.ir_l());
    disp_label_value("Right:", sensors.ir_r());
    float left_speed = 4.5/10*MAX_MOTOR - G;
    float right_speed = 4.5/10*MAX_MOTOR + G;
    pwm_start(MOTOR_LF,FREQUENCY, left_speed, RESOLUTION_16B_COMPARE_FORMAT);
    pwm_start(MOTOR_RF,FREQUENCY, right_speed, RESOLUTION_16B_COMPARE_FORMAT);

    disp_label_value("Right Speed:", right_speed);
    disp_label_value("Left Speed:", left_speed);

    prev = err;
  } else {
    robotMotor.drive_ccw();
    disp_msg("searching...");
  }
}

void tapeRejectionAndPID(){
  int left_reflection = sensors.tape_l();
  int right_reflection = sensors.tape_r();

  if (left_reflection > TAPE_THRES && right_reflection > TAPE_THRES) {
    robotMotor.drive_backward(5);
  } else if (left_reflection > TAPE_THRES){
    robotMotor.drive_cw();
  } else if (right_reflection > TAPE_THRES){
    robotMotor.drive_ccw();
  } else {
    PIDtest();
  }
}

void tapeRejectionAndPIDSylvia(){
  int left_reflection = sensors.tape_l();
  int right_reflection = sensors.tape_r();

  if (left_reflection < TAPE_THRES && right_reflection < TAPE_THRES) {
    robotMotor.drive_backward(5);
  } else if (left_reflection < TAPE_THRES){
    robotMotor.drive_cw();
  } else if (right_reflection < TAPE_THRES){
    robotMotor.drive_ccw();
  } else {
    PIDtest();
  }
}

/* INTERNAL FUNCTIONS */

void motorRawStop(){
  pwm_start(MOTOR_LF, FREQUENCY,0,RESOLUTION_16B_COMPARE_FORMAT);
  pwm_start(MOTOR_LB, FREQUENCY,0,RESOLUTION_16B_COMPARE_FORMAT);
  pwm_start(MOTOR_RF, FREQUENCY,0,RESOLUTION_16B_COMPARE_FORMAT);
  pwm_start(MOTOR_RB, FREQUENCY,0,RESOLUTION_16B_COMPARE_FORMAT);
  delay(50);
}

/* DISPLAY FUNCTIONS */

void disp_setup()
{
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);

}

void disp_label_value(const char *label, int value){
  display.print(label);
  display.println(value);
  display.display();
}

void disp_msg(const char *msg) {
  display.println(msg);
  display.display();  
}

void disp_clear() {
  display.clearDisplay();
  display.setCursor(0, 0);
}