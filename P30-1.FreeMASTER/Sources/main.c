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
#include "rotaryencoder.h"
#include "motorcontrol.h"
#include "freemaster.h"


void InitPeripherals(void);
void DoMainLoop(void);

void Callback_s(char* str);
void Callback_e(char* str);


void InitPeripherals(void)
{
	sys_init_fnc();
	DLED_Init();
	DSW_Init();
	BTMR_Init();
#if EN_FREEMASTER
	FMSTR_Init();
#else
	SDBG_Init();
#endif
	MUART_Init();
	YUART_Init();
	CLCD_Init();
	FADC_Init(0xfff3);
	FUSS_Init(FUSS_CH_ALL);
	RENC_Init();
	MCTL_Init();
	
	EnableExternalInterrupts();
}


void Callback_s(char* str)
{
	int angle;
	
	if (sscanf(str, "%d", &angle)<1) {
		return;
	}
	
	MCTL_RotateSwheel((int16_t)angle);
	SDBG_Printf("\n");
}


void Callback_e(char* str)
{
	int speed;
	
	if (sscanf(str, "%d", &speed)<1) {
		return;
	}
	
	MCTL_RotateEngine((int16_t)speed);
	SDBG_Printf("\n");
}


void DoMainLoop(void)
{
#if EN_FREEMASTER
	FMSTR_Poll();
#else	
	if (SDBG_IsEvents())
		SDBG_ExecuteCallback();
#endif
	
	if (MUART_IsEvents())
		MUART_ExecuteCallback();
}


int main(void)
{
	InitPeripherals();
    
	SDBG_RegisterSmallCmd('s', Callback_s);
	SDBG_RegisterSmallCmd('e', Callback_e);
	
	while (1)
		DoMainLoop();
	
	return 0;
}
