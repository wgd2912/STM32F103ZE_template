#include "sim7600.h"
#include "string.h"
#include "stdio.h"
#include "delay.h"
#include "usart.h"
#include "sys.h"
#include "fun.h"
/************************************************
函数名称 ： Sim7600_Phone_Config
功    能 ： 4G模块初始化函数，打电话例程初始化
参    数 ： 无
返 回 值 ： 无
作    者 ： 王国栋
时    间 ： 2020年5月15日
备    注 ： 无
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
	printf("AT指令正确\r\n");
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
	printf("回显关闭正确\r\n");
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
	printf("打开GPS成功\r\n");
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
	printf("AT+CSQ信号强度指令正确\r\n");
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
	printf("AT+CPIN?检测卡指令正确\r\n");
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
	printf("AT+CREG?网络指令正确\r\n");
	
	#if PHONE_SWITCH
	printf("开始拨打电话\r\n");
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
	printf("注册GPRS网络成功\r\n");
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
	printf("接入APN成功\r\n");
	Clear_Buffer();
	Usart3_SendString("AT+CIPCLOSE=0\r\n");//结束TCP连接
    delay_ms(500);
	Clear_Buffer();
	Usart3_SendString("AT+NETCLOSE\r\n");//关闭socket连接
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
	printf("设置为TCP指令模式成功\r\n");
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
	printf("配置SOCKET,激活PDP成功\r\n");
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
	printf("开启SOCKET成功\r\n");
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
	printf("获取设备ID成功\r\n");
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
	printf("登录成功\r\n");
	#endif
}

void SIM7600_Test(void)
{
	char *strx = NULL;
	#if PHONE_SWITCH
	if(strstr((char*)USART_RxBuffer,sim7600ce.ATD[2]) != NULL)//返回无人接听
	{
	   printf("通话已经结束\r\n");
	   Clear_Buffer();	
	}
	#endif
	
	#if GPS_SWITCH
	while(strx==NULL)
	{
		Clear_Buffer();
		Usart3_SendString("AT+CGPSINFO\r\n");//获取当前的GNSS定位信息
		delay_ms(sendtime*3);
		if(IDLE_flag == 1)
		{
			strx=strstr((const char*)USART_RxBuffer,(const char*)"OK");//返回OK
			IDLE_flag = 0;
		}
	}
	SIM7600CESend_StrData(USART_RxBuffer,strlen(USART_RxBuffer));
	#endif  
}

///发送字符型数据
void SIM7600CESend_StrData(char *bufferdata,u8 len)
{
	char *strx = NULL;
	char tempstr[20] = {0};
	sprintf(tempstr,"AT+CIPSEND=0,%d\r\n",len);
	Usart3_SendString(tempstr);//不计算长度发送
	delay_ms(100);
	Usart3_SendString(bufferdata);
    delay_ms(100);	
    printf("GPS数据发送成功\r\n");//发送完成函数
  while(USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET)
    {
    }
	delay_ms(100);
    strx=strstr((char*)USART_RxBuffer,(char*)"+CIPSEND:");//是否正确发送
  while(strx==NULL)
    {
        strx=strstr((char*)USART_RxBuffer,(char*)"+CIPSEND:");//是否正确发送
        delay_ms(10);
    }
    delay_ms(100);
    Clear_Buffer();
}

/************************************************
函数名称 ： Clear_Buffer
功    能 ： 清空缓存,清除串口3接收到的数据，
参    数 ： 无
返 回 值 ： 无
作    者 ： 王国栋
时    间 ： 2020年5月15日
备    注 ： 无
*************************************************/
void Clear_Buffer(void)
{
	memset(USART_RxBuffer,0,sizeof(USART_RxBuffer));
	USART_RxCounter = 0;
}


