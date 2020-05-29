#include "key.h"
#include "sys.h"

//������ʼ������
void KEY_Init(void) //IO��ʼ��
{ 
 	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE|RCC_APB2Periph_GPIOC,ENABLE); //���������˿�PA��ʱ��

 	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //�˿�����Ϊ��������
	GPIO_Init(GPIOE, &GPIO_InitStructure);	//��ʼ���˿�
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //�˿�����Ϊ��������
	GPIO_Init(GPIOC, &GPIO_InitStructure);	//��ʼ���˿�
}

/* ����Ƿ��а������� */
u8 Key_Scan(void)
{
	static u16 num=0,count = 0;	
	
	/*����Ƿ��а������� */
   	if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_0) == KEY_ON ) 
	{	
		num++;
	}
	else
	{
		//�̰�
		if(num > 5 && num < 50)
		{
			num = 0;
			return 2;
		}
		//����   ��ʱ�ò���
		else if(num > 150)
		{
			num = 0;
			//return KEY_ON;
		}
		num = 0; //�Ȳ��ǳ���Ҳ���Ƕ̰�����Ч����
	}
	if(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_13) == KEY_ON ) 
	{	
		count++;
	}
	else
	{
		//�̰�
		if(count > 5 && count < 50)
		{
			count = 0;
			return 3;
		}
		//����   ��ʱ�ò���
		else if(count > 150)
		{
			count = 0;
			//return KEY_ON;
		}
		count = 0; //�Ȳ��ǳ���Ҳ���Ƕ̰�����Ч����
	}
	return KEY_OFF;
}

