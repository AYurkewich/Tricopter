////////I2C Communication/////////////////
//http://www.i2c-bus.org/how-i2c-hardware-works/

#define _XTAL_FREQ 20000000
#include "xc.h" // required 
#include "p33FJ32MC202.h"
#include "i2c.h"
#define FOSC  80000000     // Device oscillator at 80 MHz.
#define FCY    FOSC/2

#include "libpic30.h"

void initializeBits(void);
void ACCGYRODATA(void);
int AccX0;
int AccX1;
int AccX2;
int AccX = 0;
int AccY0;
int AccY1;
int AccY2;
int AccY = 0;
int AccZ0;
int AccZ1;
int AccZ2;
int AccZ = 0;
int Temperature0;
int Temperature1;
int Temperature2;
int Temperature = 0;
int GyroX0;
int GyroX1;
int GyroX2;
int GyroX = 0;
int GyroY0;
int GyroY1;
int GyroY2;
int GyroY = 0;
int GyroZ0;
int GyroZ1;
int GyroZ2;
int GyroZ = 0;
//April 3 changed I2CRCV to I2C1RCV since that was the mention in the datasheet

void init_I2C(void) {
    
    //Set Baud Rate//
    //I2C1BRG = I2C_BRG( 100000 );
	I2C1BRG = 350;
    //Initialize Bits
    initializeBits();
    //START FULL SEQUENCE
    //ACCGYRODATA();

/*
//OSCILLATOR SETUP//
    // setup internal clock for 80MHz/40MIPS
    // 7.37/2=3.685*43=158.455/2=79.2275
    CLKDIVbits.PLLPRE = 0; // PLLPRE (N2) 0=/2
    PLLFBD = 41; // pll multiplier (M) = +2
    // Setup LED on Pin 2 (RA0)
    CLKDIVbits.PLLPOST = 0; // PLLPOST (N1) 0=/2
*/

}

void initializeBits(void){
        //I2C Communication Registers /////
TRISBbits.TRISB9 = 1;
TRISBbits.TRISB8 = 1;
//
//I2C1CONbits.I2CEN = 0;
//I2C1CONbits.I2CSIDL = 0;
//I2C1CONbits.SCLREL = 1;
//I2C1CONbits.IPMIEN = 0;
//I2C1CONbits.A10M = 0;
//I2C1CONbits.DISSLW = 1;
//I2C1CONbits.SMEN = 0;
//I2C1CONbits.GCEN = 0;
//I2C1CONbits.STREN = 0;
//I2C1CONbits.ACKDT = 0;
//I2C1CONbits.ACKEN = 0;
//I2C1CONbits.RCEN = 0;
//I2C1CONbits.PEN = 0;
//I2C1CONbits.RSEN = 0;
//I2C1CONbits.SEN = 0;
//
////Clearing the recieve and transmit buffers
//I2C1RCV = 0x0000;
//I2C1TRN = 0x0000;
//
////Now we can enable the peripheral
//I2C1CONbits.I2CEN = 1;
 //I2C CON Register////
    //bit 15, Enable the module (Change to turn module off)
    I2C1CONbits.I2CEN = 0;
    __delay_ms(1);
    //bit 14, unimplemented
    //bit 13,stop module when PIC is in idle
    I2C1CONbits.I2CSIDL = 1; //DIFFERENT
    //bit 12, (when being used as slave)?
    I2C1CONbits.SCLREL = 1;
    //bit 11, Acknowledge all addresses?
    I2C1CONbits.IPMIEN = 0;//DIFFERENT
    //bit 10,Invensense chip has a 7 bit slave address
    I2C1CONbits.A10M = 0;
    //bit 9, slew rate control disabled
    I2C1CONbits.DISSLW = 1;
    //bit 8, enable I/O thresholds
    I2C1CONbits.SMEN = 0;
    //bit 7, module enabled for reception
    I2C1CONbits.GCEN = 1; //DIFFERENT
    //bit 6, (when being used as slave)?
    I2C1CONbits.STREN = 0;
    //bit 5,Send NACK when data recieved
    I2C1CONbits.ACKDT = 1; //DIFFERENT
    //bit 4, enable ACK sequence on recieve
    I2C1CONbits.ACKEN = 0;
    //bit 3,Recieve not enable (Change when you want to receive data)
    I2C1CONbits.RCEN = 0;
    //bit 2, Stop sequence not enable (Change when you want to send stop sequence)
    I2C1CONbits.PEN = 0;
    //bit 1, Repeated start not enabled (Change when you want to send repeated start)
    I2C1CONbits.RSEN = 0;
    //bit 0, Start sequence not enabled (Change when you want to send start sequence)
    I2C1CONbits.SEN = 0;
	I2C1CONbits.I2CEN = 1;

    ///transmit initialization
    I2C1TRN = 0x0000;
    ///receive initialization
    I2C1RCV = 0x0000;
//AccXOLD = 0;
	TRISAbits.TRISA2 = 0; // configure direction for output
    LATAbits.LATA2 = 0;
    TRISAbits.TRISA3 = 0;
    LATAbits.LATA3 = 0;
}

void I2CSTARTSEQ(void)
{
    I2C1CONbits.SEN=1;       //Starting Start Sequence
    while (I2C1CONbits.SEN); //Check

    //Change back to 0 after how long?
}

void I2CSTOPSEQ(void)
 {
    I2C1CONbits.PEN=1;
    while (I2C1CONbits.PEN);
}

void REPEATSTART(void)
{
    I2C1CONbits.RSEN=1;
    while (I2C1CONbits.RSEN);
}

unsigned int ACKStatus(void)
{
return (!I2C1STATbits.ACKSTAT);	//Return Ack Status
return 0;
}

void SENDNACK (void)
{
  I2C1CONbits.ACKDT=1;
  I2C1CONbits.ACKEN=1;
  while(I2C1CONbits.ACKEN);
}

void SENDACK (void)
{
  I2C1CONbits.ACKDT=0;
  I2C1CONbits.ACKEN=1;
  while(I2C1CONbits.ACKEN);
}

void ACCGYRODATA(void)
{

//ARDUINO CODE sends 0x68, then 0x3B
while(1){
    //start seq
    I2CSTARTSEQ(); //This works for data  
    //send accelerometer address(1101000) + Write bit(0) (We are writing to the accelerometer) 	
	I2C1TRN= 0xD0; //0b11010000; //Success. 104, 0x00D0
	
	while (I2C1STATbits.TBF);       //wait till buffer is empty/transfer complete
    
    //Hardware set at beginning of master transmission; hardware clear at end of slave Acknowledge.
	while (I2C1STATbits.TRSTAT); //*These are needed so buffers don't overlap
	Nop();
	//__delay_us(10);
	I2C1TRN= 0x3B;//0x3B      //send accelerometer REGISTER address
 	while (I2C1STATbits.TBF);       //wait till buffer is empty/transfer complete
    while (I2C1STATbits.TRSTAT); //*These are needed so buffers don't overlap
    //while (I2C1STATbits.ACKSTAT);
	Nop();
    //Repeated Start
    REPEATSTART();

    //I2CSTARTSEQ();

    //while (I2C1STATbits.TBF);       //wait till buffer is empty/transfer complete
    while (I2C1STATbits.TRSTAT);    //wait until done transmitting

	Nop();
    I2C1TRN= 0xD1; //0b11010001;            //send slave address + Read bit (1)


    while (I2C1STATbits.TBF);       //wait till buffer is empty/transfer complete
    //while (I2C1STATbits.ACKSTAT);   //wait for acknowledge
    while (I2C1STATbits.TRSTAT);    //wait until done transmitting
}


/*
	unsigned char Data = 0x00;
	if(Data == 0x68)
    {
        printf("\nI2C Read Test Passed, MPU6050 Address: 0x%x", Data);
    }
    else
    {
        printf("ERROR: I2C Read Test Failed, Stopping");
        while(1){}    
    } */
// *********BEGIN LOOP*************
    //IdleI2C1();

    //receive Accelerometer X1 data
    I2C1CONbits.RCEN = 1;       //Enabled Receive bit
    while (I2C1CONbits.RCEN);   //FULL BYTE RECEIVED
    //while (I2C1STATbits.RBF == 0);
    AccX1= I2C1RCV;
    while (I2C1STATbits.RBF);   //I2CSTATbits.RBF=1 when receive complete
    SENDACK();                  //Send Acknowledge

    //receive Accelerometer X2 data
    I2C1CONbits.RCEN = 1;       //Enabled Receive bit
    while (I2C1CONbits.RCEN);   //FULL BYTE RECEIVED
    while (I2C1STATbits.RBF == 0);
    AccX2= I2C1RCV;
    while (I2C1STATbits.RBF);   //I2CSTATbits.RBF=1 when receive complete
    SENDACK();

    //receive Accelerometer Y1 data
    I2C1CONbits.RCEN = 1;       //Enabled Receive bit
    while (I2C1CONbits.RCEN);   //FULL BYTE RECEIVED
    while (I2C1STATbits.RBF == 0);
    AccY1= I2C1RCV;
    while (I2C1STATbits.RBF);   //I2CSTATbits.RBF=1 when receive complete
    SENDACK();

    //receive Accelerometer Y2 data
    I2C1CONbits.RCEN = 1;       //Enabled Receive bit
    while (I2C1CONbits.RCEN);   //FULL BYTE RECEIVED
    while (I2C1STATbits.RBF == 0);
    AccY2= I2C1RCV;
    while (I2C1STATbits.RBF);   //I2CSTATbits.RBF=1 when receive complete
    SENDACK();

    //receive Accelerometer Z1 data
    I2C1CONbits.RCEN = 1;       //Enabled Receive bit
    while (I2C1CONbits.RCEN);   //FULL BYTE RECEIVED
    while (I2C1STATbits.RBF == 0);
    AccZ1= I2C1RCV;
    while (I2C1STATbits.RBF);   //I2CSTATbits.RBF=1 when receive complete
    SENDACK();

    //receive Accelerometer Z2 data
    I2C1CONbits.RCEN = 1;       //Enabled Receive bit
    while (I2C1CONbits.RCEN);   //FULL BYTE RECEIVED
    while (I2C1STATbits.RBF == 0);
    AccZ2= I2C1RCV;
    while (I2C1STATbits.RBF);   //I2CSTATbits.RBF=1 when receive complete
    SENDACK();

    //receive Temperature1 data
    I2C1CONbits.RCEN = 1;       //Enabled Receive bit
    while (I2C1CONbits.RCEN);   //FULL BYTE RECEIVED
    while (I2C1STATbits.RBF == 0);
    Temperature1= I2C1RCV;
    while (I2C1STATbits.RBF);   //I2CSTATbits.RBF=1 when receive complete
    SENDACK();

    //receive Temperature2 data
    I2C1CONbits.RCEN = 1;       //Enabled Receive bit
    while (I2C1CONbits.RCEN);   //FULL BYTE RECEIVED
    while (I2C1STATbits.RBF == 0);
    Temperature2 = I2C1RCV;
    while (I2C1STATbits.RBF);   //I2CSTATbits.RBF=1 when receive complete
    SENDACK();

    //receive Gyroscope X1 data
    I2C1CONbits.RCEN = 1;       //Enabled Receive bit
    while (I2C1CONbits.RCEN);   //FULL BYTE RECEIVED
    while (I2C1STATbits.RBF == 0);
    GyroX1= I2C1RCV;
    while (I2C1STATbits.RBF);   //I2CSTATbits.RBF=1 when receive complete
    SENDACK();

    //receive Gyroscope X2 data
    I2C1CONbits.RCEN = 1;       //Enabled Receive bit
    while (I2C1CONbits.RCEN);   //FULL BYTE RECEIVED
    while (I2C1STATbits.RBF == 0);
    GyroX2= I2C1RCV;
    while (I2C1STATbits.RBF);   //I2CSTATbits.RBF=1 when receive complete
    SENDACK();

    //receive Gyroscope Y1 data
    I2C1CONbits.RCEN = 1;       //Enabled Receive bit
    while (I2C1CONbits.RCEN);   //FULL BYTE RECEIVED
    while (I2C1STATbits.RBF == 0);
    GyroY1= I2C1RCV;
    while (I2C1STATbits.RBF);   //I2CSTATbits.RBF=1 when receive complete
    SENDACK();

    //receive Gyroscope Y2 data
    I2C1CONbits.RCEN = 1;       //Enabled Receive bit
    while (I2C1CONbits.RCEN);   //FULL BYTE RECEIVED
    while (I2C1STATbits.RBF == 0);
    GyroY2= I2C1RCV;
    while (I2C1STATbits.RBF);   //I2CSTATbits.RBF=1 when receive complete
    SENDACK();


    //receive Gyroscope Z1 data
    I2C1CONbits.RCEN = 1;       //Enabled Receive bit
    while (I2C1CONbits.RCEN);   //FULL BYTE RECEIVED
    while (I2C1STATbits.RBF == 0);
    GyroZ1= I2C1RCV;
    while (I2C1STATbits.RBF);   //I2CSTATbits.RBF=1 when receive complete
    SENDACK();

    //receive Gyroscope Z2 data
    I2C1CONbits.RCEN = 1;       //Enabled Receive bit
    while (I2C1CONbits.RCEN);   //FULL BYTE RECEIVED
    while (I2C1STATbits.RBF == 0);
    GyroZ2= I2C1RCV;
    while (I2C1STATbits.RBF);   //I2CSTATbits.RBF=1 when receive complete



    //send NACK
    SENDNACK();
    //stop seq
    I2CSTOPSEQ();
    //return;
    int i =0;
    if (i == 0) {
        AccX0 = (AccX1 << 8) + AccX2;
        AccY0 = (AccY1 << 8) + AccY2;
        AccZ0 = (AccZ1 << 8) + AccZ2;
        Temperature0 = (Temperature1 << 8) + Temperature2;
        GyroX0 = (GyroX1 << 8) + GyroX2;
        GyroY0 = (GyroY1 << 8) + GyroY2;
        GyroZ0 = (GyroZ1 << 8) + GyroZ2;
        i++;
    } else {
        AccX0 = AccX;
        AccY0 = AccY;
        AccZ0 = AccZ;
        Temperature0 = Temperature;
        GyroX0 = GyroX;
        GyroY0 = GyroY;
        GyroZ0 = GyroZ;
	}

    AccX = (AccX1 << 8) + AccX2;
    AccY = (AccY1 << 8) + AccY2;
    AccZ = (AccZ1 << 8) + AccZ2;
    Temperature = (Temperature1 << 8) + Temperature2;
    GyroX = (GyroX1 << 8) + GyroX2;
    GyroY = (GyroY1 << 8) + GyroY2;
    GyroZ = (GyroZ1 << 8) + GyroZ2;

	//LED Comparisons
    if (AccY > AccY0 && AccX > AccX0) {
            TRISAbits.TRISA2 = 0; // configure direction for output
            LATAbits.LATA2 = 0;
            TRISAbits.TRISA3 = 0;
            LATAbits.LATA3 = 1;
 	} else if (AccY < AccY0 && AccX < AccX0) {
            TRISAbits.TRISA3 = 0; // configure direction for output
            LATAbits.LATA3 = 0;
            TRISAbits.TRISA2 = 0;
            LATAbits.LATA2 = 1;
  	} else {
            TRISAbits.TRISA3 = 0; // configure direction for output
            LATAbits.LATA3 = 1;
            TRISAbits.TRISA2 = 0;
            LATAbits.LATA2 = 1;
  	}
     
}
