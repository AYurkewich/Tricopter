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
    GOTO I2CSTARTSEQFINISHED


I2CSTOPSEQ:
    bset   I2CCON,#3
CHECKSTOP:
    btsc I2CCON,#3
    GOTO CHECKSTOP
    GOTO I2CSTOPSEQFINISHED


I2CREPEATSTART:
    bset I2CCON, #2
CHECKREPEAT:
    btsc I2CCON, #2
    GOTO CHECKREPEAT
    GOTO I2CREPEATSTARTFINISHED

I2CSENDNACK:
    bset I2CCON, #5
    bset I2CCON, #4
CHECKSENDNACK:
    btsc I2CCON, #4
    GOTO CHECKSENDNACK
    GOTO I2CSENDNACKFINISHED

I2CSENDACK:
    bclr I2CCON, #5
    bset I2CCON, #4
CHECKSENDACK:
    btsc I2CCON, #4
    GOTO CHECKSENDACK
    GOTO I2CSENDACKFINISHED

;Function called from interrupt.s, I2C data transmission

GETACCTEMPGYRODATA:
    ;start seq
    GOTO I2CSTARTSEQ
    ;;STARTSEQFINISHED

    ;send slave address(1101000) + Write bit(0)
    mov 0x68, w1
    mov w1, I2CTRN
    ;wait for transmit to complete
CHECKTRANSMIT:
    btsc I2CSTAT, #0
    GOTO CHECKTRANSMIT

    ;wait for acknowledge
ACKWAIT:
    btsc I2CSTAT, #15
    GOTO ACKWAIT

    ;send slave register address
    mov 0x3B, WREG  ;;why doesnt this work? start with a 1?
    mov WREG, I2CTRN

    ;wait for acknowledge
ACKWAIT:
    btsc I2CSTAT, #15
    GOTO ACKWAIT

    ;Repeated Start
    GOTO I2CREPEATSTART
    ;;I2CREPEATSTARTFINISHED

    ;send slave address + Read bit
    mov 0x68, w1
    mov w1, I2CTRN
    ;wait for transmit to complete
CHECKTRANSMIT:
    btsc I2CSTAT, #0
    GOTO CHECKTRANSMIT

    ;wait for acknowledge
ACKWAIT:
    btsc I2CSTAT, #15
    GOTO ACKWAIT



/**REPEAT THE FOLLOWING SEQUENCE FOR ALL ACC TEMP AND GYRO
;Description: Take both bytes for each x,y,z coordinate (x1, x2) and add them
;             Returns AccX/Y/Z, Temperature, GyroX/Y/Z
*/
;I2CSTATbits.RBF=1 when receive complete

;START OF REPEATING SEQUENCE for AccX
RECIEVEWAIT:
    btss I2CSTAT, #1
    GOTO RECIEVEWAIT

;receive Accelerometer X1 data
    mov I2CRCV, w1

CLEARRECEIVEWAIT:
    btsc I2CSTAT, #1
    GOTO CLEARRECIEVEWAIT

    mov w1, AccX1

    ;send ACK
    GOTO I2CSENDACK
    ;;I2CSENDACKFINISHED

    ;I2CSTATbits.RBF=1 when receive complete
RECIEVEWAIT:
    btss I2CSTAT, #1
    GOTO RECIEVEWAIT

    ;receive Accelerometer X2 data
    mov I2CRCV, w1

CLEARRECEIVEWAIT:
    btsc I2CSTAT, #1
    GOTO CLEARRECIEVEWAIT

    mov w1, AccX2

    ;Acculmulated AccelerometerX value
    ;AccX= AccX1<<8+AccX2;
    mov 256, WREG           ;move 100000000 to WREG
    mul AccX1               ;multiply AccX1 by 100000000
;;;;;;;;;;    mov w3, WREG            ;move
    add AccX2, WREG         ;add AccX2 to AccX1*E8 = 16 bit binary
    mov WREG, AccX          ;move 16 bit value to AccX

    ;send ACK
    GOTO I2CSENDACK
    ;;I2CSENDACKFINISHED
;END OF REPEATING SEQUENCE for AccX



;START OF REPEATING SEQUENCE for AccY
;I2CSTATbits.RBF=1 when receive complete
RECIEVEWAIT:
    btss I2CSTAT, #1
    GOTO RECIEVEWAIT

;receive Accelerometer Y1 data
    mov I2CRCV, w1

CLEARRECEIVEWAIT:
    btsc I2CSTAT, #1
    GOTO CLEARRECIEVEWAIT

    mov w1, AccY1

    ;send ACK
    GOTO I2CSENDACK
    ;;I2CSENDACKFINISHED

    ;I2CSTATbits.RBF=1 when receive complete
RECIEVEWAIT:
    btss I2CSTAT, #1
    GOTO RECIEVEWAIT

    ;receive Accelerometer Y2 data
    mov I2CRCV, w1

CLEARRECEIVEWAIT:
    btsc I2CSTAT, #1
    GOTO CLEARRECIEVEWAIT

    mov w1, AccY2

    ;Acculmulated AccelerometerY value
    ;AccY= AccY1<<8+AccY2;
    mov 256, WREG
    mul AccY1
;;;;;;;;;;    mov w3, WREG
    add AccY2, WREG
    mov WREG, AccY

    ;send ACK
    GOTO I2CSENDACK
    ;;I2CSENDACKFINISHED
;;END OF REPEATING SEQUENCE for AccY



;START OF REPEATING SEQUENCE for AccZ
;I2CSTATbits.RBF=1 when receive complete
RECIEVEWAIT:
    btss I2CSTAT, #1
    GOTO RECIEVEWAIT

;receive Accelerometer Z1 data
    mov I2CRCV, w1

CLEARRECEIVEWAIT:
    btsc I2CSTAT, #1
    GOTO CLEARRECIEVEWAIT

    mov w1, AccZ1

    ;send ACK
    GOTO I2CSENDACK
    ;;I2CSENDACKFINISHED

    ;I2CSTATbits.RBF=1 when receive complete
RECIEVEWAIT:
    btss I2CSTAT, #1
    GOTO RECIEVEWAIT

    ;receive Accelerometer Z2 data
    mov I2CRCV, w1

CLEARRECEIVEWAIT:
    btsc I2CSTAT, #1
    GOTO CLEARRECIEVEWAIT

    mov w1, AccZ2

    ;Acculmulated AccelerometerZ value
    ;AccZ= AccZ1<<8+AccZ2;
    mov 256, WREG
    mul AccZ1
;;;;;;;;;;    mov w3, WREG
    add AccZ2, WREG
    mov WREG, AccZ

    ;send ACK
    GOTO I2CSENDACK
    ;;I2CSENDACKFINISHED
;END OF REPEATING SEQUENCE for AccZ



;START OF REPEATING SEQUENCE for Temperature
;I2CSTATbits.RBF=1 when receive complete
RECIEVEWAIT:
    btss I2CSTAT, #1
    GOTO RECIEVEWAIT

;receive Temperature1 data
    mov I2CRCV, w1

CLEARRECEIVEWAIT:
    btsc I2CSTAT, #1
    GOTO CLEARRECIEVEWAIT

    mov w1, Temperature1

    ;send ACK
    GOTO I2CSENDACK
    ;;I2CSENDACKFINISHED

    ;I2CSTATbits.RBF=1 when receive complete
RECIEVEWAIT:
    btss I2CSTAT, #1
    GOTO RECIEVEWAIT

    ;receive Temperature2 data
    mov I2CRCV, w1

CLEARRECEIVEWAIT:
    btsc I2CSTAT, #1
    GOTO CLEARRECIEVEWAIT

    mov w1, Temperature1

    ;Acculmulated Temperature value
    ;Temperature= Temperature1<<8+Temperature2;
    mov 256, WREG
    mul Temperature1
;;;;;;;;;;    mov w3, WREG
    add Temperature2, WREG
    mov WREG, Temperature

    ;send ACK
    GOTO I2CSENDACK
    ;;I2CSENDACKFINISHED
;END OF REPEATING SEQUENCE for Temperature



;START OF REPEATING SEQUENCE for GyroX
;I2CSTATbits.RBF=1 when receive complete
RECIEVEWAIT:
    btss I2CSTAT, #1
    GOTO RECIEVEWAIT

;receive GYROX1 data
    mov I2CRCV, w1

CLEARRECEIVEWAIT:
    btsc I2CSTAT, #1
    GOTO CLEARRECIEVEWAIT

    mov w1, GyroX1

    ;send ACK
    GOTO I2CSENDACK
    ;;I2CSENDACKFINISHED

    ;I2CSTATbits.RBF=1 when receive complete
RECIEVEWAIT:
    btss I2CSTAT, #1
    GOTO RECIEVEWAIT

    ;receive Gyro X2 data
    mov I2CRCV, w1

CLEARRECEIVEWAIT:
    btsc I2CSTAT, #1
    GOTO CLEARRECIEVEWAIT

    mov w1, GyroX2

    ;Acculmulated GyroX value
    ;GyroX= GyroX1<<8+GyroX2;
    mov 256, WREG
    mul GyroX1
;;;;;;;;;;    mov w3, WREG
    add GyroX2, WREG
    mov WREG, GyroX

    ;send ACK
    GOTO I2CSENDACK
    ;;I2CSENDACKFINISHED
;END OF REPEATING SEQUENCE for GyroX



;START OF REPEATING SEQUENCE for GyroY
;I2CSTATbits.RBF=1 when receive complete
RECIEVEWAIT:
    btss I2CSTAT, #1
    GOTO RECIEVEWAIT

;receive Gyro Y1 data
    mov I2CRCV, w1

CLEARRECEIVEWAIT:
    btsc I2CSTAT, #1
    GOTO CLEARRECIEVEWAIT

    mov w1, GyroY1

    ;send ACK
    GOTO I2CSENDACK
    ;;I2CSENDACKFINISHED

    ;I2CSTATbits.RBF=1 when receive complete
RECIEVEWAIT:
    btss I2CSTAT, #1
    GOTO RECIEVEWAIT

    ;receive Gyro Y2 data
    mov I2CRCV, w1

CLEARRECEIVEWAIT:
    btsc I2CSTAT, #1
    GOTO CLEARRECIEVEWAIT

    mov w1, GyroY2

    ;Acculmulated GyroY value
    ;GyroY= GyroY1<<8+GyroY2;
    mov 256, WREG
    mul GyroY1
;;;;;;;;;;    mov w3, WREG
    add GyroY2, WREG
    mov WREG, GyroY

    ;send ACK
    GOTO I2CSENDACK
    ;;I2CSENDACKFINISHED
;END OF REPEATING SEQUENCE for GyroY



;START OF REPEATING SEQUENCE for GyroZ
;I2CSTATbits.RBF=1 when receive complete
RECIEVEWAIT:
    btss I2CSTAT, #1
    GOTO RECIEVEWAIT

;receive GyroZ1 data
    mov I2CRCV, w1

CLEARRECEIVEWAIT:
    btsc I2CSTAT, #1
    GOTO CLEARRECIEVEWAIT

    mov w1, GyroZ1

    ;send ACK
    GOTO I2CSENDACK
    ;;I2CSENDACKFINISHED

    ;I2CSTATbits.RBF=1 when receive complete
RECIEVEWAIT:
    btss I2CSTAT, #1
    GOTO RECIEVEWAIT

    ;receive Gyro Z2 data
    mov I2CRCV, w1

CLEARRECEIVEWAIT:
    btsc I2CSTAT, #1
    GOTO CLEARRECIEVEWAIT

    mov w1, GyroZ2

    ;Acculmulated GyroZ value
    ;GyroZ= GyroZ1<<8+GyroZ2;
    mov 256, WREG
    mul GyroZ1
;;;;;;;;;;    mov w3, WREG
    add GyroZ2, WREG
    mov WREG, GyroZ

    ;send ACK
    GOTO I2CSENDACK
    ;;I2CSENDACKFINISHED
;END OF REPEATING SEQUENCE for GyroZ
/*END OF FULL REPEATED SEQUENCE*/



;send nack
GOTO I2CSENDNACK
;;I2CSENDNACKFINISHED

;Stop sequence
GOTO I2CSTOPSEQ
;;I2CSTOPSEQFINISHED

GOTO I2CDATATRANSMISSIONCOMPLETE
