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
	FADC_Init(0xfff3);//전 채널 사용.
	
	EnableExternalInterrupts();
}


void DoMainLoop(void)
{
	static uint32_t t_c, t_old=(uint32_t)-1, cnt=0;
	uint32_t t_start, t_end, t_echo;
	
	t_c = BTMR_GetRuntime()/100;
	
	if (t_c != t_old) {
		t_old = t_c;
		
		GPIO_Set(GPIO_PG10, 1);
		BTMR_DelayMs(1);
		GPIO_Set(GPIO_PG10, 0);
		
		BTMR_SetTimer0(10);
		while (BTMR_GetTimer0() > 0) {
			if (GPIO_Get(GPIO_PG2)==1)
				break;
		}
		t_start = BTMR_GetRuntime();
		
		BTMR_SetTimer0(40);
		while (BTMR_GetTimer0() > 0) {
			if (GPIO_Get(GPIO_PG2)==0)
				break;
		}
		t_end = BTMR_GetRuntime();
		
		t_echo = t_end - t_start;//mm단위 리턴.
		
		SDBG_Printf("%u: %u\n", cnt++, t_echo);
		SDBG_Printf("%d\n", );
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
