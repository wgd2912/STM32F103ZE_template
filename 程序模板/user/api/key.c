#include "key.h"
#include "sys.h"

//按键初始化函数
void KEY_Init(void) //IO初始化
{ 
 	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE|RCC_APB2Periph_GPIOC,ENABLE); //开启按键端口PA的时钟

 	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //端口配置为上拉输入
	GPIO_Init(GPIOE, &GPIO_InitStructure);	//初始化端口
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //端口配置为上拉输入
	GPIO_Init(GPIOC, &GPIO_InitStructure);	//初始化端口
}

/* 检测是否有按键按下 */
u8 Key_Scan(void)
{
	static u16 num=0,count = 0;	
	
	/*检测是否有按键按下 */
   	if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_0) == KEY_ON ) 
	{	
		num++;
	}
	else
	{
		//短按
		if(num > 5 && num < 50)
		{
			num = 0;
			return 2;
		}
		//长按   暂时用不到
		else if(num > 150)
		{
			num = 0;
			//return KEY_ON;
		}
		num = 0; //既不是长按也不是短按，无效按键
	}
	if(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_13) == KEY_ON ) 
	{	
		count++;
	}
	else
	{
		//短按
		if(count > 5 && count < 50)
		{
			count = 0;
			return 3;
		}
		//长按   暂时用不到
		else if(count > 150)
		{
			count = 0;
			//return KEY_ON;
		}
		count = 0; //既不是长按也不是短按，无效按键
	}
	return KEY_OFF;
}

