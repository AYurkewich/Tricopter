/*
 * File:   Cmain.c
 * Author: Dan
 *
 * Created on March 1, 2013, 10:15 AM
 */


#include "xc.h"

int main(void) {
    PORTA = 0xff;
    TRISA = 0;      //Switches all PORTA pins to output

    return 0;
}
