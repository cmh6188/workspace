/*
 *######################################################################
 *
 * Project Name           : P01.LedBlinking
 *
 * Revision Number        : 1.0
 *
 * file                   : main.c
 *
 * Target Compiler        : Codewarrior
 *
 * Target Part            : MPC5606B
 *
 * Project Last Save Date : 29-Dec-2014
 *
 * Created on Date        : 29-Dec-2014
 *
 * Author                 : 동양미래대학교 정준
 * 
 * Brief Description      : LED를 어떻게 켜는지 맛보기 예제
 *
 *######################################################################
*/

 
 
/********************  Dependent Include files here **********************/

#include "rappid_ref.h"
#include "rappid_utils.h"
#include "sys_init.h"
#include "typedefs.h"

/**********************  Function Prototype here *************************/

void delay_ms(uint32_t ms);
void main(void);

/*********************  Initialization Function(s) ************************/


//================================================================
// ms milliseconds 만큼 시간 지연을 함
//   DELAY_1MS_CNT 값을 적절하게 정해야 함 
//================================================================
#define DELAY_1MS_CNT 2270 
void delay_ms(uint32_t ms)
{
	vuint32_t cnt;
	
	while (ms--)
		for (cnt=0; cnt<DELAY_1MS_CNT; cnt++) {
		}
}

void main(void)
{
	uint32_t i, j;
	
	//- sys_init_fnc() 함수에서 시스템을(레지스터를) 초기화함
	sys_init_fnc();
	EnableExternalInterrupts();
   
	//- 회로도를 보면, 
	//   LED1: PE4(68번), LED2: PE5(69번), LED3: PE6(70번), LED4: PE7(71번)
	//   LED가 모두 High 출력일 때, OFF, Low 출력일 때, ON임
	//

	//- PE4, PE5, PE6, PE7을 GPIO의 출력으로 초기 설정하는 것은
	//   siu_init.c의 siu_init_fnc() 함수가 담당
	//   siu_portE_init_fnc()에 보면, SIU.PCR[68].R = 0x0201; 

	//- 일단, LED 모두 OFF
	//   참고: 레지스터에 액세스에 대한 Macro 상수 선언은 jdp.h에 있음
	SIU.GPDO[68].B.PDO = 1; // 1이면 High 출력, 0이면 Low 출력
	SIU.GPDO[69].B.PDO = 1;
	SIU.GPDO[70].B.PDO = 1;
	SIU.GPDO[71].B.PDO = 1;
   
	//- LED1부터 0.5초 ON, 0.5초 OFF를 10회 반복
	while(1) {
		for (i=68; i<=71; i++) {
			for (j=0; j<10; j++) {
				SIU.GPDO[i].B.PDO = 0;
				delay_ms(500);
				SIU.GPDO[i].B.PDO = 1;
				delay_ms(500);
			}
		}
	}
}

 
/*
 *######################################################################
 *                           End of File
 *######################################################################
*/
