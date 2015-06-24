#include "control.h"
#include "lineScan.h"
#include "servo.h"
#include "dcMotor.h"

#include "uart.h"
#include "distanceSensor.h"

#include "filter.h"
#include "clcd.h"

//debug
//#define	CONTROL_DEBUG

//mode select
#define MOTOR_MODE_USE_BACK
//#define MOTOR_MODE_NOT_BACK

long int accumulateDistance=0;
int accumulateflag=0;
extern int scFlag;
long int abs(long int value){
	if(value<0)
		value = -value;
	return value;
}

void control(void){
	long int aimSpeed=30;
	aimSpeed = angleControl();	
	speedControl(aimSpeed);
}

long int angleControl(void){
	
	static int schoolZoneMode=0;
	int angle;		
	
	long int aimSpeed;	
	long int feedback;
	feedback = 30;
	//angle control
	angle = lineControl(accumulateDistance);
	
	if(angle!=SCHOOL_ZONE)
		moveAngle(angle);
	else
		moveAngle(0);

	
	if(angle == SCHOOL_ZONE){
		schoolZoneMode ++;	
		if(scFlag!=SCHOOL_ZONE_DISABLE){
			if(schoolZoneMode>1)
				schoolZoneMode = 0;
		}else{
			schoolZoneMode = 999;
		}
			
	}
		
	if(isObjectDetected()==OBJECT_NOT_DETECTED){
		if(schoolZoneMode==1){	//school zone			
			//1km/hour			
			aimSpeed = 3; //aim speed				
		}else{			
			aimSpeed = 58 - (abs(angle));					
		}
	}else{	//aism speed : stop
		aimSpeed = 99999;			
	}		
	return aimSpeed;

}

void speedControl(long int aimSpeed){
	long int speed;
	long int feedback;

	//read encoder : speed feedback
	feedback = readEnco();
	speed = pidControl(aimSpeed,feedback);	//speed control
	
	//encoder -> duty
	if(speed>0)
		speed = enToSpeed(speed);
	else{
		//speed = enToSpeed(abs(speed));
		speed =0;
	}

	//stop
#ifdef	MOTOR_MODE_USE_BACK
	if(aimSpeed == 99999 )
		speed = -50;	
	if((aimSpeed == 99999) && (feedback < 5))
		speed = 0;
#endif
#ifdef	MOTOR_MODE_NOT_BACK

	if(aimSpeed == 99999)
		speed = 0;
#endif	
	
#ifdef	CONTROL_DEBUG

	intToChar(feedback,7,buf);
	TransmitData(buf);

	TransmitData("\r\n");
#endif
	//speed = 100;
	
	dcControl(speed);
}

long int pidControl(long int speedRf,long int feedback){
	
	static long int preError[10]={0,0,0,0,0,0,0,0,0};
	static long int errorSum=0;
	volatile i;
	//pid controller	
	long int kp=300;
	long int kd=2;
	long int ki=8;
	long int pid;
	
	long int error;
	long int errorDif;		
	
	error = speedRf - feedback; 
	errorDif = error - preError[0];
	
	errorSum = 0;
	for(i=0;i<9;i++)
		errorSum +=preError[i];
	
	errorSum +=error; 

	pid = error * kp;
	pid+= errorDif * kd;
	pid+= errorSum * ki;
	
	//shift
	for(i=9;i>0;i--)
		preError[i] = preError[i-1];	
	//save data	
	preError[0] = error;

	return pid;
}


long int readEnco(void){
	unsigned long int enNum;
	volatile static unsigned long int preEnNumData[9]={0,0,0,0,0,0,0,0,0};		

	unsigned long int tempData[9];
	volatile int i;
	
	enNum =  EMIOS_0.CH[EMIOS_ENCODER_CH].CCNTR.R;
	
	//counter reset
	EMIOS_0.CH[EMIOS_ENCODER_CH].CADR.R = (volatile unsigned long int)enNum;		
	EMIOS_0.CH[EMIOS_ENCODER_CH].CADR.R = (volatile)10000; 	
	
	//shift
	for(i=8;i>0;i--)
		preEnNumData[i] = preEnNumData[i-1];
	
	preEnNumData[0] = enNum;	
	
	for(i=0;i<8;i++)
		tempData[i] = preEnNumData[i];
	
	enNum =(unsigned long int)medianFilter((int *)tempData,9,5);	
	enNum = lowPassfilter(preEnNumData[1],enNum);
	
	if(accumulateflag==0)
		accumulateDistance=0;
	else
		accumulateDistance += enNum;
	
	return (long int)enNum;
}

long int enToSpeed(long int en){
	long int duty;	 
	duty = ((en*53)+2010)/100;	
	return en;
}

 


