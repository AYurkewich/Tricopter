.include "p33FJ32MC202.inc"
;.include "Init_ASM_h.inc"
.global PWMSET

;Only check 7 bits bc only 127 can be entered into motor speed
;Set PWMzerocheck if PWMperiod > 0 
CheckPWMperiodEQzero: 
		bclr  PWMzerocheck, #0
		mov   PWMperiod, W0
		mov   #0x00, W1
		cpseq W0, W1				
		bset  PWMzerocheck, #0
		return	

;Set PWMmotor1check=1 if PWMmotor1 is set
;Smaller code Works
CheckPWMmotor1EQzero: 
		bclr  PWMmotor1check, #0
		mov   PWMmotor1, W0
		mov   #0x00, W1
		cpseq W0, W1				
		bset  PWMmotor1check, #0		;skip if PWMmotor1 = 0x00, set if PWMmotor1 /= 0
		return
CheckPWMmotor2EQzero:
		bclr  PWMmotor2check, #0
		mov   PWMmotor2, W0
		mov   #0x00, W1
		cpseq W0, W1				
		bset  PWMmotor2check, #0
		return
CheckPWMmotor3EQzero:
		bclr  PWMmotor3check, #0
		mov   PWMmotor3, W0
		mov   #0x00, W1
		cpseq W0, W1				
		bset  PWMmotor3check, #0
		return
CheckPWMmotor4EQzero:
		bclr  PWMmotor4check, #0
		mov   PWMmotor4, W0
		mov   #0x00, W1
		cpseq W0, W1				
		bset  PWMmotor4check, #0
		return
CheckPWMmotor5EQzero:
		bclr  PWMmotor5check, #0
		mov   PWMmotor5, W0
		mov   #0x00, W1
		cpseq W0, W1				
		bset  PWMmotor5check, #0
		return
		
CheckPWMmotor6EQzero:
		bclr  PWMmotor6check, #0
		mov   PWMmotor6, W0
		mov   #0x00, W1
		cpseq W0, W1				
		bset  PWMmotor6check, #0
		return

PWMperiodrestart:
		;period could go to 127 (remebering 100 is easier)
		bset Initperiodrestart, #0
		;mov #0x64, W0
		mov #0x64, W0 ;use smaller period for testing
		mov W0, PWMperiod
		;btsc PWMperiod, #2
		;bset LATA, #2    ;Debugging with the Blue LED
		mov _motor1, WREG
		mov WREG, PWMmotor1
		mov _motor2, WREG
		mov WREG, PWMmotor2
		mov _motor3, WREG
		mov WREG, PWMmotor3
		mov _motor4, WREG
		mov WREG, PWMmotor4
		mov _motor5, WREG
		mov WREG, PWMmotor5
		mov _motor6, WREG
		mov WREG, PWMmotor6
		Return

PWMSET: ;counter for period of PWM ;(use resolution 100 values; 100*1us=100us; rection time of 100us)
				
		btss Initperiodrestart, #0 ;Initperiodreset is set if PWMperiod /=0
		;Reset motors, and reset period to 100
		Call PWMperiodrestart		

		Call CheckPWMperiodEQzero
		
		btsc PWMzerocheck, #0	
		DEC PWMperiod			;decrease period if it is period is positive
		btss PWMzerocheck, #0	
		Call PWMperiodrestart	;restart period if it is 0
		
		;counter for how much of the period the PWM is high
		
;MOTOR1
		;Set PWMmotor1check=1 if PWMmotor1 is set
		Call CheckPWMmotor1EQzero
		btsc PWMmotor1check, #0
		DEC PWMmotor1		;Decrease PWMmotor1 if it is > 0
		;Set A2 (LED) and B2
		btsc PWMmotor1check, #0
		bset LATA, #2
		btsc PWMmotor1check, #0
		bset LATB, #2
		btss PWMmotor1check, #0
		bclr LATA, #2
		btss PWMmotor1check, #0
		bclr LATB, #2
		
;MOTOR2
		Call CheckPWMmotor2EQzero
		btsc PWMmotor2check, #0
		DEC PWMmotor2
		;Set A3 (LED) and B3
		btsc PWMmotor2check, #0
		bset LATA, #3
		btsc PWMmotor2check, #0
		bset LATB, #3
		btss PWMmotor2check, #0
		bclr LATA, #3
		btss PWMmotor2check, #0
		bclr LATB, #3
		
;MOTOR3
		Call CheckPWMmotor3EQzero
		btsc PWMmotor3check, #0
		DEC PWMmotor3
		;Set B4
		btsc PWMmotor3check, #0
		bset LATB, #4
		btss PWMmotor3check, #0
		bclr LATB, #4
		
;MOTOR4
		Call CheckPWMmotor4EQzero
		btsc PWMmotor4check, #0
		DEC PWMmotor4
		;Set B5
		btsc PWMmotor4check, #0
		bset LATB, #5
		btss PWMmotor4check, #0
		bclr LATB, #5
		
;MOTOR5
		Call CheckPWMmotor5EQzero
		btsc PWMmotor5check, #0
		DEC PWMmotor5
		;Set B6
		btsc PWMmotor5check, #0
		bset LATB, #6
		btss PWMmotor5check, #0
		bclr LATB, #6
		
;MOTOR6
		Call CheckPWMmotor6EQzero
		btsc PWMmotor6check, #0
		DEC PWMmotor6
		;Set B7
		btsc PWMmotor6check, #0
		bset LATB, #7
		btss PWMmotor6check, #0
		bclr LATB, #7
		Return

