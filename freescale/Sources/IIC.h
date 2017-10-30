/*
 * IIC.h
 *
 *  Created on: Oct 15, 2016
 *      Author: Administrator
 */

#ifndef IIC_H_
#define IIC_H_

#include "derivative.h"
#include <hidef.h> 

#define SDA		PTJ_PTJ0     
#define SCL		PTJ_PTJ1

#define DIR_OUT    DDRJ_DDRJ0=1
#define DIR_IN     DDRJ_DDRJ0=0
#define SDA_IN	   PTIJ_PTIJ0


#define SDA_1   SDA = 1
#define SDA_0	SDA = 0
#define SCL_1   SCL = 1
#define SCL_0	SCL = 0

/************** 引用的外部函数 *********************/
extern void I2C_Delay(void);
extern void I2C_Start(void);
extern void I2C_Stop(void);
extern uchar I2C_receivebyte(void);
extern void I2C_Read_Ack(void);
extern void I2C_Read_NoAck(void);
extern uchar I2C_Receiveuchar(void);
extern void I2C_sendbyte(uchar data_byte);
extern void I2C_Write_ACK(void);
extern void I2C_Senduchar( uchar Wr_Data );


#define WRITE 0
#define READ 1
#define u8 unsigned char
extern void Start(void);
extern void Stop(void);
extern void ACK(void);
extern void NO_ACK(void);
extern void IIC_Write_Byte(uchar data);
extern void Write_IIC(uchar addr,uchar data);
extern uchar IIC_Read_Byte(void);
extern u8 IIC_Wait_ACK();
extern uchar Read_IIC(uchar addr);
extern void Read_Data_IIC(uchar addr,uchar* buff,uchar num);


#endif /* IIC_H_ */
