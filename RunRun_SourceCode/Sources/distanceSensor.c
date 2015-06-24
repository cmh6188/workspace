#include "distanceSensor.h"
#include "adc_drv.h"
#include "filter.h"
#include "jdp.h"
#include "gpio_drv.h"
#include "uart.h"

//debug
//#define DISTANCE_DEBUG

//divce
#define USE_PIR_SENSOR

unsigned long int counter;
int sonarStatus=SONAR_WAIT_RISING;
int distance[3];



int isObjectDetected(void){
	
	int reDist;
	volatile int i;
#ifdef	DISTANCE_DEBUG
	char buf[7];
#endif
	//get distance : AEB	
	distance[0]=sonarGetDistance();
	
#ifdef USE_PIR_SENSOR
	for(i=1;i<3;i++){
		distance[i] = getDistance(i-1);	
	}
#endif
#ifdef	DISTANCE_DEBUG
	for(i=0;i<3;i++){
		intToChar(distance[i],7,buf);
		TransmitData(buf);
		TransmitData("-");
	}
	TransmitData("\r\n");
#endif
		
	if(distance[0]<160){
		reDist = distance[0];
	}else{
		reDist=OBJECT_NOT_DETECTED;
		
#ifdef USE_PIR_SENSOR
		if((distance[1]<65)){
			reDist = distance[1];
		}else{
			if(distance[2]<65){
				reDist = distance[2];
			}else{
				reDist=OBJECT_NOT_DETECTED;	
			}
		}
#endif		
	}
	return reDist;
}


void sonarSensing(void){	
	unsigned long int dummy=0;	
	static const int ch = 0;
	
	switch(sonarStatus){
		case SONAR_WAIT_RISING:	{		
			//clear rising edge
			//set falling edge				
			dummy = SIU.IREER.R;
			dummy &= ~(1<<ch);
			SIU.IREER.R = dummy;
			
			dummy = SIU.IFEER.R;
			dummy |= (1<<ch);
			SIU.IFEER.R = dummy;		
	
			//counter enable
			dummy = EMIOS_0.UCDIS.R;
			dummy &=~(1<<SONAR0_EMIOS_CH);
			EMIOS_0.UCDIS.R = dummy;
			
			//counter reset
			dummy =  EMIOS_0.CH[SONAR0_EMIOS_CH].CCNTR.R;			
			EMIOS_0.CH[SONAR0_EMIOS_CH].CADR.R = (volatile unsigned long int)dummy;			
			EMIOS_0.CH[SONAR0_EMIOS_CH].CADR.R = (volatile)60000; 	
	
			sonarStatus = SONAR_SENSING;			
			break;
		}
		case SONAR_SENSING:	{		
			dummy = SIU.IREER.R;
			dummy &= ~(1<<ch);
			
			SIU.IREER.R = dummy;
			SIU.IFEER.R = dummy;			
			//read counter
			counter =  EMIOS_0.CH[SONAR0_EMIOS_CH].CCNTR.R;	
			//counter reset			
			EMIOS_0.CH[SONAR0_EMIOS_CH].CADR.R = (volatile unsigned long int)counter;
			EMIOS_0.UCDIS.R = 0x00000000|(1<<SONAR0_EMIOS_CH);	//disable		
			sonarStatus = SONAR_WAIT_ECHO;				
			PIT.CH[ch+1].TCTRL.B.TIE  = 0x1;
			break;
		}
		default:{
			break;
		}

	}	
}

 int sonarGetDistance(void){	
	static int distanceValue[9]={
			 9999,9999,9999,9999,9999,9999,9999,9999,9999	
	};
	static const int ch =0;	
	unsigned long int tempDistance,temp;
	volatile int i,distance;
	int tempData[9];
	
	switch(sonarStatus){
	case SONAR_WAIT_RISING:
		//sonar trigger
		GPIO_SetState(SONAR0_CONTROL_CH,1);
		for(i=0;i<110;i++);
		GPIO_SetState(SONAR0_CONTROL_CH,0);
		
		SIU.IRER.R = 0x00000001;
		//set rising		
		temp = SIU.IREER.R;
		temp |= (1<<ch);
		SIU.IREER.R = temp;
			
		temp = SIU.IFEER.R;
		temp &= ~(1<<ch);
		SIU.IFEER.R = temp;	
		break;
	case SONAR_WAIT_END:
		sonarStatus = SONAR_WAIT_RISING;	
		break;
	}
	
	tempDistance = counter;
	distance = counterToDistance(tempDistance);
	
	//shift
 	for(i=8;i>0;i--)
 		distanceValue[i] = distanceValue[i-1];
 		
 	distanceValue[0] = distance;	

 	for(i=0;i<9;i++)
 		tempData[i] = distanceValue[i];
 	//median filter
 	distance = medianFilter(tempData,9,5);
 	 	
	return distance;
}
 
 int counterToDistance(unsigned int counter){
	 long int distance;
	 int reValue;
	 distance = ((long int)counter * 7)/100;
	 reValue = (int) distance;
	
	 return reValue;
 }
 
 int adcToDistance(int adcValue) {
    long int reVal=0;
    
    if(adcValue>=500 && adcValue<670)                 //7~10Cm
       reVal =(long int)(670-adcValue)*4/170+6; 
    else if(adcValue>=360 && adcValue<500)            //10~15Cm
       reVal =(long int)(500-adcValue)*5/140+10; 
    else if(adcValue>=280 && adcValue<360)            //15~20Cm
       reVal =(long int)(360-adcValue)*5/80+15; 
    else if(adcValue>=207 && adcValue<280)            //20~30cm
       reVal =(long int)(280-adcValue)*10/73+20;   
    else if(adcValue>=170 && adcValue<207)             //30~40Cm
       reVal =(long int)(207-adcValue)*10/37+30 ; 
    else if(adcValue>=150 && adcValue<170)              //40~50Cm
       reVal =(long int)(170-adcValue)*10/20+40 ; 
    else if(adcValue>=123 && adcValue<150)              //50~70Cm
         reVal =(long int)(150-adcValue)*20/27+50 ; 
    else
       reVal = 70; 
    
    return (int)reVal;  
 }

 int getDistance(int channel){
 	static const int adcCh[2] ={2,3};
 	static int distanceValue[2][9]={{255,255,255,255,255,255,255,255,255}
 									,{255,255,255,255,255,255,255,255,255}
 	};
 	
 	int tempData[9];
 	volatile int i,adcValue,distance;	
 	
 	adcValue = (int)A2D_GetSingleCh_10bit((unsigned long)adcCh[channel]);  
 	adcValue = (int)adcToDistance(adcValue);	//new distance
 	
 	//shift
 	for(i=8;i>0;i--)
 		distanceValue[channel][i] = distanceValue[channel][i-1];
 		
 	distanceValue[channel][0] = adcValue;	

 	for(i=0;i<9;i++)
 		tempData[i] = distanceValue[channel][i];
 	//median filter
 	distance = medianFilter(tempData,9,5);
 	
 	return distance;
 }
