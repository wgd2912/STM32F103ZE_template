#include "delay.h"
#include "sys.h"

/*�δ�ʱ����ʼ��*/
//��ʼ���ӳٺ���
//��ʹ��OS��ʱ��,�˺������ʼ��OS��ʱ�ӽ���
//SYSTICK��ʱ�ӹ̶�ΪHCLKʱ�ӵ�1/8
//SYSCLK:ϵͳʱ��
void Delay_Config(void)
{
	SysTick_Config(SysTick_PSC);//�δ�ʱ����ʼ�� ��һ������1ms
//	Tim4_Config(Tim4_psc,Tim4_arr); //1us��ʱ
}





/*�δ�ʱ���жϷ�����*/
void SysTick_Handler(void) 			
{
	led_time++; 
	runtime++;	 
	nms_time++;
	sim7600time++;
}

/*
	
*/
void Tim4_Config(u16 arr,u16 psc)
{
	RCC->APB1ENR |= 1<<2; 	//��TIM4ʱ��
	
	TIM4->PSC = psc;  	//����Ԥ��Ƶ
	TIM4->ARR = arr;	//������װ��ֵ
	TIM4->CNT = 0;		//����������
	
	//����TIM4 -- 
	TIM4->CR1 = 0;
	TIM4->CR1 |= (1<<7);//��װ�ؼĴ���ӵ��Ԥװ��
	
	/***************�ж�����***************/
	//�򿪶�ʱ��TIM4����ж�
	TIM4->DIER |= (1<<0);
	//NVIC
	NVIC_SetPriority(TIM4_IRQn,7);//01 00
	NVIC_EnableIRQ(TIM4_IRQn);
	/***************ʹ������***************/
	
	
	//������ʱ�����ȵ���ʱ����������жϺ�˵��
	TIM4->CR1 |= (1<<0);	
}

void TIM4_IRQHandler(void)
{
	if(TIM4->SR & 1<<0)
	{
		TIM4->SR &= ~(1<<0); 		//���жϱ�־λ
		TIM4->CNT = 0;		 		//��ʱ������
		nus_time++;
	}
}

//��ʱnus
//nusΪҪ��ʱ��us��.		    								   
void delay_us(u32 nus)
{		
	while(nus--){
		delay_1us();
	}
}

void delay_ms(u16 nms)
{	 
	while(nms--){
		delay_us(1000);
	}
}

//��ʱ������s
/*s��ʱ*/
void Delay_s(u16 ns)
{
	while(ns--){
		delay_ms(1000);
	}
}
