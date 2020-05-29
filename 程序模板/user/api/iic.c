#include "iic.h"
#include "delay.h"
#include "sys.h"
/************************************************
�������� �� IIC_Init
��    �� �� IICͨ�ų�ʼ��
��    �� �� ��
�� �� ֵ �� ��
��    �� �� ������
ʱ    �� �� 2020��5��9��
��    ע �� ��ʼ��ģʽ����Ϊ�������ģʽ
*************************************************/
void IIC_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	
	GPIO_InitStructure.GPIO_Pin=IIC_SCL;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;//�������ģʽ
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	
	GPIO_InitStructure.GPIO_Pin=IIC_SDA;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;//��©���ģʽ
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	GPIO_SetBits(GPIO_IIC,IIC_SCL|IIC_SDA); 	//PB6,PB7 �����
}

/************************************************
�������� �� IIC_SDA_OUT
��    �� �� SDA�������
��    �� �� ��
�� �� ֵ �� ��
��    �� �� ������
ʱ    �� �� 2020��5��9��
��    ע �� SDA�����������������������SDA��������ģʽ
*************************************************/
void IIC_SDA_OUT(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	GPIO_InitStructure.GPIO_Pin = IIC_SDA;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//�������ģʽ
	GPIO_Init(GPIO_IIC,&GPIO_InitStructure);

//	IIC_SCL_H;
//	IIC_SDA_H;   //�������߶���ɸߵ�ƽ
}

/************************************************
�������� �� IIC_SDA_IN
��    �� �� SDA���뷽��
��    �� �� ��
�� �� ֵ �� ��
��    �� �� ������
ʱ    �� �� 2020��5��9��
��    ע �� SDA�����������������������SDA��������ģʽ
*************************************************/
void IIC_SDA_IN(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	GPIO_InitStructure.GPIO_Pin = IIC_SDA;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;//��������ģʽ
	GPIO_Init(GPIO_IIC,&GPIO_InitStructure);
}

/************************************************
�������� �� IIC_start
��    �� �� IICͨ����ʼ�ź�
��    �� �� ��
�� �� ֵ �� ��
��    �� �� ������
ʱ    �� �� 2020��5��9��
��    ע �� SCL�ߵ�ƽ�ڼ䣬SDA���ɸߵ�ƽת��Ϊ�͵�ƽ
*************************************************/
void IIC_Start(void)
{
	IIC_SDA_OUT();	//SDA���������,�����������͵�
	IIC_SCL_H;		//����ʱ����
	delay_us(2);
	IIC_SDA_H;		//����������
	delay_us(5);	//��ʱ1΢��
	IIC_SDA_L;		//�����½���
	delay_us(5);	//��ʱ1΢��
	IIC_SCL_L;		//�����½��أ���ʼ�źųɹ�׼�����ͻ�����ź�
}

/************************************************
�������� �� IIC_Stop
��    �� �� IICͨ����ֹ�ź�
��    �� �� ��
�� �� ֵ �� ��
��    �� �� ������
ʱ    �� �� 2020��5��9��
��    ע �� SCL�ߵ�ƽ�ڼ䣬SDA���ɵ͵�ƽת��Ϊ�ߵ�ƽ
*************************************************/
void IIC_Stop(void)
{
	IIC_SDA_OUT();	//SDA���������,�����������͵�
	IIC_SCL_L;		//����ʱ����
	delay_us(2);
	IIC_SDA_L;		//����������
	delay_us(5);	//��ʱ5΢��
	IIC_SCL_H;		//����ʱ����
	delay_us(5);	//��ʱ5΢��
	IIC_SDA_H;		//�����Ͻ��أ���ֹ�źųɹ������߿���״̬
	delay_us(5);	//��ʱ5΢��
}
/************************************************
�������� �� IIC_SendByte
��    �� �� IICͨ�ŷ���һ���ֽ�
��    �� �� byte:��Ҫ���͵��ֽ�
�� �� ֵ �� ��
��    �� �� ������
ʱ    �� �� 2020��5��9��
��    ע �� IIC���߽������ݴ���ʱ��
			ʱ���ź�Ϊ�ߵ�ƽ�ڼ䣬
			�������ϵ��źű������ȶ���
			ֻ��ʱ�����ϵ��ź�Ϊ�͵�ƽ�ڼ�
			�������ϵĵ�ƽ״̬������ı�
*************************************************/
void IIC_SendByte(u8 byte)
{
	u8 i = 8;
	IIC_SDA_OUT();
	IIC_SCL_L;	//����ʱ���߿�ʼ׼������
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
�������� �� IIC_Wait_Ack
��    �� �� IICͨ�ŵȴ���Ӧ
��    �� �� ��
�� �� ֵ �� TRUE �ɹ���FLASE ʧ��
��    �� �� ������
ʱ    �� �� 2020��5��9��
��    ע �� �����������ݺ��ȴ��ӻ�����Ӧ���źţ�
			���ն�ͨ������SDA��ʾ������ɽ��գ�
			���ŷ��Ͷ˿��Լ�����������
*************************************************/
char IIC_Wait_Ack(void)
{
	u8 ucErrTime=0;
	IIC_SDA_IN();//SDA����Ϊ����ģʽ

	IIC_SDA_H;
	delay_us(1);
	IIC_SCL_H;
	delay_us(1);
	
	while(IIC_SDA_State)
	{
		ucErrTime++;
		if(ucErrTime > 250)//250us�󲻳ɹ��ͻ��˳�
		{
			IIC_Stop();
			return FALSE;
		}
	}
	IIC_SCL_L; 		//����ʱ��
	return TRUE;	//���ص͵�ƽ��ɹ�
}

/************************************************
�������� �� IIC_Ack
��    �� �� IICͨ��������Ӧ
��    �� �� ��
�� �� ֵ �� ��
��    �� �� ������
ʱ    �� �� 2020��5��9��
��    ע �� ������Ӧ
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
�������� �� IIC_NACK
��    �� �� IICͨ��������Ӧ
��    �� �� ��
�� �� ֵ �� ��
��    �� �� ������
ʱ    �� �� 2020��5��9��
��    ע �� ��������Ӧ
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
�������� �� IIC_ReadByte
��    �� �� IICͨ�Ž���һ���ֽ�
��    �� �� ack=1ʱ������ACK��ack=0������nACK
�� �� ֵ �� ��
��    �� �� ������
ʱ    �� �� 2020��5��9��
��    ע �� ��
*************************************************/
u8 IIC_ReadByte(u8 ack)
{ 
	u8 i = 8,receive = 0;
	IIC_SDA_IN();	//SDA����Ϊ���룬

	while(i--)
	{
		IIC_SCL_L;	//����ʱ���߿�ʼ׼����������
		delay_us(2);
		IIC_SCL_H;
		receive<<=1;
		if(IIC_SDA_State)
			receive++;
		delay_us(2);
	}
	if(!ack)
		IIC_NACK();	//������Ӧ��
	else
		IIC_ACK();	//����Ӧ��
	return receive;
}












