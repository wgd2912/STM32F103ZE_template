#include "iic.h"
#include "delay.h"
#include "sys.h"
/************************************************
函数名称 ： IIC_Init
功    能 ： IIC通信初始化
参    数 ： 无
返 回 值 ： 无
作    者 ： 王国栋
时    间 ： 2020年5月9日
备    注 ： 初始化模式配置为推挽输出模式
*************************************************/
void IIC_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	
	GPIO_InitStructure.GPIO_Pin=IIC_SCL;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;//推挽输出模式
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	
	GPIO_InitStructure.GPIO_Pin=IIC_SDA;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;//开漏输出模式
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	GPIO_SetBits(GPIO_IIC,IIC_SCL|IIC_SDA); 	//PB6,PB7 输出高
}

/************************************************
函数名称 ： IIC_SDA_OUT
功    能 ： SDA输出方向
参    数 ： 无
返 回 值 ： 无
作    者 ： 王国栋
时    间 ： 2020年5月9日
备    注 ： SDA有输出和输入两个方向，配置SDA的这两个模式
*************************************************/
void IIC_SDA_OUT(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	GPIO_InitStructure.GPIO_Pin = IIC_SDA;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//推挽输出模式
	GPIO_Init(GPIO_IIC,&GPIO_InitStructure);

//	IIC_SCL_H;
//	IIC_SDA_H;   //把两条线都变成高电平
}

/************************************************
函数名称 ： IIC_SDA_IN
功    能 ： SDA输入方向
参    数 ： 无
返 回 值 ： 无
作    者 ： 王国栋
时    间 ： 2020年5月9日
备    注 ： SDA有输出和输入两个方向，配置SDA的这两个模式
*************************************************/
void IIC_SDA_IN(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	GPIO_InitStructure.GPIO_Pin = IIC_SDA;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;//输入上拉模式
	GPIO_Init(GPIO_IIC,&GPIO_InitStructure);
}

/************************************************
函数名称 ： IIC_start
功    能 ： IIC通信起始信号
参    数 ： 无
返 回 值 ： 无
作    者 ： 王国栋
时    间 ： 2020年5月9日
备    注 ： SCL高电平期间，SDA线由高电平转换为低电平
*************************************************/
void IIC_Start(void)
{
	IIC_SDA_OUT();	//SDA是输出方向,即由主机发送的
	IIC_SCL_H;		//拉高时钟线
	delay_us(2);
	IIC_SDA_H;		//拉高数据线
	delay_us(5);	//延时1微妙
	IIC_SDA_L;		//产生下降沿
	delay_us(5);	//延时1微妙
	IIC_SCL_L;		//产生下降沿，起始信号成功准备发送或接收信号
}

/************************************************
函数名称 ： IIC_Stop
功    能 ： IIC通信终止信号
参    数 ： 无
返 回 值 ： 无
作    者 ： 王国栋
时    间 ： 2020年5月9日
备    注 ： SCL高电平期间，SDA线由低电平转换为高电平
*************************************************/
void IIC_Stop(void)
{
	IIC_SDA_OUT();	//SDA是输出方向,即由主机发送的
	IIC_SCL_L;		//拉低时钟线
	delay_us(2);
	IIC_SDA_L;		//拉低数据线
	delay_us(5);	//延时5微妙
	IIC_SCL_H;		//拉高时钟线
	delay_us(5);	//延时5微妙
	IIC_SDA_H;		//产生上降沿，终止信号成功，总线空闲状态
	delay_us(5);	//延时5微妙
}
/************************************************
函数名称 ： IIC_SendByte
功    能 ： IIC通信发送一个字节
参    数 ： byte:将要发送的字节
返 回 值 ： 无
作    者 ： 王国栋
时    间 ： 2020年5月9日
备    注 ： IIC总线进行数据传送时，
			时钟信号为高电平期间，
			数据线上的信号必须是稳定的
			只有时钟线上的信号为低电平期间
			数据线上的电平状态才允许改变
*************************************************/
void IIC_SendByte(u8 byte)
{
	u8 i = 8;
	IIC_SDA_OUT();
	IIC_SCL_L;	//拉低时钟线开始准备数据
	while(i--)
	{
		if((byte & 0x80)>>7)
			IIC_SDA_H;
		else
			IIC_SDA_L;
		byte<<=1;
		delay_us(2);
		IIC_SCL_H;
		delay_us(2);
		IIC_SCL_L;
		delay_us(2);
	}
}
/************************************************
函数名称 ： IIC_Wait_Ack
功    能 ： IIC通信等待响应
参    数 ： 无
返 回 值 ： TRUE 成功、FLASE 失败
作    者 ： 王国栋
时    间 ： 2020年5月9日
备    注 ： 主机发送数据后会等待从机返回应答信号：
			接收端通过拉低SDA提示主机完成接收，
			接着发送端可以继续发送数据
*************************************************/
char IIC_Wait_Ack(void)
{
	u8 ucErrTime=0;
	IIC_SDA_IN();//SDA设置为输入模式

	IIC_SDA_H;
	delay_us(1);
	IIC_SCL_H;
	delay_us(1);
	
	while(IIC_SDA_State)
	{
		ucErrTime++;
		if(ucErrTime > 250)//250us后不成功就会退出
		{
			IIC_Stop();
			return FALSE;
		}
	}
	IIC_SCL_L; 		//拉低时钟
	return TRUE;	//读回低电平则成功
}

/************************************************
函数名称 ： IIC_Ack
功    能 ： IIC通信主机响应
参    数 ： 无
返 回 值 ： 无
作    者 ： 王国栋
时    间 ： 2020年5月9日
备    注 ： 主机响应
*************************************************/
void IIC_ACK(void)
{
	IIC_SCL_L;
	IIC_SDA_OUT();
	IIC_SDA_L;
	delay_us(3);
	IIC_SCL_H;
	delay_us(2);
	IIC_SCL_L;
}

/************************************************
函数名称 ： IIC_NACK
功    能 ： IIC通信主机响应
参    数 ： 无
返 回 值 ： 无
作    者 ： 王国栋
时    间 ： 2020年5月9日
备    注 ： 主机无响应
*************************************************/
void IIC_NACK(void)
{
	IIC_SCL_L;
	IIC_SDA_OUT();
	IIC_SDA_H;
	delay_us(3);
	IIC_SCL_H;
	delay_us(2);
	IIC_SCL_L;
}
/************************************************
函数名称 ： IIC_ReadByte
功    能 ： IIC通信接收一个字节
参    数 ： ack=1时，发送ACK，ack=0，发送nACK
返 回 值 ： 无
作    者 ： 王国栋
时    间 ： 2020年5月9日
备    注 ： 无
*************************************************/
u8 IIC_ReadByte(u8 ack)
{ 
	u8 i = 8,receive = 0;
	IIC_SDA_IN();	//SDA设置为输入，

	while(i--)
	{
		IIC_SCL_L;	//拉低时钟线开始准备接收数据
		delay_us(2);
		IIC_SCL_H;
		receive<<=1;
		if(IIC_SDA_State)
			receive++;
		delay_us(2);
	}
	if(!ack)
		IIC_NACK();	//主机不应答
	else
		IIC_ACK();	//主机应答
	return receive;
}












