#ifndef _SYS_H_
#define _SYS_H_

#include "stm32f10x.h"
#include "binand.h"

/*----------------------------��ʼ�����ò���--------------------------------*/
#define NVIC_SetPriorityGrouping_5 	5   		//�жϷ������ã�32��Ƭ��ֻʹ����ǰ��λ��Ŀǰʹ�õ����� 11.11 ������ռ���ȼ��������μ����ȼ�
#define RS485_Baud_rate				9600		//modbusͨ�Ų�����
/*---------------------------------------------------------------------------*/

/*led.c*/
#define LED1(x) x?(GPIOD->ODR |= (1<<13)):(GPIOD->ODR &= ~(1<<13)) 
#define LED1_Blink (GPIOD->ODR ^= (0x1<<13))
#define LED2(x) x?(GPIOD->ODR |= (1<<14)):(GPIOD->ODR &= ~(1<<14)) 
#define LED2_Blink (GPIOD->ODR ^= (0x1<<14))
/*---------------------------------------------------------------------------*/


/*key.c*/
#define KEY_ON	0	//����
#define KEY_OFF	1	//�ɿ�
/*---------------------------------------------------------------------------*/


/*delay.c*/
#define SysTick_PSC					72000		//�δ�ʱ��Ԥ��Ƶ
#define	Tim3_psc           			36			//��ʱ��3��Ԥ��Ƶϵ��
#define	Tim3_arr   					3800		//��ʱ��3����װ��ֵ
#define	Tim4_psc           			36			//��ʱ��4��Ԥ��Ƶϵ��
#define	Tim4_arr   					1			//��ʱ��4����װ��ֵ
#define LED1_Blink_time				100			//led�Ƶ���˸ʱ��
extern u32 nus_time;							//nus��ʱ
extern u16 nms_time;							//nms��ʱ
extern vu32 led_time;							//ϵͳָʾ����˸ʱ��
extern vu32 runtime;        					//ϵͳ����ʱ��
extern vu32 sim7600time;						//4Gģ��ѯ�ʷ���ʱ��
/*---------------------------------------------------------------------------*/


/*USART.c*/
#define USART_NVIC_FLAG 			0  			//�����жϿ��� 1����    0����
#define USART1_Baud_rate           	115200		//����1�Ĳ�����
#define USART2_Baud_rate           	115200		//����2�Ĳ�����
extern u16  USART_RxCounter;					//���USART_REC_LEN���ֽ�.
extern char USART_RxBuffer[1000];    			//���ջ�����
extern  u8 IDLE_flag;							//���ڿ����жϱ�־λ
/*---------------------------------------------------------------------------*/


/*CAN.c*/
#define myCAN_SJW                   CAN_SJW_1tq	//����ͬ����Ծ���
#define myCAN_BS2					CAN_BS2_8tq	//ָ��ʱ�����̵ı�������2
#define myCAN_BS1					CAN_BS1_9tq	//ָ��ʱ�����̵ı�������1
#define myFIDV           			16			//��Ƶϵ��(Fdiv)Ϊbrp+1
#define myCAN_Mode					0			//0:CAN_Mode_Normal   1:CAN_Mode_LoopBack
/*---------------------------------------------------------------------------*/


/*IIC.c*/
#define IIC_SCL    	GPIO_Pin_6
#define IIC_SDA   	GPIO_Pin_7
#define GPIO_IIC  	GPIOB
//PB6--IIC1_SCL��PB7--IIC1_SDA
#define TRUE 	0		//Ӧ��ɹ�
#define FALSE	1		//Ӧ��ʧ��
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
//��������ʹ�õ������ģ�飬AT24C256
#define EE_TYPE AT24C02
//AT24CXX_ADDR
#define AT24C02_Check_online_addr	AT24C02
#define AT24C256_Check_online_addr	AT24C256
#define AT24C02_addr	5
#define AT24C256_addr	2
/*---------------------------------------------------------------------------*/
 
/*SIM7600CE_T.c*/
#define sendtime 1000		//��������ʱ��ļ��
#define PHONE_SWITCH 	0	//��绰���� �绰���룺10000
#define GPS_SWITCH 		1	//GPS���ܿ��أ��ϴ���Ϣ��������
typedef struct sim7600	//���������
{
	char AT			[2][4];			//AT
	char ATE0		[2][6];      	//����
	char CSQ		[2][8];      	//�ź�ǿ��ָ��
	char CPIN		[2][12];     	//��⿨ָ��
	char CREG		[3][13];	    //����ָ��
	char ATD		[3][20];		//��绰����
	char CGPS		[3][14];		//CPS����
	char CGREG		[3][20];		//ע��GPRS�����ѯ
	char CGDCONT	[2][30];		//����APN�����û��������� �ƶ�CMNET  ��ͨ3gnet  ����ctnet
	char CIPCLOSE	[2][18];		//����TCP����
	char NETCLOSE	[2][16];		//�ر�socket����
	char CIPMODE	[2][17];		//����ΪTCPָ��ģʽ 1��͸�� 0��ָ��
	char CSOCKSETPN	[2][21];		//����SOCKET,����PDP
	char NETOPEN	[3][25];		//����SOCKET
	char IPADDR		[2][14];		//��ȡ�豸IP
	char CIPOPEN	[3][55];		//���������ڽ�����TCP��������UDP������������
}SIM7600CE;

extern SIM7600CE sim7600ce;

/*---------------------------------------------------------------------------*/





#endif

