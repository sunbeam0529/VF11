#include <hidef.h> /* for EnableInterrupts macro */
#include "derivative.h" /* include peripheral declarations */
#include "DMK-VF11-03.h"
#include "CPU.h"



/*-------------------2016/10/10更新----------------*/
//新建了工程，新建了lin的ldf，npf文件
//ldf文件为LDF_DMK-VF11-03.ldf，npf文件为NPF_DMK-VF11-03-1，和NPF_DMK-VF11-03的区别
//是diagnostic class为3，之前M85项目如此设置，否则会出错，然后新建的时候选择的是SCI multi-interface
//暂时这个还没发现有什么不同
//diagnostic_service_slave.c貌似没什么用
//需要确认他发的数据是信号式还是状态式的，即是保持发送的数据，还是跳变的呢
/*-------------------2016/12/9更新----------------*/
//更改了新硬件，逻辑还是旧的，是在软件DMK-VF11-03-V1.0基础上改的，常态时将端口配置成输入，需要输出时配置成输出
/*-------------------2017/2/7更新----------------*/
//删除（常态时将端口配置成输入，需要输出时配置成输出）
//增加指示灯亮度调节，背光改为常亮状态（2017.2.9发货10）
/*-------------------2017/5/17更新----------------*/
//将lin通讯错误标志位加入到信号矩阵

void main(void) 
{
  /* include your code here */
  unsigned char EEP_Data;
  CLK_CONFIG();
  Peripheral_Init();
  IEE1_Init();
  Function_OFFSET_Save_Address_read();//获取OFFSET_Save_Address
  Function_EEP_SAVE_count_read();     //获取EEP_SAVE_count
  IEE1_GetByte((IEE1_TAddress)(EEP_SAVE_ADDRESS_start+1+OFFSET_Save_Address*8),&EEP_Data);//获取存储的数据
  Blower_Level = EEP_Data&0x0f;
  Rear_CCU_On = EEP_Data>>4;
  if(Rear_CCU_On!=0 && Rear_CCU_On!=1)
  {
	  Rear_CCU_On=0;
  }
  if(Blower_Level>8)
  {
	  Blower_Level = 0;
  }
  l_sys_init();
  l_ifc_init(LI0);
  ld_init();

  while(1)
  {
	  Appli_task();	 
	  Lin_Task();
  }
  /* please make sure that you never leave main */

}

