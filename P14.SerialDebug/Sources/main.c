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



void InitPeripherals(void);


void Callback_A(void);
void Callback_B(void);
void Callback_a(char* str);
void Callback_b(char* str);

void DoMainLoop(void);


void InitPeripherals(void)
{
	sys_init_fnc();
	DLED_Init();
	DSW_Init();
	BTMR_Init();
	SDBG_Init();
	
	EnableExternalInterrupts();
}


// 'A'를 누르면 실행되는 함수
void Callback_A(void)
{
	DLED_Set(DLED_LED1, DLED_ON);
	SDBG_Printf("\nLED1 is ON!\n");
}


// 'B'를 누르면 실행되는 함수
void Callback_B(void)
{
	DLED_Set(DLED_LED1, DLED_OFF);
	SDBG_Printf("\nLED1 is OFF!\n");
}

// "a 3 1"(LED3 ON)처럼 입력한 후 엔터를 누르면 실행되는 함수
void Callback_a(char* str)
{
	int lednum, val;
	
	if (sscanf(str, "%d %d", &lednum, &val)<2) {
		SDBG_Printf("\nParameter Missing!\n");
		return;
	}
	
	if (lednum==1)
		DLED_Set(DLED_LED1, val ? DLED_ON : DLED_OFF);
	else if (lednum==2)
		DLED_Set(DLED_LED2, val ? DLED_ON : DLED_OFF);
	else if (lednum==3)
		DLED_Set(DLED_LED3, val ? DLED_ON : DLED_OFF);
	else if (lednum==4)
		DLED_Set(DLED_LED4, val ? DLED_ON : DLED_OFF);
	
	SDBG_Printf("\nLED_%u is %u\n", lednum, val);
}


// "b" 후 엔터를 누르면 실행되는 함수
void Callback_b(char* str)
{
	(void)str;
	
	SDBG_Printf("\nTact SW Status = %x(hex), ", DSW_GetTactAll());
	SDBG_Printf("Dip SW Status = %x(hex)\n", DSW_GetDipAll());
}

//G
void Callback_G(void)
{
	uint32_t i, j;
	for(j=1; j<=9; j++){
		for(i=1; i<=9; i++){
			SDBG_Printf("%d X %d = %d\n",j,i,j*i);
		}
	}
}

//g
void Callback_g(char* str)
{
	uint32_t dan, i;
	sscanf(str,"%d",&dan);
	
	for(i=1; i<=9; i++){
		SDBG_Printf("%d X %d = %d\n",dan,i,dan*i);
	}
}


void DoMainLoop(void)
{
	static uint32_t t_c, t_old=(uint32_t)-1;
	
	t_c = BTMR_GetRuntime()/500;
	
	if (t_c != t_old) {
		t_old = t_c;
		DLED_Toggle(DLED_LED1);
	}
	
	if (SDBG_IsEvents())
		SDBG_ExecuteCallback();
}


int main(void)
{
	InitPeripherals();

	SDBG_RegisterCapitalCmd('A', Callback_A);
	SDBG_RegisterCapitalCmd('B', Callback_B);
	SDBG_RegisterCapitalCmd('G', Callback_G);
	SDBG_RegisterSmallCmd('a', Callback_a);
	SDBG_RegisterSmallCmd('b', Callback_b);
	SDBG_RegisterSmallCmd('g', Callback_g);
	
	SDBG_Printf("\nNGV! DMU! JJ! Start!\n");
	
	while (1)
		DoMainLoop();
	
	return 0;
}
