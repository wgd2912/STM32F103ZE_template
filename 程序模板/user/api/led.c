#include "led.h"

void Led_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD,ENABLE);//��D�˿�ʱ��
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;  		//�������
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz; 		//�ٶ�
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14;//����
	
	GPIO_Init(GPIOD,&GPIO_InitStruct);//��ʼ��GPIO
}

