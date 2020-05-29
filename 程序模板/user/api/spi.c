#include "spi.h"

/************************************************
�������� �� Spi_Config
��    �� �� SPI1��ʼ������----Ӳ��SPI
��    �� �� ��
�� �� ֵ �� ��
��    �� �� ������
ʱ    �� �� 2020��5��13��
��    ע �� STM32_GPIOA4--SPIƬѡ�ܽ�
			STM32_GPIOA5--SPIʱ�ӹܽ�
			STM32_GPIOA6--SPIMISO�ܽ�
			STM32_GPIOA7--SPIMOSI�ܽ�
*************************************************/
void Spi_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	SPI_InitTypeDef  SPI_InitStruct;
	
	/*��GPIOA��SPI1 ��ʱ��*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_SPI1,ENABLE);
	
	/*Ƭѡ���� CS -- PA4 --- ͨ���������*/
	GPIO_InitStruct.GPIO_Pin   = GPIO_Pin_4;
	GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruct);   //��ʼ����Ӧ������
	
	/*ʱ������ CLK  PA5 --- �����������*/
	/*����ӳ� MISO PA6 --- ��������ģʽ*/
	/*�������� MOSI PA7 --- �����������*/
	GPIO_InitStruct.GPIO_Pin   = GPIO_Pin_7|GPIO_Pin_6|GPIO_Pin_5;
	GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_AF_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruct);   //��ʼ����Ӧ������
	
	/*SPI1�⺯������*/
	SPI_InitStruct.SPI_Direction = SPI_Direction_2Lines_FullDuplex; //ָ��SPI�����˫������ģʽ
	SPI_InitStruct.SPI_Mode = SPI_Mode_Master;						//����Ϊ���豸
	SPI_InitStruct.SPI_DataSize = SPI_DataSize_8b;					//����֡��ʽ8λ
	SPI_InitStruct.SPI_CPOL = SPI_CPOL_High;						//����״̬ʱ��SCK���ֵ͵�ƽ
	SPI_InitStruct.SPI_CPHA = SPI_CPHA_2Edge;						//���ݲ����ӵ�1��ʱ�ӱ��ؿ�ʼ
	SPI_InitStruct.SPI_NSS = SPI_NSS_Soft;							//����Ա����NSS���ŵ�ʹ��ģʽ������ѡ��ΪӲ��ģʽ��SPI_NSS_Hard�������ģʽ��SPI_NSS_Soft��
																	//��Ӳ��ģʽ�е�SPIƬѡ�ź���Ӳ���Զ������������ģʽ����Ҫ�������԰���Ӧ�� 
																	//GPIO�˿����߻��õͲ�����Ƭѡ��Ƭѡ�źš���������������Ӳ��ģʽ�����Զ���STM32��SPI����Ϊ������
																	//��ʵ��ʹ�����ģʽ���������Ա��ֵΪSPI_NSS_Soft
	SPI_InitStruct.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_4;	//�����ʿ���4��Ƶ
	SPI_InitStruct.SPI_FirstBit = SPI_FirstBit_MSB;					//֡��ʽ���ȷ���MSB
	SPI_InitStruct.SPI_CRCPolynomial = 7;							//����SPI��CRCУ���еĶ���ʽ��������ʹ��CRCУ��ʱ����ʹ�������Ա�Ĳ���������ʽ��������CRC��ֵ��
																	//���ڱ�ʵ���Flash��֧�� CRCУ�飬��������������ṹ���Ա��ֵΪ7 ʵ������û������ġ�
	SPI_Init(SPI1,&SPI_InitStruct);									//��ʼ����Ӧ��
	SPI_Cmd(SPI1,ENABLE);											//ʹ��
}

/************************************************
�������� �� SPI1_SendByte
��    �� �� ͨ��SPI�ӿڷ���һ���ֽڵ����ݲ�����һ���ֽڵ�����
��    �� �� byte:Ҫ���͵�����
�� �� ֵ �� ���յ����ֽڵ�ֵ
��    �� �� ������
ʱ    �� �� 2019��5��13��
��    ע �� �� 
*************************************************/
u8 SPI1_SendByte(u8 byte)
{
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);	//���ͻ�����Ϊ��-���Է���������
	SPI_I2S_SendData(SPI1, byte);  		//��ʼ�������� 								   
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET);//���ջ������ǿ�-���Խ���������
	return SPI_I2S_ReceiveData(SPI1);	//��ʼ��������
}

