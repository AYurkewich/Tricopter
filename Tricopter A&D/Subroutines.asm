;***********************************************************
;WE Bots
;Subroutines Templet

;********************************************************
;Document Control
;	Version Number chage by a large changes to code
;	Revision Number change by small changes to code
;	Add new entries to the top line and move older entries down
;	DO NOT erase any entries!!!
;
;Date/Time			:	Who	 			   		:	Version/Revision	:	Description		
;2006/02/13 08:30 	:E. Porter Electronics Shop :	0.0					:	Templet File
;
;
;
;**********************************************************



Subroutines 
SB0

TableLookup:

;		banksel	bProcessByte
;		movlw	HIGH LEDOutputTable		;table label
;		movwf	PCLATH		
;		bcf		STATUS,C
;		movf 	bLedBlinkCounter,W		;user variable as pointer in to table
;		btfsc	STATUS,C
;		incf	PCLATH,f
;		call 	LEDOutputTable		;call into the table
;		movwf	GPIO				;store returned value
;		banksel	bProcessByte	

		return
GetSensorData:

		banksel	AccX
		movlw	HIGH AccelGyroTable	; =4		;table label
		movwf	PCLATH					; =4
		bcf		STATUS,C				; C is BIT0
		movf 	bCurrentIndex,W			; =1 user variable as pointer in to table
		btfsc	STATUS,C				; Only set if carry is set / overflow
		incf	PCLATH,f ;0x00 - 85?
		call 	AccelGyroTable		;Lookup Table Values
		banksel FSR
		movwf 	FSR		; = 2A? ;to RAM / Can be used as a pointer
		movfw 	INDF	;indirect referencing
		movwf   bSendBuffer	; =0
		banksel	AccX	

		return

ADCLookupTable:

		banksel	bProcessByte
		movlw	HIGH ADCSelectTable		;table label
		movwf	PCLATH		
		bcf		STATUS,C
		movf 	bADCAddress,W		;user variable as pointer in to table
		btfsc	STATUS,C ;TSR resets here on 3rd pass??
		incf	PCLATH,f
		call 	ADCSelectTable		;call into the table
;		banksel	bProcessByte	
		return
;end Subroutines

AccelerometerX:
	banksel ADCON0
	movfw ADRESH
	movwf bSensor1
	movfw ADRESL ;Read lower 8 bits
	movwf bSensor1L ;Store in GPR space
	bsf ADCON0,2;read AN2
	bcf ADCON0,3
	bcf ADCON0,4
	bcf ADCON0,5
	banksel bADCAddress
	incf bADCAddress,F	;bADCAddress increases by 1
	return

AccelerometerY: ;**AN2** (no Sensor0) DY (May 15 2013) Decided this is the goal Sensor
	banksel ADCON0
	movfw ADRESH
	movwf bSensor2
	movfw ADRESL ;Read lower 8 bits
	movwf bSensor2L ;Store in GPR space
	bcf ADCON0,2;read AN2
	bsf ADCON0,3
	bcf ADCON0,4
	bcf ADCON0,5
	banksel bADCAddress
	incf bADCAddress,F	;bADCAddress increases by 1
	return

AccelerometerZ:
	banksel ADCON0
	movfw ADRESH
	movwf bSensor3
	movfw ADRESL ;Read lower 8 bits
	movwf bSensor3L ;Store in GPR space
	bsf ADCON0,2;read AN3
	bsf ADCON0,3
	bcf ADCON0,4
	bcf ADCON0,5
	banksel bADCAddress
	incf bADCAddress,F
	return	 

Temperature:
	banksel ADCON0
	movfw ADRESH
	movwf bSensor4
	movfw ADRESL ;Read lower 8 bits
	movwf bSensor4L ;Store in GPR space
	bcf ADCON0,2;read AN4
	bcf ADCON0,3
	bsf ADCON0,4
	bcf ADCON0,5
	banksel bADCAddress
	incf bADCAddress,F
	return	

GyrometerX:
	banksel ADCON0
	movfw ADRESH
	movwf bSensor5
	movfw ADRESL ;Read lower 8 bits
	movwf bSensor5L ;Store in GPR space
	bsf ADCON0,2;read AN5
	bcf ADCON0,3
	bsf ADCON0,4
	bcf ADCON0,5
	banksel bADCAddress
	incf bADCAddress,F
	return	 	

GyrometerY:
	banksel ADCON0
	movfw ADRESH
	movwf bSensor6
	movfw ADRESL ;Read lower 8 bits
	movwf bSensor6L ;Store in GPR space
	bcf ADCON0,2;read AN6
	bsf ADCON0,3
	bsf ADCON0,4
	bcf ADCON0,5
	banksel bADCAddress
	incf bADCAddress,F
	return	

GyrometerZ:
	banksel ADCON0
	movfw ADRESH
	movwf bSensor7
	movfw ADRESL ;Read lower 8 bits
	movwf bSensor7L ;Store in GPR space
	bsf ADCON0,2;read AN7
	bsf ADCON0,3
	bsf ADCON0,4
	bcf ADCON0,5
	banksel bADCAddress
	movlw 0x00
	movwf bADCAddress
	;incf bADCAddress,F
	return	

;END HERE

Sensor8:
	banksel bADCAddress
	movlw 0x00
	movwf bADCAddress
	return
Sensor9:
	banksel bADCAddress
	movlw 0x00
	movwf bADCAddress
	return
Sensor10:
	banksel bADCAddress
	movlw 0x00
	movwf bADCAddress
	return
Sensor11:
	banksel bADCAddress
	movlw 0x00
	movwf bADCAddress
	return
Sensor12:
	banksel bADCAddress
	movlw 0x00
	movwf bADCAddress
	return
counterError:
	banksel bADCAddress
	movlw 0x00
	movwf bADCAddress
	return