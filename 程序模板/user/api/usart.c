#include "usart.h"
#include "stdio.h"
#include "string.h"
#include "sys.h"

void Usart1_Config(u32 brr)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	USART_InitTypeDef USART_InitStruct;

	//开时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_USART1, ENABLE);//开A端口和串口1的时钟
	//PA10初始化
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10;			//PA10
	//PA9初始化
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP; 	//复用推挽输出
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;	//输出速度50MKHz
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9;			//PA9
	GPIO_Init(GPIOA,&GPIO_InitStruct);//初始化GPIO
	
	USART_InitStruct.USART_BaudRate = brr; 										//波特率
	USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件流
	USART_InitStruct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;				//发送和接收模式
	USART_InitStruct.USART_Parity = USART_Parity_No;							//无奇偶检验
	USART_InitStruct.USART_StopBits = USART_StopBits_1;							//一个停止位
	USART_InitStruct.USART_WordLength = USART_WordLength_8b;					//8个数据位
	
	USART_Init(USART1,&USART_InitStruct);	//初始化串口
	USART_Cmd(USART1, ENABLE);				//使能串口
	
#if USART_NVIC_FLAG
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//开启中断
	NVIC_InitTypeDef NVIC_InitStructure;   
	
	NVIC_SetPriorityGrouping(5);     //第五组，前四位
	
	//Usart1 NVIC 配置
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器
#endif
	printf("串口1初始化成功\r\n");
}
 
#if USART_NVIC_FLAG
void USART1_IRQHandler(void)
{
	if(USART1->SR & 1<<5)
	{
		USART1->SR &= ~(1<<5);				//RXNE位也可以通过写入0来清除
		USART_RxBuffer[USART_RxCounter++] = USART1->DR;	//接收模块的数据//要执行的操作
	}
} 
#endif
 
//串口1发送一个字节
void Usart1_SendByte(u8 val)
{
	USART_SendData(USART1,val);
	while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);	//等待发送完成
}

//串口1发送一个数据包
void Usart1_SendBuf(u8 *buf,u8 len)
{
    while(len--)	Usart1_SendByte(*buf++);
}

//串口1发送一个字符串
void Usart1_SendString(char *str)
{
    while(*str)	Usart1_SendByte(*str++);
}


//重定向函数
int fputc(int c,FILE *fp)
{
	while(!(USART1->SR & 1<<6));
	USART1->DR = c;
	return c;
}



/*--------------USART3-----------------*/
/************************************************
函数名称 ： Usart3_NVIC_Configuration
功    能 ： 串口3中断配置
参    数 ： 无
返 回 值 ： 无
作    者 ： 王国栋
时    间 ： 2019年11月10日
备    注 ： 无
*************************************************/
static void Usart3_NVIC_Configuration(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; //先占优先级
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0; //从优先级
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //使能外部中断通道
    NVIC_Init(&NVIC_InitStructure); //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器
}

/************************************************
函数名称 ： Usart3_Configuration
功    能 ： 串口3配置函数，连接4G模块EC20
参    数 ： BAUD:波特率
返 回 值 ： 无
作    者 ： 王国栋
时    间 ： 2019年11月10日
备    注 ： PB10 -- USART3_TX   PB11 -- USART3_RX
*************************************************/
void Usart3_Configuration(u32 BAUD)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;

	/*配置USART3和GPIO时钟*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);

	/*GPIO配置*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	    
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	  
	/* UART3配置 */
	USART_InitStructure.USART_BaudRate = BAUD;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No ;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

	USART_Init(USART3, &USART_InitStructure); 
	USART_Cmd(USART3, ENABLE);
    USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);
	USART_ITConfig(USART3, USART_IT_IDLE, ENABLE);	
	
	Usart3_NVIC_Configuration();
	printf("串口3初始化成功\r\n");
}

void USART3_IRQHandler(void)
{
	u8 temp = 0;
	if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET) //判断接收数据寄存器是否有数据
    {
		USART3->SR &= ~(1<<5);
		temp = USART3->DR;
		USART_RxBuffer[USART_RxCounter++] = temp;	//接收模块的数据
		USART_RxCounter%=sizeof(USART_RxBuffer);	//再次确保缓存区数据长度
//		USART1->DR = USART3->DR;              //打印
    }
	if(USART_GetITStatus(USART3, USART_IT_IDLE) != RESET)	//产生了串口空闲中断
	{
		//先读USART_SR，然后读USART_DR
		temp = USART3->SR;
		temp = USART3->DR;
		
		IDLE_flag = 1;
	}
}

//串口3发送一个字节
void Usart3_SendByte(u8 val)
{
	USART3->DR = val;
	
//   USART_SendData(USART3, val);
//    while (USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET);	//等待发送完成

	while(!(USART3->SR & 1<<6));
	
	USART3->SR &= ~(1<<6);
}
//串口3发送一个数据包
void Usart3_SendBuf(u8 *buf,u8 len)
{
    while(len--)	Usart3_SendByte(*buf++);
}

//串口3发送一个字符串
void Usart3_SendString(char *str)
{
    while(*str)	Usart3_SendByte(*str++);
}

