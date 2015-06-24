//FreeRun ADC. 알아서 돌아가는 ADC

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
#include "freerunadc.h"


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
	FADC_Init(0xfff3);
	
	EnableExternalInterrupts();
}


void DoMainLoop(void)
{
	static uint32_t t_c, t_old=(uint32_t)-1, cnt=0;
	int16_t i;
	
	t_c = BTMR_GetRuntime()/50//100; for 0.2 ms
	
	if (t_c != t_old) {
		t_old = t_c;
		
		SDBG_Printf("%d ", cnt++);
		
		//for (i=0; i<6; i++) {
			//SDBG_Printf("%4d ", FADC_Get(1));//Pot on board
			SDBG_Printf("%4d ", FADC_Get(5));//pd0 distance sensor
		//}
		SDBG_Printf("\n");
	}
	
	if (SDBG_IsEvents())
		SDBG_ExecuteCallback();
	
	if (MUART_IsEvents())
		MUART_ExecuteCallback();
}


int main(void)
{
	InitPeripherals();

	while (1)
		DoMainLoop();
	
	return 0;
}
