#include <hidef.h> /* for EnableInterrupts macro */
#include "derivative.h" /* include peripheral declarations */
#include "DMK-VF11-03.h"
#include "CPU.h"



/*-------------------2016/10/10����----------------*/
//�½��˹��̣��½���lin��ldf��npf�ļ�
//ldf�ļ�ΪLDF_DMK-VF11-03.ldf��npf�ļ�ΪNPF_DMK-VF11-03-1����NPF_DMK-VF11-03������
//��diagnostic classΪ3��֮ǰM85��Ŀ������ã���������Ȼ���½���ʱ��ѡ�����SCI multi-interface
//��ʱ�����û������ʲô��ͬ
//diagnostic_service_slave.cò��ûʲô��
//��Ҫȷ���������������ź�ʽ����״̬ʽ�ģ����Ǳ��ַ��͵����ݣ������������
/*-------------------2016/12/9����----------------*/
//��������Ӳ�����߼����Ǿɵģ��������DMK-VF11-03-V1.0�����ϸĵģ���̬ʱ���˿����ó����룬��Ҫ���ʱ���ó����
/*-------------------2017/2/7����----------------*/
//ɾ������̬ʱ���˿����ó����룬��Ҫ���ʱ���ó������
//����ָʾ�����ȵ��ڣ������Ϊ����״̬��2017.2.9����10��
/*-------------------2017/5/17����----------------*/
//��linͨѶ�����־λ���뵽�źž���

void main(void) 
{
  /* include your code here */
  unsigned char EEP_Data;
  CLK_CONFIG();
  Peripheral_Init();
  IEE1_Init();
  Function_OFFSET_Save_Address_read();//��ȡOFFSET_Save_Address
  Function_EEP_SAVE_count_read();     //��ȡEEP_SAVE_count
  IEE1_GetByte((IEE1_TAddress)(EEP_SAVE_ADDRESS_start+1+OFFSET_Save_Address*8),&EEP_Data);//��ȡ�洢������
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

