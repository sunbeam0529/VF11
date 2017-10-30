/*
 * IIC.c
 *
 *  Created on: Oct 15, 2016
 *      Author: Administrator
 */

#include "IIC.h"


void I2C_Delay(void)
{
	uchar i;
	for(i = 0; i < 5; i++)//5
	{asm NOP ;}	

}

void I2C_Start(void)
{
	DIR_OUT;
	SDA_1;
	SCL_1;
	I2C_Delay();
	SDA_0;
	I2C_Delay();
	SCL_0;
}//End I2C_Start

/*��������I2C_Stop ���ܣ���ѭI2C����Э�鶨���ֹͣ*/

void I2C_Stop(void)
{
	DIR_OUT;
	SCL_0;
	I2C_Delay();
	SDA_0;
	SCL_1;
	I2C_Delay();
	SDA_1;
	I2C_Delay();
}//End I2C_Stop

/* ��������I2C_ReceiveACK ���ܣ�������ACK �ź�,���һ�β��� */
void I2C_Write_ACK( void )
{
	SDA_1;
	DIR_IN;
	SCL_1;
	I2C_Delay();
	while(SDA_IN);
	SCL_0;
	I2C_Delay();
	DIR_OUT;
	return;
}//End I2C_ReceiveACK

/* ��������2C_Read_Ack ���ܣ��������ݺ���һ��ACK�ź� */

void I2C_Read_Ack(void)
{
	DIR_OUT;
	SCL_0;
	SDA_0;
	I2C_Delay();
	SCL_1;
	I2C_Delay();
	SCL_0;
	SDA_1;
}//End I2C_Read_Ack

/* ��������I2C_Read_NoAck ���ܣ����������ݺ���NoACK�ź� */

void I2C_Read_NoAck(void)

{
	DIR_OUT;
	SCL_0;
	SDA_1;
	I2C_Delay();
	SCL_1;
	I2C_Delay();
	SCL_0;
}//End I2C_Read_Ack

/* ��������I2C_Receiveuchar ���ܣ�����һ���ֽڵ����� */

uchar I2C_Receiveuchar(void)
{
	uchar i;
	uchar Read_Data = 0x00; //����ֵ
	uchar DataBit = 0x00; //ÿһ��clk ���ܵ�������
	SCL_0;
	I2C_Delay();
	SDA_1;
	DIR_IN;
	for(i = 0;i < 8;i++)
	{
		SCL_1;
		I2C_Delay();
		DataBit = SDA_IN;
		SCL_0;
		I2C_Delay();
		I2C_Delay();
		Read_Data = ((Read_Data << 1 ) | DataBit ); //���������δ���Read_Data
	}
	return( Read_Data );
}//End I2C_Receiveuchar

/* ��������I2C_Senduchar ���ܣ���ѭI2C����Э�鶨�巢��һ�ֽ����� */

void I2C_Senduchar( uchar Wr_Data )
{
	uchar i;
	DIR_OUT;
	SCL_0;
	SDA_1;
	for(i = 0;i < 8;i++)
	{
	if( Wr_Data & 0x80 )
	{
		SDA_1; //���λ�Ƿ�Ϊ1,Ϊ1��SDA= 1
	}
	else
	{
		SDA_0; //���� SDA=0
	}
	I2C_Delay();
	SCL_1;
	I2C_Delay();
	SCL_0;
	I2C_Delay();
	Wr_Data <<= 1; //��������һλ,������һ������
	}
	SDA_1;
return;

}//End I2C_Senduchar

void I2C_sendbyte(uchar data_byte)
{
	uchar i;
	DIR_OUT;
	for(i = 0; i < 8; i++)
	{
		if((data_byte << i) & 0x80)
			{SDA_1;}
		else
			{SDA_0;}
		I2C_Delay();
		SCL_0;
		I2C_Delay();
		SCL_1;
		I2C_Delay();
		SCL_0;
		I2C_Delay();		
	}
	SDA_0;
	I2C_Delay();
	SCL_0;
	I2C_Delay();
	SCL_1;
	I2C_Delay();
	SCL_0;
	I2C_Delay();		
}

uchar I2C_receivebyte(void)
{
	uchar data_byte;
	uchar i;
	for(i = 0; i < 8; i++)
	{
		DIR_IN;
        
        
		SCL_1;
		I2C_Delay();
		data_byte <<= 1;
		data_byte |= SDA_IN;
		SCL_0;
		I2C_Delay();
	}
	DIR_OUT;
	SDA_0;
	I2C_Delay();
	SCL_1;
	I2C_Delay();
	SCL_0; 
	I2C_Delay();
	return(data_byte);
}

/*****************************************************************************
�����ɶ�ȡ��Ӧ��ַ���ݵ�IIC
*****************************************************************************/

void Start(void)
{
	DIR_OUT;
	SDA_1;
	SCL_1;
	I2C_Delay();
	SDA_0;
	I2C_Delay();
	SCL_0;
	I2C_Delay();
}

void Stop(void)
{
	DIR_OUT;
	SDA_0;
	SCL_1;
	I2C_Delay();
	SDA_1;
	I2C_Delay();
	SCL_0;
	I2C_Delay();
}

void ACK(void)
{
	DIR_OUT;
	SCL_0;
	I2C_Delay();
	SDA_0;
	I2C_Delay();
	SCL_1;
	I2C_Delay();
}

void NO_ACK(void)
{
	DIR_OUT;
	SDA_1;
	SCL_1;
	I2C_Delay();
	SCL_0;
	I2C_Delay();
	SDA_0;
	I2C_Delay();
}

void IIC_Write_Byte(uchar data)
{
	uchar i,temp=0;
	DIR_OUT;
	for(i=0;i<8;i++)
	{
		SCL_0;
		I2C_Delay();
		temp=(data&0x80);
		if(temp>0)
			SDA_1;
		else
			SDA_0;
		data<<=1;
		I2C_Delay();
		SCL_1;
		I2C_Delay();
	}
	SCL_0;
	I2C_Delay();
	//ACK();	
}

void Write_IIC(uchar addr,uchar data)
{
	Start();
	IIC_Write_Byte((addr<<1)+WRITE);
	IIC_Write_Byte(data);
	Stop();
	I2C_Delay();	
}

uchar IIC_Read_Byte(void)
{
	uchar i,data;
	DIR_IN;
	data=0;
	SCL_0;
	I2C_Delay();
	for(i=0;i<8;i++)
	{
		SCL_1;
		I2C_Delay();
		data<<=1;
		data|=SDA_IN;
		I2C_Delay();
		SCL_0;
		I2C_Delay();
		
	}
	return data;
}

u8 IIC_Wait_ACK()
{
	u8 IIC_communicate_time = 0;
	
	SDA_1;
	I2C_Delay();
	SCL_1;
	I2C_Delay();
    DIR_IN;
	while(SDA_IN)
	{
		IIC_communicate_time++;
		if(IIC_communicate_time>250)
		{
			Stop();
			return 1;
		}
	}
	
	return 0;
}

uchar Read_IIC(uchar addr)
{
	uchar data;
	Start();
	IIC_Write_Byte((addr<<1)+READ);
	if(!IIC_Wait_ACK())
	{
		data = IIC_Read_Byte();
		NO_ACK();
		Stop();
	}
	return data;
}

void Read_Data_IIC(uchar addr,uchar* buff,uchar num)
{
	char i;
	Start();
	(void)IIC_Write_Byte((addr<<1)+READ);
	if(!IIC_Wait_ACK())
	{
		for(i=num;i>0;i--)
		{
			*buff=IIC_Read_Byte();
			if(i!=0)
				I2C_Read_Ack();
				//ACK();
			buff++;
			I2C_Delay();
		}
		NO_ACK();
		Stop();
	}
}




