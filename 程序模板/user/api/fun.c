#include "fun.h"
#include "string.h"
#include "delay.h"
/**
 * 功能：查找字符串中是否包含另一个字符串
 * 参数：
 *       dest：待查找目标字符串
 *       src： 待查找内容
 *       retry_ms:查询超时时间
 * 返回值：查找结果，非0为查找成功,0为失败
 */
u8 FindStr(char* dest,char* src,u16 retry_nms)
{
    retry_nms/=10;                   //超时时间

    while(strstr(dest,src)==0 && retry_nms--)//等待串口接收完毕或超时退出
    {		
		delay_ms(10);
		if(retry_nms == 0xffff)
			retry_nms = 0;
    }
	if(retry_nms == 0xffff)
		retry_nms = 0;
	if(retry_nms > 0)     
	   return 1;                       
	return 0; 
}





