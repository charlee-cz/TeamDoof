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
 * Returns 0 for NONE on tape, 1 for LEFT on tape, 2 for RIGHT on Tape, 3 for BOTH on tape
 * The return values are defined in INIT
 */
int Sensors::on_tape() 
{
    int L_tape = analogRead(TAPE_L);
    int R_tape = analogRead(TAPE_R);

    if (L_tape <= TAPE_THRES && R_tape <= TAPE_THRES)
        return NONE; //0
    else if (L_tape > TAPE_THRES) 
        return LEFT;
    else if (R_tape > TAPE_THRES)
        return RIGHT;

    return BOTH;
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

//   For Double readings:
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
