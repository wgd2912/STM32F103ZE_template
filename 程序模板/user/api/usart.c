#include "usart.h"
#include "stdio.h"
#include "string.h"
#include "sys.h"

void Usart1_Config(u32 brr)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	USART_InitTypeDef USART_InitStruct;

	//��ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_USART1, ENABLE);//��A�˿ںʹ���1��ʱ��
	//PA10��ʼ��
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10;			//PA10
	//PA9��ʼ��
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP; 	//�����������
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;	//����ٶ�50MKHz
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9;			//PA9
	GPIO_Init(GPIOA,&GPIO_InitStruct);//��ʼ��GPIO
	
	USART_InitStruct.USART_BaudRate = brr; 										//������
	USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ����
	USART_InitStruct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;				//���ͺͽ���ģʽ
	USART_InitStruct.USART_Parity = USART_Parity_No;							//����ż����
	USART_InitStruct.USART_StopBits = USART_StopBits_1;							//һ��ֹͣλ
	USART_InitStruct.USART_WordLength = USART_WordLength_8b;					//8������λ
	
	USART_Init(USART1,&USART_InitStruct);	//��ʼ������
	USART_Cmd(USART1, ENABLE);				//ʹ�ܴ���
	
#if USART_NVIC_FLAG
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//�����ж�
	NVIC_InitTypeDef NVIC_InitStructure;   
	
	NVIC_SetPriorityGrouping(5);     //�����飬ǰ��λ
	
	//Usart1 NVIC ����
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���
#endif
	printf("����1��ʼ���ɹ�\r\n");
}
 
#if USART_NVIC_FLAG
void USART1_IRQHandler(void)
{
	if(USART1->SR & 1<<5)
	{
		USART1->SR &= ~(1<<5);				//RXNEλҲ����ͨ��д��0�����
		USART_RxBuffer[USART_RxCounter++] = USART1->DR;	//����ģ�������//Ҫִ�еĲ���
	}
} 
#endif
 
//����1����һ���ֽ�
void Usart1_SendByte(u8 val)
{
	USART_SendData(USART1,val);
	while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);	//�ȴ��������
}

//����1����һ�����ݰ�
void Usart1_SendBuf(u8 *buf,u8 len)
{
    while(len--)	Usart1_SendByte(*buf++);
}

//����1����һ���ַ���
void Usart1_SendString(char *str)
{
    while(*str)	Usart1_SendByte(*str++);
}


//�ض�����
int fputc(int c,FILE *fp)
{
	while(!(USART1->SR & 1<<6));
	USART1->DR = c;
	return c;
}



/*--------------USART3-----------------*/
/************************************************
�������� �� Usart3_NVIC_Configuration
��    �� �� ����3�ж�����
��    �� �� ��
�� �� ֵ �� ��
��    �� �� ������
ʱ    �� �� 2019��11��10��
��    ע �� ��
*************************************************/
static void Usart3_NVIC_Configuration(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; //��ռ���ȼ�
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0; //�����ȼ�
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //ʹ���ⲿ�ж�ͨ��
    NVIC_Init(&NVIC_InitStructure); //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���
}

/************************************************
�������� �� Usart3_Configuration
��    �� �� ����3���ú���������4Gģ��EC20
��    �� �� BAUD:������
�� �� ֵ �� ��
��    �� �� ������
ʱ    �� �� 2019��11��10��
��    ע �� PB10 -- USART3_TX   PB11 -- USART3_RX
*************************************************/
void Usart3_Configuration(u32 BAUD)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;

	/*����USART3��GPIOʱ��*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);

	/*GPIO����*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	    
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	  
	/* UART3���� */
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
	printf("����3��ʼ���ɹ�\r\n");
}

void USART3_IRQHandler(void)
{
	u8 temp = 0;
	if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET) //�жϽ������ݼĴ����Ƿ�������
    {
		USART3->SR &= ~(1<<5);
		temp = USART3->DR;
		USART_RxBuffer[USART_RxCounter++] = temp;	//����ģ�������
		USART_RxCounter%=sizeof(USART_RxBuffer);	//�ٴ�ȷ�����������ݳ���
//		USART1->DR = USART3->DR;              //��ӡ
    }
	if(USART_GetITStatus(USART3, USART_IT_IDLE) != RESET)	//�����˴��ڿ����ж�
	{
		//�ȶ�USART_SR��Ȼ���USART_DR
		temp = USART3->SR;
		temp = USART3->DR;
		
		IDLE_flag = 1;
	}
}

//����3����һ���ֽ�
void Usart3_SendByte(u8 val)
{
	USART3->DR = val;
	
//   USART_SendData(USART3, val);
//    while (USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET);	//�ȴ��������

	while(!(USART3->SR & 1<<6));
	
	USART3->SR &= ~(1<<6);
}
//����3����һ�����ݰ�
void Usart3_SendBuf(u8 *buf,u8 len)
{
    while(len--)	Usart3_SendByte(*buf++);
}

//����3����һ���ַ���
void Usart3_SendString(char *str)
{
    while(*str)	Usart3_SendByte(*str++);
}

