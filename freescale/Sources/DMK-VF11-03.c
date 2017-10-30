/*
 * DMK-VF11-03.c
 *
 *  Created on: Oct 11, 2016
 *      Author: Administrator
 */
#include "DMK-VF11-03.h"


//-------IIC parameters----------------------
unsigned char IIC_MXB[4];
unsigned char KEY_Statu_Last;
key KEY;
unsigned char Check_Cnt;
KEY_DEAL FAN_On_Off;
KEY_DEAL FAN_Add;
KEY_DEAL FAN_Minus;

//-------BEEP DEAL---------------------------
BEEP_DEAL Beep;

unsigned int ADCVALUE[3]={0,0,0};
unsigned char Ad_cal_Loop;	 //循环计数
unsigned int FAN_FB_H_Values[4],FAN_FB_L_Values[4],IGN_Values[4];
unsigned int FAN_FB_H_Data,FAN_FB_L_Data,IGN_Data;

unsigned char IGN_power_Error_Flag=1;
unsigned int IGN_power_OverVoltage_count;
unsigned int IGN_power_UnderVoltage_count;

unsigned char IGN_OverVoltage_Flag,IGN_UnderVoltage_Flag;
unsigned char Blower_Level,Blower_Level_Temp;
unsigned char Blower_Error_Flag;
unsigned int Blower_Error_count;

unsigned char Rear_Lock_Status;

unsigned char OnOff_Req;
unsigned char Rear_CCU_On;
unsigned char Control_Lock_Req;
unsigned char Control_Lock_Flag;

unsigned char OnOff_Req_lock,OnOff_Req_Change_Times;
unsigned char Control_Lock_Req_lock,Control_Lock_Req_Change_Times;

unsigned char Blower_On_Flag;

const signed long PWM_Blower_Set[9]={0,19700,25000,30200,35400,40800,46000,51500,65535};
signed long Blower_Value_SET,Blower_Value_Lock=0;

unsigned char IGN_Lost_Count;

unsigned char ILL_Int_count;
unsigned char Light_Mode;

void Appli_task(void)
{
	 if(Control_Lock_Flag==0 && IGN_power_Error_Flag==0)//未锁定、电源电压正常
	 {
		Key_Get_Value();
	 }
	
	 if(app_base_2mStick == 1)
	 {
	    app_base_2mStick = 0;
	    LED_Light_Control();
	 }
	 
	 if(app_base_5mStick == 1)
	 {
		app_base_5mStick = 0;
		ADCVALUE_Deal();
	 }
	 
	 if(app_base_10mStick == 1)
	 {
		app_base_10mStick = 0;
	 }
	 
	 if(app_base_20mStick == 1)
	 {
		app_base_20mStick = 0;
		if(IGN_power_Error_Flag==0)
		{
			Blower_Control();
		}
		else
		{
			shut_down();
		}
	 }
	 
	 if(app_base_50mStick == 1)
	 {
		app_base_50mStick = 0;
		LINDATA_Deal();
		if(LP0IF_LPOCIF==1)
		{
			LP0IF_LPOCIF=1;
		}
	 }
	 
	 if(app_base_100mStick == 1)
	 {
		app_base_100mStick = 0;
	 }	          
}

void Lin_Task(void)
{
	//Blower_Level_Temp=l_u8_rd_LI0_L_AC_BlowerLevel();//此信号取消了
	//Control_Lock_Req=l_u8_rd_LI0_L_AC_Control_Lock_Req();//锁定信号取消
	OnOff_Req=l_u8_rd_LI0_L_AC_OnOff_Req();
	
	if(Blower_Level_Temp>=0 && Blower_Level_Temp<=8)
	{
		//Blower_Level=Blower_Level_Temp;
	}	
	
	l_bool_wr_LI0_L_RCP_OverVoltage(IGN_OverVoltage_Flag);
	l_bool_wr_LI0_L_RCP_UnderVoltage(IGN_UnderVoltage_Flag);
	if(Blower_On_Flag==0)
	{
		l_u8_wr_LI0_L_RCP_Blower_Speed(0);
	}
	else
	{
		l_u8_wr_LI0_L_RCP_Blower_Speed(Blower_Level);
	}
	//l_u8_wr_LI0_L_RCP_Blower_Speed(Blower_On_Flag);//临时版本
	//l_bool_wr_LI0_L_RCP_Lock_Status(Rear_Lock_Status);
	l_bool_wr_LI0_L_RCP_Blower_Err(Blower_Error_Flag);	
	//l_bool_wr_LI0_L_RCP_Error(lin_error_in_response);//这句话根本不需要调用，若错误，标志会自动置位
}

void LINDATA_Deal(void)
{
	if(Control_Lock_Req!=Control_Lock_Req_lock)
	{
		Control_Lock_Req_Change_Times++;
	}
	else
	{
		Control_Lock_Req_Change_Times=0;
	}
	if(Control_Lock_Req_Change_Times>=3)
	{
		Control_Lock_Req_lock=Control_Lock_Req;
		if(Control_Lock_Req_lock==1)//锁定
		{
			//Control_Lock_Flag=1;
			Rear_Lock_Status=1;
		}
		else if(Control_Lock_Req_lock==2)//不锁定
		{
			Control_Lock_Flag=0;
			Rear_Lock_Status=0;
		}
	}
	
	if(OnOff_Req!=OnOff_Req_lock)
	{
		OnOff_Req_Change_Times++;
	}
	else
	{
		OnOff_Req_Change_Times=0;
	}
	if(OnOff_Req_Change_Times>=3)
	{	
		OnOff_Req_lock=OnOff_Req;
		if(OnOff_Req_lock==1)//开启
		{
			Rear_CCU_On=1;
			Array_save[1]=(Blower_Level&0x0f)|(Rear_CCU_On<<4);
			Function_array_save();
		}
		else if(OnOff_Req_lock==2)//关闭
		{
			Rear_CCU_On=0;
			Array_save[1]=(Blower_Level&0x0f)|(Rear_CCU_On<<4);
			Function_array_save();
		}		
	}
}

void Key_Get_Value(void)
{
	Read_Data_IIC(0x09,IIC_MXB,4);
	if((IIC_MXB[0]==0x10) && (IIC_MXB[3]==0x35) && Data_Check(IIC_MXB[1])) 
	{ 
		if(IIC_MXB[1]==KEY_Statu_Last && Check_Cnt>=25) 
			KEY.Statuses = IIC_MXB[1]; 
		if(IIC_MXB[1]==KEY_Statu_Last) 
			Check_Cnt++; 
		else 
			Check_Cnt=0; 
		KEY_Statu_Last=IIC_MXB[1]; 
	}
	//----------KEY DEAL----------------
	if(Beep.Enable==0)
	{
		FAN_On_Off.Now_Status=KEY.Status.FAN_ON_OFF;
		FAN_Add.Now_Status=KEY.Status.FAN_ADD;
		FAN_Minus.Now_Status=KEY.Status.FAN_MINUS;
	}
	if(FAN_On_Off.Now_Status==1)
	{
		if(FAN_On_Off.Signal_Count<=6000)
		{
			FAN_On_Off.Signal_Count++;
			if(FAN_On_Off.Once_Flag==1)
			{
				FAN_On_Off.Once_Flag=0;
				if(Rear_CCU_On==1)
				{
					Rear_CCU_On=0;	
					Beep.Enable=1;
				}
				Array_save[1]=(Blower_Level&0x0f)|(Rear_CCU_On<<4);
			    Function_array_save();
			}
		}
	}
	else
	{
		FAN_On_Off.Signal_Count=0;
		FAN_On_Off.Once_Flag=1;
	}
	
	if(FAN_Add.Now_Status==1)
	{
		if(FAN_Add.Signal_Count<=6000)
		{
			FAN_Add.Signal_Count++;
			if(FAN_Add.Once_Flag==1)
			{
				FAN_Add.Once_Flag=0;				
				if(Rear_CCU_On==0)
				{
					Rear_CCU_On=1;
					Beep.Enable=1;
				}
				else
				{
					if(Blower_Level>=8)
					{
						Blower_Level=8;
					}
					else
					{
						Blower_Level++;
						Beep.Enable=1;
					}	
				}
				Array_save[1]=(Blower_Level&0x0f)|(Rear_CCU_On<<4);
				Function_array_save();
			}
		}
	}
	else
	{
		FAN_Add.Signal_Count=0;
		FAN_Add.Once_Flag=1;
	}
	
	if(FAN_Minus.Now_Status==1)
	{
		if(FAN_Minus.Signal_Count<=6000)
		{
			FAN_Minus.Signal_Count++;			
			if(FAN_Minus.Once_Flag==1)
			{
				FAN_Minus.Once_Flag=0;				
				if(Rear_CCU_On==0)
				{
					Rear_CCU_On=1;
					Beep.Enable=1;
				}
				else
				{
					if(Blower_Level<=1)
					{
						Blower_Level=1;
					}
					else
					{
						Blower_Level--;
						Beep.Enable=1;
					}
				}
				Array_save[1]=(Blower_Level&0x0f)|(Rear_CCU_On<<4);
				Function_array_save();
			}
		}
	}
	else
	{
		FAN_Minus.Signal_Count=0;
		FAN_Minus.Once_Flag=1;
	}
}

unsigned char Data_Check(unsigned char Dat)
{ 
	unsigned char  i,Dat_t; 
	if(Dat==0) 
		return 1; 
	for(i=0;i<8;i++) 
	{ 
		Dat_t=Dat-(1<<i); 
		if(Dat_t==0) 
		{ 
			return 1; 
		} 
	} 
	return 0; 
}

void Blower_Control(void)
{
	long signed int R1;
	if(Rear_CCU_On==0)
	{
		O_FAN_RLY_SIGN=0;		
		O_FAN_EN=1;
		FAN_1_LED=0;
		FAN_2_LED=0;
		FAN_3_LED=0;
		FAN_4_LED=0;
		FAN_5_LED=0;
		FAN_6_LED=0;
		FAN_7_LED=0;
		FAN_8_LED=0;
		PWM1_SetRatio16(0);
		Blower_Value_Lock=0;
		Blower_On_Flag=0;
	}
	else
	{
		Blower_On_Flag=1;
		if(Blower_Level==0)
		{
			Blower_Level=1;
		}
	}
		
	if(Rear_CCU_On==1)
	{
		switch(Blower_Level)
		{
			case 0:
				O_FAN_RLY_SIGN=0;		
				O_FAN_EN=1;
				FAN_1_LED=0;
				FAN_2_LED=0;
				FAN_3_LED=0;
				FAN_4_LED=0;
				FAN_5_LED=0;
				FAN_6_LED=0;
				FAN_7_LED=0;
				FAN_8_LED=0;		
			break;
			case 1:
				O_FAN_RLY_SIGN=1;		
				O_FAN_EN=0;
				FAN_1_LED=1;
				FAN_2_LED=0;
				FAN_3_LED=0;
				FAN_4_LED=0;
				FAN_5_LED=0;
				FAN_6_LED=0;
				FAN_7_LED=0;
				FAN_8_LED=0;
			break;
			case 2:	
				O_FAN_RLY_SIGN=1;		
				O_FAN_EN=0;
				FAN_1_LED=1;
				FAN_2_LED=1;
				FAN_3_LED=0;
				FAN_4_LED=0;
				FAN_5_LED=0;
				FAN_6_LED=0;
				FAN_7_LED=0;
				FAN_8_LED=0;	
			break;
			case 3:	
				O_FAN_RLY_SIGN=1;		
				O_FAN_EN=0;
				FAN_1_LED=1;
				FAN_2_LED=1;
				FAN_3_LED=1;
				FAN_4_LED=0;
				FAN_5_LED=0;
				FAN_6_LED=0;
				FAN_7_LED=0;
				FAN_8_LED=0;
			break;
			case 4:	
				O_FAN_RLY_SIGN=1;		
				O_FAN_EN=0;
				FAN_1_LED=1;
				FAN_2_LED=1;
				FAN_3_LED=1;
				FAN_4_LED=1;
				FAN_5_LED=0;
				FAN_6_LED=0;
				FAN_7_LED=0;
				FAN_8_LED=0;	
			break;
			case 5:	
				O_FAN_RLY_SIGN=1;		
				O_FAN_EN=0;
				FAN_1_LED=1;
				FAN_2_LED=1;
				FAN_3_LED=1;
				FAN_4_LED=1;
				FAN_5_LED=1;
				FAN_6_LED=0;
				FAN_7_LED=0;
				FAN_8_LED=0;
			break;			 
			case 6:	
				O_FAN_RLY_SIGN=1;		
				O_FAN_EN=0;
				FAN_1_LED=1;
				FAN_2_LED=1;
				FAN_3_LED=1;
				FAN_4_LED=1;
				FAN_5_LED=1;
				FAN_6_LED=1;
				FAN_7_LED=0;
				FAN_8_LED=0;
			break;			 
			case 7:	
				O_FAN_RLY_SIGN=1;		
				O_FAN_EN=0;
				FAN_1_LED=1;
				FAN_2_LED=1;
				FAN_3_LED=1;
				FAN_4_LED=1;
				FAN_5_LED=1;
				FAN_6_LED=1;
				FAN_7_LED=1;
				FAN_8_LED=0;
			break;			 
			case 8:	
				O_FAN_RLY_SIGN=1;		
				O_FAN_EN=0;
				FAN_1_LED=1;
				FAN_2_LED=1;
				FAN_3_LED=1;
				FAN_4_LED=1;
				FAN_5_LED=1;
				FAN_6_LED=1;
				FAN_7_LED=1;
				FAN_8_LED=1;
			break;			 
			default:
				
			break;  
		}
		Blower_Value_SET=PWM_Blower_Set[Blower_Level];
		R1=Blower_Value_SET-Blower_Value_Lock;
		if(R1<-600)
		{
			Blower_Value_Lock-=300;
			PWM1_SetRatio16((unsigned int)Blower_Value_Lock);
		}
		else
		{
			if(R1>600)
			{
				Blower_Value_Lock+=300;
				PWM1_SetRatio16((unsigned int)Blower_Value_Lock);
			}
			else
			{
				Blower_Value_Lock=Blower_Value_SET;
				PWM1_SetRatio16((unsigned int)Blower_Value_Lock);
			}
		}		
	}
}


void ADCVALUE_Deal(void)
{
	AD1_Measure(1);
	AD1_GetValue16(ADCVALUE);
	IGN_Values[Ad_cal_Loop]=ADCVALUE[0];
	FAN_FB_H_Values[Ad_cal_Loop]=ADCVALUE[1];
	FAN_FB_L_Values[Ad_cal_Loop]=ADCVALUE[2];
	Ad_cal_Loop++;
	if(Ad_cal_Loop>=4)
	{
		Ad_cal_Loop=0;
		FAN_FB_H_Data=AD_Average_Calculate(FAN_FB_H_Values,4);
		FAN_FB_L_Data=AD_Average_Calculate(FAN_FB_L_Values,4);
		IGN_Data=AD_Average_Calculate(IGN_Values,4);
		if(IGN_Data>600)      //IGN>16.7v
		{
			IGN_power_OverVoltage_count++;
			if(IGN_power_OverVoltage_count>=250)//5 seconds
			{
				IGN_power_OverVoltage_count=0;
				IGN_OverVoltage_Flag=1;
				IGN_UnderVoltage_Flag=0;
				IGN_power_Error_Flag=1;
			}			
		}
		else if(IGN_Data<294) //IGN<8.2v
		{
			IGN_power_UnderVoltage_count++;
			if(IGN_power_UnderVoltage_count>=250)//5 seconds
			{
				IGN_power_UnderVoltage_count=0;
				IGN_UnderVoltage_Flag=1;
				IGN_OverVoltage_Flag=0;
				IGN_power_Error_Flag=1;
			}
		}
		else if(IGN_Data>312 && IGN_Data<581)//>8.7v，<16.2v
		{
			IGN_power_Error_Flag=0;
			IGN_OverVoltage_Flag=0;
			IGN_UnderVoltage_Flag=0;
			IGN_power_OverVoltage_count=0;
			IGN_power_UnderVoltage_count=0;			
		}
		
		if(IGN_power_Error_Flag==0)//电源电压正常
		{
			if(Rear_CCU_On==0 && (FAN_FB_H_Data>=15 || FAN_FB_L_Data>=15))//继电器断了之后，H和L端丢电
			{
				Blower_Error_count++;
				if(Blower_Error_count>=100)
				{
					Blower_Error_count=0;
					Blower_Error_Flag=1;
				}
			}
			else if(Rear_CCU_On!=0 && ((FAN_FB_H_Data>=(IGN_Data+20) || FAN_FB_H_Data<=(IGN_Data-20)) || FAN_FB_L_Data>=(IGN_Data-20)))
			{
				Blower_Error_count++;
				if(Blower_Error_count>=100)
				{
					Blower_Error_count=0;
					Blower_Error_Flag=1;
				}
			}
			else
			{
				Blower_Error_count=0;
				Blower_Error_Flag=0;
			}
		}
	}
}


void LED_Light_Control(void)
{
	//return ;
	if(PTT_PTT6==0)
	//if(PTIT_PTIT6==0)	
	{
		ILL_Int_count++;
		if(ILL_Int_count>=10)//20ms
		{
			Light_Mode=1;//黑夜			
		}
	}
	else
	{
		ILL_Int_count=0;
		Light_Mode=0;//白天
	}
	if(Light_Mode==0)
	{
		PWM2_SetRatio16(65535);
	}
	else
	{
		PWM2_SetRatio16(16000);
	}
}

void shut_down(void)//电压异常时，关闭外设输出
{
	O_FAN_RLY_SIGN=0;		
	O_FAN_EN=1;
	FAN_1_LED=0;
	FAN_2_LED=0;
	FAN_3_LED=0;
	FAN_4_LED=0;
	FAN_5_LED=0;
	FAN_6_LED=0;
	FAN_7_LED=0;
	FAN_8_LED=0;
	PWM1_SetRatio16(0);
	Blower_Value_Lock=0;
	Blower_On_Flag=0;
}
