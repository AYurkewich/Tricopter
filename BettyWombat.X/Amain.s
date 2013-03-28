/*
Learning Assembly Notes
l = literal
w = work register
f = desination
move l into w register, then from w register to f

Initialize Ports, Declare Variables, Initialize Variables, Write Code
Learn Subroutines, GOTO, Debouncing
*/

IN21
        banksel PORTA 
        movlw   b'10101010' ;make alternating pins Hi/Low
        movwf   PORTA

IN22
        banksel TRISA
        movlw   b'00000000' ;make all pins outputs
        movwf   TRISA

DeBounce
    ;switch debounce
        btfsc   PORTA, cButton
        goto    ButtonPressed
        banksel bDebounceCounter
        clrf    bDebounceCounter
        btfss   bProcessByte,bt1_ButtonPushed
        goto    OverDebounce
        decfsz  bRebounceCounter,F
        goto    OverDebounce
        bcf     bProcessByte,bt1_ButtonPushed
        movlw   0x004
        xorwf   bProcessByte,F
        goto    OverDebounce

ButtonPressed
        banksel bDebounceCounter
        clrf    bRebounceCounter
        decfsz  bDebounceCounter,F
        goto    OverDebounce
        bsf     bProcessByte,bt1_ButtonPushed

OverDebounce
        return

btimer1 ;memory space is reserved for 2 variables
btimer2

ADC     ;The first 3 lines put the current value of the digitized analog signal
        ;in the file "bPotA2DInput" for later use in the code. The last line repeats
        movf    ADRESH,W
        ;movlw  0x080
        movwf   bPotA2DInput
        bsf     ADCON0,GO

/************************************
**CODE FOR LEDS
*************************************/

call    DeBounce

movf    ADRESH,W        ;Moves the ADRESH registry into WREG
;movlw  0x080
movwf   bPotA2DInput    ;Moves a byte into the file bPot...
bsf     ADCON0,GO       ;if __is clear, then clear __

banksel btimer1
decfsz  btimer1,f
goto    OverInterrupt
decfsz  btimer2,f
goto    OverInterrupt

bcf     STATUS,C
rrf     bPotA2DInput,W
andlw   0x0FF
btfsc   STATUS,Z
addlw   0x001
;movlw  0x028
movwf   btimer2

btfsc   bProcessByte,bt2_ToggleSequenceDirection
goto    Backward

Forward
        bcf     STATUS,C
        rlf     bOutputImage,f
        movlw   0x001
        btfsc   bOutputImage,4
        movwf   bOutputImage
        goto    LoadOutputImage

Backward
        bcf     STATUS,C
        rlf     bOutputImage,f
        movlw   0x008
        btfsc   STATUS,C
        movwf   bOutputImage

LoadOutputImage
        movf    bOutputImage,W
        movwf   PORTC

;********************************END OF LED CODE

banksel btimer1
movlw   0xFF
movwf   btimer1 ;enter 0xFF into btimer1
movwf   btimer2 ;shortcut to copy same info into each variable

banksel btimer1     ;go to btimer1 location
decfsz  btimer1     ;kills time
goto OverInterrupt
movlw   0xFF        ;reset btimer1 to 0xFF
movwf   btimer1
decfsz  btimer2     ;kills more time
goto OverInterrupt
movlw   0xFF        ;reset btimer2 to 0xFF
movwf   btimer2
comf    PORTA       ;changes 0 to 1 and 1 to 0 for all pins (alternates LEDs)
OverInterrupt

banksel TRISA       ;Choose A Register, i.e. pins 2,3,9,10,12
movlw 0x00          ;Set Register A as all outputs
movwf TRISA
banksel PORTA       ;Choose a port on the A register
movlw 0xFF          ;Set all pins to high (output)
movwf PORTA




