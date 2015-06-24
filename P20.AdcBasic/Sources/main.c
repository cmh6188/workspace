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
#include "adc_drv.h"//fast starter kit >> driver code


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
	static uint32_t t_c, t_old=(uint32_t)-1;
	int32_t pot_a, pot_d, psen_a, psen_d;
	
	
	t_c = BTMR_GetRuntime()/100;
	
	if (t_c != t_old) {
		t_old = t_c;
		
		pot_a = A2D_GetSingleCh_10bit(0);//12비ㅏ트로
		psen_a = A2D_GetSingleCh_10bit(1);//12비트로
		
		pot_d = (pot_a*500+512)>>10;//512>>2048
		psen_d = (psen_a*500+512)>>10;//512>>2048 하면 안나올지도?
		
				
		SDBG_Printf("Pot = %d(%d.%02d), PhSen = %d(%d.%02d)\n",
			pot_a, pot_d/100, pot_d%100, psen_a, psen_d/100, psen_d%100);
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

	while (1)
		DoMainLoop();
	
	return 0;
}
