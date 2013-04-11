;Set up I2C comunication and store data in bit form as AccX-Z/GyroX-Z/Temp

;.include "p33FJ32MC202.inc"
;.include	"Init_ASM_h.inc"

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

;Functions called from inside I2C_Data

;Start sequence includes setting I2C1CON
I2CSTARTSEQ:
    bset   I2C1CON,#0
CHECKSTART:
    btsc I2C1CON,#0
    GOTO CHECKSTART
    Return

I2CSTOPSEQ:
    bset   I2C1CON,#2
CHECKSTOP:
    btsc I2C1CON,#2
    GOTO CHECKSTOP
    Return

I2CREPEATSTART:
    bset I2C1CON, #1
CHECKREPEAT:
    btsc I2C1CON, #1
    GOTO CHECKREPEAT
    Return

I2CSENDNACK:
    bset I2C1CON, #5
    bset I2C1CON, #4
CHECKSENDNACK:
    btsc I2C1CON, #4
    GOTO CHECKSENDNACK
    Return

I2CSENDACK:
    bclr I2C1CON, #5
    bset I2C1CON, #4
CHECKSENDACK:
    btsc I2C1CON, #4
    GOTO CHECKSENDACK
    Return

RECEIVEWAIT:
    bset I2C1CON, #3
    btss I2C1STAT, #1
    GOTO RECEIVEWAIT
    Return

CLEARRECEIVEWAIT:
    btsc I2C1STAT, #1
    GOTO CLEARRECEIVEWAIT
    Return

;Function called from interrupt.s, I2C data transmission

GETACCTEMPGYRODATA:
    ;start seq
    Call I2CSTARTSEQ
    
    ;;;;;;is I2C1STAT #2 right to use/correct order? ;send slave address(1101000) + Write bit(0)
    mov #0b11010000, w1
  ;  btsc I2C1STATbits, #2
    mov w1, I2CTRN

    ;wait for transmit to complete
CHECKTRANSMIT1:
    btsc I2C1STAT, #0
    GOTO CHECKTRANSMIT1

    ;wait for acknowledge
ACKWAIT1:
    btsc I2C1STAT, #15
    GOTO ACKWAIT1

TRANSMITCOMPLETE1:
    btsc I2C1STAT, #14
    GOTO TRANSMITCOMPLETE1

    ;send slave register address
    mov #59, W0
    mov W0, I2CTRN

CHECKTRANSMIT2:
    btsc I2C1STAT, #0
    GOTO CHECKTRANSMIT2
    ;wait for acknowledge
ACKWAIT2:
    btsc I2C1STAT, #15
    GOTO ACKWAIT2

TRANSMITCOMPLETE2:
    btsc I2C1STAT, #14
    GOTO TRANSMITCOMPLETE2

    ;Repeated Start
    Call I2CREPEATSTART
    ;;I2CREPEATSTARTFINISHED

    ;send slave address + Read bit
    mov #0b11010001, w0
   ; btsc I2C1STAT, #2
    mov w0, I2CTRN
    ;wait for transmit to complete
CHECKTRANSMIT3:
    btsc I2C1STAT, #0
    GOTO CHECKTRANSMIT3

    ;wait for acknowledge
ACKWAIT3:
    btsc I2C1STAT, #15
    GOTO ACKWAIT3
TRANSMITCOMPLETE3:
    btsc I2C1STAT, #14
    GOTO TRANSMITCOMPLETE3

/**REPEAT THE FOLLOWING SEQUENCE FOR ALL ACC TEMP AND GYRO
;Description: Take both bytes for each x,y,z coordinate (x1, x2) and add them
;             Returns AccX/Y/Z, Temperature, GyroX/Y/Z
*/
;I2C1STATbits.RBF=1 when receive complete

;START OF REPEATING SEQUENCE for AccX
Call RECEIVEWAIT

;receive Accelerometer X1 data
  
;;;;;;;;;;;;;;;;;;;;;;;;;
;;Wb=w1, Wns=w2, Wnd=w3
    mov I2CRCV, W1
    Call CLEARRECEIVEWAIT
    mov 8, W2
    ;Wnd=Left shift Wb by Wns
    SL W1, W2, W3
    mov W3, AccX1
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

    ;send ACK
    Call I2CSENDACK
    ;;I2CSENDACKFINISHED

    ;I2C1STATbits.RBF=1 when receive complete
    Call RECEIVEWAIT
   
    ;receive Accelerometer X2 data
    mov I2CRCV, WREG

    Call CLEARRECEIVEWAIT

    ;add AccX1 to AccX2

;;;;;;;;;;;;;;;;;;;;;
    add AccX1
    RRNC AccX1
    RRNC AccXOLD
    mov AccX1, WREG
    add AccXOLD, WREG
    mov WREG, AccX
;;;;;;;;;;;;;;;;;;;;;;

    ;Acculmulated AccelerometerX value
    
    ;send ACK
    Call I2CSENDACK
    ;;I2CSENDACKFINISHED
;END OF REPEATING SEQUENCE for AccX

;START OF REPEATING SEQUENCE for AccY
;I2C1STATbits.RBF=1 when receive complete
    Call RECEIVEWAIT

;receive Accelerometer Y1 data

;;;;;;;;;;;;;;;;;;;;;;;;;
;;Wb=w1, Wns=w2, Wnd=w3
    mov I2CRCV, W1
    Call CLEARRECEIVEWAIT
    mov 8, W2
    ;Wnd=Left shift Wb by Wns
    SL W1, W2, W3
    mov W3, AccY1
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

    ;send ACK
    Call I2CSENDACK
    ;;I2CSENDACKFINISHED

    ;I2C1STATbits.RBF=1 when receive complete
Call RECEIVEWAIT

    ;receive Accelerometer Y2 data
    mov I2CRCV, WREG

Call CLEARRECEIVEWAIT

;;;;;;;;;;;;;;;;;;;;;
    add AccY1
    RRNC AccY1
    RRNC AccYOLD
    mov AccY1, WREG
    add AccYOLD, WREG
    mov WREG, AccY
;;;;;;;;;;;;;;;;;;;;;;

    ;send ACK
    Call I2CSENDACK
    ;;I2CSENDACKFINISHED
;;END OF REPEATING SEQUENCE for AccY

;START OF REPEATING SEQUENCE for AccZ
;I2C1STATbits.RBF=1 when receive complete
Call RECEIVEWAIT
   
;receive Accelerometer Z1 data

;;;;;;;;;;;;;;;;;;;;;;;;;
;;Wb=w1, Wns=w2, Wnd=w3

    mov I2CRCV, W1
    Call CLEARRECEIVEWAIT
    mov 8, W2
    ;Wnd=Left shift Wb by Wns
    SL W1, W2, W3
    mov W3, AccZ1
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

    ;send ACK
    Call I2CSENDACK
    ;;I2CSENDACKFINISHED

    ;I2C1STATbits.RBF=1 when receive complete
    Call RECEIVEWAIT

   ;receive Accelerometer Z2 data
    mov I2CRCV, WREG

    Call CLEARRECEIVEWAIT

;;;;;;;;;;;;;;;;;;;;;
    add AccZ1
    RRNC AccZ1
    RRNC AccZOLD
    mov AccZ1, WREG
    add AccZOLD, WREG
    mov WREG, AccZ
;;;;;;;;;;;;;;;;;;;;;;

    ;send ACK
    Call I2CSENDACK
    ;;I2CSENDACKFINISHED
;END OF REPEATING SEQUENCE for AccZ



;START OF REPEATING SEQUENCE for Temperature
;I2C1STATbits.RBF=1 when receive complete
Call RECEIVEWAIT

;receive Temperature1 data

;;;;;;;;;;;;;;;;;;;;;;;;;
;;Wb=w1, Wns=w2, Wnd=w3
    mov I2CRCV, W1
    Call CLEARRECEIVEWAIT
    mov 8, W2
    ;Wnd=Left shift Wb by Wns
    SL W1, W2, W3
    mov W3, Temperature1
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

    ;send ACK
    Call I2CSENDACK
    ;;I2CSENDACKFINISHED

    ;I2C1STATbits.RBF=1 when receive complete
    Call RECEIVEWAIT

    ;receive Temperature2 data
    mov I2CRCV, WREG

    Call CLEARRECEIVEWAIT

     ;;;;;;;;;;;;;;;;;;;;;
    add Temperature1
    RRNC Temperature1
    RRNC TemperatureOLD
    mov Temperature1, WREG
    add TemperatureOLD, WREG
    mov WREG, Temperature
;;;;;;;;;;;;;;;;;;;;;;

    ;send ACK
    Call I2CSENDACK
    ;;I2CSENDACKFINISHED
;END OF REPEATING SEQUENCE for Temperature



;START OF REPEATING SEQUENCE for GyroX
;I2C1STATbits.RBF=1 when receive complete
    Call RECEIVEWAIT

;receive GYROX1 data

;;;;;;;;;;;;;;;;;;;;;;;;;
;;Wb=w1, Wns=w2, Wnd=w3
    mov I2CRCV, W1
    Call CLEARRECEIVEWAIT
    mov 8, W2
    ;Wnd=Left shift Wb by Wns
    SL W1, W2, W3
    mov W3, GyroX1
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

    ;send ACK
    Call I2CSENDACK
    ;;I2CSENDACKFINISHED

    ;I2C1STATbits.RBF=1 when receive complete
    Call RECEIVEWAIT

    ;receive Gyro X2 data
    mov I2CRCV, WREG

    Call CLEARRECEIVEWAIT

;;;;;;;;;;;;;;;;;;;;;
    add GyroX1
    RRNC GyroX1
    RRNC GyroXOLD
    mov GyroX1, WREG
    add GyroXOLD, WREG
    mov WREG, GyroX
;;;;;;;;;;;;;;;;;;;;;;

    ;send ACK
    Call I2CSENDACK
    ;;I2CSENDACKFINISHED
;END OF REPEATING SEQUENCE for GyroX



;START OF REPEATING SEQUENCE for GyroY
;I2C1STATbits.RBF=1 when receive complete
    Call RECEIVEWAIT

;receive Gyro Y1 data

;;;;;;;;;;;;;;;;;;;;;;;;;
;;Wb=w1, Wns=w2, Wnd=w3
    mov I2CRCV, W1
    Call CLEARRECEIVEWAIT
    mov 8, W2
    ;Wnd=Left shift Wb by Wns
    SL W1, W2, W3
    mov W3, GyroY1
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

    ;send ACK
    Call I2CSENDACK
    ;;I2CSENDACKFINISHED

    ;I2C1STATbits.RBF=1 when receive complete
    Call RECEIVEWAIT
 
    ;receive Gyro Y2 data
    mov I2CRCV, WREG

    Call CLEARRECEIVEWAIT

;;;;;;;;;;;;;;;;;;;;;
    add GyroY1
    RRNC GyroY1
    RRNC GyroYOLD
    mov GyroY1, WREG
    add GyroYOLD, WREG
    mov WREG, GyroY
;;;;;;;;;;;;;;;;;;;;;;

    ;send ACK
    Call I2CSENDACK
    ;;I2CSENDACKFINISHED
;END OF REPEATING SEQUENCE for GyroY



;START OF REPEATING SEQUENCE for GyroZ
;I2C1STATbits.RBF=1 when receive complete
    Call RECEIVEWAIT
   
;receive GyroZ1 data

;;;;;;;;;;;;;;;;;;;;;;;;;
;;Wb=w1, Wns=w2, Wnd=w3
    mov I2CRCV, W1
    Call CLEARRECEIVEWAIT
    mov 8, W2
    ;SL  Wb,Wns,Wnd   Wnd=Left shift Wb by Wns
    SL W1, W2, W3
    mov W3, GyroZ1
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

    ;send ACK
    Call I2CSENDACK
    ;;I2CSENDACKFINISHED

    ;I2C1STATbits.RBF=1 when receive complete
    Call RECEIVEWAIT

    ;receive Gyro Z2 data
    mov I2CRCV, WREG

    Call CLEARRECEIVEWAIT
   
;;;;;;;;;;;;;;;;;;;;;
    add GyroZ1
    RRNC GyroZ1
    RRNC GyroZOLD
    mov GyroZ1, WREG
    add GyroZOLD, WREG
    mov WREG, GyroZ
;;;;;;;;;;;;;;;;;;;;;;

    ;send ACK
    Call I2CSENDACK
    ;;I2CSENDACKFINISHED
;END OF REPEATING SEQUENCE for GyroZ
/*END OF FULL REPEATED SEQUENCE*/

;send nack
Call I2CSENDNACK
;;I2CSENDNACKFINISHED

;Stop sequence
Call I2CSTOPSEQ
;;I2CSTOPSEQFINISHED

Return
