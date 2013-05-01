;.include "p33FJ32MC202.inc"
;.include "Init_ASM_h.inc"

    .equiv PWMzerocheck, 0x0000
    .equiv PWMperiod, 0x0000
    .equiv PWMmotor1check, 0x0000
    .equiv PWMmotor2check, 0x0000
    .equiv PWMmotor3check, 0x0000
    .equiv PWMmotor4check, 0x0000
    .equiv PWMmotor5check, 0x0000
    .equiv PWMmotor6check, 0x0000
    .equiv PWMmotor1, 0x0000
    .equiv PWMmotor2, 0x0000
    .equiv PWMmotor3, 0x0000
    .equiv PWMmotor4, 0x0000
    .equiv PWMmotor5, 0x0000
    .equiv PWMmotor6, 0x0000
    .equiv motor1, 0x0000
    .equiv motor2, 0x0000
    .equiv motor3, 0x0000
    .equiv motor4, 0x0000
    .equiv motor5, 0x0000
    .equiv motor6, 0x0000
    .equiv Initperiodrestart, 0x0000

;check if PWM's equal zero bit by bit (is there a better way?)


CheckPWMperiodEQzero:
bclr PWMzerocheck, #0
btsc PWMperiod, #6
bset PWMzerocheck, #0
btsc PWMperiod, #6
Return

btsc PWMperiod, #5
bset PWMzerocheck, #0
btsc PWMperiod, #5
Return

btsc PWMperiod, #4
bset PWMzerocheck, #0
btsc PWMperiod, #4
Return

btsc PWMperiod, #3
bset PWMzerocheck, #0
btsc PWMperiod, #3
Return

btsc PWMperiod, #2
bset PWMzerocheck, #0
btsc PWMperiod, #2
Return

btsc PWMperiod, #1
bset PWMzerocheck, #0
btsc PWMperiod, #1
Return

btsc PWMperiod, #0
bset PWMzerocheck, #0
Return

CheckPWMmotor1EQzero:
bclr PWMmotor1check, #0
btsc PWMmotor1, #6
bset PWMmotor1check, #0
btsc PWMmotor1, #6
Return

btsc PWMmotor1, #5
bset PWMmotor1check, #0
btsc PWMmotor1, #5
Return

btsc PWMmotor1, #4
bset PWMmotor1check, #0
btsc PWMmotor1, #4
Return

btsc PWMmotor1, #3
bset PWMmotor1check, #0
btsc PWMmotor1, #3
Return

btsc PWMmotor1, #2
bset PWMmotor1check, #0
btsc PWMmotor1, #2
Return

btsc PWMmotor1, #1
bset PWMmotor1check, #0
btsc PWMmotor1, #1
Return

btsc PWMmotor1, #0
bset PWMmotor1check, #0
Return

CheckPWMmotor2EQzero:
bclr PWMmotor2check, #0
btsc PWMmotor2, #6
bset PWMmotor2check, #0
btsc PWMmotor2, #6
Return

btsc PWMmotor2, #5
bset PWMmotor2check, #0
btsc PWMmotor2, #5
Return

btsc PWMmotor2, #4
bset PWMmotor2check, #0
btsc PWMmotor2, #4
Return

btsc PWMmotor2, #3
bset PWMmotor2check, #0
btsc PWMmotor2, #3
Return

btsc PWMmotor2, #2
bset PWMmotor2check, #0
btsc PWMmotor2, #2
Return

btsc PWMmotor2, #1
bset PWMmotor2check, #0
btsc PWMmotor2, #1
Return

btsc PWMmotor2, #0
bset PWMmotor2check, #0
Return

CheckPWMmotor3EQzero:
bclr PWMmotor3check, #0
btsc PWMmotor3, #6
bset PWMmotor3check, #0
btsc PWMmotor3, #6
Return

btsc PWMmotor3, #5
bset PWMmotor3check, #0
btsc PWMmotor3, #5
Return

btsc PWMmotor3, #4
bset PWMmotor3check, #0
btsc PWMmotor3, #4
Return

btsc PWMmotor3, #3
bset PWMmotor3check, #0
btsc PWMmotor3, #3
Return

btsc PWMmotor3, #2
bset PWMmotor3check, #0
btsc PWMmotor3, #2
Return

btsc PWMmotor3, #1
bset PWMmotor3check, #0
btsc PWMmotor3, #1
Return

btsc PWMmotor3, #0
bset PWMmotor3check, #0
Return

CheckPWMmotor4EQzero:
bclr PWMmotor4check, #0
btsc PWMmotor4, #6
bset PWMmotor4check, #0
btsc PWMmotor4, #6
Return

btsc PWMmotor4, #5
bset PWMmotor4check, #0
btsc PWMmotor4, #5
Return

btsc PWMmotor4, #4
bset PWMmotor4check, #0
btsc PWMmotor4, #4
Return

btsc PWMmotor4, #3
bset PWMmotor4check, #0
btsc PWMmotor4, #3
Return

btsc PWMmotor4, #2
bset PWMmotor4check, #0
btsc PWMmotor4, #2
Return

btsc PWMmotor4, #1
bset PWMmotor4check, #0
btsc PWMmotor4, #1
Return

btsc PWMmotor4, #0
bset PWMmotor4check, #0
Return

CheckPWMmotor5EQzero:
bclr PWMmotor5check, #0
btsc PWMmotor5, #6
bset PWMmotor5check, #0
btsc PWMmotor5, #6
Return

btsc PWMmotor5, #5
bset PWMmotor5check, #0
btsc PWMmotor5, #5
Return

btsc PWMmotor5, #4
bset PWMmotor5check, #0
btsc PWMmotor5, #4
Return

btsc PWMmotor5, #3
bset PWMmotor5check, #0
btsc PWMmotor5, #3
Return

btsc PWMmotor5, #2
bset PWMmotor5check, #0
btsc PWMmotor5, #2
Return

btsc PWMmotor5, #1
bset PWMmotor5check, #0
btsc PWMmotor5, #1
Return

btsc PWMmotor5, #0
bset PWMmotor5check, #0
Return

CheckPWMmotor6EQzero:
bclr PWMmotor6check, #0
btsc PWMmotor6, #6
bset PWMmotor6check, #0
btsc PWMmotor6, #6
Return

btsc PWMmotor6, #5
bset PWMmotor6check, #0
btsc PWMmotor6, #5
Return

btsc PWMmotor6, #4
bset PWMmotor6check, #0
btsc PWMmotor6, #4
Return

btsc PWMmotor6, #3
bset PWMmotor6check, #0
btsc PWMmotor6, #3
Return

btsc PWMmotor6, #2
bset PWMmotor6check, #0
btsc PWMmotor6, #2
Return

btsc PWMmotor6, #1
bset PWMmotor6check, #0
btsc PWMmotor6, #1
Return

btsc PWMmotor1, #0
bset PWMmotor1check, #0
Return

PWMperiodrestart:
;period could go to 127 (remebering 100 is easier)
mov #100, W0
mov W0, PWMperiod
mov motor1, WREG
mov WREG, PWMmotor1
mov motor2, WREG
mov WREG, PWMmotor2
mov motor3, WREG
mov WREG, PWMmotor3
mov motor4, WREG
mov WREG, PWMmotor4
mov motor5, WREG
mov WREG, PWMmotor5
mov motor6, WREG
mov WREG, PWMmotor6
Return

PWMSET:

;counter for period of PWM
;(use resolution 100 values; 100*1us=100us; rection time of 100us)
btss Initperiodrestart, #0
Call PWMperiodrestart
btss Initperiodrestart, #0
bset Initperiodrestart, #0

Call CheckPWMperiodEQzero

btsc PWMzerocheck, #0
DEC PWMperiod
btss PWMzerocheck, #0
Call PWMperiodrestart

;counter for how much of the period the PWM is high

;motor1
Call CheckPWMmotor1EQzero
;if PWMmotor1 is not zero than PWMmotor1check is 1 so decrement PWMmotor1
btsc PWMmotor1check, #0
DEC PWMmotor1

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;test PWM using LED'S
btsc PWMmotor1check, #0
bset LATA, #2
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;if PWMmotor1 is not zero than PWMmotor1check is 1 so motor1 is off
btsc PWMmotor1check, #0
bset LATB, #2

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;test PWM using LED'S
btss PWMmotor1check, #0
bclr LATA, #2
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;if PWMmotor1 is not zero than PWMmotor1check is 1 so motor1 is off
btss PWMmotor1check, #0
bclr LATB, #2

;motor2
Call CheckPWMmotor2EQzero
;if PWMmotor1 is not zero than PWMmotor1check is 1 so decrement PWMmotor1
btsc PWMmotor2check, #0
DEC PWMmotor2

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;test PWM using LED'S
btsc PWMmotor2check, #0
bset LATA, #3
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;if PWMmotor1 is not zero than PWMmotor1check is 1 so motor1 is off
btsc PWMmotor2check, #0
bset LATB, #3

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;test PWM using LED'S
btss PWMmotor2check, #0
bclr LATA, #3
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;if PWMmotor1 is not zero than PWMmotor1check is 1 so motor1 is off
btss PWMmotor2check, #0
bclr LATB, #3

;motor3
Call CheckPWMmotor3EQzero
;if PWMmotor1 is not zero than PWMmotor1check is 1 so decrement PWMmotor1
btsc PWMmotor3check, #0
DEC PWMmotor3
;if PWMmotor1 is not zero than PWMmotor1check is 1 so motor1 is off
btsc PWMmotor3check, #0
bset LATB, #4
;if PWMmotor1 is not zero than PWMmotor1check is 1 so motor1 is off
btss PWMmotor3check, #0
bclr LATB, #4

;motor4
Call CheckPWMmotor4EQzero
;if PWMmotor1 is not zero than PWMmotor1check is 1 so decrement PWMmotor1
btsc PWMmotor4check, #0
DEC PWMmotor4
;if PWMmotor1 is not zero than PWMmotor1check is 1 so motor1 is off
btsc PWMmotor4check, #0
bset LATB, #5
;if PWMmotor1 is not zero than PWMmotor1check is 1 so motor1 is off
btss PWMmotor4check, #0
bclr LATB, #5

;motor5
Call CheckPWMmotor5EQzero
;if PWMmotor1 is not zero than PWMmotor1check is 1 so decrement PWMmotor1
btsc PWMmotor5check, #0
DEC PWMmotor5
;if PWMmotor1 is not zero than PWMmotor1check is 1 so motor1 is off
btsc PWMmotor5check, #0
bset LATB, #6
;if PWMmotor1 is not zero than PWMmotor1check is 1 so motor1 is off
btss PWMmotor5check, #0
bclr LATB, #6
;motor6
Call CheckPWMmotor6EQzero
;if PWMmotor1 is not zero than PWMmotor1check is 1 so decrement PWMmotor1
btsc PWMmotor6check, #0
DEC PWMmotor6
;if PWMmotor1 is not zero than PWMmotor1check is 1 so motor1 is off
btsc PWMmotor6check, #0
bset LATB, #7
;if PWMmotor1 is not zero than PWMmotor1check is 1 so motor1 is off
btss PWMmotor6check, #0
bclr LATB, #7
Return
