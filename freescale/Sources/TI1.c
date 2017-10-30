#include "TI1.h"

static unsigned int AppliTick=0;
bool app_base_2mStick,app_base_5mStick,app_base_10mStick,app_base_20mStick,app_base_50mStick,app_base_100mStick;
//1msÖÐ¶Ï
#pragma CODE_SEG __NEAR_SEG NON_BANKED
void interrupt VectorNumber_Vtim1ch0 TI1_OnInterrupt(void)
{
	TIM1TC0 += 0x1F40U;                  /* Add value corresponding with period */
	TIM1TFLG1 = 0x01U;                   /* Reset interrupt request flag */
	
	AppliTick++;
	if(AppliTick % 2 == 0)
	{
	  app_base_2mStick = 1;
	}       
	if(AppliTick % 5 == 0)
	{
	  app_base_5mStick = 1;
	}
	if(AppliTick % 10 == 0)
	{
	  app_base_10mStick = 1;
	}
	if(AppliTick % 20 == 0)
	{
	  app_base_20mStick = 1;
	}
	if(AppliTick %50 == 0)
	{
	  app_base_50mStick = 1;
	}
	if(AppliTick % 100 == 0)
	{
	  app_base_100mStick = 1;
	  AppliTick=0;
	}
	if(Beep.Enable==1)
	{
		PWM3_SetRatio16(32768);
		Beep.On_Count++;
		if(Beep.On_Count>=200)
		{
			Beep.On_Count=0;
			Beep.Enable=0;
			PWM3_SetRatio16(0);
		}
	}
}

#pragma CODE_SEG TI1_CODE
