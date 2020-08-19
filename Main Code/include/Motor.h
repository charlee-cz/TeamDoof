#ifndef Motor_h
#define Motor_h
#endif

#include "Arduino.h"
#include "INIT.h"

class Motor{
    public:
        // Constructors
        Motor();

        // Drives motors forward
        void drive_forward(int speed);

        // Drives motors backwards
        void drive_backward(int speed);

        //
        void drive_cw();
        void drive_ccw();
        void stop();
        void stop_back();

        void drive_cw_slow();
        void drive_ccw_slow();
};