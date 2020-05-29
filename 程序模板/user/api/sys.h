#ifndef _SYS_H_
#define _SYS_H_

#include "stm32f10x.h"
#include "binand.h"

/*----------------------------初始化配置参数--------------------------------*/
#define NVIC_SetPriorityGrouping_5 	5   		//中断分组设置，32单片机只使用了前四位，目前使用第五组 11.11 两个抢占优先级、两个次级优先级
#define RS485_Baud_rate				9600		//modbus通信波特率
/*---------------------------------------------------------------------------*/

/*led.c*/
#define LED1(x) x?(GPIOD->ODR |= (1<<13)):(GPIOD->ODR &= ~(1<<13)) 
#define LED1_Blink (GPIOD->ODR ^= (0x1<<13))
#define LED2(x) x?(GPIOD->ODR |= (1<<14)):(GPIOD->ODR &= ~(1<<14)) 
#define LED2_Blink (GPIOD->ODR ^= (0x1<<14))
/*---------------------------------------------------------------------------*/


/*key.c*/
#define KEY_ON	0	//按下
#define KEY_OFF	1	//松开
/*---------------------------------------------------------------------------*/


/*delay.c*/
#define SysTick_PSC					72000		//滴答定时器预分频
#define	Tim3_psc           			36			//定时器3的预分频系数
#define	Tim3_arr   					3800		//定时器3的重装载值
#define	Tim4_psc           			36			//定时器4的预分频系数
#define	Tim4_arr   					1			//定时器4的重装载值
#define LED1_Blink_time				100			//led灯的闪烁时间
extern u32 nus_time;							//nus延时
extern u16 nms_time;							//nms延时
extern vu32 led_time;							//系统指示灯闪烁时长
extern vu32 runtime;        					//系统运行时间
extern vu32 sim7600time;						//4G模块询问发送时间
/*---------------------------------------------------------------------------*/


/*USART.c*/
#define USART_NVIC_FLAG 			0  			//串口中断开关 1：开    0：关
#define USART1_Baud_rate           	115200		//串口1的波特率
#define USART2_Baud_rate           	115200		//串口2的波特率
extern u16  USART_RxCounter;					//最大USART_REC_LEN个字节.
extern char USART_RxBuffer[1000];    			//接收缓冲区
extern  u8 IDLE_flag;							//串口空闲中断标志位
/*---------------------------------------------------------------------------*/


/*CAN.c*/
#define myCAN_SJW                   CAN_SJW_1tq	//重新同步跳跃宽度
#define myCAN_BS2					CAN_BS2_8tq	//指定时间量程的比特数段2
#define myCAN_BS1					CAN_BS1_9tq	//指定时间量程的比特数段1
#define myFIDV           			16			//分频系数(Fdiv)为brp+1
#define myCAN_Mode					0			//0:CAN_Mode_Normal   1:CAN_Mode_LoopBack
/*---------------------------------------------------------------------------*/


/*IIC.c*/
#define IIC_SCL    	GPIO_Pin_6
#define IIC_SDA   	GPIO_Pin_7
#define GPIO_IIC  	GPIOB
//PB6--IIC1_SCL、PB7--IIC1_SDA
#define TRUE 	0		//应答成功
#define FALSE	1		//应答失败
#define IIC_SCL_H		(GPIOB->ODR |= 1<<6)
#define IIC_SCL_L		(GPIOB->ODR &= ~(1<<6))
#define IIC_SDA_H		(GPIOB->ODR |= 1<<7)
#define IIC_SDA_L		(GPIOB->ODR &= ~(1<<7))	
#define IIC_SDA_State	GPIO_ReadInputDataBit(GPIO_IIC,IIC_SDA)
/*---------------------------------------------------------------------------*/


/*AT24CXX.c*/
#define AT24C01		127
#define AT24C02		255
#define AT24C04		511
#define AT24C08		1023
#define AT24C16		2047
#define AT24C32		4095
#define AT24C64	    8191
#define AT24C128	16383
#define AT24C256	32767  
//本开发板使用的是外接模块，AT24C256
#define EE_TYPE AT24C02
//AT24CXX_ADDR
#define AT24C02_Check_online_addr	AT24C02
#define AT24C256_Check_online_addr	AT24C256
#define AT24C02_addr	5
#define AT24C256_addr	2
/*---------------------------------------------------------------------------*/
 
/*SIM7600CE_T.c*/
#define sendtime 1000		//发送命令时间的间隔
#define PHONE_SWITCH 	0	//打电话开关 电话号码：10000
#define GPS_SWITCH 		1	//GPS功能开关，上传信息到服务器
typedef struct sim7600	//所有命令集合
{
	char AT			[2][4];			//AT
	char ATE0		[2][6];      	//回显
	char CSQ		[2][8];      	//信号强度指令
	char CPIN		[2][12];     	//检测卡指令
	char CREG		[3][13];	    //网络指令
	char ATD		[3][20];		//打电话命令
	char CGPS		[3][14];		//CPS开关
	char CGREG		[3][20];		//注册GPRS网络查询
	char CGDCONT	[2][30];		//接入APN，无用户名和密码 移动CMNET  联通3gnet  电信ctnet
	char CIPCLOSE	[2][18];		//结束TCP连接
	char NETCLOSE	[2][16];		//关闭socket连接
	char CIPMODE	[2][17];		//设置为TCP指令模式 1是透传 0是指令
	char CSOCKSETPN	[2][21];		//配置SOCKET,激活PDP
	char NETOPEN	[3][25];		//开启SOCKET
	char IPADDR		[2][14];		//获取设备IP
	char CIPOPEN	[3][55];		//此命令用于建立与TCP服务器和UDP服务器的连接
}SIM7600CE;

extern SIM7600CE sim7600ce;

/*---------------------------------------------------------------------------*/





#endif

