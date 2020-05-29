#ifndef _AT24CXX_H_
#define _AT24CXX_H_

#include "stm32f10x.h"

void AT24CXX_Init(void);
u8 AT24CXX_ReadOneByte(u16 AT24CXX,u8 AT24CXX_ADDR,u16 ReadAddr);
void AT24CXX_WriteOneByte(u16 AT24CXX,u8 AT24CXX_ADDR,u16 WriteAddr,u8 DataToWrite);
void AT24CXX_WriteLenByte(u16 AT24CXX,u8 AT24CXX_ADDR,u16 WriteAddr,u32 DataToWrite,u8 Len);
u32 AT24CXX_ReadLenByte(u16 AT24CXX,u8 AT24CXX_ADDR,u16 ReadAddr,u8 Len);
void AT24CXX_Read(u16 AT24CXX,u8 AT24CXX_ADDR,u16 ReadAddr,u8 *pBuffer,u16 NumToRead);
void AT24CXX_Write(u16 AT24CXX,u8 AT24CXX_ADDR,u16 WriteAddr,u8 *pBuffer,u16 NumToWrite);
u8 AT24CXX_Check(u16 AT24CXX,u8 AT24CXX_ADDR,u16 dataaddr);

void AT24CXX_Test(void);

#endif

