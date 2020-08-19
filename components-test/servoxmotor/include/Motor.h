#ifndef Motor_h
#define Motor_h
#endif

#include <INIT.h>

class Motor{
    public:
        // Constructors
        Motor();
        Motor(PinName left_f, PinName left_b, PinName right_f, PinName right_b);

        // Drives motors forward
        void drive_forward(int speed);

        // Drives motors backwards
        void drive_backward(int speed);

        //
        void drive_cw();
        void drive_ccw();
        void stop();
};