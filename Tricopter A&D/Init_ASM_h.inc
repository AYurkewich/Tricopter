/**********************************************************
;Electronics Shop 
;Initialization for ASM Templet

;*********************************************************
;Document Control
;	Version Number chage by a large changes to code
;	Revision Number change by small changes to code
;	Add new entries to the top line and move older entries down
;	DO NOT erase any entries!!!
;
;Date/Time			:	Who	 			   		:	Version/Revision	:	Description		
;2011/08/09 08:30 	:E. Porter Electronics Shop :	0.0					:	Templet File
;
;
;
;**********************************************************/




	;//.global _cTAGCLOCK
;	.global _ubHichClockCount


    
	
	
	
   .text

    .equiv  C_TMR1_TIME, 0x0feE2


    .equiv  cLEDBLINK, 0x004  ;
    .equiv  cTAGCLOCK, 0x007
    .equiv  cTAGDATA,  0x006

    ;ubProcessByte
    .equiv  cbtLastClkState, 0x000
    .equiv  cbtHeaderFound, 0x001
    .equiv  cbtRxDataAllIn, 0x002

    ;uiSelectWhichBuffer
    .equiv  cbtLSBSwitchesRxBuffer, 0x000

    ;ucData2bCRCd
    .equiv  cbtCRCHiLowBit2Check, 0x000

;#ifndef __PWM
;
;    .equiv PWMzerocheck, 0x0000
;    .equiv PWMperiod, 0x0000
;    .equiv PWMmotor1check, 0x0000
;    .equiv PWMmotor2check, 0x0000
;    .equiv PWMmotor3check, 0x0000
;    .equiv PWMmotor4check, 0x0000
;    .equiv PWMmotor5check, 0x0000
;    .equiv PWMmotor6check, 0x0000
;    .equiv PWMmotor1, 0x0000
;    .equiv PWMmotor2, 0x0000
;    .equiv PWMmotor3, 0x0000
;    .equiv PWMmotor4, 0x0000
;    .equiv PWMmotor5, 0x0000
;    .equiv PWMmotor6, 0x0000
;    .equiv motor1, 0x0000
;    .equiv motor2, 0x0000
;    .equiv motor3, 0x0000
;    .equiv motor4, 0x0000
;    .equiv motor5, 0x0000
;    .equiv motor6, 0x0000
;
;#endif  ;PWM


;;    ;Accelerometer and Gyro values
;;    ;                     '5432109876543210
;;
;;    .equiv AccX,0x0000
;;    .equiv AccY,0x0000
;;    .equiv AccZ,0x0000
;;    .equiv Temperature, 0x0000
;;    .equiv GyroX, 0x0000
;;    .equiv GyroY, 0x0000
;;    .equiv GyroZ, 0x0000
;;
;;    .equiv AccX1, 0x0000
;;    .equiv AccX2, 0x0000
;;    .equiv AccY1, 0x0000
;;    .equiv AccY2, 0x0000
;;    .equiv AccZ1, 0x0000
;;    .equiv AccZ2, 0x0000
;;    .equiv Temperature1, 0x0000
;;    .equiv Temperature2, 0x0000
;;    .equiv GyroX1, 0x0000
;;    .equiv GyroX2, 0x0000
;;    .equiv GyroY1, 0x0000
;;    .equiv GyroY2, 0x0000
;;    .equiv GyroZ1, 0x0000
;;    .equiv GyroZ2, 0x0000
;;    .equiv AccOLD, 0x0000
;
;
;;**********************Added********************************
;
;	;Constants
;;PortA0		EQU 0x000
;;PortA1		EQU	0x001
;;PortA2		EQU	0x002	
;;PortA3		EQU	0x003
;;PortA4		EQU	0x004
;;PortA5		EQU	0x005
;;
;;PortB4		EQU 0x004
;;PortB5		EQU	0x005
;;PortB6		EQU	0x006	
;;PortB7		EQU	0x007
;;
;;PortC0		EQU 0x000
;;PortC1		EQU	0x001
;;PortC2		EQU	0x002	
;;PortC3		EQU	0x003
;;PortC4		EQU	0x004
;;PortC5		EQU	0x005		
;;
;;cTimer0 	EQU	0x04a ;sets interupt rate
;;cTimer1L	EQU	0x000
;;cTimer1H	EQU	0x069
;;cTimer2		equ	0x007	
;;
;;cSensorOne  EQU 0x061
;;;Bit Variables
;;bt0_ProcessBit0	EQU	0x000
;
;
;	;integer Variables Bank 0
;	;Free banks are 20 to 7F; A0 to EF; 120 to 16F
;	cblock 0x20   
;;Place your variables here - First add them in
;	bProcessByte	
;	wAWord:0, bHighByteAWordH,bLowByteAWordL
; 	;*******************Newly Added vvv
;    .global AccX1
;    .global AccX2
;    .global AccX
;    .global AccY1
;    .global AccY2
;    .global AccY
;    .global AccZ1
;    .global AccZ2
;    .global AccZ
;    .global Temp1
;    .global Temp2
;    .global Temp
;    .global GyroX1
;    .global GyroX2
;    .global GyroX
;    .global GyroY1
;    .global GyroY2
;    .global GyroY
;    .global GyroZ1
;    .global GyroZ2
;    .global GyroZ
;	;*******************Newly Added ^^^
;	bSendBuffer
;	bADCAddress
;;	btimer1
;;	btimer2
;;	bCurrentIndex
;;	bSensorOneAddress
;;	bSensor1
;;	bSensor2
;;	bSensor3
;	endc
;
;;********Add any variables to second bank area?
;	cblock 0x70	
;;	TempWreg
;;	TempStatus	
;	endc	
;	
;		;User Variable init
;UserVarInit 		
;				
;UV0
;;*****************Second, initialize the variables
;		banksel AccX1
;		movlw 0x00	
;		movwf AccX1
;	    movwf AccX2
;	    movwf AccX
;	    movwf AccY1
;	    movwf AccY2
;	    movwf AccY
;	    movwf AccZ1
;	    movwf AccZ2
;	    movwf AccZ
;	    movwf Temp1
;	    movwf Temp2
;	    movwf Temp
;	    movwf GyroX1
;	    movwf GyroX2
;	    movwf GyroX
;	    movwf GyroY1
;	    movwf GyroY2
;	    movwf GyroY
;	    movwf GyroZ1
;	    movwf GyroZ2
;	    movwf GyroZ

