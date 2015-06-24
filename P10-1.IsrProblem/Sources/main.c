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
 * Author                 : 동양미래대학교 정준 (2015년 NGV 장학생 외 무단 전재, 복제, 배포를 금합니다.)
 * 
 * Brief Description      : 인터럽트 서비스 루틴 ISR을 잘못 사용해서 발생하는 문제
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
	
	
	//- 다음의 if에서는 flag 변수의 참/거짓을 판단할까?
	flag = 0;
	if (flag) {
		DLED_Toggle(DLED_LED1);
		for (i=0; i<10; i++)
			DLED_Toggle(DLED_LED2);
	}
	
	while(1) {
		
		//- LED1과 LED2를 PIT0_ISR에서는 0.25초 간격으로 토글
		//    여기서는 매우 빠르게 약 1.1초 동안 토글 후 1.1초 동안 아무 것도 안 함
		//    과연 LED1과 LED2 토글 후의 On/Off 상태는 같을까?
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
