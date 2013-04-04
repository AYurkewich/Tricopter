;Set up I2C comunication and store data in bit form as AccX-Z/GyroX-Z/Temp

.include "p33FJ32MC202.inc"
.include	"Init_ASM_h.inc"
;Functions called from inside I2C_Data

;Start sequence includes setting I2CCON
I2CSTARTSEQ:
    bset   I2CCON,#1
CHECKSTART:
    btsc I2CCON,#1
    GOTO CHECKSTART
    Return


I2CSTOPSEQ:
    bset   I2CCON,#3
CHECKSTOP:
    btsc I2CCON,#3
    GOTO CHECKSTOP
    Return


I2CREPEATSTART:
    bset I2CCON, #2
CHECKREPEAT:
    btsc I2CCON, #2
    GOTO CHECKREPEAT
    Return

I2CSENDNACK:
    bset I2CCON, #5
    bset I2CCON, #4
CHECKSENDNACK:
    btsc I2CCON, #4
    GOTO CHECKSENDNACK
    Return

I2CSENDACK:
    bclr I2CCON, #5
    bset I2CCON, #4
CHECKSENDACK:
    btsc I2CCON, #4
    GOTO CHECKSENDACK
    Return

RECEIVEWAIT:
    btss I2CSTAT, #1
    GOTO RECEIVEWAIT
    Return

CLEARRECEIVEWAIT:
    btsc I2CSTAT, #1
    GOTO CLEARRECEIVEWAIT
    Return

;Function called from interrupt.s, I2C data transmission

GETACCTEMPGYRODATA:
    ;start seq
    Call I2CSTARTSEQ
    
    ;;;;;;is this the right value? ;send slave address(1101000) + Write bit(0)
    mov b11010000, w1
    mov w1, I2CTRN
    ;wait for transmit to complete
CHECKTRANSMIT1:
    btsc I2CSTAT, #0
    GOTO CHECKTRANSMIT1

    ;wait for acknowledge
ACKWAIT1:
    btsc I2CSTAT, #15
    GOTO ACKWAIT1

    ;send slave register address
    mov .59, WREG  ;;why doesnt this work? start with a 1?
    mov WREG, I2CTRN

    ;wait for acknowledge
ACKWAIT2:
    btsc I2CSTAT, #15
    GOTO ACKWAIT2

    ;Repeated Start
    Call I2CREPEATSTART
    ;;I2CREPEATSTARTFINISHED

    ;send slave address + Read bit
    mov .68, w1
    mov w1, I2CTRN
    ;wait for transmit to complete
CHECKTRANSMIT2:
    btsc I2CSTAT, #0
    GOTO CHECKTRANSMIT2

    ;wait for acknowledge
ACKWAIT3:
    btsc I2CSTAT, #15
    GOTO ACKWAIT3

/**REPEAT THE FOLLOWING SEQUENCE FOR ALL ACC TEMP AND GYRO
;Description: Take both bytes for each x,y,z coordinate (x1, x2) and add them
;             Returns AccX/Y/Z, Temperature, GyroX/Y/Z
*/
;I2CSTATbits.RBF=1 when receive complete

;START OF REPEATING SEQUENCE for AccX
Call RECEIVEWAIT

;receive Accelerometer X1 data
    mov I2CRCV, w1

Call CLEARRECEIVEWAIT

    mov w1, AccX1

    ;send ACK
    Call I2CSENDACK
    ;;I2CSENDACKFINISHED

    ;I2CSTATbits.RBF=1 when receive complete
Call RECEIVEWAIT
   

    ;receive Accelerometer X2 data
    mov I2CRCV, WREG

Call CLEARRECEIVEWAIT

;add AccX1 to AccX2
    add AccX1
    RRNC AccX1
    ;Acculmulated AccelerometerX value
    mov AccX1, WREG
    mov WREG, AccX

    ;send ACK
    Call I2CSENDACK
    ;;I2CSENDACKFINISHED
;END OF REPEATING SEQUENCE for AccX



;START OF REPEATING SEQUENCE for AccY
;I2CSTATbits.RBF=1 when receive complete
Call RECEIVEWAIT

;receive Accelerometer Y1 data
    mov I2CRCV, w1

Call CLEARRECEIVEWAIT

    mov w1, AccY1

    ;send ACK
    Call I2CSENDACK
    ;;I2CSENDACKFINISHED

    ;I2CSTATbits.RBF=1 when receive complete
Call RECEIVEWAIT

    ;receive Accelerometer Y2 data
    mov I2CRCV, WREG

Call CLEARRECEIVEWAIT

;add AccY1 to AccY2
    add AccY1
    RRNC AccY1
    ;Acculmulated AccelerometerY value
    mov AccY1, WREG
    mov WREG, AccY
    ;send ACK
    Call I2CSENDACK
    ;;I2CSENDACKFINISHED
;;END OF REPEATING SEQUENCE for AccY



;START OF REPEATING SEQUENCE for AccZ
;I2CSTATbits.RBF=1 when receive complete
Call RECEIVEWAIT
   
;receive Accelerometer Z1 data
    mov I2CRCV, w1

Call CLEARRECEIVEWAIT

    mov w1, AccZ1

    ;send ACK
    Call I2CSENDACK
    ;;I2CSENDACKFINISHED

    ;I2CSTATbits.RBF=1 when receive complete
Call RECEIVEWAIT

   ;receive Accelerometer Z2 data
   mov I2CRCV, WREG

Call CLEARRECEIVEWAIT

;add AccZ1 to AccZ2
    add AccZ1
    RRNC AccZ1
    ;Acculmulated AccelerometerZ value
    mov AccZ1, WREG
    mov WREG, AccZ

    ;send ACK
    Call I2CSENDACK
    ;;I2CSENDACKFINISHED
;END OF REPEATING SEQUENCE for AccZ



;START OF REPEATING SEQUENCE for Temperature
;I2CSTATbits.RBF=1 when receive complete
Call RECEIVEWAIT

;receive Temperature1 data
    mov I2CRCV, w1

Call CLEARRECEIVEWAIT

    mov w1, Temperature1

    ;send ACK
    Call I2CSENDACK
    ;;I2CSENDACKFINISHED

    ;I2CSTATbits.RBF=1 when receive complete
Call RECEIVEWAIT

    ;receive Temperature2 data
    mov I2CRCV, WREG

Call CLEARRECEIVEWAIT

    add Temperature1
    RRNC Temperature1

    ;Acculmulated Temperature value
    ;Temperature= Temperature1<<8+Temperature2;
;;;;;;;;;;    mov w3, WREG
    mov Temperature1, WREG
    mov WREG, Temperature

    ;send ACK
    Call I2CSENDACK
    ;;I2CSENDACKFINISHED
;END OF REPEATING SEQUENCE for Temperature



;START OF REPEATING SEQUENCE for GyroX
;I2CSTATbits.RBF=1 when receive complete
Call RECEIVEWAIT

;receive GYROX1 data
    mov I2CRCV, w1

Call CLEARRECEIVEWAIT

    mov w1, GyroX1

    ;send ACK
    Call I2CSENDACK
    ;;I2CSENDACKFINISHED

    ;I2CSTATbits.RBF=1 when receive complete
Call RECEIVEWAIT

    ;receive Gyro X2 data
    mov I2CRCV, WREG

Call CLEARRECEIVEWAIT

    add GyroX1
    RRNC GyroX1
    ;Acculmulated GyroX value
    ;GyroX= GyroX1<<8+GyroX2;
    mov GyroX1, WREG
    mov WREG, GyroX

    ;send ACK
    Call I2CSENDACK
    ;;I2CSENDACKFINISHED
;END OF REPEATING SEQUENCE for GyroX



;START OF REPEATING SEQUENCE for GyroY
;I2CSTATbits.RBF=1 when receive complete
Call RECEIVEWAIT

;receive Gyro Y1 data
    mov I2CRCV, w1

Call CLEARRECEIVEWAIT

    mov w1, GyroY1

    ;send ACK
    Call I2CSENDACK
    ;;I2CSENDACKFINISHED

    ;I2CSTATbits.RBF=1 when receive complete
Call RECEIVEWAIT
 
    ;receive Gyro Y2 data
    mov I2CRCV, WREG

Call CLEARRECEIVEWAIT

    add GyroY1
    RRNC GyroY1
    mov GyroY1, WREG
    mov WREG, GyroY

    ;send ACK
    Call I2CSENDACK
    ;;I2CSENDACKFINISHED
;END OF REPEATING SEQUENCE for GyroY



;START OF REPEATING SEQUENCE for GyroZ
;I2CSTATbits.RBF=1 when receive complete
Call RECEIVEWAIT
   
;receive GyroZ1 data
    mov I2CRCV, w1

Call CLEARRECEIVEWAIT

    mov w1, GyroZ1

    ;send ACK
    Call I2CSENDACK
    ;;I2CSENDACKFINISHED

    ;I2CSTATbits.RBF=1 when receive complete
Call RECEIVEWAIT

    ;receive Gyro Z2 data
    mov I2CRCV, WREG

Call CLEARRECEIVEWAIT
   
    add GyroZ1
    RRNC GyroZ1
    mov GyroZ1, WREG
    mov WREG, GyroZ

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
