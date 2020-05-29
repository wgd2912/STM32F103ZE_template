#ifndef _IIC_H_
#define _IIC_H_

#include "stm32f10x.h"

void IIC_Init(void);
void IIC_SDA_OUT(void);
void IIC_SDA_IN(void);
void IIC_Start(void);
void IIC_Stop(void);
void IIC_SendByte(u8 byte);
char IIC_Wait_Ack(void);
void IIC_ACK(void);
void IIC_NACK(void);
u8 IIC_ReadByte(u8 ack);


#endif

