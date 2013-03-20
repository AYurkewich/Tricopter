/**********************************************************
;WE Bots
;Main

**********************************************************/




#include "Micros_h_File.h"
#include "Init_Declarations.h"

#include "Configutation_Bits_File.h"

/*********************************************************
 * PORT DESIGNATIONS
 * Motor Signals: RB2 - RB7
 * Accel/gyro: RB8(SCL), RB9(SDA), RA4(INT)
 * LEDs: RA2, RA3
 * Programming: RB0(PGD1), RB1(PGC1), VSS, VDD, MCLR
 * Test pins: AVDD, RA0, RA1, RB13, VSS
 * Bluetooth: AVDD, VSS, RB11, RB12
 * Master power: RB15
 * BAT low: RB14
 * Motor Power: RB10
 ********************************************************/

//TRIS DEFINE STATEMENTS
#define TA00     TRISAbits.TRISA0 //
#define TA01     TRISAbits.TRISA1 //
#define TA02     TRISAbits.TRISA2 //
#define TA03     TRISAbits.TRISA3 //
#define TA04     TRISAbits.TRISA4 //
#define TB00     TRISBbits.TRISB0 //
#define TB01     TRISBbits.TRISB1 //
#define TB02     TRISBbits.TRISB2 //
#define TB03     TRISBbits.TRISB3 //
#define TB04     TRISBbits.TRISB4 //
#define TB05     TRISBbits.TRISB5 //
#define TB06     TRISBbits.TRISB6 //
#define TB07     TRISBbits.TRISB7 //
#define TB08     TRISBbits.TRISB8 //
#define TB09     TRISBbits.TRISB9 //
#define TB10    TRISBbits.TRISB10 //
#define TB11    TRISBbits.TRISB11 //
#define TB12    TRISBbits.TRISB12 //
#define TB13    TRISBbits.TRISB13 //
#define TB14    TRISBbits.TRISB14 //
#define TB15    TRISBbits.TRISB15 //

//LAT DEFINE STATEMENTS
#define LA00     LATAbits.LATA0 //
#define LA01     LATAbits.LATA1 //
#define LA02     LATAbits.LATA2 //
#define LA03     LATAbits.LATA3 //
#define LA04     LATAbits.LATA4 //
#define LB00     LATBbits.LATB0 //
#define LB01     LATBbits.LATB1 //
#define LB02     LATBbits.LATB2 //
#define LB03     LATBbits.LATB3 //
#define LB04     LATBbits.LATB4 //
#define LB05     LATBbits.LATB5 //
#define LB06     LATBbits.LATB6 //
#define LB07     LATBbits.LATB7 //
#define LB08     LATBbits.LATB8 //
#define LB09     LATBbits.LATB9 //
#define LB10    LATBbits.LATB10 //
#define LB11    LATBbits.LATB11 //
#define LB12    LATBbits.LATB12 //
#define LB13    LATBbits.LATB13 //
#define LB14    LATBbits.LATB14 //
#define LB15    LATBbits.LATB15 //

int main(void)
{
    //Initialize registers and ports


    /*
        ubBufferIndex = 0;
        ubLastBufferIndex = 0;

	init_Osc();


	init_PWM();								// PWM Setup
	init_ADC();								// ADC Setup
	init_DAC_Comparators();


        init_T1();
        

	//TRISBbits.TRISB4  = 0;		    	 		//RB4 as output
        //LATBbits.LATB4 = 1; high
        //TRISBbits.TRISB6  = 1;
        //TRISBbits.TRISB7  = 1;

   // PTCONbits.PTEN = 1;					// Enable the PWM
//	ADCONbits.ADON = 1;					// Enable the ADC

        uiHeaderZeroCount = 0;
	IEC0bits.T1IE = 1;
//	uc_Main_Case_Index = 0;



*/
    	while(1)
	{
          //calculate position based on accelerometer  
            
          //calculate orientation based on gyro  
            
          //calculate the forces and torques on the helicopter based on previous values 
            
          //what position do you want to go to  
            
          //what orientation do you want to be at 
            
          //use PID to establish how much to to pulse motor
            
          //tell motor 1 what to do
            TB02 = 0;
            
          //tell motor 2 what to do
            TB03 = 0;
          //tell motor 3 what to do
            TB04 = 0;
          //tell motor 4 what to do
            TB05 = 0;
          //tell motor 5 what to do
            TB06 = 0;
          //tell motor 6 what to do
            TB07 = 0;
          //tell Red LED what to do
                //RA3

          //tell Green LED what to do
                //RA2
          //do something if battery low (land) or very low (shut off)

            //Future stuff//

          //Vision System
          //Object Detection

        };

}

