/*
 * DMK-VF11-03.h
 *
 *  Created on: Oct 11, 2016
 *      Author: Administrator
 */

#ifndef DMK_VF11_03_H_
#define DMK_VF11_03_H_

#include "derivative.h"
#include "TI1.h"
#include "AD1.h"
#include "PWM1.h"
#include "PWM2.h"
#include "PWM3.h"
#include "lin.h"
#include "IIC.h"
#include "EInt1.h"
#include "IEE1.h"
//#include "diagnostic_service_slave.h"
#include "lin_lin21tl_api.h"

typedef  unsigned char  uint8;

typedef struct 
{ 
   uint8 FAN_ADD:1; 
   uint8 FAN_ON_OFF:1; 
   uint8 FAN_MINUS:1; 
   uint8 Hot:1; 
   uint8 Cool:1; 
   uint8 Open:1; 
   uint8 Reserve:2; 
   //uint8 Key_Status; 
}STATUSES;

typedef union 
{ 
   STATUSES Status; 
   uint8   Statuses; 
}key;

typedef struct 
{ 
	unsigned char Now_Status;
	unsigned char Once_Flag;
	unsigned int  Signal_Count;
}KEY_DEAL;

typedef struct 
{ 
	unsigned char Enable;
	unsigned int On_Count;
}BEEP_DEAL;

extern BEEP_DEAL Beep;
extern unsigned char Blower_Level;
extern unsigned char Rear_CCU_On;

void Appli_task(void);
void Lin_Task(void);
void LINDATA_Deal(void);
void ADCVALUE_Deal(void);
void Key_Get_Value(void);
unsigned char Data_Check(unsigned char Dat);
void Blower_Control(void);
void LED_Light_Control(void);
void shut_down(void);











#endif /* DMK_VF11_03_H_ */
