#ifndef Sensors_h
#define Sensors_h
#endif

#include <INIT.h>

class Sensors{
    public:
        // Constructors
        Sensors();
        void setup();

        // TAPE
        int on_tape(); 
        int tape_l();
        int tape_r();

        // IR
        bool ir_noise(); //returns TRUE if only reading noise, FALSE if beacon found
        int ir_error(); //returns (left - right) sensor reading
        bool ir_nearbin();
        int ir_l();
        int ir_r();
};