#include "servo.h"
#include "typedefs.h"
#include "jdp.h"



//max value : 2645 
//min value : 380  
#define FUTABA_S3010_MAX		2645
#define FUTABA_S3010_MIN		390
#define FUTABA_S3010_MIDDLE		1512

#define EMIOS_O_CHANNEL		23	//PE7

void servoAngle(int angle){	
	if(angle>MAX_ANGLE)
		angle = MAX_ANGLE;
	else if(angle<MIN_ANGLE)
		angle = MIN_ANGLE;
		
	EMIOS_0.CH[EMIOS_O_CHANNEL].CADR.R = (unsigned long int)(FUTABA_S3010_MIN + 11*angle);
}
 
//min : 65 degree
//max : 135 degree
//center : 100 degree
void moveAngle(int angle){
	angle +=100;
	
	if(angle>135){
		angle = 135;	
	}else if(angle<65){
		angle = 65;
	}
	
	servoAngle(angle);

}
