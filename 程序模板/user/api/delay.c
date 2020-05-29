#include "delay.h"
#include "sys.h"

/*滴答定时器初始化*/
//初始化延迟函数
//当使用OS的时候,此函数会初始化OS的时钟节拍
//SYSTICK的时钟固定为HCLK时钟的1/8
//SYSCLK:系统时钟
void Delay_Config(void)
{
	SysTick_Config(SysTick_PSC);//滴答定时器初始化 记一个数是1ms
//	Tim4_Config(Tim4_psc,Tim4_arr); //1us延时
}





/*滴答定时器中断服务函数*/
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
	RCC->APB1ENR |= 1<<2; 	//打开TIM4时钟
	
	TIM4->PSC = psc;  	//设置预分频
	TIM4->ARR = arr;	//设置重装载值
	TIM4->CNT = 0;		//计数器清零
	
	//配置TIM4 -- 
	TIM4->CR1 = 0;
	TIM4->CR1 |= (1<<7);//重装载寄存器拥有预装载
	
	/***************中断设置***************/
	//打开定时器TIM4溢出中断
	TIM4->DIER |= (1<<0);
	//NVIC
	NVIC_SetPriority(TIM4_IRQn,7);//01 00
	NVIC_EnableIRQ(TIM4_IRQn);
	/***************使能设置***************/
	
	
	//开启定时器，等到定时器发送溢出中断后说明
	TIM4->CR1 |= (1<<0);	
}

void TIM4_IRQHandler(void)
{
	if(TIM4->SR & 1<<0)
	{
		TIM4->SR &= ~(1<<0); 		//清中断标志位
		TIM4->CNT = 0;		 		//定时器清零
		nus_time++;
	}
}

//延时nus
//nus为要延时的us数.		    								   
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

//延时任意秒s
/*s延时*/
void Delay_s(u16 ns)
{
	while(ns--){
		delay_ms(1000);
	}
}
