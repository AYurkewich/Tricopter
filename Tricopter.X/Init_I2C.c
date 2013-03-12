


#include "p33Fxxxx.h"
#include "i2c.h"
void Init_I2C(void)
{
////////HOW TO USE I2C/////////////////
//http://www.robot-electronics.co.uk/acatalog/I2C_Tutorial.html
 //to write to a slave device:
 //1. Send a start sequence
 //2. Send the I2C address of the slave with the R/W bit low (even address)
 //3. Send the internal register number you want to write to
 //4. Send the data byte
 //5. [Optionally, send any further data bytes]
 //6. Send the stop sequence.

 //to read from save device:
 //1. Send a start sequence
 //2. Send 0xC0 ( I2C address of the CMPS03 with the R/W bit low (even address)
 //3. Send 0x01 (Internal address of the bearing register)
 //4. Send a start sequence again (repeated start)
 //5. Send 0xC1 ( I2C address of the CMPS03 with the R/W bit high (odd address)
 //6. Read data byte from CMPS03
 //7. Send the stop sequence.
//may need to add pull up resistors b/w SDA and 5+ and SCL and 5+
// May need to change port pins and initialization for different processor

//#define SCL     TRISB4 // I2C bus
//#define SDA     TRISB1 //
//#define SCL_IN  RB4    //
//#define SDA_IN  RB1    //

//To initialize the ports set the output registers to 0 and the tristate registers to 1 which disables the outputs and allows them to be pulled high by the resistors.
//SDA = SCL = 1;
 //SCL_IN = SDA_IN = 0;

//We use a small delay routine between SDA and SCL changes to give a clear sequence on the I2C bus. This is nothing more than a subroutine call and return.
//void i2c_dly(void)
 //{
 //}

//The following 4 functions provide the primitive start, stop, read and write sequences. All I2C transactions can be built up from these.
//void i2c_start(void)
// {
//   SDA = 1;             // i2c start bit sequence
//   i2c_dly();
//   SCL = 1;
//   i2c_dly();
//   SDA = 0;
//   i2c_dly();
//   SCL = 0;
//   i2c_dly();
// }

//void i2c_stop(void)
// {
 //  SDA = 0;             // i2c stop bit sequence
 //  i2c_dly();
 //  SCL = 1;
 //  i2c_dly();
  // SDA = 1;
  // i2c_dly();
 //}

//unsigned char i2c_rx(char ack)
// {
// char x, d=0;
 //  SDA = 1;
 //  for(x=0; x<8; x++) {
 //    d <<= 1;
 //    do {
 //      SCL = 1;
 //    }
  //   while(SCL_IN==0);    // wait for any SCL clock stretching
  //   i2c_dly();
  //   if(SDA_IN) d |= 1;
  //   SCL = 0;
  // }
  // if(ack) SDA = 0;
  // else SDA = 1;
  // SCL = 1;
  // i2c_dly();             // send (N)ACK bit
  // SCL = 0;
  // SDA = 1;
  // return d;
 //}

//bit i2c_tx(unsigned char d)
 //{
 //char x;
 //static bit b;
  // for(x=8; x; x--) {
  //   if(d&0x80) SDA = 1;
  //   else SDA = 0;
  //   SCL = 1;
  //   d <<= 1;
  //   SCL = 0;
  // }
  // SDA = 1;
  // SCL = 1;
  // i2c_dly();
  // b = SDA_IN;          // possible ACK bit
  // SCL = 0;
  // return b;
// }

// The 4 primitive functions above can easily be put together to form complete I2C transactions. Here's and example to start an SRF08 ranging in cm:

//i2c_start();              // send start sequence
// i2c_tx(0xE0);             // SRF08 I2C address with R/W bit clear
//i2c_tx(0x00);             // SRF08 command register address
//i2c_tx(0x51);             // command to start ranging in cm
//i2c_stop();               // send stop sequence

//Now after waiting 65mS for the ranging to complete (I've left that to you) the following example shows how to read the light sensor value from register 1 and the range result from registers 2 & 3.

//i2c_start();              // send start sequence
// i2c_tx(0xE0);             // SRF08 I2C address with R/W bit clear
//i2c_tx(0x01);             // SRF08 light sensor register address
//i2c_start();              // send a restart sequence
 //i2c_tx(0xE1);             // SRF08 I2C address with R/W bit set
//lightsensor = i2c_rx(1);  // get light sensor and send acknowledge. Internal register address will increment automatically.
// rangehigh = i2c_rx(1);    // get the high byte of the range and send acknowledge.
// rangelow = i2c_rx(0);     // get low byte of the range - note we don't acknowledge the last byte.
// i2c_stop();               // send stop sequence

//NOTE: If Slave not read to take data it will hold SCL Low
//NOTE: Must modify board add 1800ohm resistor b/w +5 and SDA and +5 and SCL
//Use Tris to control values sent to accelerometer (pic SDA/SCL input=+5V to accel SDA/SCL)
/////////////////END Tutorial/////////////////////////
//SDA port RB9
//SCL port RB8
//       5432109876543210


//Set Baud Rate//
    I2C1BRG=47;
///I2C Communication Registers /////
    //I2C CON Register////
//bit 15, Enable the module (Change to turn module off)
I2CCONbits.I2CEN=1;
//bit 14, unimplemented
//bit 13,stop module when PIC is in idle
I2CCONbits.I2CSIDL=1;
//bit 12, (when being used as slave)?
I2CCONbits.SCLREL=1;
//bit 11, Acknowledge all addresses?
I2CCONbits.IPMIEN=0;
//bit 10,Invensense chip has a 7 bit slave address
I2CCONbits.A10M=0;
//bit 9, slew rate control disabled
I2CCONbits.DISSLW=1;
//bit 8, enable I/O thresholds
I2CCONbits.SMEN=1;
//bit 7, module enabled for reception
I2CCONbits.GCEN=1;
//bit 6, (when being used as slave)?
I2CCONbits.STREN=0;
//bit 5,Send NACK when data recieved
I2CCONbits.ACKDT=1;
//bit 4, enable ACK sequence on recieve
I2CCONbits.ACKEN=0;
//bit 3,Recieve not enable (Change when you want to receive data)
I2CCONbits.RCEN=0;
//bit 2, Stop sequence not enable (Change when you want to send stop sequence)
I2CCONbits.PEN=0;
//bit 1, Repeated start not enabled (Change when you want to send repeated start)
I2CCONbits.RSEN=0;
//bit 0, Start sequence not enabled (Change when you want to send start sequence)
I2CCONbits.SEN=0;

///transmit initialization
I2CTRN = 0x0000;
///receive initialization
I2CRCV = 0x0000;

///I2C STATUS REGISTER///
//bit 15, 1=NACK received from slave (Check for 0 meaning slave acknowledges transmit)
//bit 14, Master transmit in progress
 //bit 10,bus collision
  //bit 9,General Call status received
 //bit 8,Ten bit address match
 //bit 7,Write to transmit bit did not fail
  //bit 6,Receive Overflow
  //bit 5,Indicates last byte recieved was data
 //bit 4,Stop bit detected last
 //bit 3,Start bit detected last
 //bit 2,Read=1 Write=0
 //bit 1, Data not recieved
  //bit 0, Transmit complete
}
/*
void I2CSTARTSEQ(void)
{
    I2CCONbits.SEN=1;
    while (I2CCONbits.SEN);
}

void I2CSTOPSEQ(void)
 {
    I2CCONbits.PEN=1;
    while (I2CCONbits.PEN);
}

void REPEATSTART(void)
{
    I2CCONbits.RSEN=1;
    while (I2CCONbits.RSEN);
}

void SENDNACK (void)
{
  I2CCONbits.ACKDT=1;
  I2CCONbits.ACKEN=1;
  while(I2C1CONbits.ACKEN);
}

void SENDACK (void)
{
  I2CCONbits.ACKDT=0;
  I2CCONbits.ACKEN=1;
  while(I2C1CONbits.ACKEN);
}

void ACCGYRODATA(int *AccX, int *AccY, int *AccZ, int *Temperature, int *GyroX, int *GyroY, int *GyroZ)
{
    int AccX1;
    int AccX2;
    int AccY1;
    int AccY2;
    int AccZ1;
    int AccZ2;
    int Temperature1;
    int Temperature2;
    int GyroX1;
    int GyroX2;
    int GyroY1;
    int GyroY2;
    int GyroZ1;
    int GyroZ2;

    //start seq
    I2CSTARTSEQ();
    //send slave address(1101000) + Write bit(0)
    I2CTRN= 0b11010000;
    //wait for transmit to complete
    while (I2CSTATbits.TBF);
    //wait for acknowledge
    while (I2CSTATbits.ACKSTAT);
    //send slave register address
    I2CTRN= 59;
    //wait for acknowledge
    while (I2CSTATbits.ACKSTAT);
    //Repeated Start
    REPEATSTART();
    //send slave address + Read bit
    I2CTRN= 0b11010001;
    //wait for transmit to complete
    while (I2CSTATbits.TBF);
    //wait for acknowledge
    while (I2CSTATbits.ACKSTAT);
    
    //receive Accelerometer X1 data
    AccX1= I2CRCV ;
    //I2CSTATbits.RBF=1 when receive complete
    while (I2CSTATbits.RBF==0);

    //send ACK
    SENDACK();
    //receive Accelerometer X2 data
    AccX2= I2CRCV ;
    //I2CSTATbits.RBF=1 when receive complete
    while (I2CSTATbits.RBF==0);

    //Acculmulated AccelerometerX value
    AccX= AccX1<<8+AccX2;

    //send ACK
    SENDACK();
    //receive Accelerometer Y1 data
    AccY1= I2CRCV ;
    //I2CSTATbits.RBF=1 when receive complete
    while (I2CSTATbits.RBF==0);

    //send ACK
    SENDACK();
    //receive Accelerometer Y2 data
    AccY2= I2CRCV ;
    //I2CSTATbits.RBF=1 when receive complete
    while (I2CSTATbits.RBF==0);

    //Acculmulated AccelerometerY value
    AccY= AccY1<<8+AccY2;

    //send ACK
    SENDACK();
    //receive Accelerometer Z1 data
    AccZ1= I2CRCV ;
    //I2CSTATbits.RBF=1 when receive complete
    while (I2CSTATbits.RBF==0);

    //send ACK
    SENDACK();
    //receive Accelerometer Z2 data
    AccZ2= I2CRCV ;
    //I2CSTATbits.RBF=1 when receive complete
    while (I2CSTATbits.RBF==0);

    //Acculmulated AccelerometerZ value
    AccZ= AccZ1<<8+AccZ2;

    //send ACK
    SENDACK();
    //receive Temperature1 data
    int Temperature1= I2CRCV ;
    //I2CSTATbits.RBF=1 when receive complete
    while (I2CSTATbits.RBF==0);

    //send ACK
    SENDACK();
    //receive Temperature2 data
    int Temperature2= I2CRCV ;
    //I2CSTATbits.RBF=1 when receive complete
    while (I2CSTATbits.RBF==0);

    //Accumulated Temperatur Data
    Temperature= Temperature1<<8 + Temperature2;

    //send ACK
    SENDACK();
    //receive Gyroscope X1 data
    GyroX1= I2CRCV ;
    //I2CSTATbits.RBF=1 when receive complete
    while (I2CSTATbits.RBF==0);

    //send ACK
    SENDACK();
    //receive Gyroscope X2 data
    GyroX2= I2CRCV ;
    //I2CSTATbits.RBF=1 when receive complete
    while (I2CSTATbits.RBF==0);

    //Accumulated GyroX data
    GyroX= GyroX1<<8 + GyroX2;

    //send ACK
    SENDACK();
    //receive Gyroscope Y1 data
    GyroY1= I2CRCV ;
    //I2CSTATbits.RBF=1 when receive complete
    while (I2CSTATbits.RBF==0);

    //send ACK
    SENDACK();
    //receive Gyroscope Y2 data
    GyroY2= I2CRCV ;
    //I2CSTATbits.RBF=1 when receive complete
    while (I2CSTATbits.RBF==0);

    //Accumulated GyroX data
    GyroY= GyroY1<<8 + GyroY2;

    //send ACK
    SENDACK();
    //receive Gyroscope Z1 data
    GyroZ1= I2CRCV ;
    //I2CSTATbits.RBF=1 when receive complete
    while (I2CSTATbits.RBF==0);

    //send ACK
    SENDACK();
    //receive Gyroscope Z2 data
    GyroZ2= I2CRCV ;
    //I2CSTATbits.RBF=1 when receive complete
    while (I2CSTATbits.RBF==0);

    //Accumulated GyroX data
    GyroZ= GyroZ1<<8 + GyroZ2;

    //send NACK
    SENDNACK();
    //stop seq
    I2CSTOPSEQ();
    return;
}

*/
