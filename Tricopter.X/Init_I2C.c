
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