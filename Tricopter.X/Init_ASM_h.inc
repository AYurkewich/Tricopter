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


    .equiv  cLEDBLINK, 0x004
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

    ;Accelerometer and Gyro values
    ;                     '5432109876543210

    

/*
#ifndef __PWM

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

#endif  ;PWM

#ifndef __I2C_DATA

    .equiv AccX,0x0000
    .equiv AccY,0x0000
    .equiv AccZ,0x0000
    .equiv Temperature, 0x0000
    .equiv GyroX, 0x0000
    .equiv GyroY, 0x0000
    .equiv GyroZ, 0x0000

    .equiv AccX1, 0x0000
    .equiv AccX2, 0x0000
    .equiv AccY1, 0x0000
    .equiv AccY2, 0x0000
    .equiv AccZ1, 0x0000
    .equiv AccZ2, 0x0000
    .equiv Temperature1, 0x0000
    .equiv Temperature2, 0x0000
    .equiv GyroX1, 0x0000
    .equiv GyroX2, 0x0000
    .equiv GyroY1, 0x0000
    .equiv GyroY2, 0x0000
    .equiv GyroZ1, 0x0000
    .equiv GyroZ2, 0x0000
    .equiv AccXOLD, 0x0000
    .equiv AccYOLD, 0x0000
    .equiv AccZOLD, 0x0000
    .equiv TemperatureOLD, 0x0000
    .equiv GyroXOLD, 0x0000
    .equiv GyroYOLD, 0x0000
    .equiv GyroZOLD, 0x0000

#endif ;I2C_DATA
*/