#ifndef Claw_h
#define Claw_h
#endif

#include <INIT.h>

// CONSTANTS
#define SERVO_FREQ 50
#define MIN_ANGLE_PULSE 500
#define MAX_ANGLE_PULSE 2500

// const int closepos = CLOSEPOS;
// const int openpos = OPENPOS;
// const int speedsmall = SPEED_SMALL;
// const int downpos = DOWNPOS;
// const int uppos = UPPOS;
// const int speedbig = SPEED_BIG;

class Claw{
    public:
        // Constructors
        Claw();

        // Sets up the claw
        void setup();

        // claw motions
        void open();
        void close();
        void raise();
        void lower();
        void reset();

        // servo write
        void writeSmall(int degree);
        void writeBig(int degree);

    private:
        int convertSmall(int degree);
        int convertBig(int degree);
};