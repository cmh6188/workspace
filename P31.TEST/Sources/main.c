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
#if NGV_DMU_SYSCLK == SYSCLK_IRC_16MHZ
#define DELAY_1MS_CNT 2270
#elif NGV_DMU_SYSCLK == SYSCLK_PLL_32MHZ
#define DELAY_1MS_CNT (2270*2)
#elif NGV_DMU_SYSCLK == SYSCLK_PLL_64MHZ
#define DELAY_1MS_CNT (2270*4)
#endif



void InitPeripherals(void);
void DoMainLoop(void);
void delay_ms(uint32_t ms);

void delay_ms(uint32_t ms)
{
	vuint32_t cnt;
	
	while (ms--)
		for (cnt=0; cnt<DELAY_1MS_CNT; cnt++) {
		}
}

void switch_pushed();
//volatile uint16_t switchFlag = 0; //interupt flag for switch
int16_t pot_value = 0;
int16_t angle = 0;

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
	RENC_Init();
	MCTL_Init();
	
	EnableExternalInterrupts();
}

void switch_pushed()
{	//DSW_S2
	//if(1){	
	//	switchFlag = !switchFlag;

	//}
}
/*#define MCTL_SWHEEL_MAX		(100)
#define MCTL_SWHEEL_MIN		(-100)

#define MCTL_ENGINE_MAX	(2047)
#define MCTL_ENGINE_MIN	(-2047)*/


void DoMainLoop(void)
{
	//USONIC PART// Replace with Displacement
	static uint32_t t_c, t_old=(uint32_t)-1, cnt=0;
		
	//pot_value = (FADC_Get(1)-870)*10; //860-1024
	//MCTL_RotateEngine(pot_value);
		
	angle = (FADC_Get(1)-950)*2;
	MCTL_RotateSwheel(angle);	
		
	
		t_c = BTMR_GetRuntime()/200;//GetRuntime == mills//for 200 ms(0.2sec)
		
		if (t_c != t_old) {
			t_old = t_c;
			
			SDBG_Printf("Runtime = %u.%01u sec.", t_c/5, (t_c%5)*2);
			//SDBG_Printf("%d ", cnt++);
			
			//for (i=4; i<5; i++) {//6; i++) {
				pot_value = (FADC_Get(1)-850)*10; //860-1024
				SDBG_Printf("%4d\t", angle);//Potentiometer on Board
				SDBG_Printf("%4d\t", FADC_Get(5)); // ADC on PD0
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
	
	SDBG_Printf("\nDisplacement test\n");
	SDBG_Printf("Press S2!\n");
	
	while (FADC_Get(1) < 950)
	{
		SDBG_Printf("Release S2!\n");
		DLED_Set(DLED_LED2, DLED_ON);
		delay_ms(50);
		DLED_Set(DLED_LED2, DLED_OFF);
		delay_ms(50);
	}
	while(1){
		
		//while ((DSW_GetTactAll() & 0b0000) != 0b0000){
			DoMainLoop();
		//}
	}
	return 0;
}
