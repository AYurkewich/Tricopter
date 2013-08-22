/**********************************************************
;Asterik Research Electonics
;Interrupt Header Templet

;**********************************************************/

;.include "p33FJ32MC202.inc" //already defined previously
.include "Init_ASM_h.inc"
;.include "PWM.s"
;Include I2CBBTricopter.c if anything
						  ;Include I2C_Data.s if I change the Acc code to Assembly

      .global __T1Interrupt    ;Declare Timer 1 ISR name global
;..............................................................................
;Constants stored in Program space
;..............................................................................
 .text
;There is only 1 bank!

__T1Interrupt: 
		;Changed from 0,2,4 since the PWMset code used 0 and 1
      	push.d	w4	
      	push.d	w6
      	push.d	w8
		
        bclr	IFS0,#3 ;T1IF=bit3
		;mov		_c_Tmr1_Tim,w0
		mov		0x00,w0 ;test longer timer to see if it gets to teh while loop
		mov		w0,TMR1 			;Increases TMR1 to FEE2 from 000C
		
		inc 	_uc_100uS_Timer		;counts the number of interrupts run?

		;Should run Acc/Gyro Function first
		
Call _ACCGYRODATABB ;TMR1 +=0xD700 (TMR1 can be cleared midfunction)
Call PWMSET			;TMR1 +=0x0200
Call _POSANGDATA


/* NOW IN I2C Data

;make accelerometer average
mov AccX, WREG
add AccXOLD
RRNC AccXOLD

mov AccY, WREG
add AccYOLD
RRNC AccYOLD

mov AccZ, WREG
add AccZOLD
RRNC AccZOLD

mov Temperature, WREG
add TemperatureOLD
RRNC TemperatureOLD

mov AccX, WREG
add AccXOLD
RRNC AccXOLD

mov AccX, WREG
add AccXOLD
RRNC AccXOLD

mov AccX, WREG
add AccXOLD
RRNC AccXOLD

mov AccX, WREG
add AccXOLD
RRNC AccXOLD

mov AccX, WREG
add AccXOLD
RRNC AccXOLD

mov AccX, WREG
add AccXOLD
RRNC AccXOLD

*/

;make gyro average

;read if battery low
;RB13
;Read if battery is less than 2.9
;RB14
        
T1_Out:
		pop.d	w8
		pop.d	w6
		pop.d	w4
        RETFIE 
	  
.end
