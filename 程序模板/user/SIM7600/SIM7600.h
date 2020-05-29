#ifndef _SIM7600_H_
#define _SIM7600_H_

#include "stm32f10x.h"

void Sim7600_Config(void);
void SIM7600_Test(void);
void Clear_Buffer(void);
void SIM7600CESend_StrData(char *bufferdata,u8 len);




#endif

