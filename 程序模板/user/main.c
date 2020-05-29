#include "main.h"


int main(void)
{

	NVIC_SetPriorityGrouping(NVIC_SetPriorityGrouping_5);
	Led_Config();
	Usart1_Config(USART1_Baud_rate);
	Usart3_Configuration(USART2_Baud_rate);
	Delay_Config();
//	AT24CXX_Init();
//	AT24CXX_Test();	
//	Sim7600_Config();
	

	while (1)
	{
		SIM7600_Test();
		if(led_time > LED1_Blink_time)
		{
			LED1_Blink;
			LED2_Blink;
			led_time = 0;
		}
	}
}
