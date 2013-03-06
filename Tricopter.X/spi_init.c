//NOT USING SPI
// ssp configuration- clock input control
// manipulate clock line (SCK)to control exchange
// CS (Chip Select) or SS (Slave Select, we have only one slave) signal controls when device accessed
// SS tells slave that master wishes to start (SDA from 1 to 0) --acc data sheet
// Data changes on falling edge of SCK, Data read on rising edge of SCK
// EXAMPLE CODE
// SPItstM0.asm
// MASTER Rev 0
// Demonstrates SPI connection between 2 PICmicro devices
// Master sends data (a counter), Slave receives and outputs to LEDs on PORTB
// list p=16F876 #include "p16F876.inc"
// Ctr0    EQU 0x20            ; Counter variable - sent to SPI
// Dly0    EQU 0x21            ; Delay Variable (low byte)
// Dly1       EQU 0x22            ; Delay Variable (high byte)
// #define CS  0x02            ; PORTA,2
// ORG 0               ; Begin Code at location 0
// nop                 ; FOR ICD
// Set up the SPI Support
// BANKSEL TRISA       ; BANK 1
// movlw 0x00        ;  Set PORTA as
// movwf TRISA       ;  all Outputs
// movlw 0x06        ;   Turn off A/D movwf   ADCON1      ;   so PORTA can be used
// Set up the SPI Port
// BANKSEL TRISC       ; BANK 1
// movlw   0x10        ;  SCK is output (Master), SDI is input,
// movwf   TRISC       ;  SDO is output, all others output
// movlw   0x40        ;   Mode 1,1 SPI, middle of output
// movwf   SSPSTAT     ;   time sampling
// BANKSEL SSPCON      ; BANK 0
// movlw   0x31        ; Mode 1,1 SPI Master Mode, 1/16 Tosc bit time
// movwf   SSPCON      ; SSP is on

//Send_DT bcf     PORTA,CS    ; Enable Chip Select Output (low)
//movf    Ctr0,W      ; Get Ctr (Counter Value) in W
//movwf   SSPBUF      ; put in SSPBUF
//BANKSEL SSPSTAT     ; BANK 1
//Char1   btfss   SSPSTAT,BF  ; Data transfer complete? (Buffer Full?)
//goto    Char1       ;  if not, check again
//BANKSEL SSPBUF      ; BANK0
//movf    SSPBUF,W    ; Get Data from SSPBUF ;                   ; Throw it away
//bsf     PORTA,CS    ; Disable Chip Select Output (high)
//Update_Test_Counter incf    Ctr0,F      ; Increment counter variable
//Delay   movlw   0x01        ; Simple Delay loop
//movwf   Dly1        ;         |
//movlw   0x0F        ;         |
//movwf   Dly0        ;         |
//DlyLoop decfsz  Dly0,F      ; |
//goto    DlyLoop     ;         |
//decfsz  Dly1,F      ;         |
//goto    DlyLoop     ;         |
//; Done Delay        ;        \_/
//DoAgain goto Send_DT     ; Done, Send Next Byte.
//end

