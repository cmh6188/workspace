#include "dcMotor.h"
#include "typedefs.h"
#include "jdp.h"
#include "gpio_drv.h"
#include "adc_drv.h"

void leftDC(long int duty){	
		
	GPIO_SetState(DC_ENALBLE,1);
	
	if(duty>=0)
		GPIO_SetState(DC1_OUT2,0);
	else{
		
		GPIO_SetState(DC1_OUT2,1);
		duty = -duty;	
		duty = 1000 - duty;
		
		if(duty>50)
			duty =50;
		//duty =0;
	}
		
	if(duty>1000)
		duty =1000;
	
	EMIOS_0.CH[LEFT_MOTOR_EMIOS_O_CHANNEL].CADR.R = (unsigned long int)duty;	
}

void rightDC(long int duty){	
	GPIO_SetState(DC_ENALBLE,1);
	
	if(duty>=0)
		GPIO_SetState(DC2_OUT2,0);
	else{
		
		GPIO_SetState(DC2_OUT2,1);				
		duty = -duty;
		duty = 1000 - duty;
		
		if(duty>50)
			duty =50;
			
		//duty = 0;
	}
			
	if(duty>1000)
		duty =1000;		
			
	EMIOS_0.CH[RIGHT_MOTOR_EMIOS_O_CHANNEL].CADR.R = (unsigned long int)duty;
}

void dcControl(long int duty){
	rightDC(duty);
	leftDC(duty);	
}
 
