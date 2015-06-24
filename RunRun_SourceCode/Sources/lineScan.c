#include "lineScan.h"
#include "adc_drv.h"
#include "gpio_drv.h"
#include "typedefs.h"
#include "uart.h"

//#define LINE_DEBUG1			//adjust line value
//#define LINE_DEBUG2			//start add & end add
//#define LINE_DEBUG3
//#define SCHOOL_ZONE_DEBUG
//char buffer[8];

//mode select
#define USE_SCHOOLZONE_ERROR_DISABLE
#define SCHOOLZONE_PERIOD_GAIN		100L	//do not edit
#define SCHOOLZONE_ERROR_SEC		25L

/***********[line Data]***********/
uint16_t leftLineScanData[NUM_LINE_DATA];
uint16_t rightLineScanData[NUM_LINE_DATA];

uint16_t thLV=700;
uint16_t thRV=700;
uint16_t minRV=1023;
uint16_t maxRV=0;
uint16_t minLV=1023;
uint16_t maxLV=0;
volatile int scFlag = SCHOOL_ZONE_ABLE;

extern int accumulateflag;

int lineScan(void){

	volatile int i;	
	
	uint16_t temp = 0;	
	uint16_t dummyData;
	
	minRV=1023;
	maxRV=0;
	minLV=1023;
	maxLV=0;
	
	//******************************[camera 1]********************************************//	
	//First 1 clock
	GPIO_SetState(LINESCAN2_SI,1);
	GPIO_SetState(LINESCAN2_CLOCK,1);
	GPIO_SetState(LINESCAN1_SI,1);	
	GPIO_SetState(LINESCAN1_CLOCK,1);
	dummyData = A2D_GetSingleCh_10bit(LINESCAN1_ADC);
	
	GPIO_SetState(LINESCAN2_SI,0);
	GPIO_SetState(LINESCAN2_CLOCK,0);
	GPIO_SetState(LINESCAN1_SI,0);				
	GPIO_SetState(LINESCAN1_CLOCK,0);
	dummyData = A2D_GetSingleCh_10bit(LINESCAN2_ADC);
	
	//2nd clock
	GPIO_SetState(LINESCAN2_CLOCK,1);	
	GPIO_SetState(LINESCAN1_CLOCK,1);
	dummyData = A2D_GetSingleCh_10bit(LINESCAN1_ADC);
	
	GPIO_SetState(LINESCAN2_CLOCK,0);	
	GPIO_SetState(LINESCAN1_CLOCK,0);
	dummyData= A2D_GetSingleCh_10bit(LINESCAN2_ADC);
		
	//third clock	
	GPIO_SetState(LINESCAN2_CLOCK,1);	
	GPIO_SetState(LINESCAN1_CLOCK,1);
	dummyData = A2D_GetSingleCh_10bit(LINESCAN1_ADC);	
	
	GPIO_SetState(LINESCAN2_CLOCK,0);
	GPIO_SetState(LINESCAN1_CLOCK,0);
	dummyData = A2D_GetSingleCh_10bit(LINESCAN2_ADC);
			
	for(i=0;i<1;i++){			
		GPIO_SetState(LINESCAN2_CLOCK,1);
		GPIO_SetState(LINESCAN1_CLOCK,1);		
		dummyData = A2D_GetSingleCh_10bit(LINESCAN1_ADC);
		
					
		GPIO_SetState(LINESCAN2_CLOCK,0);
		GPIO_SetState(LINESCAN1_CLOCK,0);
		rightLineScanData[i] = A2D_GetSingleCh_10bit(LINESCAN2_ADC);			
	}	
		
	
	//The others clock pulse 
	i=0;
	while(i<(NUM_LINE_DATA-1)){
		GPIO_SetState(LINESCAN2_CLOCK,1);
		GPIO_SetState(LINESCAN1_CLOCK,1);				
		leftLineScanData[i] = A2D_GetSingleCh_10bit(LINESCAN1_ADC);		
				
		GPIO_SetState(LINESCAN2_CLOCK,0);
		GPIO_SetState(LINESCAN1_CLOCK,0);
		rightLineScanData[i+1] = A2D_GetSingleCh_10bit(LINESCAN2_ADC);		
		
		i++;	
	}		
	
	GPIO_SetState(LINESCAN2_CLOCK,1);
	GPIO_SetState(LINESCAN1_CLOCK,1);		
	leftLineScanData[NUM_LINE_DATA-1] = A2D_GetSingleCh_10bit(LINESCAN1_ADC);	


	GPIO_SetState(LINESCAN2_CLOCK,0);
	GPIO_SetState(LINESCAN1_CLOCK,0);	
	dummyData = A2D_GetSingleCh_10bit(LINESCAN2_ADC);
		
	
	//**********************[thresh holding]***************************//
	for(i=0;i<NUM_LINE_DATA;i++){
		if(leftLineScanData[i]<minLV){
			minLV = leftLineScanData[i];
		}		
		if(leftLineScanData[i]>maxLV){
			maxLV = leftLineScanData[i];
		}	
		
		if(rightLineScanData[i]<minRV){
			minRV = rightLineScanData[i];
		}	
		if(rightLineScanData[i]>maxRV){
			maxRV = rightLineScanData[i];
		}
	}
		
#ifdef	LINE_DEBUG1
	
	TransmitData("left :");
	intToChar(leftLineScanData[0],5,buffer);
	TransmitData(buffer);
	TransmitData("-");
	intToChar(leftLineScanData[NUM_LINE_DATA-1],5,buffer);
	TransmitData(buffer);
	
	TransmitData("right:");
	intToChar(rightLineScanData[0],5,buffer);
	TransmitData(buffer);
	TransmitData("-");
	intToChar(rightLineScanData[NUM_LINE_DATA-1],5,buffer);
	TransmitData(buffer);
	TransmitData("\r\n");	
#endif
	
	return SENSING_SUCCESS;
}


int lineSensing(struct lineDataSt * leftLineData,struct lineDataSt * rightLineData){
	
	//******** declare variable ***********//
	unsigned char leftLineBinaryData[NUM_LINE_DATA];
	unsigned char rightLineBinaryData[NUM_LINE_DATA];
	volatile int i,findBlackFlag;	
	

	//make binary data
	for(i=0;i<NUM_LINE_DATA;i++){
		if(leftLineScanData[i]>thLV)
			leftLineBinaryData[i] = WHITE_LINE;
		else
			leftLineBinaryData[i] = BLACK_LINE;
	
		if(rightLineScanData[i]>thRV)
			rightLineBinaryData[i] = WHITE_LINE;
		else
			rightLineBinaryData[i] = BLACK_LINE;
	}
		
	
	//******** analyze of line data ***********//
	//initialization of data
	findBlackFlag = 0;
	leftLineData->numOfLine = 0;
	leftLineData->blackLineCount = 0;
	for(i=0;i<MAX_LINE;i++){
		leftLineData->blackLine[i].startAdd = NOT_DETECTED;
		leftLineData->blackLine[i].endAdd = NOT_DETECTED;
	}
	
	//left camera 	
	for(i=(NUM_LINE_DATA-1);i>=0;i--){	
		if(leftLineBinaryData[i]==BLACK_LINE){
			if(findBlackFlag==0){	//find start address of black line 			
				leftLineData->numOfLine++;				
				leftLineData->blackLine[leftLineData->numOfLine-1].startAdd =NUM_LINE_DATA-(i+1);
				findBlackFlag=1;				
			}
			leftLineData->blackLineCount++;
		}else if(leftLineBinaryData[i]==WHITE_LINE){
			if(findBlackFlag==1){	//find end address of black line 
				leftLineData->blackLine[leftLineData->numOfLine-1].endAdd = NUM_LINE_DATA-(i+1);
				findBlackFlag=0;
			}
		}		
	}
	i++;	//min(i) = 0;
	//error check : black line end
	if((findBlackFlag==1)&&(i==0)){					
		leftLineData->blackLine[leftLineData->numOfLine-1].endAdd = NUM_LINE_DATA-(i+1);
	}
	
	//right camera 	
	findBlackFlag = 0;
	rightLineData->numOfLine = 0;
	rightLineData->blackLineCount =0;
	for(i=0;i<MAX_LINE;i++){
			rightLineData->blackLine[i].startAdd = NOT_DETECTED;
			rightLineData->blackLine[i].endAdd = NOT_DETECTED;
	}	

	for(i=0;i<NUM_LINE_DATA;i++){			
		if(rightLineBinaryData[i]==BLACK_LINE){
			if(findBlackFlag==0){	//find start address of black line 			
				rightLineData->numOfLine++;
				rightLineData->blackLine[rightLineData->numOfLine-1].startAdd = i;
				findBlackFlag=1;				
			}
			rightLineData->blackLineCount++;
		}else if(rightLineBinaryData[i]==WHITE_LINE){
			if(findBlackFlag==1){	//find end address of black line 
				rightLineData->blackLine[rightLineData->numOfLine-1].endAdd = i;
				findBlackFlag=0;
			}
		}		
	}
	i--;	//max(i) = 124
	//error check : black line end
	if((findBlackFlag==1)&&(i==124)){				
		rightLineData->blackLine[rightLineData->numOfLine-1].endAdd = i;
	}
	
	return SENSING_SUCCESS;
}


int lineControl(int encoFeedback){
	
	volatile static long int scErrorCounter=0;
	
	
	struct lineDataSt leftLineData,rightLineData;
	static int preAngle,schoolZone;
	static int schoolZoneMode =0;		
	static int controlStatus=CROSS_LINE_CONTROL;	
	
	static int preError[10]={0,0,0,0,0,0,0,0,0,0};
	static int refPos = 0;
	static int prePos=0;
	static int lineControl=0;
	static int errorCounter=0;
	
	const int kp = 75;	//150
	const int kd = 0;
	const int ki = 0;
	volatile int i;	
	int angle,pos;
	int errorSum=0;
	int posError,posDif;
	
	//******** detection of line ***********//
	//line scan from line scan camera
	if(lineScan()==SENSING_ERROR)
		return preAngle;
	//detect line
	if(lineSensing(&leftLineData,&rightLineData)==SENSING_ERROR)	
		return preAngle;
	
	if(scFlag==SCHOOL_ZONE_DISABLE){
		encoFeedback = 25000;
		schoolZoneMode=0;
	}
#ifdef	SCHOOL_ZONE_DEBUG
	
	if(accumulateflag){
		intToChar(encoFeedback,5,buffer);		
		TransmitData(buffer);	
		TransmitData("-");
	

		intToChar(preAngle,5,buffer);
		TransmitData(buffer);	
		TransmitData("\r\n");
	}
	else
		TransmitData("\r\n");
#endif
	
#ifdef SCHOOL_ZONE_DEBUG
	if(schoolZoneMode)
		TransmitData("[scm]");
	else
		TransmitData("[nor]");
			
	TransmitData("bls:");			
	intToChar(leftLineData.blackLineCount,5,buffer);
	TransmitData(buffer);	
	TransmitData(",");
	intToChar(rightLineData.blackLineCount,5,buffer);
	TransmitData(buffer);	
	TransmitData("-nl:");
	intToChar(leftLineData.numOfLine,3,buffer);
	TransmitData(buffer);
	TransmitData(",");
	intToChar(rightLineData.numOfLine,3,buffer);
	TransmitData(buffer);
	TransmitData("\r\n");
#endif
	//******** analyze of line data ***********//
	//analyze
	if((leftLineData.blackLine[0].startAdd)!=NOT_DETECTED && (rightLineData.blackLine[0].startAdd)!=NOT_DETECTED){
		//two line control
		if(((-25<=preAngle)&&(preAngle<=25))&&((leftLineData.blackLineCount>20) || (rightLineData.blackLineCount>20))){
			controlStatus = SCHOOL_LINE1_CONTROL;
#ifdef	SCHOOL_ZONE_DEBUG
	TransmitData("sc2\r\n");
#endif		
			if(scFlag!=SCHOOL_ZONE_DISABLE)
				if(schoolZone==0){
					schoolZone=1;
					accumulateflag=1;	
	#ifdef	SCHOOL_ZONE_DEBUG
		TransmitData("sc2-1\r\n");
	#endif
				}else if(schoolZone==2){
					//0.0038095cm /pulse = 0.038095 mm/pulse = 38.095 um / pulse
					// 10 cm = 100 mm = 100000um
					// 100000um / (38.095 um/pulse) =  2625pulse
					if((2200 < encoFeedback)  && (encoFeedback < 5300)){
						controlStatus = SCHOOL_LINE2_CONTROL;
						schoolZone=0;
						accumulateflag=0;	
						schoolZoneMode++;
						
						if(schoolZoneMode==2){
							schoolZoneMode=0;
						}						
	#ifdef	SCHOOL_ZONE_DEBUG
		TransmitData("sc2-2\r\n");
	#endif
					}else{					
						controlStatus = CROSS_LINE_CONTROL;
						accumulateflag=0;
						schoolZone=0;						
					}
				}

		}else{
			controlStatus = TWO_LINE_CONTROL;
			if((leftLineData.blackLine[0].startAdd>120) && (leftLineData.blackLine[0].startAdd>120)){
				if(scFlag!=SCHOOL_ZONE_DISABLE)
					if(schoolZone==1){
						schoolZone=2;	
	#ifdef	SCHOOL_ZONE_DEBUG
					TransmitData("sc1-cr\r\n");
	#endif
					}
			}
		
		}
		
	}else if((leftLineData.blackLine[0].startAdd)==NOT_DETECTED && (rightLineData.blackLine[0].startAdd==NOT_DETECTED)){
		//cross line control
		controlStatus = CROSS_LINE_CONTROL;
		if(scFlag!=SCHOOL_ZONE_DISABLE)
			if(schoolZone==1){
				schoolZone=2;	
	#ifdef	SCHOOL_ZONE_DEBUG
		TransmitData("sc1-cr\r\n");
	#endif
			}
	}else if((leftLineData.blackLine[0].startAdd)!=NOT_DETECTED || (rightLineData.blackLine[0].startAdd)!=NOT_DETECTED){		
		if((scFlag!=SCHOOL_ZONE_DISABLE)&&(schoolZoneMode)&&((leftLineData.blackLine[0].endAdd - leftLineData.blackLine[0].startAdd)>20 || (rightLineData.blackLine[0].endAdd - rightLineData.blackLine[0].startAdd)>20)){
			controlStatus = CROSS_LINE_CONTROL;				
		}else{
			//one line control
			if(leftLineData.blackLine[0].startAdd!=NOT_DETECTED){	//left			
				pos = leftLineData.blackLine[0].startAdd;
				controlStatus = LEFT_ONE_LINE_CONTROL;										
			}else{	//right				
				pos = rightLineData.blackLine[0].startAdd;
				controlStatus = RIGHT_ONE_LINE_CONTROL;	
			}
		}	
		
		if(schoolZone==1){
			schoolZone=2;	
#ifdef	SCHOOL_ZONE_DEBUG
	TransmitData("sc1-1l\r\n");
#endif
		}
						
	}	
	if(scFlag!=SCHOOL_ZONE_DISABLE){
		if(schoolZone){
			errorCounter++;
			if(errorCounter>400||encoFeedback > 5300){
				accumulateflag=0;
				schoolZone=0;
				errorCounter=0;
			}
		}
	}
#ifdef	USE_SCHOOLZONE_ERROR_DISABLE	
	if(schoolZoneMode==1){
		scErrorCounter++;
		if(scErrorCounter>SCHOOLZONE_ERROR_SEC*SCHOOLZONE_PERIOD_GAIN){
			scErrorCounter = 0;
			schoolZoneMode = 0;
			scFlag = SCHOOL_ZONE_DISABLE;			
			return SCHOOL_ZONE;
		}	
	}else{
		scErrorCounter=0;
	}
#endif
	
#ifdef	LINE_DEBUG2
	TransmitData("left:");
	intToChar(leftLineData.blackLine[0].startAdd,5,buffer);
	TransmitData(buffer);
	TransmitData(",");
	intToChar(leftLineData.blackLine[0].endAdd,5,buffer);
	TransmitData(buffer);
	TransmitData("-");
	
	TransmitData("right:");
	intToChar(rightLineData.blackLine[0].startAdd,5,buffer);
	TransmitData(buffer);
	TransmitData(",");
	intToChar(rightLineData.blackLine[0].endAdd,5,buffer);
	TransmitData(buffer);

	TransmitData("\r\n");
	

#endif	
	
	//angle control
	switch(controlStatus){
		case SCHOOL_LINE2_CONTROL:	
			if(scFlag!=SCHOOL_ZONE_DISABLE)
				return SCHOOL_ZONE;
			else{
				angle = preAngle;
				schoolZoneMode = 0;
			}
				
			break;
		default:
		case SCHOOL_LINE1_CONTROL:
			angle = preAngle;		
			
			break;
		case CROSS_LINE_CONTROL:	//cross line	
			angle = preAngle;			
			break;				
		case TWO_LINE_CONTROL:			
			angle = preAngle;			
			break;				
		case LEFT_ONE_LINE_CONTROL:	//normal line
		case RIGHT_ONE_LINE_CONTROL:		
						
			pos = 124 -pos;				
			
			if(controlStatus==RIGHT_ONE_LINE_CONTROL){
				pos = -pos;	
			}
			
			refPos = (prePos-pos)/2;

			posError = refPos - pos;
			posDif = posError - preError[0];
			
			for(i=0;i<10;i++)
				errorSum += preError[i];			
			errorSum += posError;
			
			angle  = (kp * posError)/100;
			angle += (kd * posDif)/100;
			angle += (ki * errorSum)/100;					
						
			//save data
			for(i=9;i>0;i--)
				preError[i] = preError[i-1];
			preError[0] = posError;	
				
				
			angle = -angle;			
			prePos = pos;
			break;				
	}		
	
	if(scFlag!=SCHOOL_ZONE_DISABLE)
		if(schoolZoneMode==1){
			if(angle<-25)
				angle = -25;
			if(angle>25)
				angle = 25;			
		}
	
	
#ifdef	LINE_DEBUG3
	intToChar(pos,5,buffer);
	TransmitData(buffer);
	TransmitData("\r\n");
#endif

	if(angle>35)
		angle =35;
	else if(angle<-35)
		angle = -35;

	preAngle = angle;
	
	return angle;

}



