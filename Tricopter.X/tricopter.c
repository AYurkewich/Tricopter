/**********************************************************
;WE Bots
;Main

**********************************************************/




#include "Micros_h_File.h"
#include "Init_Declarations.h"

#include "Configutation_Bits_File.h"

/*********************************************************
 * PORT DESIGNATIONS
 * Motor Signals: RB2 - RB7
 * Accel/gyro: RB8(SCL), RB9(SDA), RA4(INT)
 * LEDs: RA2, RA3
 * Programming: RB0(PGD1), RB1(PGC1), VSS, VDD, MCLR
 * Test pins: AVDD, RA0, RA1, RB13, VSS
 * Bluetooth: AVDD, VSS, RB11, RB12
 * Master power: RB15
 * BAT low: RB14   batLow=high=1?
 * Motor Power: RB10
 ********************************************************
 *           X
      1,4    ^      2,5
         \   |   /
          \  |  /
      Y<-----O------
             |
             |
            3,6
 */

//TRIS DEFINE STATEMENTS
#define TA00     TRISAbits.TRISA0 //
#define TA01     TRISAbits.TRISA1 //
#define TA02     TRISAbits.TRISA2 //
#define TA03     TRISAbits.TRISA3 //
#define TA04     TRISAbits.TRISA4 //
#define TB00     TRISBbits.TRISB0 //
#define TB01     TRISBbits.TRISB1 //
#define TB02     TRISBbits.TRISB2 //
#define TB03     TRISBbits.TRISB3 //
#define TB04     TRISBbits.TRISB4 //
#define TB05     TRISBbits.TRISB5 //
#define TB06     TRISBbits.TRISB6 //
#define TB07     TRISBbits.TRISB7 //
#define TB08     TRISBbits.TRISB8 //
#define TB09     TRISBbits.TRISB9 //
#define TB10    TRISBbits.TRISB10 //
#define TB11    TRISBbits.TRISB11 //
#define TB12    TRISBbits.TRISB12 //
#define TB13    TRISBbits.TRISB13 //
#define TB14    TRISBbits.TRISB14 //
#define TB15    TRISBbits.TRISB15 //

//LAT DEFINE STATEMENTS
#define LA00     LATAbits.LATA0 //
#define LA01     LATAbits.LATA1 //
#define LA02     LATAbits.LATA2 //
#define LA03     LATAbits.LATA3 //
#define LA04     LATAbits.LATA4 //
#define LB00     LATBbits.LATB0 //
#define LB01     LATBbits.LATB1 //
#define LB02     LATBbits.LATB2 //
#define LB03     LATBbits.LATB3 //
#define LB04     LATBbits.LATB4 //
#define LB05     LATBbits.LATB5 //
#define LB06     LATBbits.LATB6 //
#define LB07     LATBbits.LATB7 //
#define LB08     LATBbits.LATB8 //
#define LB09     LATBbits.LATB9 //
#define LB10    LATBbits.LATB10 //
#define LB11    LATBbits.LATB11 //
#define LB12    LATBbits.LATB12 //
#define LB13    LATBbits.LATB13 //
#define LB14    LATBbits.LATB14 //
#define LB15    LATBbits.LATB15 //

//VARIABLE DEFINITIONS
int xPos, yPos, zPos, xAng, yAng, zAng; 
volatile unsigned int spaceAbs[6] = {xPos, yPos, zPos, xAng, yAng, zAng}; //Absolute Pos/Orientation array
int xPosD, yPosD, zPosD, xAngD, yAngD, zAngD; 
volatile unsigned int spaceDes[6] = {xPosD, yPosD, zPosD, xAngD, yAngD, zAngD}; //Destination Pos/Orientation array
int xPosR, yPosR, zPosR, xAngR, yAngR, zAngR;
volatile unsigned int spaceRel[6] = {xPosR, yPosR, zPosR, xAngR, yAngR, zAngR}; //Relative Pos/Orientation array
int xPosIn, yPosIn, zPosIn, xAngIn, yAngIn, zAngIn;                              
volatile unsigned int input[6] = {xPosIn, yPosIn, zPosIn, xAngIn, yAngIn, zAngIn}; //accel and gyro input placeholders
int xPosCal, yPosCal, zPosCal, xAngCal, yAngCal, zAngCal;                              
volatile unsigned int spaceCal[6] = {xPosCal, yPosCal, zPosCal, xAngCal, yAngCal, zAngCal}; //accel and gyro input placeholders
volatile unsigned int motSpeed[6];
volatile unsigned int batLow;
int ms;
int distToGround;

//SET GOALS
int numGoals = 2; //Number of set goals
volatile unsigned int goal[numGoals][6];
//volatile unsigned int goal[0][6]; //set in calibrate method
int goal[1][0]= 5 ; //position 1
int goal[1][1]= 3; //position 2
int goal[1][2]= -2; //position 3
int goal[1][3]= 0; //position 4
int goal[1][4]= 6; //position 5
int goal[1][5]= -10; //position 5
//volatile unsigned int goal1[6] = {};


//DECFLARE FUNCTIONS
void initialize(void);
void go(void);
void calibrate(void);
void delay(int);

/***********************
 * Questions
 * Are we using a camera? path planning?
 * Are we inputting different destinations?
 * Does the chip always know where it is? NO It senses it from where it starts
 * What does the accel/gyro return?
 * */

void main(void)
{
    //Initialize registers and ports
    initialize();
    delay(1000); //Delay??
    calibrate();
    go();
}

void initialize(void){
  //WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
        ubBufferIndex = 0;
        ubLastBufferIndex = 0;

	init_Osc();


	init_PWM();								// PWM Setup
	init_ADC();								// ADC Setup
	init_DAC_Comparators();


        init_T1();


	//TB04 = 0;                 //Set RB4 as output
        //LB04 = 1; high            //Set RB4 as high

   // PTCONbits.PTEN = 1;                   // Enable the PWM
//	ADCONbits.ADON = 1;                 // Enable the ADC

        uiHeaderZeroCount = 0;
	IEC0bits.T1IE = 1;
//	uc_Main_Case_Index = 0;

  /*P1DIR = 0xFF; //(nov 13th)0xFF;           // All P1.x outputs
  P1OUT = 0;                                // All P1.x reset
  P2DIR = 0xFF;                             // All P2.x outputs
  P2OUT = 0;                                // All P2.x reset
  P1SEL = BIT1 + BIT2;                      //(nov 13th) add bit 0/ACLK                 // P1.1 = RXD, P1.2=TXD
  P1SEL2 = BIT1 + BIT2;                     // P1.1 = RXD, P1.2=TXD
  P3DIR = 0xFF;                             // All P3.x outputs
  //P3REN = 0x00;                           // Set all Pulldown resistors to prevent random button pushes
  P3OUT = 0;                                // All P3.x reset

//BUTTON INITIALIZATION
  P1OUT |= 8;
  P1REN |= 8;
  P1DIR &= ~8;

//Clock Initialization
  UCA0CTL1 |= UCSSEL_1;                     // CLK = ACLK
  UCA0BR0 = 0x03;                           // 32kHz/9600 = 3.41
  UCA0BR1 = 0x00;                           //
  UCA0MCTL = UCBRS1 + UCBRS0;               // Modulation UCBRSx = 3
  UCA0CTL1 &= ~UCSWRST;                     // **Initialize USCI state machine**

//TIMER INITIALIZATION >>Timer resets cause interrupt
  TA0CCR0 = 62500 - 1;                      // A period of 62,500 cycles is 0 to 62,499.
  TA0CCTL0 = CCIE;                          // Enable interrupts for CCR0.
  TA0CTL = TASSEL_2 + ID_3 + MC_1 + TACLR;  // SMCLK, div 8, up mode,


//ENABLE INTERRUPTS (IN 'LOW POWER MODE 3')
  IFG2 &= ~UCA0RXIFG;                       //Clear the flag first to prevent immediate interrupt
  IE2 |= UCA0RXIE;// + UCA0TXIE;            // Enable USCI_A0 RX TX or timer interrupt....CLEAR FLAGS FIRST?
  _enable_interrupt();                      // Enable interrupts
  //__bis_SR_register(LPM3_bits + GIE);     // Enter LPM3 w/ int until Byte RXed
  */
}

void calibrate(void){
    //Is it being calibrated with a camera?
    waitForStartBit();
    for(int i(0); i<6; i++){
        goal[0][i] = input[i]; //set start position and straight orientation
    }
    ascend(-1,1);

}

void go(void) {
    while (1)
        for (int i(0); i < numGoals; i++) { //cycle through goals
            for (int j = 0; j < 6; j++) {
                //Take 6 inputs from accelerometer and gyro into input[]
                //Create 6 coordinate system
                //Does gyro and accelerometer measure relative or absolute values?? Relative?
                spaceRel[j] = input[j];
                spaceAbs[j] = spaceAbs[j] + spaceRel[j];
            }

            //Desired position/orientation
            goal[][];
            //Recalculate every how much distance? Does it waste more power to keep changing motor speeds
            //Recalculate every how much distance? Or does it waste more power
            //??calculate the forces and torques on the helicopter based on previous values
            //use PID to establish how much to to pulse motor

            setMot(1,)
            //tell motor 1 what to do
            TB02 = 0;

            //tell motor 2 what to do
            TB03 = 0;
            //tell motor 3 what to do
            TB04 = 0;
            //tell motor 4 what to do
            TB05 = 0;
            //tell motor 5 what to do
            TB06 = 0;
            //tell motor 6 what to do
            TB07 = 0;
            //tell Red LED what to do
            //RA3

            //tell Green LED what to do
            //RA2

            if(batLow){
                land();
            }
            //do something if battery low (land) or very low (shut off)

            //Future stuff//

            //Vision System
            //Object Detection
        }
}

int camSensor(void){
    //read camera sensor
    return distToGround;
}

void flatten(void){             //***********Check sensitivity to prevent vibrating
    while(xAng !=0 && yAng !=0){
        if (xAng<0){

        }
          //check speed
        //check acceleration
        //check orientation
        //space[] = checkPos();
        //if space[1].isCloseTo
    }
}

void land(void){
    //check speed
    //check speed
    //check acceleration
    //check orientation
    //space[] = checkPos();
    flatten();
    descend(-1); //Descend to ground

}
void ascend(int height, int speed){
    //ascent to height "height" at a speed of "speed"
    if(height == -1){
        //rise to an inch above ground
    }
    incAll(speed);
}
void descend(int height, int speed){ //descends at constant speed to height
    if(height = -1){
        while(camSensor()>1){

        }
        //decrease until cameras sense ground 2 inches away
        decAll(speed); //PID?
    }else{
        //descend to height
    }
}

void incAll(int speed){
    if(retMot(1)<speed){
        M1++;
    }
    if(retMot(2)<speed){
        M2++;
    }
    if(retMot(3)<speed){
        M3++;
    }
    if(retMot(4)<speed){
        M4++;
    }
    if(retMot(5)<speed){
        M5++;
    }
    if(retMot(6)<speed){
        M6++;
    }
}

void decAll(int speed){
    if(retMot(1)>speed){
        M1--;
    }
    if(retMot(2)>speed){
        M2--;
    }
    if(retMot(3)>speed){
        M3--;
    }
    if(retMot(4)>speed){
        M4--;
    }
    if(retMot(5)>speed){
        M5--;
    }
    if(retMot(6)>speed){
        M6--;
    }
}

void flatten(void){
    while (xAng != 0 && yAng != 0){
    //check speed
    //check acceleration
    //check orientation
    //space[] = checkPos();
        //if space[1].isCloseTo

    }
}

void setMot(int motNum, motSpeed){
    motSpeed[motNum-1] = motSpeed; //**********Arithmetic to determine what is sent to motor
}

int retMot(int motNum){
    return motSpeed[motNum-1];
}

void delay(int delTime){
    for(int z(0); z<delTime; z++){
        //delay
    }
}
