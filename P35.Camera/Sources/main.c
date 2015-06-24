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
//#include "freerunusonic.h"
#include "rotaryencoder.h"
#include "motorcontrol.h"
#include "camera.h"


void InitPeripherals(void);
void DoMainLoop(void);

void Callback_s(char* str);

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
	//FUSS_Init(FUSS_CH2);
	RENC_Init();
	MCTL_Init();
	//CAM_Init(CAM_CH1);
	
	EnableExternalInterrupts();
}

#define MCTL_SWHEEL_MAX		(100)
#define MCTL_SWHEEL_MIN		(-100)

#define MCTL_ENGINE_MAX	(2047)
#define MCTL_ENGINE_MIN	(-2047)

void Callback_s(char* str)
{
	int angle;
	
	if (sscanf(str, "%d", &angle)<1) {
		return;
	}
	
	MCTL_RotateSwheel((int16_t)angle);
	SDBG_Printf("\nS\n");
}


void DoMainLoop(void)
{
	//COUNT FOR TIMER
	static uint32_t t_c, t_old=(uint32_t)-1, cnt=0;
	
	//SERIAL COMMUNICATE
	if (SDBG_IsEvents())
		SDBG_ExecuteCallback();
	
	if (MUART_IsEvents())
		MUART_ExecuteCallback();
	
	//TIMER FOR EACH 100 ms	
	t_c = BTMR_GetRuntime()/100;
	
	if (t_c != t_old) {
		t_old = t_c;
		CAM_Clock_ISR();
		//SDBG_Printf("%u: %u mm\n", cnt++, FUSS_GetMm(FUSS_CH0));
	}
}


int main(void)
{
	InitPeripherals();
    
	SDBG_RegisterSmallCmd('s', Callback_s);
	//SDBG_RegisterSmallCmd('e', Callback_e);
	
	while (1)
		DoMainLoop();
	
	return 0;
}
