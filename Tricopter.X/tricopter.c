/**********************************************************
;WE Bots
;Main

**********************************************************/




#include "Micros_h_File.h"
#include "Init_Declarations.h"

#include "Configutation_Bits_File.h"



int main(void)
{
        ubBufferIndex = 0;
        ubLastBufferIndex = 0;

	init_Osc();


	init_PWM();								// PWM Setup
	init_ADC();								// ADC Setup
	init_DAC_Comparators();


        init_T1();
        

	TRISBbits.TRISB4  = 0;		    	 		//RB4 as output
        TRISBbits.TRISB6  = 1;
        TRISBbits.TRISB7  = 1;

   // PTCONbits.PTEN = 1;					// Enable the PWM
//	ADCONbits.ADON = 1;					// Enable the ADC

        uiHeaderZeroCount = 0;
	IEC0bits.T1IE = 1;
//	uc_Main_Case_Index = 0;




    	while(1)
	{
          //calculate position based on accelerometer  
            
          //calculate orientation based on gyro  
            
          //calculate the forces and torques on the helicopter based on previous values 
            
          //what position do you want to go to  
            
          //what orientation do you want to be at 
            
          //use PID to establish how much to to pulse motor
            
          //tell motor 1 what to do
                //RB2
          //tell motor 2 what to do
                //RB3
          //tell motor 3 what to do
                //RB4
          //tell motor 4 what to do
                //RB5
          //tell motor 5 what to do
                //RB6
          //tell motor 6 what to do
                //RB7
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

