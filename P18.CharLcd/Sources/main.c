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
#include "serialdebug.h"
#include "myuart.h"
#include "youruart.h"
#include "charlcd.h"


void InitPeripherals(void);
void DoMainLoop(void);


void InitPeripherals(void)
{
	sys_init_fnc();
	DLED_Init();
	DSW_Init();
	BTMR_Init();
	SDBG_Init();
	MUART_Init();
	YUART_Init();
	CLCD_Init();
	
	EnableExternalInterrupts();
}


void DoMainLoop(void)
{
	static uint32_t t_c, t_old=(uint32_t)-1;//11111111111~
	
	t_c = BTMR_GetRuntime()/100;
	
	if (t_c != t_old) {//0.1초마다 진입
		t_old = t_c;
		
		CLCD_PrintfXy(0, 2, "Runtime = %u.%01u sec.", t_c/10, t_c%10);//작동시간 표시
	}
	
	if (SDBG_IsEvents())
		SDBG_ExecuteCallback();
	
	if (MUART_IsEvents())
		MUART_ExecuteCallback();
}


int main(void)
{
	uint16_t i;
	
	InitPeripherals();

	CLCD_GotoXy(0, 0);
	for (i=0; i<8; i++) {
		CLCD_PutCh((char)i);
	}
	CLCD_GotoXy(1, 1);
	CLCD_Printf("NGV! DMU! JJ!");
	  
	while (1)
		DoMainLoop();
	
	return 0;
}
