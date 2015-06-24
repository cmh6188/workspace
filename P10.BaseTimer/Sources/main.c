/*
 *######################################################################
 *
 * Project Name           : P10.BaseTimer
 *
 * Revision Number        : 1.0
 *
 * file                   : main.c
 *
 * Target Compiler        : Codewarrior
 *
 * Target Part            : MPC5606B
 *
 * Project Last Save Date : 01-Jan-2015
 *
 * Created on Date        : 01-Jan-2015
 *
 * Author                 : ����̷����б� ���� (2015�� NGV ���л� �� ���� ����, ����, ������ ���մϴ�.)
 * 
 * Brief Description      : �ð� ���� �⺻ �Լ��� ����
 *
 *######################################################################
*/

 
 
/********************  Dependent Include files here **********************/

#include "stdlib.h"
#include "stdio.h"

#include "ngv_dmu.h"
#include "rappid_ref.h"
#include "rappid_utils.h"
#include "sys_init.h"
#include "gpio.h"
#include "demoled.h"
#include "demoswitch.h"
#include "basetimer.h"


/**********************  Function Prototype here *************************/

void InitPeripherals(void);
void main(void);

/*********************  Initialization Function(s) ************************/


void InitPeripherals(void)
{
	sys_init_fnc();
	DLED_Init();
	DSW_Init();
	BTMR_Init();
	
	EnableExternalInterrupts();
}


void main(void)
{
	uint16_t i;
	  
	InitPeripherals();
	
	srand(0x0307);
	
	while(1) {

		// LED1�� 250msec. �������� 8�� ���
		for (i=1; i<=8; i++) {
			DLED_Toggle(DLED_LED1);
			BTMR_DelayMs(250);
		}
		
		// LED1�� ������ ����(50~149msec.)���� 5000 msec. ���� ��� 
		BTMR_SetTimer0(5000);
		while (BTMR_GetTimer0()) { 
			DLED_Toggle(DLED_LED1);
			BTMR_DelayMs(((uint32_t)rand()%100)+50); // 50~149
		}

		// 1�ʰ� LED1 OFF
		DLED_Set(DLED_LED1, DLED_OFF);
		BTMR_DelayMs(1000);
	}
}

 
/*
 *######################################################################
 *                           End of File
 *######################################################################
*/
