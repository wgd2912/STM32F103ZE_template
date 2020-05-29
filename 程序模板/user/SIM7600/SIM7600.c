#include "sim7600.h"
#include "string.h"
#include "stdio.h"
#include "delay.h"
#include "usart.h"
#include "sys.h"
#include "fun.h"
/************************************************
�������� �� Sim7600_Phone_Config
��    �� �� 4Gģ���ʼ����������绰���̳�ʼ��
��    �� �� ��
�� �� ֵ �� ��
��    �� �� ������
ʱ    �� �� 2020��5��15��
��    ע �� ��
*************************************************/
void Sim7600_Config(void)
{
	char *strx = NULL,*extstrx = NULL;
	while(strx == NULL)
	{
		Clear_Buffer();
		Usart3_SendString(sim7600ce.AT[0]);	
		delay_ms(sendtime);
		if(IDLE_flag == 1)
		{
			strx = strstr((char*)USART_RxBuffer,sim7600ce.AT[1]);
			IDLE_flag = 0;
		}		
	}		
	printf("ATָ����ȷ\r\n");
	strx = NULL;
	while(strx == NULL)
	{
		Clear_Buffer();
		Usart3_SendString(sim7600ce.ATE0[0]);	
		delay_ms(sendtime);
		if(IDLE_flag == 1)
		{
			IDLE_flag = 0;
			strx = strstr((char*)USART_RxBuffer,sim7600ce.ATE0[1]);
		}		
	}
	printf("���Թر���ȷ\r\n");
	#if GPS_SWITCH
	strx = NULL;
	extstrx = NULL;
	while(strx == NULL && extstrx == NULL)
	{
		Clear_Buffer();
		Usart3_SendString(sim7600ce.CGPS[0]);	
		delay_ms(sendtime);
		if(IDLE_flag == 1)
		{
			strx = strstr((char*)USART_RxBuffer,sim7600ce.CGPS[1]);
			extstrx = strstr((char*)USART_RxBuffer,sim7600ce.CGPS[2]);
			IDLE_flag = 0;
		}			
	}
	printf("��GPS�ɹ�\r\n");
	#endif
	strx = NULL;
	while(strx == NULL)
	{
		Clear_Buffer();
		Usart3_SendString(sim7600ce.CSQ[0]);	
		delay_ms(sendtime);
		if(IDLE_flag == 1)
		{
			strx = strstr((char*)USART_RxBuffer,sim7600ce.CSQ[1]);
			IDLE_flag = 0;
		}	
	}
	printf("AT+CSQ�ź�ǿ��ָ����ȷ\r\n");
	strx = NULL;
	while(strx == NULL)
	{
		Clear_Buffer();
		Usart3_SendString(sim7600ce.CPIN[0]);	
		delay_ms(sendtime);
		if(IDLE_flag == 1)
		{
			strx = strstr((char*)USART_RxBuffer,sim7600ce.CPIN[1]);
			IDLE_flag = 0;
		}	
	}
	printf("AT+CPIN?��⿨ָ����ȷ\r\n");
	strx = NULL;
	while(strx == NULL && extstrx == NULL)
	{
		Clear_Buffer();
		Usart3_SendString(sim7600ce.CREG[0]);	
		delay_ms(sendtime);
		if(IDLE_flag == 1)
		{
			strx = strstr((char*)USART_RxBuffer,sim7600ce.CREG[1]);
			extstrx = strstr((char*)USART_RxBuffer,sim7600ce.CREG[2]);
			IDLE_flag = 0;
		}		
	}
	printf("AT+CREG?����ָ����ȷ\r\n");
	
	#if PHONE_SWITCH
	printf("��ʼ����绰\r\n");
	Usart3_SendString(sim7600ce.ATD[0]);
	Clear_Buffer();
	delay_ms(sendtime*5);
	#endif
	
	#if GPS_SWITCH
	
	strx = NULL;
	while(strx == NULL)
	{
		Clear_Buffer();
		Usart3_SendString(sim7600ce.CGREG[0]);	
		delay_ms(sendtime);
		if(IDLE_flag == 1)
		{
			strx = strstr((char*)USART_RxBuffer,sim7600ce.CGREG[1]);
			IDLE_flag = 0;
		}
	}
	printf("ע��GPRS����ɹ�\r\n");
	strx = NULL;
	while(strx == NULL)
	{
		Clear_Buffer();
		Usart3_SendString(sim7600ce.CGDCONT[0]);	
		delay_ms(sendtime);
		if(IDLE_flag == 1)
		{	
			strx = strstr((char*)USART_RxBuffer,sim7600ce.CGDCONT[1]);
			IDLE_flag = 0;
		}
	}
	printf("����APN�ɹ�\r\n");
	Clear_Buffer();
	Usart3_SendString("AT+CIPCLOSE=0\r\n");//����TCP����
    delay_ms(500);
	Clear_Buffer();
	Usart3_SendString("AT+NETCLOSE\r\n");//�ر�socket����
	strx = NULL;
	while(strx == NULL)
	{
		Clear_Buffer();
		Usart3_SendString(sim7600ce.CIPMODE[0]);	
		delay_ms(sendtime);
		if(IDLE_flag == 1)
		{	
			strx = strstr((char*)USART_RxBuffer,sim7600ce.CIPMODE[1]);
			IDLE_flag = 0;
		}
	}
	printf("����ΪTCPָ��ģʽ�ɹ�\r\n");
	strx = NULL;
	while(strx == NULL)
	{
		Clear_Buffer();
		Usart3_SendString(sim7600ce.CSOCKSETPN[0]);	
		delay_ms(sendtime);
		if(IDLE_flag == 1)
		{	
			strx = strstr((char*)USART_RxBuffer,sim7600ce.CSOCKSETPN[1]);
			IDLE_flag = 0;
		}	
	}
	printf("����SOCKET,����PDP�ɹ�\r\n");
	strx = NULL;
	extstrx = NULL;
	while(strx == NULL && extstrx == NULL)
	{
		Clear_Buffer();
		Usart3_SendString(sim7600ce.NETOPEN[0]);	
		delay_ms(sendtime);
		if(IDLE_flag == 1)
		{	
			strx = strstr((char*)USART_RxBuffer,sim7600ce.NETOPEN[1]);
			extstrx = strstr((char*)USART_RxBuffer,sim7600ce.NETOPEN[2]);
			IDLE_flag = 0;
		}
	}
	printf("����SOCKET�ɹ�\r\n");
	strx = NULL;
	extstrx = NULL;
	while(strx == NULL)
	{
		Clear_Buffer();
		Usart3_SendString(sim7600ce.IPADDR[0]);	
		delay_ms(sendtime);
		if(IDLE_flag == 1)
		{	
			strx = strstr((char*)USART_RxBuffer,sim7600ce.IPADDR[1]);
			IDLE_flag = 0;
		}
	}
	printf("��ȡ�豸ID�ɹ�\r\n");
	strx = NULL;
	while(strx == NULL && extstrx == NULL)
	{
		Clear_Buffer();
		Usart3_SendString(sim7600ce.CIPOPEN[0]);	
		delay_ms(sendtime);
		if(IDLE_flag == 1)
		{	
			strx = strstr((char*)USART_RxBuffer,sim7600ce.CIPOPEN[1]);
			extstrx = strstr((char*)USART_RxBuffer,sim7600ce.CIPOPEN[2]);
			IDLE_flag = 0;
		}
	}
	printf("��¼�ɹ�\r\n");
	#endif
}

void SIM7600_Test(void)
{
	char *strx = NULL;
	#if PHONE_SWITCH
	if(strstr((char*)USART_RxBuffer,sim7600ce.ATD[2]) != NULL)//�������˽���
	{
	   printf("ͨ���Ѿ�����\r\n");
	   Clear_Buffer();	
	}
	#endif
	
	#if GPS_SWITCH
	while(strx==NULL)
	{
		Clear_Buffer();
		Usart3_SendString("AT+CGPSINFO\r\n");//��ȡ��ǰ��GNSS��λ��Ϣ
		delay_ms(sendtime*3);
		if(IDLE_flag == 1)
		{
			strx=strstr((const char*)USART_RxBuffer,(const char*)"OK");//����OK
			IDLE_flag = 0;
		}
	}
	SIM7600CESend_StrData(USART_RxBuffer,strlen(USART_RxBuffer));
	#endif  
}

///�����ַ�������
void SIM7600CESend_StrData(char *bufferdata,u8 len)
{
	char *strx = NULL;
	char tempstr[20] = {0};
	sprintf(tempstr,"AT+CIPSEND=0,%d\r\n",len);
	Usart3_SendString(tempstr);//�����㳤�ȷ���
	delay_ms(100);
	Usart3_SendString(bufferdata);
    delay_ms(100);	
    printf("GPS���ݷ��ͳɹ�\r\n");//������ɺ���
  while(USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET)
    {
    }
	delay_ms(100);
    strx=strstr((char*)USART_RxBuffer,(char*)"+CIPSEND:");//�Ƿ���ȷ����
  while(strx==NULL)
    {
        strx=strstr((char*)USART_RxBuffer,(char*)"+CIPSEND:");//�Ƿ���ȷ����
        delay_ms(10);
    }
    delay_ms(100);
    Clear_Buffer();
}

/************************************************
�������� �� Clear_Buffer
��    �� �� ��ջ���,�������3���յ������ݣ�
��    �� �� ��
�� �� ֵ �� ��
��    �� �� ������
ʱ    �� �� 2020��5��15��
��    ע �� ��
*************************************************/
void Clear_Buffer(void)
{
	memset(USART_RxBuffer,0,sizeof(USART_RxBuffer));
	USART_RxCounter = 0;
}


