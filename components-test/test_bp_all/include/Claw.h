#ifndef Claw_h
#define Claw_h
#endif

#include <INIT.h>

// CONSTANTS
#define SERVO_FREQ 50
#define MIN_ANGLE_PULSE 500
#define MAX_ANGLE_PULSE 2500

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

        // servo write
        void writeSmall(int degree);
        void writeBig(int degree);

    private:
        int convertSmall(int degree);
        int convertBig(int degree);
};