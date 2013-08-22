;;**********************************************************
;WE Bots
;Table Templet

;*********************************************************
;Document Control
;	Version Number chage by a large changes to code
;	Revision Number change by small changes to code
;	Add new entries to the top line and move older entries down
;	DO NOT erase any entries!!!
;
;Date/Time			:	Who	 			   		:	Version/Revision	:	Description		
;2010/02/07 08:30 	:E. Porter Electronics Shop :	0.0					:	Templet File
;
;
;
;*********************************************************

;This Code initializes the table

	org 0x0400
AccelGyroTable:
	addwf PCL,F   	;PCL is 3
	retlw AccX1
    retlw AccX2
    retlw AccX
    retlw AccY1
    retlw AccY2
    retlw AccY
    retlw AccZ1
    retlw AccZ2
    retlw AccZ
    retlw Temp1
    retlw Temp2
    retlw Temp
    retlw GyroX1
    retlw GyroX2
    retlw GyroX
    retlw GyroY1
    retlw GyroY2
    retlw GyroY
    retlw GyroZ1
    retlw GyroZ2
    retlw GyroZ
	retlw 0x00
	retlw 0x00
	retlw 0x00
	retlw 0x00
	retlw 0x00
	retlw 0x00
	retlw 0x00
	retlw 0x00
		
;;These can be the subroutines where you go to assign Hi and Lo bits
ADCSelectTable:
	addwf PCL,F
	goto AccelerometerX
	goto AccelerometerY
	goto AccelerometerZ
	goto Temperature
	goto GyrometerX
	goto GyrometerY
	goto GyrometerZ
	goto counterError
	goto counterError
	goto counterError
	goto counterError



;end Tables

