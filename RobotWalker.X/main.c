/* 
 * File:   main.c
 * Author: Dan
 *
 * Created on March 20, 2013, 5:32 PM
 */

#include <stdio.h>
#include <stdlib.h>
//#include "msp430g2553.h"

/* ALTERNATE MAIN
 *
 * int main(int argc, char** argv) {
    return (EXIT_SUCCESS);
    }
 */

/* Global Variables */
volatile unsigned int turnDeg, servoNum, angle, delayMSec, delayTime;
volatile unsigned int rxCounter = 0;
volatile unsigned int timeCount = 0;
volatile unsigned int j,k;
volatile unsigned int xVal1, xVal2, yVal1, yVal2, zVal1;
volatile unsigned int testing;
volatile unsigned int defTest;
volatile unsigned int accInp;

/* Function Declarations */
void initialize(void);
void dly(int);
void start(void);

//CHECK THE TESTING PARAMETER*****************************************************************
void main(void)
{
	initialize();
	testing = 0; //1 is for testing
	while(!((P1IN & BIT3) != BIT3)); 	//press button to enter Manual Input - reliable
	start(); 							//Set start position

	while(1)
	{
		P1OUT ^= 0x01;
		dly(1000);
		P1OUT ^= 0x01;
		dly(1000);
	}
}
/* sParky Goal */
/*
Take in RX information
Test if received bit is above or below a specific value
HEX CODE   2_ 3_ 4_ 5_ 6_ 30

Flat pos.  27 3F 4B 5E 61 30

Resolution Limits (3 and 5 change the least, so are easier to measure
2A - 30 high, tilt forward (Needs to hit mid 30 range)
2* - 3E low, tilt backward (Needs to just hit 3E value)

4* - 50 high, right side  (if it just hits 50 it has gone too high)
49 - 5D low,  left side   (Needs to hit middle of 5D range)  - make sure you test for a range of values ex 47-49 so you don't skip over anything

 How does the receive buffer work through if/while statements, and within the interrupt
 */

/* Functions */
void initialize(void){
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  P1DIR = 0xFF; //(nov 13th)0xFF;                             // All P1.x outputs
  P1OUT = 0;                                // All P1.x reset
  P2DIR = 0xFF;                             // All P2.x outputs
  P2OUT = 0;                                // All P2.x reset
  P1SEL = BIT1 + BIT2;  //(nov 13th) add bit 0/ACLK                 // P1.1 = RXD, P1.2=TXD
  P1SEL2 = BIT1 + BIT2;                    // P1.1 = RXD, P1.2=TXD
  P3DIR = 0xFF;                             // All P3.x outputs
  //P3REN = 0x00;								// Set all Pulldown resistors to prevent random button pushes
  P3OUT = 0;                                // All P3.x reset

//BUTTON INITIALIZATION
  P1OUT |= 8;
  P1REN |= 8;
  P1DIR &= ~8;

//Clock Initialization
  UCA0CTL1 |= UCSSEL_1;                     // CLK = ACLK
  UCA0BR0 = 0x03;                           // 32kHz/9600 = 3.41
  UCA0BR1 = 0x00;                           //
  UCA0MCTL = UCBRS1 + UCBRS0;               // Modulation UCBRSx = 3
  UCA0CTL1 &= ~UCSWRST;                     // **Initialize USCI state machine**
/*
//TIMER INITIALIZATION >>Timer resets cause interrupt
  TA0CCR0 = 62500 - 1;    // A period of 62,500 cycles is 0 to 62,499.
  TA0CCTL0 = CCIE;        // Enable interrupts for CCR0.
  TA0CTL = TASSEL_2 + ID_3 + MC_1 + TACLR;  // SMCLK, div 8, up mode,
  */

//ENABLE INTERRUPTS (IN 'LOW POWER MODE 3')
  IFG2 &= ~UCA0RXIFG;						//Clear the flag first to prevent immediate interrupt
  IE2 |= UCA0RXIE;// + UCA0TXIE;               // Enable USCI_A0 RX TX or timer interrupt....CLEAR FLAGS FIRST?
  _enable_interrupt();       				// Enable interrupts
  //__bis_SR_register(LPM3_bits + GIE);		// Enter LPM3 w/ int until Byte RXed
}
void start(void){
		UCA0TXBUF = 0x35; 			//Start the accelerometer ASCII = 4
		dly(20);
}


/* DO CODE IN INTERRUPT*/

// RECEIVE INTERRUPT
#pragma vector=USCIAB0RX_VECTOR
__interrupt void USCI0RX_ISR(void)
{
	/* WATCH THE VALUE OVERLAP IN THE LESS SENSITIVE CASE, ex. 0x31 could be more tipped than 0x3F
	 * Only check 2* and 4* if 3* and 5* equal the midrange case
	 * WHEN DOES THE FLAG CHANGE??!?!?!?
	 * Watch timing cases and turn light off when reset
	 * Either its in range and the count increases, or the count is reset
	 * green LED goes on when stable for 10 seconds
	 * green LED goes off whenever outside of range, and when not within range for 10 seconds
	 */
accInp = UCA0RXBUF; //See the accelerometer input

if (testing) { //Realterm Test Values

	if(accInp >= 0x32 && accInp <= 0x32){
		xVal1 = UCA0RXBUF; //2*
		defTest = 0; //Takes care of random 0x30 value
	}else if(UCA0RXBUF>=0x33 && UCA0RXBUF<=0x33 && UCA0RXBUF!= defTest){
		xVal2 = UCA0RXBUF; //3*
		defTest = 1; //Takes care of random 0x30 value
	}else if(UCA0RXBUF>=0x34 && UCA0RXBUF<=0x34){
		yVal1 = UCA0RXBUF; //4*
	}else if(UCA0RXBUF>=0x35 && UCA0RXBUF<=0x35){
		yVal2 = UCA0RXBUF; //5*
	}else if(UCA0RXBUF>=0x36 && UCA0RXBUF<=0x37){
		zVal1 = UCA0RXBUF; //6*
	}

	//FORWARD/BACK and LEFT/RIGHT checks
		if((xVal2 == 0x33) && (xVal1 == 0x32) && (yVal2 == 0x35) && (yVal1 == 0x34)&& (zVal1 == 0x36))
		{
			++timeCount;
		}else
		{
			timeCount = 0;
			P1OUT &= ~BIT6; // THIS DOESNT TURN IT OFF!!!!
		}
		//From the CPS of Realterm, there are 120 bits sent per second
		if(timeCount == 3)
		{
			P1OUT |= BIT6;
		}
	}

if (!testing) { //Actual Values
//Until startbit is changed, set up to only read input sequentially. This is in order to prevent mixups. Only works if chip reads FAST
	if(accInp >= 0x20 && accInp <= 0x2F){
		xVal1 = accInp; //2*
		defTest = 0; //Takes care of random 0x30 value
	}else if(accInp >= 0x30 && accInp <= 0x3F && !defTest){
		xVal2 = accInp; //3*
		defTest = 1; //Takes care of random 0x30 value
	}else if(accInp >= 0x40 && accInp <= 0x4F){
		yVal1 = accInp; //4*
	}else if(accInp >= 0x50 && accInp <= 0x5F){
		yVal2 = accInp; //5*
	}else if(accInp >= 0x60 && accInp <= 0x6F){
		zVal1 = accInp; //6*
	}

	//FORWARD/BACK and LEFT/RIGHT checks
		if(((xVal2 == 0x3E || xVal2 == 0x3F) || (xVal2 == 0x30 && xVal1 <= 0x2A)) && ((yVal2 == 0x5F || yVal2 == 0x5E) || (yVal2 == 0x5D && yVal1 >= 0x49)))
		{
			++timeCount;
		}else
		{
			timeCount = 0;
			P1OUT &= ~BIT6;
		}
		//From the CPS of Realterm, there are 20 sets of coordinates sent per second
		if(timeCount >= 300)
		{
			P1OUT |= BIT6;
		}
	}
}


void dly(delayTime){
	unsigned int j;
	for(j = delayTime; j>0; --j){
		_delay_cycles(1000);
	}
}
/*void blinkG(){
	for(int m = 0; m<P1OUT ^=
}*/


