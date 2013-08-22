#include "p33Fxxxx.h"
//#include "libpic30.h"
#include <math.h>

#define FCY 40000000ULL
#define PI 3.14159265

double distanceX(void);
void updateDist(void);
double findAngle(char);

static double DistX, DistY, DistZ;
double DdistX, DdistY, DdistZ;
double angleX, angleY, angleZ;
double angleX0, angleY0, angleZ0;
double VelX, VelY, VelZ;
double DvelX, DvelY, DvelZ;
double DAccX, DAccY, DAccZ; 
extern int AccX, AccY, AccZ;
extern int AccXprev, AccYprev, AccZprev;
extern int AccXRef, AccYRef, AccZRef;
extern double AccXavg, AccYavg, AccZavg;
extern int GyroX, GyroY, GyroZ;
extern double GyroXavg, GyroYavg, GyroZavg;
double AccXest, AccYest, AccZest;
double timeConst;
int timeConstCounter;

void init_MoveTricopter(void){
	DistX = 0;
	DistY = 0;
	DistZ = 0;
	VelX  = 0;
	VelY  = 0;
	VelZ  = 0;
	timeConst = 0.001; ////calculated August 18th
	//angleX0 = asin(AccXavg/32767*2)*180/PI;
	//angleY0 = asin(AccYavg/32767*2)*180/PI;
	//angleZ0 = asin(AccZavg/32767*2)*180/PI;
	//posX0
}

void POSANGDATA(void){
	//angleX += GyroX/32767*250 * timeConst; //Just using GyroX doesn't change the value??
	angleX += GyroXavg/32767*250 * timeConst;
	angleX -= .0006;  						//drift (P control)
	angleY += GyroYavg/32767*250 * timeConst;
	angleZ += GyroZavg/32767*250 * timeConst;
	
	//Divide into Acc(pos) and Acc(ang)
	DAccX = AccXavg - sin(angleX*PI/180)/2*32767; 	//Acc only due to acc not angle (bit)
	VelX += DAccX/1672 * timeConst;						//1671.836734693877551
	DistX += VelX*timeConst + DAccX*timeConst*timeConst/2;

	DAccY = AccYavg - sin(angleY*PI/180)/2*32767; 	//Acc only due to acc not angle (bit)
	VelY += DAccY/1672 * timeConst;						//1671.836734693877551
	DistY += VelY*timeConst + DAccY*timeConst*timeConst/2;

	DAccZ = AccZavg - sin(angleZ*PI/180)/2*32767; 	//Acc only due to acc not angle (bit)
	VelZ += DAccZ/1672 * timeConst;						//1671.836734693877551
	DistZ += VelZ*timeConst + DAccZ*timeConst*timeConst/2;

	timeConstCounter++; //calculate the actual timeConst
}

double distanceX(void){
	return DistX;
}

double findAngle(char angle){
//	AccXest = AccXavg;
//	AccYest = AccYavg;
//	AccZest = AccZavg;
//
//	angleX += GyroXavg * timeConst;
//
//	//Initial Positions
//	aX0 = AccXavg*90/32767;
//	aXcurr = aX0;
//	aXcurr += GyroXavg * timeConst;
//
//	
//
//	//static measurement of (-90, 90)
//	angleX = AccXavg/182;
//	angleY = AccYavg/182;
//	angleZ = AccZavg/182;
//
//	if(angle=='X' || angle == 'x'){
//		return angleX;
//	}
//	if(angle=='Y' || angle == 'y'){
//		return angleY;
//	}
//	if(angle=='Z' || angle == 'z'){
//		return angleZ;
//	}
return 0;
} 