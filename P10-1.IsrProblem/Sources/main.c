/*
 *######################################################################
 *
 * Project Name           : P10-1.IsrProblem
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
 * Brief Description      : ���ͷ�Ʈ ���� ��ƾ ISR�� �߸� ����ؼ� �߻��ϴ� ����
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


uint16_t flag;

void main(void)
{
	uint16_t i;
	  
	InitPeripherals();
	
	
	//- ������ if������ flag ������ ��/������ �Ǵ��ұ�?
	flag = 0;
	if (flag) {
		DLED_Toggle(DLED_LED1);
		for (i=0; i<10; i++)
			DLED_Toggle(DLED_LED2);
	}
	
	while(1) {
		
		//- LED1�� LED2�� PIT0_ISR������ 0.25�� �������� ���
		//    ���⼭�� �ſ� ������ �� 1.1�� ���� ��� �� 1.1�� ���� �ƹ� �͵� �� ��
		//    ���� LED1�� LED2 ��� ���� On/Off ���´� ������?
		BTMR_SetTimer0(1100);
		while (BTMR_GetTimer0()) {
			for (i=0; i<10; i++) {
				//DisableExternalInterrupts();
				DLED_Toggle(DLED_LED1);
				DLED_Toggle(DLED_LED2);
				//EnableExternalInterrupts();
			}
		}
		BTMR_DelayMs(1100);
	}
}

 
/*
 *######################################################################
 *                           End of File
 *######################################################################
*/
