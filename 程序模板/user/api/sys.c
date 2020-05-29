#include "sys.h"

/*delay.c*/
u32 nus_time;			//nus延时
u16 nms_time;			//nms延时
vu32 led_time = 0;		//系统指示灯闪烁时长
vu32 runtime = 0;		//系统运行时间
vu32 sim7600time = 0;	//4G模块

/*USART.c*/
//注意,读取USARTx->SR能避免莫名其妙的错误 
u16  USART_RxCounter;			//最大USART_REC_LEN个字节.
char USART_RxBuffer[1000];    	//接收缓冲区
u8 IDLE_flag = 0;				//串口空闲中断标志位

/*SIM7600CE.c*/
SIM7600CE sim7600ce = {
	{"AT\r\n",			"OK"							},
	{"ATE0\r\n",		"OK"							},
	{"AT+CSQ\r\n",		"OK"							},
	{"AT+CPIN?\r\n",	"OK"							},
	{"AT+CREG?\r\n",	"+CREG: 0,1",		"+CREG: 0,5"},
	{"ATD10000;\r\n",	"VOICE CALL: BEGIN","NO CARRIER"},
	{"AT+CGPS=1\r\n",	"OK",		"ERROR"},
	{"AT+CGREG?\r\n",	"+CGREG: 0,1",		"+CGREG: 0,5"},
	{"AT+CGDCONT=1,\"IP\",\"3gnet\"\r\n",	"OK"},
	{"AT+CIPCLOSE=0\r\n",					"OK"},
	{"AT+NETCLOSE\r\n",						"OK"},
	{"AT+CIPMODE=1\r\n",					"OK"},
	{"AT+CSOCKSETPN=1\r\n",					"OK"},
	{"AT+NETOPEN\r\n",	"+NETOPEN: 0",		"Network is already opened"},
	{"AT+IPADDR\r\n",	"+IPADDR:"},
	{"AT+CIPOPEN=0,\"TCP\",\"180.97.81.180\",51206\r\n","+CIPOPEN: 0,0","CONNECT"}
};
 


