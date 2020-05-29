#include "AT24Cxx.h"
#include "string.h"
#include "delay.h"
#include "stdio.h"
#include "iic.h"
#include "sys.h"


void AT24CXX_Init(void)
{
	IIC_Init();
}


/************************************************
�������� �� AT24CXX_ReadOneByte
��    �� �� ��AT24CXXָ����ַ����һ������
��    �� �� ReadAddr:��ʼ�����ĵ�ַ
�� �� ֵ �� ����������
��    �� �� ������
ʱ    �� �� 2020��5��11��
��    ע �� ��
*************************************************/
u8 AT24CXX_ReadOneByte(u16 AT24CXX,u8 AT24CXX_ADDR,u16 ReadAddr)
{
	u8 temp=0;		  	    																 
    IIC_Start();  
	if(AT24CXX>AT24C16)
	{
		IIC_SendByte(0XA0+(AT24CXX_ADDR<<1));	   //����д����
		IIC_Wait_Ack();
		IIC_SendByte(ReadAddr>>8);//���͸ߵ�ַ		 
	}else IIC_SendByte(0XA0+(AT24CXX_ADDR<<1)+((ReadAddr/256)<<1));   //����������ַ0XA0,д���� 	 

	IIC_Wait_Ack(); 
    IIC_SendByte(ReadAddr%256);   //���͵͵�ַ
	IIC_Wait_Ack();	    
	IIC_Start();  	 	   
	IIC_SendByte(0XA0+(AT24CXX_ADDR<<1)+1);           //�������ģʽ			   
	IIC_Wait_Ack();	 
    temp=IIC_ReadByte(0);		   
    IIC_Stop();//����һ��ֹͣ����	    
	return temp;
}

/************************************************
�������� �� AT24CXX_WriteOneByte
��    �� �� ��AT24CXXָ����ַд��һ������
��    �� �� WriteAddr  :д�����ݵ�Ŀ�ĵ�ַ    
			DataToWrite:Ҫд�������
�� �� ֵ �� ��
��    �� �� ������
ʱ    �� �� 2020��5��11��
��    ע �� ��
*************************************************/
void AT24CXX_WriteOneByte(u16 AT24CXX,u8 AT24CXX_ADDR,u16 WriteAddr,u8 DataToWrite)
{			  	    	  	    																 
    IIC_Start();   
	if(AT24CXX>AT24C16)
	{
		IIC_SendByte(0XA0+(AT24CXX_ADDR<<1));	    //����д����
		IIC_Wait_Ack();
		IIC_SendByte(WriteAddr>>8);//���͸ߵ�ַ���Ĵ�����ַ
 	}else
	{
		IIC_SendByte(0XA0+(AT24CXX_ADDR<<1)+((WriteAddr/256)<<1));   //����������ַ0XA0,д���� 
	}	 
	IIC_Wait_Ack();	   
    IIC_SendByte(WriteAddr%256);   //���͵͵�ַ���Ĵ�����ַ
	IIC_Wait_Ack(); 	 										  		   
	IIC_SendByte(DataToWrite);     //�����ֽ�							   
	IIC_Wait_Ack();  		    	   
    IIC_Stop();//����һ��ֹͣ���� 
	delay_ms(10);	 
}

/************************************************
�������� �� AT24CXX_WriteLenByte
��    �� �� ��AT24CXX�����ָ����ַ��ʼд�볤��ΪLen������
��    �� �� WriteAddr  :��ʼд��ĵ�ַ  
			DataToWrite:���������׵�ַ
			Len        :Ҫд�����ݵĳ���2,4
�� �� ֵ �� ��
��    �� �� ������
ʱ    �� �� 2020��5��11��
��    ע �� �ú�������д��16bit����32bit������
*************************************************/
void AT24CXX_WriteLenByte(u16 AT24CXX,u8 AT24CXX_ADDR,u16 WriteAddr,u32 DataToWrite,u8 Len)
{  	
	u8 t;
	for(t=0;t<Len;t++)
	{
		AT24CXX_WriteOneByte(AT24CXX,AT24CXX_ADDR,WriteAddr+t,(DataToWrite>>(8*t))&0xff);
	}												    
}
/************************************************
�������� �� AT24CXX_ReadLenByte
��    �� �� ��AT24CXX�����ָ����ַ��ʼ��ȡ����ΪLen������
��    �� �� WriteAddr  :��ʼд��ĵ�ַ  
			DataToWrite:���������׵�ַ
			Len        :Ҫд�����ݵĳ���2,4
�� �� ֵ �� ��
��    �� �� ������
ʱ    �� �� 2020��5��11��
��    ע �� �ú�������д��16bit����32bit������
*************************************************/
u32 AT24CXX_ReadLenByte(u16 AT24CXX,u8 AT24CXX_ADDR,u16 ReadAddr,u8 Len)
{  	
	u8 t;
	u32 temp=0;
	for(t=0;t<Len;t++)
	{
		temp<<=8;
		temp+=AT24CXX_ReadOneByte(AT24CXX,AT24CXX_ADDR,ReadAddr+Len-t-1); 	 				   
	}
	return temp;											    
}

//���AT24CXX�Ƿ�����
//��������24XX�����һ����ַ(255)���洢��־��.
//���������24Cϵ��,�����ַҪ�޸�
//����1:���ʧ��
//����0:���ɹ�
u8 AT24CXX_Check(u16 AT24CXX,u8 AT24CXX_ADDR,u16 dataaddr)
{
	u8 temp; 
	temp=AT24CXX_ReadOneByte(AT24CXX,AT24CXX_ADDR,dataaddr);//����ÿ�ο�����дAT24CXX			   
	if(temp==0X55)return 0;		   
	else//�ų���һ�γ�ʼ�������
	{
		AT24CXX_WriteOneByte(AT24CXX,AT24CXX_ADDR,dataaddr,0X55);
	    temp=AT24CXX_ReadOneByte(AT24CXX,AT24CXX_ADDR,dataaddr);	  
		if(temp==0X55)return 0;
	}
	return 1;											  
}

/************************************************
�������� �� AT24CXX_Read
��    �� �� ��AT24CXX�����ָ����ַ��ʼ����ָ������������
��    �� �� ReadAddr 	:��ʼ�����ĵ�ַ ��24c02Ϊ0~255
			pBuffer  	:���������׵�ַ
			NumToRead	:Ҫ�������ݵĸ���
�� �� ֵ �� ��
��    �� �� ������
ʱ    �� �� 2020��5��11��
��    ע �� 
*************************************************/
void AT24CXX_Read(u16 AT24CXX,u8 AT24CXX_ADDR,u16 ReadAddr,u8 *pBuffer,u16 NumToRead)
{
	while(NumToRead)
	{
		*pBuffer=AT24CXX_ReadOneByte(AT24CXX,AT24CXX_ADDR,ReadAddr);	
		NumToRead--;
		ReadAddr++;
		pBuffer++;
	}

}  
/************************************************
�������� �� AT24CXX_Read
��    �� �� ��AT24CXX�����ָ����ַ��ʼд��ָ������������
��    �� �� WriteAddr 	:��ʼд��ĵ�ַ ��24c02Ϊ0~255
			pBuffer  	:���������׵�ַ
			NumToWrite	:Ҫд�����ݵĸ���
�� �� ֵ �� ��
��    �� �� ������
ʱ    �� �� 2020��5��11��
��    ע �� 
*************************************************/
void AT24CXX_Write(u16 AT24CXX,u8 AT24CXX_ADDR,u16 WriteAddr,u8 *pBuffer,u16 NumToWrite)
{
	while(NumToWrite--)
	{
		AT24CXX_WriteOneByte(AT24CXX,AT24CXX_ADDR,WriteAddr,*pBuffer);
		WriteAddr++;
		pBuffer++;
	}
	
}

void AT24CXX_Test(void)
{
	const u8 sss[] = "AT24C02��д����789099*/8569/*85+9*89AT24Cxx��д����012345678909*/8569/*85+9*89AT24Cxx��д����012345678909*/8569/*85+9*8965+8969568*86959-*89569*65+69*+1234567890123456789012345678901234567890123456789454445451452424524242855243210";
	u8 mmm[300];
	printf("sss��С��%d\r\n",sizeof(sss)-1);
	if(AT24CXX_Check(AT24C256,AT24C256_addr,AT24C256_Check_online_addr) == 0)
	{
		printf("AT24C256���ɹ�\r\n");
//		AT24CXX_Write(AT24C256,AT24C256_addr,0,(u8*)sss,sizeof(sss));
		AT24CXX_Read(AT24C256,AT24C256_addr,0,mmm,200);
	}
	if(AT24CXX_Check(AT24C02,AT24C02_addr,AT24C02_Check_online_addr) == 0)
	{
		printf("AT24C02���ɹ�\r\n");
//		AT24CXX_Write(AT24C02,AT24C02_addr,0,(u8*)sss,sizeof(sss));
		AT24CXX_Read(AT24C02,AT24C02_addr,0,mmm,200);
	}
	printf("mmm ��С�� %d\r\n",strlen((const char *)mmm));
	printf("%s\r\n",mmm);
}

