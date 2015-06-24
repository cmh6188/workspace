/*
 * motorcontrol.c
 *
 *  Created on: Jan 11, 2015
 *      Author: ����̷����б� ����
 *        Note: 2015�� NGV ���л� �� ���� ����, ����, ������ ���մϴ�.        
 */


#include "motorcontrol.h"
#include "gpio.h"


void MCTL_Init(void)
{
	GPIO_Set(GPIO_PA5, 1);
}

//- RC Servo ���Ϳ� angle�� �ش��ϴ� ���� ����� ����
//    angle�� ������ MCTL_SWHEEL_MIN ~ MCTL_SWHEEL_MAX
void MCTL_RotateSwheel(int16_t angle)
{
	if (angle < MCTL_SWHEEL_MIN)
		angle = MCTL_SWHEEL_MIN;
	
	if (angle > MCTL_SWHEEL_MAX)
		angle = MCTL_SWHEEL_MAX;

	EMIOS_0.CH[1].CADR.R = (uint32_t)((angle<<5)+MCTL_SWHEEL_RAW_MID);
//	EMIOS_0.CH[1].CADR.R = (angle*(MCTL_SWHEEL_RAW_MAX-MCTL_SWHEEL_RAW_MID)/MCTL_SWHEEL_MAX)+MCTL_SWHEEL_RAW_MID;
}

//- DC Motor�� speed�� �ش��ϴ� PWM ���
//	  speed�� MCTL_ENGINE_MIN ~ MCTL_ENGINE_MAX ����
void MCTL_RotateEngine(int16_t speed)
{
	if (speed < MCTL_ENGINE_MIN)
		speed = MCTL_ENGINE_MIN;
	
	if (speed > MCTL_ENGINE_MAX)
		speed = MCTL_ENGINE_MAX;

	GPIO_Set(GPIO_PA4, 0);
	GPIO_Set(GPIO_PA6, 0);

	if (speed>=0) {
		GPIO_Set(GPIO_PA4, 0);
		GPIO_Set(GPIO_PA6, 1);
		EMIOS_0.CH[2].CADR.R = speed;  
	}
	else {
		GPIO_Set(GPIO_PA4, 1);
		GPIO_Set(GPIO_PA6, 0);
		EMIOS_0.CH[2].CADR.R = (uint32_t)(-speed);  
	}
}

//- DC Motor Brake
void MCTL_BrakeEngle(void)
{
	GPIO_Set(GPIO_PA4, 0);
	GPIO_Set(GPIO_PA6, 0);
}
