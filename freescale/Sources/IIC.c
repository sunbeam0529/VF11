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

/*函数名：I2C_Stop 功能：遵循I2C总线协议定义的停止*/

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

/* 函数名：I2C_ReceiveACK 功能：待接受ACK 信号,完成一次操作 */
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

/* 函数名：2C_Read_Ack 功能：接受数据后发送一个ACK信号 */

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

/* 函数名：I2C_Read_NoAck 功能：最后接受数据后发送NoACK信号 */

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

/* 函数名：I2C_Receiveuchar 功能：接受一个字节的数据 */

uchar I2C_Receiveuchar(void)
{
	uchar i;
	uchar Read_Data = 0x00; //返回值
	uchar DataBit = 0x00; //每一个clk 接受到的数据
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
		Read_Data = ((Read_Data << 1 ) | DataBit ); //将数据依次存入Read_Data
	}
	return( Read_Data );
}//End I2C_Receiveuchar

/* 函数名：I2C_Senduchar 功能：遵循I2C总线协议定义发送一字节数据 */

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
		SDA_1; //最高位是否为1,为1则SDA= 1
	}
	else
	{
		SDA_0; //否则 SDA=0
	}
	I2C_Delay();
	SCL_1;
	I2C_Delay();
	SCL_0;
	I2C_Delay();
	Wr_Data <<= 1; //数据左移一位,进入下一轮送数
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
新增可读取对应地址数据的IIC
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




