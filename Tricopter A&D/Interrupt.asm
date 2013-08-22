	;Interrupt Section
		;Interrupt Section
Interrupt 
	;Timer 0
Timer0:  ;First sensor value is looked up
		movwf	TempWreg
		movf	STATUS,w
		movwf	TempStatus	
		
		banksel	TMR0
		movlw	cTimer0			
		movwf	TMR0	;TMR0 = 4A	
		;Delay can be used for testing to slow down rate of interupt
			;banksel btimer1
			;decfsz btimer1
			;goto OverInterrupt
		btfsc ADCON0,GO ;BIT1
		goto OverADC  		;skip if A/D conversion completed(first time)
		call ADCLookupTable ;ADC Table is not looked up if A/D conv is going
							;Update ADC table
		bsf ADCON0,GO
		
OverADC: ;A/D conversion in progress

		banksel RCSTA
		btfss RCSTA,OERR
		goto OverTest ;Skip if ADC input gives an overrun error (Clear CREN bit)
		movwf bTemp
		movlw 0xfe

	;	movwf PORTC
	;	incf PORTC	
		movfw bTemp	

OverTest: ;No overrun error
		banksel bTemp
		movwf bTemp
		;movlw 0xfe
		movfw bSensor2
							;banksel PORTC
							;movwf PORTC
							;incf PORTC,F
		movfw bTemp	
		banksel PIR1		;1st: TX and RX are empty
;*****	
		
btfss PIR1,RCIF;BIT5;skip OverInterrupt if Receive Buffer is full
goto OverInterrupt  ;Commented out on May 3 to bypass the Rx flag
				;Only returns something if I send something
				;Right at the start it bypasses once, then RCIF is never set again.
							;banksel PORTC
							;movlw 0xFF 
							;movwf PORTC
			
				;GETS HERE IF SOMETHING IS SENT TO CHIP/SET RCIF
		
		banksel RCREG
movfw RCREG			;RCREG = 0x62 = 01100011 >>w

			;keeps reading input as 0
			;sets flag but doesn't change RCREG
;*****	
		
;movlw 0x66;HiJack		;*AN2* = "b" (no Sensor0) DY (May 15 2013
			;When I transmit something it freezes
			;What happens?**
		andlw 0x7F			;7F = 01111111, w = 01100011
		movwf bTemp			;bTemp = "c" = 01100011		
		movlw cSensorOne	;"a"
		subwf bTemp,W		;WREG = "c" - "a" = 00000010
							;	banksel PORTC
							;	movwf PORTC
						
							;	btfsc W,7
							;	goto OverInterrupt
							;	btfsc W,6
							;	goto OverInterrupt
							;	btfsc W,5
							;	goto OverInterrupt
		banksel bCurrentIndex
		movwf bCurrentIndex	;bCurrentIndex = 2
		call GetSensorData 	;Read Sensor Values
		movfw bSendBuffer
    	banksel TXSTA
		btfss TXSTA,1	;TSR is empty
		goto OverTrasmit;TSR is set when TXREG sends a character to TSR
		banksel TXREG	
		movwf TXREG ;This clears TSR

		banksel bCurrentIndex
		movlw 0x08
		addwf bCurrentIndex
		call GetSensorData 	;Read Sensor Values
		movfw bSendBuffer
		banksel TXREG
		movwf TXREG ;This clears TSR		

OverTrasmit:
		;TEST: OFF with PIC, ON with computer
		;on power, TSR is empty, but is filled when plugged in to the computer

;Loops until Receive Buffer is empty, then resets;
OverInterrupt: 
		;End of changes
		;TEST: ON with PIC
		
		bcf	INTCON, T0IF	;clear interrupt status bit
		movf	TempStatus,W
		movwf	STATUS
		movf	TempWreg,W
		retfie


	
Timer1:	
		movwf	TempWreg
		movf	STATUS,w
		movwf	TempStatus	
		banksel PIE1		;Bank 1
		bcf	PIE1, TMR1IE		;disable(0)/enable(1) timer 1
		banksel T1CON		;Bank 0
		bcf	T1CON,TMR1ON		;disable(0)/enable(1) turn off timer 1 
	
		movlw	cTimer1H
		movwf	TMR1H
		bcf	PIR1, TMR1IF		;clear interrupt status bit
		

		movf	TempStatus,W
		movwf	STATUS
		movf	TempWreg,W
		retfie	
		
	;Timer 2
Timer2:
		movwf	TempWreg
		movf	STATUS,w
		movwf	TempStatus	
		banksel PIE1		;Bank 1
		bcf	PIE1,TMR2IE		;disable(0)/enable(1) timer 2
		banksel T2CON		;Bank 0
		bcf	T2CON,TMR2ON		;disable(0)/enable(1) turn off timer 2 
	
		bcf	PIR1, TMR2IF		;clear interrupt status bit	
		movf	TempStatus,W
		movwf	STATUS
		movf	TempWreg,W
		retfie			

	;External interrupt				
ExternalInt:
		movwf	TempWreg
		movf	STATUS,w
		movwf	TempStatus	
		
		banksel	OPTION_REG
		bsf 	OPTION_REG, INTEDG	;Set port2 to interrupt on rising edge
		bcf	INTCON, INTF		;clear interrupt status bit
		
		movf	TempStatus,W
		movwf	STATUS
		movf	TempWreg,W
		retfie
		
IntOnChange:
   		movwf	TempWreg
		movf	STATUS,w
		movwf	TempStatus	
	
	
		bcf	INTCON, RABIF		;clear Interrupt ON Change  interrupted bit
		movf	TempStatus,W
		movwf	STATUS
		movf	TempWreg,W
		retfie

A2DInt:		movwf	TempWreg
		movf	STATUS,w
		movwf	TempStatus
	
		banksel	PIR1
		bcf	PIR1, ADIF			;clear interrupted flag bit
		btfsc	ADCON0,CHS0
		bsf	ADCON0,CHS0	
		bsf	ADCON0,CHS1	
		bcf	ADCON0,GO
		
		movf	TempStatus,W
		movwf	STATUS
		movf	TempWreg,W	
		retfie

RxInt:							;EUSART Receive Interrupt Flag bit
   		movwf	TempWreg
		movf	STATUS,w
		movwf	TempStatus	
		
		banksel	PIR1
		bcf		PIR1, RCIF		;clear interrupted flag bit

		movf	TempStatus,W
		movwf	STATUS
		movf	TempWreg,W
		retfie

TxInt:							;EUSART Transmit Interrupt Flag bit
   		movwf	TempWreg
		movf	STATUS,w
		movwf	TempStatus	

		banksel	PIR1
		bcf		PIR1, TXIF		;clear interrupted flag bit
		
		movf	TempStatus,W
		movwf	STATUS
		movf	TempWreg,W
		retfie

SSPInt:							;Synchronous Serial Port (SSP) Interrupt Flag bit
   		movwf	TempWreg
		movf	STATUS,w
		movwf	TempStatus	

		banksel	PIR1
		bcf		PIR1, SSPIF				;clear interrupted flag bit

		movf	TempStatus,W
		movwf	STATUS
		movf	TempWreg,W
		retfie


EEInt:							; EEPROM Write Operation Interrupt Flag bit
   		movwf	TempWreg
		movf	STATUS,w
		movwf	TempStatus	

		banksel	PIR2
		bcf		PIR2, EEIF		;clear interrupted flag bit

		movf	TempStatus,W
		movwf	STATUS
		movf	TempWreg,W
		retfie

CCPInt:								; CCP1 Interrupt Flag bit
   		movwf	TempWreg
		movf	STATUS,w
		movwf	TempStatus	
		
		banksel	PIR1
		bcf		PIR1, CCP1IF		;clear interrupted flag bit

		movf	TempStatus,W
		movwf	STATUS
		movf	TempWreg,W
		retfie

C2Int:							; Comparator 2 Interrupt Flag bit
   		movwf	TempWreg
		movf	STATUS,w
		movwf	TempStatus	
		
		banksel	PIR2
		bcf		PIR2, C2IF		;clear interrupted flag bit

		movf	TempStatus,W
		movwf	STATUS
		movf	TempWreg,W
		retfie

C1Int:							; Comparator 1 Interrupt Flag bit
   		movwf	TempWreg
		movf	STATUS,w
		movwf	TempStatus	
		
		banksel	PIR2
		bcf		PIR2, C1IF		;clear interrupted flag bit

		movf	TempStatus,W
		movwf	STATUS
		movf	TempWreg,W
		retfie

OSFInt:							; Oscillator Fail Interrupt Flag bit
   		movwf	TempWreg
		movf	STATUS,w
		movwf	TempStatus	
		
		banksel	PIR2
		bcf		PIR2, OSFIF		;clear interrupted flag bit

		movf	TempStatus,W
		movwf	STATUS
		movf	TempWreg,W
		retfie
