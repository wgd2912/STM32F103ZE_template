#ifndef __SDIO_TEST_H
#define __SDIO_TEST_H

#include "stm32f10x.h"

void SD_EraseTest(void);
void SD_SingleBlockTest(void);
void SD_MultiBlockTest(void);
void Sd_Test(void);

void add_fatfs_SD_test(void);

#endif 

