#ifndef _USART_H_
#define _USART_H_
        
#include "stm32f10x.h"

void Usart1_Config(u32 brr);
void Usart1_SendByte(u8 val);
void Usart1_SendBuf(u8 *buf,u8 len);
void Usart1_SendString(char *str);

/*串口3-4G模块通信*/
void Usart3_Configuration(u32 BAUD);
void Usart3_SendByte(u8 val);
void Usart3_SendBuf(u8 *buf,u8 len);
void Usart3_SendString(char *str);
void NVIC_Configuration(void);

#endif 

