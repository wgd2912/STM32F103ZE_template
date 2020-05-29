#ifndef __DELAY_H
#define __DELAY_H

#include "stm32f10x.h"

/*1us×óÓÒµÄ__NOPÑÓÊ±*/
#define delay_1us()	{\
		__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();\
		__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();\
		__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();\
		__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();\
		__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();\
		__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();\
		__NOP();__NOP();}




void Delay_Config(void);
void Tim4_Config(u16 arr,u16 psc);
void delay_us(u32 nus);
void delay_ms(u16 nms);


#endif 

