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
函数名称 ： AT24CXX_ReadOneByte
功    能 ： 在AT24CXX指定地址读出一个数据
参    数 ： ReadAddr:开始读数的地址
返 回 值 ： 读到的数据
作    者 ： 王国栋
时    间 ： 2020年5月11日
备    注 ： 无
*************************************************/
u8 AT24CXX_ReadOneByte(u16 AT24CXX,u8 AT24CXX_ADDR,u16 ReadAddr)
{
	u8 temp=0;		  	    																 
    IIC_Start();  
	if(AT24CXX>AT24C16)
	{
		IIC_SendByte(0XA0+(AT24CXX_ADDR<<1));	   //发送写命令
		IIC_Wait_Ack();
		IIC_SendByte(ReadAddr>>8);//发送高地址		 
	}else IIC_SendByte(0XA0+(AT24CXX_ADDR<<1)+((ReadAddr/256)<<1));   //发送器件地址0XA0,写数据 	 

	IIC_Wait_Ack(); 
    IIC_SendByte(ReadAddr%256);   //发送低地址
	IIC_Wait_Ack();	    
	IIC_Start();  	 	   
	IIC_SendByte(0XA0+(AT24CXX_ADDR<<1)+1);           //进入接收模式			   
	IIC_Wait_Ack();	 
    temp=IIC_ReadByte(0);		   
    IIC_Stop();//产生一个停止条件	    
	return temp;
}

/************************************************
函数名称 ： AT24CXX_WriteOneByte
功    能 ： 在AT24CXX指定地址写入一个数据
参    数 ： WriteAddr  :写入数据的目的地址    
			DataToWrite:要写入的数据
返 回 值 ： 无
作    者 ： 王国栋
时    间 ： 2020年5月11日
备    注 ： 无
*************************************************/
void AT24CXX_WriteOneByte(u16 AT24CXX,u8 AT24CXX_ADDR,u16 WriteAddr,u8 DataToWrite)
{			  	    	  	    																 
    IIC_Start();   
	if(AT24CXX>AT24C16)
	{
		IIC_SendByte(0XA0+(AT24CXX_ADDR<<1));	    //发送写命令
		IIC_Wait_Ack();
		IIC_SendByte(WriteAddr>>8);//发送高地址、寄存器地址
 	}else
	{
		IIC_SendByte(0XA0+(AT24CXX_ADDR<<1)+((WriteAddr/256)<<1));   //发送器件地址0XA0,写数据 
	}	 
	IIC_Wait_Ack();	   
    IIC_SendByte(WriteAddr%256);   //发送低地址、寄存器地址
	IIC_Wait_Ack(); 	 										  		   
	IIC_SendByte(DataToWrite);     //发送字节							   
	IIC_Wait_Ack();  		    	   
    IIC_Stop();//产生一个停止条件 
	delay_ms(10);	 
}

/************************************************
函数名称 ： AT24CXX_WriteLenByte
功    能 ： 在AT24CXX里面的指定地址开始写入长度为Len的数据
参    数 ： WriteAddr  :开始写入的地址  
			DataToWrite:数据数组首地址
			Len        :要写入数据的长度2,4
返 回 值 ： 无
作    者 ： 王国栋
时    间 ： 2020年5月11日
备    注 ： 该函数用于写入16bit或者32bit的数据
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
函数名称 ： AT24CXX_ReadLenByte
功    能 ： 在AT24CXX里面的指定地址开始读取长度为Len的数据
参    数 ： WriteAddr  :开始写入的地址  
			DataToWrite:数据数组首地址
			Len        :要写入数据的长度2,4
返 回 值 ： 无
作    者 ： 王国栋
时    间 ： 2020年5月11日
备    注 ： 该函数用于写入16bit或者32bit的数据
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

//检查AT24CXX是否正常
//这里用了24XX的最后一个地址(255)来存储标志字.
//如果用其他24C系列,这个地址要修改
//返回1:检测失败
//返回0:检测成功
u8 AT24CXX_Check(u16 AT24CXX,u8 AT24CXX_ADDR,u16 dataaddr)
{
	u8 temp; 
	temp=AT24CXX_ReadOneByte(AT24CXX,AT24CXX_ADDR,dataaddr);//避免每次开机都写AT24CXX			   
	if(temp==0X55)return 0;		   
	else//排除第一次初始化的情况
	{
		AT24CXX_WriteOneByte(AT24CXX,AT24CXX_ADDR,dataaddr,0X55);
	    temp=AT24CXX_ReadOneByte(AT24CXX,AT24CXX_ADDR,dataaddr);	  
		if(temp==0X55)return 0;
	}
	return 1;											  
}

/************************************************
函数名称 ： AT24CXX_Read
功    能 ： 在AT24CXX里面的指定地址开始读出指定个数的数据
参    数 ： ReadAddr 	:开始读出的地址 对24c02为0~255
			pBuffer  	:数据数组首地址
			NumToRead	:要读出数据的个数
返 回 值 ： 无
作    者 ： 王国栋
时    间 ： 2020年5月11日
备    注 ： 
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
函数名称 ： AT24CXX_Read
功    能 ： 在AT24CXX里面的指定地址开始写入指定个数的数据
参    数 ： WriteAddr 	:开始写入的地址 对24c02为0~255
			pBuffer  	:数据数组首地址
			NumToWrite	:要写入数据的个数
返 回 值 ： 无
作    者 ： 王国栋
时    间 ： 2020年5月11日
备    注 ： 
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
	const u8 sss[] = "AT24C02读写测试789099*/8569/*85+9*89AT24Cxx读写测试012345678909*/8569/*85+9*89AT24Cxx读写测试012345678909*/8569/*85+9*8965+8969568*86959-*89569*65+69*+1234567890123456789012345678901234567890123456789454445451452424524242855243210";
	u8 mmm[300];
	printf("sss大小是%d\r\n",sizeof(sss)-1);
	if(AT24CXX_Check(AT24C256,AT24C256_addr,AT24C256_Check_online_addr) == 0)
	{
		printf("AT24C256检测成功\r\n");
//		AT24CXX_Write(AT24C256,AT24C256_addr,0,(u8*)sss,sizeof(sss));
		AT24CXX_Read(AT24C256,AT24C256_addr,0,mmm,200);
	}
	if(AT24CXX_Check(AT24C02,AT24C02_addr,AT24C02_Check_online_addr) == 0)
	{
		printf("AT24C02检测成功\r\n");
//		AT24CXX_Write(AT24C02,AT24C02_addr,0,(u8*)sss,sizeof(sss));
		AT24CXX_Read(AT24C02,AT24C02_addr,0,mmm,200);
	}
	printf("mmm 大小是 %d\r\n",strlen((const char *)mmm));
	printf("%s\r\n",mmm);
}

