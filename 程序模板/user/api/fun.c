#include "fun.h"
#include "string.h"
#include "delay.h"
/**
 * ���ܣ������ַ������Ƿ������һ���ַ���
 * ������
 *       dest��������Ŀ���ַ���
 *       src�� ����������
 *       retry_ms:��ѯ��ʱʱ��
 * ����ֵ�����ҽ������0Ϊ���ҳɹ�,0Ϊʧ��
 */
u8 FindStr(char* dest,char* src,u16 retry_nms)
{
    retry_nms/=10;                   //��ʱʱ��

    while(strstr(dest,src)==0 && retry_nms--)//�ȴ����ڽ�����ϻ�ʱ�˳�
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





