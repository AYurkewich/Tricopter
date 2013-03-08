/**********************************************************
;Asterik Research Electonics
;Interrupt Header Templet

;**********************************************************/

.include "p33FJ32MC202.inc"

.include	"Init_ASM_h.inc"	

      .global __T1Interrupt    ;Declare Timer 1 ISR name global

;..............................................................................
;Constants stored in Program space
;..............................................................................
 .text


__T1Interrupt: 
      	push.d	w0	
      	push.d	w2
      	push.d	w4

        bclr	IFS0,#T1IF 
		mov		_c_Tmr1_Tim,w0
		mov		w0,TMR1

		inc 	_uc_100uS_Timer

        btg     PORTB,#cLEDBLINK

;get accelerometer values
;get gyro values
///Ask Adam if this works!
global  _main

extern  _ACCGYRODATA

section .data

section .code

_main

        push    int &AccelerometerX
        push    int &AccelerometerY
        push    int &AccelerometerZ
        push    int &GyroscopeX
        push    int &GyroscopeY
        push    int &GyroscopeZ
        call    _ACCGYRODATA
        ret






//make accelerometer average

//make gyro average

//read if battery low
//RB13
//Read if battery is less than 2.9
//RB14
        
T1_Out:
		pop.d	w4
		pop.d	w2
		pop.d	w0
        RETFIE 
	  
.end
