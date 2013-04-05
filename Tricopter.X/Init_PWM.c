/**********************************************************
;Asterik Research Electonics
;Initialize PWM Templet

;*********************************************************/


#include "Micros_h_File.h"

void init_PWM(void)    
{
   /*
    P1TCONbits.PTEN=1;
    P1TCONbits.PTSIDL=0;
    P1TCONbits.PTOPS3=0;
    P1TCONbits.PTOPS2=0;
    P1TCONbits.PTOPS1=0;
    P1TCONbits.PTOPS0=0;
    P1TCONbits.PTCKPS1=0;
    P1TCONbits.PTCKPS0=0;
    P1TCONbits.PTMOD1=0;
    P1TCONbits.PTMOD1=0;

    P1TMRbits.PTDIR=1;

    ///What do I put here?
    //P1TMRbits.PTMR=1;

    ///What do I put here?
    //P1TPERbits.PTPER=1;

    */


   /*
    //setup Timer 2
    T2CONbits.TON=0;
    T2CONbits.TSIDL=0;
    T2CONbits.TGATE=0;
    T2CONbits.TCKPS1=0;
    T2CONbits.TCKPS0=1;
    T2CONbits.T32=0;
    T2CONbits.TCS=0;

    */


 	//PTCONbits.PCLKDIV=0b110;		//PWM input clk devider =64
	//PHASE1 = 0x00FF;			// Timer1 period=max, this is just convenient for validation
	PDC1 = 0x007F; 					// Duty Cycle is 50%  
	//IOCON1bits.PENH = 1;                  	// PWM1H is controlled by PWM module
	//IOCON1bits.PENL = 1;                  	// PWM1H is controlled by PWM module
	//IOCON1bits.POLH = 0;                  	// Drive signals are active-high
	//IOCON1bits.PMOD=1;				// PWM pair works in Independent Mode
	//PWMCON1bits.ITB = 1;				// Select Independent Timebase mode


}
