#include <Sensors.h>

Sensors::Sensors()
{
}

void Sensors::setup()
{
    pinMode(IR_LA, INPUT);
    pinMode(IR_LB, INPUT);
    pinMode(IR_RA, INPUT);
    pinMode(IR_RB, INPUT);
    pinMode(TAPE_L, INPUT_PULLUP);
    pinMode(TAPE_R, INPUT_PULLUP);
}

/**
 * 
 * Currently implementing (not completed): 
 * The return values are defined in INIT
 */
int Sensors::on_tape()
{
    int L_tape = analogRead(TAPE_L);
    int R_tape = analogRead(TAPE_R);

    // USE THIS if your competition surface is FLOOR for robot, TAPE for bounds, and WHITE for bin
    if (L_tape > UPPER_THRES && R_tape > UPPER_THRES)      // both sensors read tape
        return T_BOTH;                                     //3
    else if (L_tape > UPPER_THRES)                         //left sensors read tape
        return T_LEFT;                                     //1
    else if (R_tape > UPPER_THRES)                         // right sensors read tape
        return T_RIGHT;                                    //2
    else if (L_tape < LOWER_THRES && R_tape < LOWER_THRES) //both sensors read paper
        return P_BOTH;                                     //6
    else if (L_tape < LOWER_THRES)                         //left sensor read paper
        return P_LEFT;                                     //4
    else if (R_tape < LOWER_THRES)                         // right sensor read paper
        return P_RIGHT;                                    //5

    // USE THIS if your competition surface is FLOOR for robot, WHITE for bounds, and TAPE for bin (NOT tested use at your own peril)
    // if (L_tape > FLOOR_THRES || R_tape > FLOOR_THRES)
    //     return BORDER;
    // else if (L_tape < PAPER_THRES)
    //     return LEFT;
    // else if (R_tape < PAPER_THRES)
    //     return RIGHT;
    // else if (L_tape <= FLOOR_THRES && R_tape <= FLOOR_THRES)
    //     return NONE; //0

    return NONE; //sensors are both reading floor
}

int Sensors::tape_l()
{
    return analogRead(TAPE_L);
}

int Sensors::tape_r()
{
    return analogRead(TAPE_R);
}

/**Returns TRUE if only reading noise, FALSE if beacon found
 */
bool Sensors::ir_noise()
{
    int l_hi = analogRead(IR_LA);
    int r_hi = analogRead(IR_RA);
    // int l_lo = analogRead(IR_LB);
    // int r_lo = analogRead(IR_RB);
    // int left = 0;
    // int right = 0;

    //  For readings with the lower resistor as well:
    //     if (l_hi > ANALOG_MAX)
    //      left = l_lo;
    //    else
    //      left = l_hi;

    //    if (r_hi > ANALOG_MAX)
    //      right = r_lo;
    //    else
    //      right = r_hi;

    if (l_hi > IR_NOISE || r_hi > IR_NOISE)
        return FALSE;

    return TRUE;
}

int Sensors::ir_error()
{
    int l_hi = analogRead(IR_LA);
    int r_hi = analogRead(IR_RA);

    return l_hi - r_hi;
}

/**Returns TRUE if near beacon/bin, FALSE otherwise
 */
bool Sensors::ir_nearbin()
{
    int l_hi = analogRead(IR_LA);
    int r_hi = analogRead(IR_RA);

    if (l_hi > IR_BIN && r_hi > IR_BIN)
        return TRUE;

    return FALSE;
}

int Sensors::ir_l()
{
    return analogRead(IR_LA);
}

int Sensors::ir_r()
{
    return analogRead(IR_RA);
}
