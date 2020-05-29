#include "spi.h"

/************************************************
函数名称 ： Spi_Config
功    能 ： SPI1初始化函数----硬件SPI
参    数 ： 无
返 回 值 ： 无
作    者 ： 王国栋
时    间 ： 2020年5月13日
备    注 ： STM32_GPIOA4--SPI片选管脚
			STM32_GPIOA5--SPI时钟管脚
			STM32_GPIOA6--SPIMISO管脚
			STM32_GPIOA7--SPIMOSI管脚
*************************************************/
void Spi_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	SPI_InitTypeDef  SPI_InitStruct;
	
	/*开GPIOA和SPI1 的时钟*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_SPI1,ENABLE);
	
	/*片选引脚 CS -- PA4 --- 通用推挽输出*/
	GPIO_InitStruct.GPIO_Pin   = GPIO_Pin_4;
	GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruct);   //初始化相应的引脚
	
	/*时钟引脚 CLK  PA5 --- 复用推挽输出*/
	/*主入从出 MISO PA6 --- 浮空输入模式*/
	/*主出从入 MOSI PA7 --- 复用推挽输出*/
	GPIO_InitStruct.GPIO_Pin   = GPIO_Pin_7|GPIO_Pin_6|GPIO_Pin_5;
	GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_AF_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruct);   //初始化相应的引脚
	
	/*SPI1库函数配置*/
	SPI_InitStruct.SPI_Direction = SPI_Direction_2Lines_FullDuplex; //指定SPI单向或双向数据模式
	SPI_InitStruct.SPI_Mode = SPI_Mode_Master;						//配置为主设备
	SPI_InitStruct.SPI_DataSize = SPI_DataSize_8b;					//数据帧格式8位
	SPI_InitStruct.SPI_CPOL = SPI_CPOL_High;						//空闲状态时，SCK保持低电平
	SPI_InitStruct.SPI_CPHA = SPI_CPHA_2Edge;						//数据采样从第1个时钟边沿开始
	SPI_InitStruct.SPI_NSS = SPI_NSS_Soft;							//本成员配置NSS引脚的使用模式，可以选择为硬件模式（SPI_NSS_Hard）与软件模式（SPI_NSS_Soft）
																	//在硬件模式中的SPI片选信号由硬件自动产生，而软件模式则需要我们亲自把相应的 
																	//GPIO端口拉高或置低产生非片选和片选信号。如果外界条件允许，硬件模式还会自动将STM32的SPI设置为主机。
																	//本实验使用软件模式，向这个成员赋值为SPI_NSS_Soft
	SPI_InitStruct.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_4;	//波特率控制4分频
	SPI_InitStruct.SPI_FirstBit = SPI_FirstBit_MSB;					//帧格式：先发送MSB
	SPI_InitStruct.SPI_CRCPolynomial = 7;							//这是SPI的CRC校验中的多项式，若我们使用CRC校验时，就使用这个成员的参数（多项式）来计算CRC的值。
																	//由于本实验的Flash不支持 CRC校验，所以我们向这个结构体成员赋值为7 实际上是没有意义的。
	SPI_Init(SPI1,&SPI_InitStruct);									//初始化相应的
	SPI_Cmd(SPI1,ENABLE);											//使能
}

/************************************************
函数名称 ： SPI1_SendByte
功    能 ： 通过SPI接口发送一个字节的数据并返回一个字节的数据
参    数 ： byte:要发送的数据
返 回 值 ： 接收到的字节的值
作    者 ： 王国栋
时    间 ： 2019年5月13日
备    注 ： 无 
*************************************************/
u8 SPI1_SendByte(u8 byte)
{
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);	//发送缓冲区为空-可以发送数据了
	SPI_I2S_SendData(SPI1, byte);  		//开始发送数据 								   
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET);//接收缓存区非空-可以接收数据了
	return SPI_I2S_ReceiveData(SPI1);	//开始接收数据
}

