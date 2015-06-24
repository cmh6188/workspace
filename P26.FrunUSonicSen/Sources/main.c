//FRUN USONIC //알아서 돌아가는 초음파.
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
#include "freerunusonic.h"


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
	FUSS_Init(FUSS_CH_ALL);
	
	EnableExternalInterrupts();
}


void DoMainLoop(void)
{
	static uint32_t t_c, t_old=(uint32_t)-1, cnt=0;
	
	t_c = BTMR_GetRuntime()/100;
	
	if (t_c != t_old) {
		t_old = t_c;
		
		SDBG_Printf("%u: %u mm\n", cnt++, FUSS_GetMm(FUSS_CH0));
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
