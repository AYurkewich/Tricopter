.include "p33FJ32MC202.inc"
.include	"Init_ASM_h.inc"
;Functions called from inside I2C_Data
I2CSTARTSEQ
    bset   I2CCON, #bit1
CHECKSTART    
    btsc I2CCON, #bit1
    GOTO CHECKSTART 
    GOTO I2CSTARTSEQFINISHED


I2CSTOPSEQ
    bset   I2CCON, #bit3
CHECKSTOP
    btsc I2CCON, #bit3
    GOTO CHECKSTOP
    GOTO I2CSTOPSEQFINISHED


I2CREPEATSTART
    bset I2CCON, #bit2
CHECKREPEAT
    btsc I2CCON, #bit2
    GOTO CHECKREPEAT
    GOTO I2CREPEATSTARTFINISHED

I2CSENDNACK
    bset I2CCON, #bit5
    bset I2CCON, #bit4
CHECKSENDNACK
    btsc I2CCON, #bit4
    GOTO CHECKSENDNACK
    GOTO I2CSENDNACKFINISHED

I2CSENDACK
    bclr I2CCON, #bit5
    bset I2CCON, #bit4
CHECKSENDACK
    btsc I2CCON, #bit4
    GOTO CHECKSENDACK
    GOTO I2CSENDACKFINISHED

;Function called from interrupt.s, I2C data transmission

GETACCTEMPGYRODATA
    ;start seq
    GOTO I2CSTARTSEQ
    STARTSEQFINISHED

    ;send slave address(1101000) + Write bit(0)
    mov 0b11010000, w1
    mov w1, I2CTRN
    ;wait for transmit to complete
CHECKTRANSMIT
    btsc I2CSTAT, #bit0
    GOTO CHECKTRANSMIT

    ;wait for acknowledge
ACKWAIT
    btsc I2CSTAT, #bit15
    GOTO ACKWAIT
    
    ;send slave register address
    mov 0b00111011, w1
    mov w1, I2CTRN

    ;wait for acknowledge
ACKWAIT
    btsc I2CSTAT, #bit15
    GOTO ACKWAIT
    
    ;Repeated Start
    GOTO I2CREPEATSTART
    I2CREPEATSTARTFINISHED

    ;send slave address + Read bit
    mov 0b11010000, w1
    mov w1, I2CTRN
    ;wait for transmit to complete
CHECKTRANSMIT
    btsc I2CSTAT, #bit0
    GOTO CHECKTRANSMIT

    ;wait for acknowledge
ACKWAIT
    btsc I2CSTAT, #bit15
    GOTO ACKWAIT

;REPEAT THE FOLLOWING SEQUENCE FOR ALL ACC TEMP AND GYRO
;I2CSTATbits.RBF=1 when receive complete
RECIEVEWAIT
    btss I2CSTAT, #bit1
    GOTO RECIEVEWAIT
    
;receive Accelerometer X1 data   
    mov I2CRCV, w1

CLEARRECEIVEWAIT
    btsc I2CSTAT, #bit1
    GOTO CLEARRECIEVEWAIT

    mov w1, AccX1

    ;send ACK
    GOTO I2CSENDACK
    I2CSENDACKFINISHED
    
    ;I2CSTATbits.RBF=1 when receive complete
RECIEVEWAIT
    btss I2CSTAT, #bit1
    GOTO RECIEVEWAIT

    ;receive Accelerometer X2 data
    mov I2CRCV, w1

CLEARRECEIVEWAIT
    btsc I2CSTAT, #bit1
    GOTO CLEARRECIEVEWAIT

    mov w1, AccX2

    ;Acculmulated AccelerometerX value
    ;AccX= AccX1<<8+AccX2;
    mov 256, WREG
    mul AccX1
    mov w3, WREG
    add AccX2, WREG
    mov WREG, AccX

    ;send ACK
    GOTO I2CSENDACK
    I2CSENDACKFINISHED
;END OF REPEATING SEQUENCE FOR ALL ACC TEMP GYRO

;REPEAT THE FOLLOWING SEQUENCE FOR ALL ACC TEMP AND GYRO
;I2CSTATbits.RBF=1 when receive complete
RECIEVEWAIT
    btss I2CSTAT, #bit1
    GOTO RECIEVEWAIT

;receive Accelerometer Y1 data
    mov I2CRCV, w1

CLEARRECEIVEWAIT
    btsc I2CSTAT, #bit1
    GOTO CLEARRECIEVEWAIT

    mov w1, AccY1

    ;send ACK
    GOTO I2CSENDACK
    I2CSENDACKFINISHED

    ;I2CSTATbits.RBF=1 when receive complete
RECIEVEWAIT
    btss I2CSTAT, #bit1
    GOTO RECIEVEWAIT

    ;receive Accelerometer Y2 data
    mov I2CRCV, w1

CLEARRECEIVEWAIT
    btsc I2CSTAT, #bit1
    GOTO CLEARRECIEVEWAIT

    mov w1, AccY2

    ;Acculmulated AccelerometerY value
    ;AccY= AccY1<<8+AccY2;
    mov 256, WREG
    mul AccY1
    mov w3, WREG
    add AccY2, WREG
    mov WREG, AccY

    ;send ACK
    GOTO I2CSENDACK
    I2CSENDACKFINISHED
;END OF REPEATING SEQUENCE FOR ALL ACC TEMP GYRO

;REPEAT THE FOLLOWING SEQUENCE FOR ALL ACC TEMP AND GYRO
;I2CSTATbits.RBF=1 when receive complete
RECIEVEWAIT
    btss I2CSTAT, #bit1
    GOTO RECIEVEWAIT

;receive Accelerometer Z1 data
    mov I2CRCV, w1

CLEARRECEIVEWAIT
    btsc I2CSTAT, #bit1
    GOTO CLEARRECIEVEWAIT

    mov w1, AccZ1

    ;send ACK
    GOTO I2CSENDACK
    I2CSENDACKFINISHED

    ;I2CSTATbits.RBF=1 when receive complete
RECIEVEWAIT
    btss I2CSTAT, #bit1
    GOTO RECIEVEWAIT

    ;receive Accelerometer Z2 data
    mov I2CRCV, w1

CLEARRECEIVEWAIT
    btsc I2CSTAT, #bit1
    GOTO CLEARRECIEVEWAIT

    mov w1, AccZ2

    ;Acculmulated AccelerometerZ value
    ;AccZ= AccZ1<<8+AccZ2;
    mov 256, WREG
    mul AccZ1
    mov w3, WREG
    add AccZ2, WREG
    mov WREG, AccZ

    ;send ACK
    GOTO I2CSENDACK
    I2CSENDACKFINISHED
;END OF REPEATING SEQUENCE FOR ALL ACC TEMP GYRO

;REPEAT THE FOLLOWING SEQUENCE FOR ALL ACC TEMP AND GYRO
;I2CSTATbits.RBF=1 when receive complete
RECIEVEWAIT
    btss I2CSTAT, #bit1
    GOTO RECIEVEWAIT

;receive Temperature1 data
    mov I2CRCV, w1

CLEARRECEIVEWAIT
    btsc I2CSTAT, #bit1
    GOTO CLEARRECIEVEWAIT

    mov w1, Temperature1

    ;send ACK
    GOTO I2CSENDACK
    I2CSENDACKFINISHED

    ;I2CSTATbits.RBF=1 when receive complete
RECIEVEWAIT
    btss I2CSTAT, #bit1
    GOTO RECIEVEWAIT

    ;receive Temperature2 data
    mov I2CRCV, w1

CLEARRECEIVEWAIT
    btsc I2CSTAT, #bit1
    GOTO CLEARRECIEVEWAIT

    mov w1, Temperature1

    ;Acculmulated Temperature value
    ;Temperature= Temperature1<<8+Temperature2;
    mov 256, WREG
    mul Temperature1
    mov w3, WREG
    add Temperature2, WREG
    mov WREG, Temperature

    ;send ACK
    GOTO I2CSENDACK
    I2CSENDACKFINISHED
;END OF REPEATING SEQUENCE FOR ALL ACC TEMP GYRO

;REPEAT THE FOLLOWING SEQUENCE FOR ALL ACC TEMP AND GYRO
;I2CSTATbits.RBF=1 when receive complete
RECIEVEWAIT
    btss I2CSTAT, #bit1
    GOTO RECIEVEWAIT

;receive GYROX1 data
    mov I2CRCV, w1

CLEARRECEIVEWAIT
    btsc I2CSTAT, #bit1
    GOTO CLEARRECIEVEWAIT

    mov w1, GyroX1

    ;send ACK
    GOTO I2CSENDACK
    I2CSENDACKFINISHED

    ;I2CSTATbits.RBF=1 when receive complete
RECIEVEWAIT
    btss I2CSTAT, #bit1
    GOTO RECIEVEWAIT

    ;receive Gyro X2 data
    mov I2CRCV, w1

CLEARRECEIVEWAIT
    btsc I2CSTAT, #bit1
    GOTO CLEARRECIEVEWAIT

    mov w1, GyroX2

    ;Acculmulated GyroX value
    ;GyroX= GyroX1<<8+GyroX2;
    mov 256, WREG
    mul GyroX1
    mov w3, WREG
    add GyroX2, WREG
    mov WREG, GyroX

    ;send ACK
    GOTO I2CSENDACK
    I2CSENDACKFINISHED
;END OF REPEATING SEQUENCE FOR ALL ACC TEMP GYRO

;REPEAT THE FOLLOWING SEQUENCE FOR ALL ACC TEMP AND GYRO
;I2CSTATbits.RBF=1 when receive complete
RECIEVEWAIT
    btss I2CSTAT, #bit1
    GOTO RECIEVEWAIT

;receive Gyro Y1 data
    mov I2CRCV, w1

CLEARRECEIVEWAIT
    btsc I2CSTAT, #bit1
    GOTO CLEARRECIEVEWAIT

    mov w1, GyroY1

    ;send ACK
    GOTO I2CSENDACK
    I2CSENDACKFINISHED

    ;I2CSTATbits.RBF=1 when receive complete
RECIEVEWAIT
    btss I2CSTAT, #bit1
    GOTO RECIEVEWAIT

    ;receive Gyro Y2 data
    mov I2CRCV, w1

CLEARRECEIVEWAIT
    btsc I2CSTAT, #bit1
    GOTO CLEARRECIEVEWAIT

    mov w1, GyroY2

    ;Acculmulated GyroY value
    ;GyroY= GyroY1<<8+GyroY2;
    mov 256, WREG
    mul GyroY1
    mov w3, WREG
    add GyroY2, WREG
    mov WREG, GyroY

    ;send ACK
    GOTO I2CSENDACK
    I2CSENDACKFINISHED
;END OF REPEATING SEQUENCE FOR ALL ACC TEMP GYRO

;REPEAT THE FOLLOWING SEQUENCE FOR ALL ACC TEMP AND GYRO
;I2CSTATbits.RBF=1 when receive complete
RECIEVEWAIT
    btss I2CSTAT, #bit1
    GOTO RECIEVEWAIT

;receive GyroZ1 data
    mov I2CRCV, w1

CLEARRECEIVEWAIT
    btsc I2CSTAT, #bit1
    GOTO CLEARRECIEVEWAIT

    mov w1, GyroZ1

    ;send ACK
    GOTO I2CSENDACK
    I2CSENDACKFINISHED

    ;I2CSTATbits.RBF=1 when receive complete
RECIEVEWAIT
    btss I2CSTAT, #bit1
    GOTO RECIEVEWAIT

    ;receive Gyro Z2 data
    mov I2CRCV, w1

CLEARRECEIVEWAIT
    btsc I2CSTAT, #bit1
    GOTO CLEARRECIEVEWAIT

    mov w1, GyroZ2

    ;Acculmulated GyroZ value
    ;GyroZ= GyroZ1<<8+GyroZ2;
    mov 256, WREG
    mul GyroZ1
    mov w3, WREG
    add GyroZ2, WREG
    mov WREG, GyroZ

    ;send ACK
    GOTO I2CSENDACK
    I2CSENDACKFINISHED
;END OF REPEATING SEQUENCE FOR ALL ACC TEMP GYRO

;send nack
GOTO I2CSENDNACK
I2CSENDNACKFINISHED

;Stop sequence
GOTO I2CSTOPSEQ
I2CSTOPSEQFINISHED
   
GOTO I2CDATATRANSMISSIONCOMPLETE



