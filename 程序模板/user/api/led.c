#include "led.h"

void Led_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD,ENABLE);//开D端口时钟
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;  		//推挽输出
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz; 		//速度
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14;//引脚
	
	GPIO_Init(GPIOD,&GPIO_InitStruct);//初始化GPIO
}

