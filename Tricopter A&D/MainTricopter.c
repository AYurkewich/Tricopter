/**************************************
Notes: Using References in case board is not level when on copter
Only use Refs when it is actually on the copter, otherwise make sure to program it flat




**************************************/

//#include <p33FJ32MC202.h>
#define FCY 40000000
#include "libpic30.h" //allows delay function
#include <TIME.H>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "Micros_h_File.h"
#include "Init_Declarations.h" //By calling ACCELGYRO, you also call the Init declarations in its include
//Could also test deleting this from I2CBBTricopter.
#include "Configutation_Bits_File.h"
//#include "Init_PWM.inc"


//A2 is blue, A3 is red

void testBlink(void);
void blinkRed(void);
void blinkYellow(void);
void blinkBothAlt(void);
void blinkBothSim(int);
void blinkOff(void);
void blinkOn(void);
void turnYellow(void);
void turnRed(void);
void turnBoth(void);
void go(void);
void blinkPort(void);
extern double AccXavg;
extern double AccYavg;
extern double AccZavg;
extern double Tempavg;
extern double GyroXavg;
extern double GyroYavg;
extern double GyroZavg;

extern int motor1, motor2, motor3, motor4, motor5, motor6;

double DistX, DistY, DistZ;
int j;

int main() {

//OSCILLATOR SETUP//
    // setup internal clock for 80MHz/40MIPS
    // 7.37/2=3.685*43=158.455/2=79.2275
    CLKDIVbits.PLLPRE = 0; // PLLPRE (N2) 0=/2
    PLLFBD = 41; // pll multiplier (M) = +2
    CLKDIVbits.PLLPOST = 0; // PLLPOST (N1) 0=/2
    while (!OSCCONbits.LOCK); // wait for PLL ready
    AD1PCFGL = 0xFFFF; // disable analog function on pins
    // I'm a dinosaur!!!!!!
    //init_ADC(); // ADC Setup
    //init_DAC_Comparators();
    //------------------------------
    //__enable_interrupt();
    //ADCONbits.ADON = 1;                 // Enable the ADC

    /*Enable Interrupts

    PIE1_MASK1 EQU B?01101010? ; This is the Interrupt Enable
	: ; Register mask value
	:
	CLRF STATUS ; Bank0
	CLRF INTCON ; Disable interrupts and clear some flags
	CLRF PIR1 ; Clear all flag bits
	BSF STATUS, RP0 ; Bank1
	MOVLW PIE1_MASK1 ; This is the initial masking for PIE1
	MOVWF PIE1 ;
	BCF STATUS, RP0 ; Bank0
	BSF INTCON, GIE ; Enable Interrupts
	*/
    __delay_ms(500);

	init_I2CBB(); //Run this first
	init_MoveTricopter();
	init_PWM();
	init_Osc(); // Needed for PWM (check PLLFBD, defined diff)
	init_T1(); //Needed for interrupts
     
	while(1){
		if (AccZavg>0){ //in meters
			//Turn Blue ON
	        TRISAbits.TRISA2 = 0;
	    	LATAbits.LATA2 = 1;
		}else{//Turn Blue Off
			TRISAbits.TRISA2 = 0;
	    	LATAbits.LATA2 = 0;
		}
		if (GyroZavg>0){ //in meters
			//Turn Red ON
	        TRISAbits.TRISA3 = 0;
	    	LATAbits.LATA3 = 1;
		}else{//Turn Red Off
			TRISAbits.TRISA3 = 0;
	    	LATAbits.LATA3 = 0;
		}
		//motor1 = (AccXavg+32768)/656;
		//motor2 = (AccYavg+32768)/656;		
	
		/*updateDist();

		if (distanceX()>0.03){ //in meters
			//Turn Blue ON
	        TRISAbits.TRISA2 = 0;
	    	LATAbits.LATA2 = 1;
		}else{//Turn Blue Off
			TRISAbits.TRISA2 = 0;
	    	LATAbits.LATA2 = 0;
		}*/
	}
    return 0;
}



void testBlink(void){
    //Test BLINK FUNCTIONs
    int repeat;
    for (repeat = 0; repeat<1; repeat++){
            blinkRed();
            //blinkYellow();
        }
    //blinkBothAlt();
    //blinkBothSim();
    //blinkOff();
}

void go(void) {
    /*while(1) {
        //ACCGYRODATA();
        if (AccY > AccY0 && AccX > AccX0) {
            turnRed();
        } else if (AccY < AccY0 && AccX < AccX0) {
            turnYellow();
        } else {
            turnBoth();
        }
    }*/
}

void turnRed(void){
    TRISAbits.TRISA2 = 0; // configure direction for output
    LATAbits.LATA2 = 1;
    //TRISAbits.TRISA3 = 0;
    //LATAbits.LATA3 = 0;
}

void blinkRed(void) { //pin 9
    //BLINK FUNCTION
    TRISAbits.TRISA2 = 0; // configure direction for output
    LATAbits.LATA2 = 0;
    TRISAbits.TRISA3 = 0;
    LATAbits.LATA3 = 0;
    int count;
    for(count = 0; count<8; count++) {
        LATAbits.LATA2 = ~LATAbits.LATA2; // toggle LED
        __delay_ms(500);
    }
}

void blinkYellow(void){ //pin 10
    //BLINK FUNCTION
    TRISAbits.TRISA2 = 0; // configure direction for output
    LATAbits.LATA2 = 0;
    TRISAbits.TRISA3 = 0;
    LATAbits.LATA3 = 0;
    int count;
        for(count = 0; count<8; count++) {
        LATAbits.LATA3 = ~LATAbits.LATA3; // toggle LED
        __delay_ms(500);
    }
}

void turnYellow(void){
    //TRISAbits.TRISA2 = 0; // configure direction for output
    //LATAbits.LATA2 = 0;
    TRISAbits.TRISA3 = 0;
    LATAbits.LATA3 = 1;
}

void turnBoth(void){
    TRISAbits.TRISA2 = 0; // configure direction for output
    LATAbits.LATA2 = 1;
    TRISAbits.TRISA3 = 0;
    LATAbits.LATA3 = 1;
}

void blinkBothAlt(void) {
    //BLINK FUNCTION
    TRISAbits.TRISA3 = 0; // configure direction for output
    TRISAbits.TRISA2 = 0;
    LATAbits.LATA2 = 0;
    LATAbits.LATA3 = 0;
    int count;
    for (count = 0; count < 10; count++) {
        LATAbits.LATA2 = ~LATAbits.LATA2; // toggle LED
        __delay_ms(500);
        LATAbits.LATA3 = ~LATAbits.LATA3; // toggle LED
    }
}

void blinkBothSim(int blinkNum) {
    //BLINK FUNCTION
    TRISAbits.TRISA2 = 0; // configure direction for output
    TRISAbits.TRISA3 = 0;
    LATAbits.LATA2 = 0;
    LATAbits.LATA3 = 0;
    int count;
    for (count = 0; count < blinkNum; count++) {
        LATAbits.LATA2 = ~LATAbits.LATA2; // toggle LED
        LATAbits.LATA3 = ~LATAbits.LATA3; // toggle LED
        __delay_ms(500);                    //      :D Hiiiiiii!!!!!!!
    }
}

void blinkOff(void) {
    TRISAbits.TRISA2 = 0;  // configure direction for output
    TRISAbits.TRISA3 = 0;
    LATAbits.LATA2 = 0;
    LATAbits.LATA3 = 0;
}

void blinkOn(void) {
    TRISAbits.TRISA2 = 0;  // configure direction for output
    TRISAbits.TRISA3 = 0;
    LATAbits.LATA2 = 1;
    LATAbits.LATA3 = 1;
}

/*  Interrupt Service Routines
void __attribute__((__interrupt__)) _T1Interrupt(void){
	ACCGYRODATA();
}
void __attribute__((__interrupt__)) _MI2C2Interrupt(void){
	ACCGYRODATA();
}*/

