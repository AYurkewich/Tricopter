////////HOW TO USE I2C/////////////////
//http://www.robot-electronics.co.uk/acatalog/I2C_Tutorial.html

//VERSION UPDATES
//April 5th, added IdleI2C1 - started receiving data
//BCL error from SCL wire being disconnected
//April 9th changed everything to bit banging

//Note: In General you should always: WRITE using LAT, READ using PORT
//Setting TRISB8 to 1 gives a high value because MSCL pulls it high except for clock stretching
//Setting TRISB8 to 0 always gives a low value because portB8 = 0
//Setting TRISB9 to 1 gives a high value because of the PU Resistor except when receiving an ACK
//Setting TRISB9 to 0 always gives a low value because portB9 = 0

#include "p33Fxxxx.h"
//#include "i2c.h"                  ***CHANGED
#define FCY 40000000ULL
//#include "libpic30.h"
//#include "Init_Declarations.h" //uses the init_decl in Main
//#include "Init_ASM_h.inc" //Treats it as C code
	void initializeBits(void);
	void initializeMPU(void);
	char I2CTX(int);
	unsigned char I2CRX(char);
	void I2CSTARTSEQ(void);
	void I2CREPEATSTARTSEQ(void);
	void I2CSTOPSEQ(void);
	void ACCGYRODATABB(void);
	void turnRed(void);
	void turnYellow(void);
	void turnBoth(void);
	void calibrate(void);

    extern unsigned char AccX1;
    extern unsigned char AccX2;
    extern int AccX;
    extern unsigned char AccY1;
    extern unsigned char AccY2;
    extern int AccY;
    extern unsigned char AccZ1;
    extern unsigned char AccZ2;
    extern int AccZ;
    extern unsigned char Temp1;
    extern unsigned char Temp2;
    extern int Temp;
    extern unsigned char GyroX1;
    extern unsigned char GyroX2;
    extern int GyroX;
    extern unsigned char GyroY1;
    extern unsigned char GyroY2;
    extern int GyroY;
    extern unsigned char GyroZ1;
    extern unsigned char GyroZ2;
    extern int GyroZ;
	extern double AccXsum, AccXavg;
	extern double AccYsum, AccYavg;
	extern double AccZsum, AccZavg;
	extern int AccXprev, AccYprev, AccZprev;
	extern double Tempsum, Tempavg;
	extern double GyroXsum, GyroXavg;
	extern double GyroYsum, GyroYavg;
	extern double GyroZsum, GyroZavg;
	extern int AccXRef, AccYRef, AccZRef, TempRef, GyroXRef, GyroYRef, GyroZRef; //Reference Values


	char b;
	int band;
	int FILTER_SIZE = 10; //Using an Average Filter. Change all these 8 values 
	static int AccXFilter[10], AccYFilter[10], AccZFilter[10], TempFilter[10], GyroXFilter[10], GyroYFilter[10], GyroZFilter[10];  
	int i;
	int calibrationCounter;
	static int startPoint = 0; 

void init_I2CBB(void) {
    initializeBits();
	initializeMPU();
	calibrate();
}

//worked at 18,36
void i2c_dly(void) {
	//for(i = 0; i<2; i++) 
		Nop();
}
void i2c_dly_half(void) {
	//for(i = 0; i<1; i++)
		Nop();
}

void calibrate(void){
	for(calibrationCounter=0; calibrationCounter<20; calibrationCounter++){
		ACCGYRODATABB();
	}
	AccXRef = AccXavg;
	AccYRef = AccYavg;
	AccZRef = AccZavg;
	TempRef = Tempavg;
	GyroXRef = GyroXavg;
	GyroYRef = GyroYavg;
	GyroZRef = GyroZavg;

}

void ACCGYRODATABB(void) {

	    I2CSTARTSEQ(); // send start sequence
	    I2CTX(0xD0); // 11010000 address with R/W bit clear
		i2c_dly_half(); 
	    I2CTX(0x3B); 
	    I2CREPEATSTARTSEQ(); 
	    I2CTX(0xD1); 
	    //Unsure about this
		TRISBbits.TRISB9 = 0; 	
    	i2c_dly_half();	
		//Order. X Hi > X Lo > Y Hi > Y Lo > Z Hi > Z Lo
		//Higher Order Bits (8), then Lower Order Bits (2)
        AccX1 = I2CRX(1); 
        AccX2 = I2CRX(2);
        AccY1 = I2CRX(3);
		AccY2 = I2CRX(4); 
        AccZ1 = I2CRX(5);
        AccZ2 = I2CRX(6);
        Temp1 = I2CRX(7);
        Temp2 = I2CRX(8);
        GyroX1 =  I2CRX(9); 
        GyroX2 = I2CRX(10);
        GyroY1 = I2CRX(11);
		GyroY2 = I2CRX(12); 
        GyroZ1 = I2CRX(13);
        GyroZ2 = I2CRX(0);
        I2CSTOPSEQ();

		//If AccX1 = 1
		//Turn Values into integers (-32768, 0, 32767) resolution = 1
		//SIGNED integer means 16th bit is the sign (1-negative) and the top half is reversed
		AccX = AccX1 > 127 ? (AccX1-256)*256 +AccX2: AccX1 * 256 + AccX2;
		AccY = AccY1 > 127 ? (AccY1-256)*256 +AccY2: AccY1 * 256 + AccY2;
		AccZ = AccZ1 > 127 ? (AccZ1-256)*256 +AccZ2: AccZ1 * 256 + AccZ2;
		Temp = Temp1 > 127 ? (Temp1-256)*256 +Temp2: Temp1 * 256 + Temp2;
		GyroX = GyroX1 > 127 ? (GyroX1-256)*256 +GyroX2: GyroX1 * 256 + GyroX2;
		GyroY = GyroY1 > 127 ? (GyroY1-256)*256 +GyroY2: GyroY1 * 256 + GyroY2;
		GyroZ = GyroZ1 > 127 ? (GyroZ1-256)*256 +GyroZ2: GyroZ1 * 256 + GyroZ2;
		//AccX = AccX1 > 01111111 ? ((AccX1&0xFF)-256)*4 +AccX2: AccX1*4 +AccX2

		//Initialize Filters - WORKS
		  if(startPoint == 0){
		    for (i=0; i<FILTER_SIZE; i++){
		      AccXFilter[i] = 0;
			  AccYFilter[i] = 0; 
			  AccZFilter[i] = 0;
			  TempFilter[i] = 0;
			  GyroXFilter[i]= 0;
			  GyroYFilter[i]= 0;
			  GyroZFilter[i]= 0;
			  AccXavg = 0;
			  AccYavg = 0;
			  AccZavg = 0;
		    }
		    startPoint++;
		  }
		
		  //Enter Values into Filters
		  for (i=0; i<FILTER_SIZE-1; i++){  	//Timer Note: Each line is 0xC
		    AccXFilter[i] = AccXFilter[i+1];
			AccYFilter[i] = AccYFilter[i+1]; 
		    AccZFilter[i] = AccZFilter[i+1];
			TempFilter[i] = TempFilter[i+1];	
			GyroXFilter[i] = GyroXFilter[i+1];
			GyroYFilter[i] = GyroYFilter[i+1];	
			GyroZFilter[i] = GyroZFilter[i+1];
		  }
		  AccXFilter[FILTER_SIZE-1] = AccX;
		  AccYFilter[FILTER_SIZE-1] = AccY;
		  AccZFilter[FILTER_SIZE-1] = AccZ;
		  TempFilter[FILTER_SIZE-1] = Temp;
		  GyroXFilter[FILTER_SIZE-1] = GyroX;
		  GyroYFilter[FILTER_SIZE-1] = GyroY;
		  GyroZFilter[FILTER_SIZE-1] = GyroZ;	//Timer 0x197A

		  TMR1=0x00; 		//Need to reset timer so it doesn't flag the interrupt before ending  
		
		  //Find Averages
		 for (i=0; i<FILTER_SIZE; i++){			//Timer Note: 0x6000 for the full loop
		     AccXsum += AccXFilter[i]; 			
			 AccYsum += AccYFilter[i];
			 AccZsum += AccZFilter[i];
			 Tempsum += TempFilter[i];
			 GyroXsum+= GyroXFilter[i];
			 GyroYsum += GyroYFilter[i];
			 GyroZsum+= GyroZFilter[i];
		  }
		  AccXprev = AccXavg;
		  AccYprev = AccYavg;
		  AccZprev = AccZavg;
		  AccXavg = AccXsum/FILTER_SIZE;		//Timer 0x3B3D
		  AccYavg = AccYsum/FILTER_SIZE;
		  AccZavg = AccZsum/FILTER_SIZE;
		  Tempavg = Tempsum/FILTER_SIZE;
		  GyroXavg = GyroXsum/FILTER_SIZE;
		  GyroYavg = GyroYsum/FILTER_SIZE;
		  GyroZavg = GyroZsum/FILTER_SIZE;
		  //reset manually (software will not)
		  AccXsum = 0; 
		  AccYsum = 0; 
		  AccZsum = 0;  
		  Tempsum = 0;
		  GyroXsum= 0;
		  GyroYsum= 0;
		  GyroZsum= 0;		  	

//        //Test Sequence
//        if (AccXavg > 0) {//Turn Blue ON
//            TRISAbits.TRISA2 = 0;
//    		LATAbits.LATA2 = 1;
//		}else{//Turn Blue Off
//			TRISAbits.TRISA2 = 0;
//    		LATAbits.LATA2 = 0;
//		}
//        if (AccYavg > 0){//Turn Red On
//			TRISAbits.TRISA3 = 0;
//    		LATAbits.LATA3 = 1;
//        }else{//Turn Red Off
//			TRISAbits.TRISA3 = 0;
//    		LATAbits.LATA3 = 0;
//		}

    }

void initializeBits(void) {
	CNEN2bits.CN21IE = 0; // Enable(1)/Disable(0) CN3 pin for interrupt detection
	CNEN2bits.CN22IE = 0; // Enable(1)/Disable(0) CN3 pin for interrupt detection
    CNPU2bits.CN21PUE = 0; //Disable CN21 pin
	CNPU2bits.CN22PUE = 0; //Disable CN22 pin
	PWM2CON1bits.PEN1L = 0;
	PWM2CON1bits.PEN1H = 0;
	RPOR4bits.RP9R = 0;
	I2C1CONbits.I2CEN = 0; //Disable SDA/SCL modules, and leave to port pins

	TRISBbits.TRISB8 = 1;
    LATBbits.LATB8 = 0; //If set to 1, pushes everything Hi when INPUT
    //PORTBbits.RB8 = 0; //doesn't change anything
    TRISBbits.TRISB9 = 1;
    LATBbits.LATB9 = 0; //If set to 1, pushes everything Hi when INPUT
    //PORTBbits.RB9 = 1; //Makes everything HI (clock and data
	//PORTBbits.RB9 = 0; //Floats everything HI on input


    //AccXOLD = 0;
}

//make the argument void for now, change later to incorporate easier changing
void initializeMPU(void) {
	char old_Clock;
	char old_Gyro;
	char old_Acc;
	char old_Sleep;

	i2c_dly();

	I2CSTARTSEQ();
	I2CTX(0xD0);
	i2c_dly_half();
	I2CTX(0x6B);
	I2CREPEATSTARTSEQ();
	I2CTX(0xD1);
	TRISBbits.TRISB9 = 0; 	
   	i2c_dly_half();
	old_Clock = I2CRX(0); //I suppose this is to first read the current value
	I2CSTOPSEQ();
	I2CSTARTSEQ();
	I2CTX(0xD0);
	i2c_dly_half();
	I2CREPEATSTARTSEQ();
	I2CTX(0xD0);
	i2c_dly_half();	
	I2CTX(0x6B);
	i2c_dly_half();	
	I2CTX(0x01);
	i2c_dly_half();
	I2CSTOPSEQ();

	I2CSTARTSEQ();
	I2CTX(0xD0);
	i2c_dly_half();
	I2CTX(0x1B);
	I2CREPEATSTARTSEQ();
	I2CTX(0xD1);
	TRISBbits.TRISB9 = 0; 	
   	i2c_dly_half();
	old_Gyro = I2CRX(0); //I suppose this is to first read the current value
	I2CSTOPSEQ();
	I2CSTARTSEQ();
	I2CTX(0xD0);
	i2c_dly_half();
	I2CREPEATSTARTSEQ();
	I2CTX(0xD0);
	i2c_dly_half();	
	I2CTX(0x1B);
	i2c_dly_half();	
	I2CTX(0x00);
	i2c_dly_half();
	I2CSTOPSEQ();

	I2CSTARTSEQ();
	I2CTX(0xD0);
	i2c_dly_half();
	I2CTX(0x1C);
	I2CREPEATSTARTSEQ();
	I2CTX(0xD1);
	TRISBbits.TRISB9 = 0; 	
   	i2c_dly_half();
	old_Acc = I2CRX(0); //I suppose this is to first read the current value
	I2CSTOPSEQ();
	I2CSTARTSEQ();
	I2CTX(0xD0);
	i2c_dly_half();
	I2CREPEATSTARTSEQ();
	I2CTX(0xD0);
	i2c_dly_half();	
	I2CTX(0x1C);
	i2c_dly_half();	
	I2CTX(0x00);
	i2c_dly_half();
	I2CSTOPSEQ();

	I2CSTARTSEQ();
	I2CTX(0xD0);
	i2c_dly_half();
	I2CTX(0x6B);
	I2CREPEATSTARTSEQ();
	I2CTX(0xD1);
	TRISBbits.TRISB9 = 0; 	
   	i2c_dly_half();
	old_Sleep = I2CRX(0); //I suppose this is to first read the current value
	I2CSTOPSEQ();
	I2CSTARTSEQ();
	I2CTX(0xD0);
	i2c_dly_half();
	I2CREPEATSTARTSEQ();
	I2CTX(0xD0);
	i2c_dly_half();	
	I2CTX(0x6B);
	i2c_dly_half();	
	I2CTX(0x01);
	i2c_dly_half();
	I2CSTOPSEQ();

	i2c_dly();
}

void I2CSTARTSEQ(void) {
    TRISBbits.TRISB9 = 1;
    i2c_dly_half();
    TRISBbits.TRISB8 = 1;
    i2c_dly_half();
    TRISBbits.TRISB9 = 0;
    i2c_dly_half();
    TRISBbits.TRISB8 = 0;
    i2c_dly_half();
}
void I2CREPEATSTARTSEQ() {
	TRISBbits.TRISB9 = 0; 	//Have to keep low(/input?) for an extra bit of time since ACKSTAT
    i2c_dly_half();				//changes a bit later than the previous times
	i2c_dly_half();
	TRISBbits.TRISB8 = 1;
	i2c_dly_half();

	TRISBbits.TRISB9 = 1;
    i2c_dly();
    i2c_dly_half();
    TRISBbits.TRISB9 = 0;
    i2c_dly_half();
    TRISBbits.TRISB8 = 0;
    i2c_dly_half();
}

void I2CSTOPSEQ(void) {
    TRISBbits.TRISB9 = 0;
    i2c_dly_half();
    TRISBbits.TRISB8 = 1;
    i2c_dly_half();
    TRISBbits.TRISB9 = 1;
    i2c_dly_half();
}

unsigned char I2CRX(char ack) {
    char x;
	int d = 0;
    TRISBbits.TRISB9 = 1;
    for (x = 0; x < 8; x++) {
        d <<= 1;
//		do {
//			i2c_dly_half();
//            TRISBbits.TRISB8 = 1;
//        } while (PORTBbits.RB8 == 0); // wait for any SCL clock stretching; Clock stretches double
									
		i2c_dly_half();			//skip clock stretching
        TRISBbits.TRISB8 = 1;	//skip clock stretching
		
		 //if (LATBbits.LATB9) d |= 1;
        if (PORTBbits.RB9) d |= 1;  //original, test port or latch
     	i2c_dly_half();   
		TRISBbits.TRISB8 = 0;
    }
    if (ack) TRISBbits.TRISB9 = 0;
    else TRISBbits.TRISB9 = 1;
    i2c_dly_half();
    TRISBbits.TRISB8 = 1;
    i2c_dly_half(); // send (N)ACK bit
    TRISBbits.TRISB8 = 0;
    TRISBbits.TRISB9 = 1;
	i2c_dly_half();
    return d;
}

char I2CTX(int d) //changed b to char? changed d to int from unsigned char
{
    char x;
    //static bit b;
    for (x = 8; x; x--) {
        if (d & 0x80) TRISBbits.TRISB9 = 1;
        else TRISBbits.TRISB9 = 0;
        i2c_dly_half();
		TRISBbits.TRISB8 = 1;
        d <<= 1;
		i2c_dly_half();
        TRISBbits.TRISB8 = 0;

    }
	//Proven to work and actually be pulled low on 9th bit by mpu
	TRISBbits.TRISB9 = 1; //Get ready for ACK bit
	i2c_dly_half();
    TRISBbits.TRISB8 = 1; //Get ready for Ack bit
	//b = LATBbits.LATB9; //should always READ from PORT
	b = PORTBbits.RB9;  // possible ACK bit    
	i2c_dly_half();
	TRISBbits.TRISB8 = 0;
	//TRISBbits.TRISB9 = 0;
    //cLo();
    return b;
}

