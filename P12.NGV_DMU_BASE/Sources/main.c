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



void InitPeripherals(void);
void DoMainLoop(void);

void InitPeripherals(void)
{
	sys_init_fnc();
	DLED_Init();
	DSW_Init();
	BTMR_Init();
	
	EnableExternalInterrupts();
}

void DoMainLoop(void)
{
	uint16_t i;
	
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

int main(void)
{
	InitPeripherals();

	srand(0x0307);
	
	while (1)
		DoMainLoop();
	
	return 0;
}
