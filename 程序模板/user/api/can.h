#ifndef __CAN_H
#define __CAN_H

#include "stm32f10x.h"

//CAN����RX0�ж�ʹ��
#define CAN_RX0_INT_ENABLE	1		//0,��ʹ��;1,ʹ��.	

void CAN_Mode_Init(u8 tsjw,u8 tbs2,u8 tbs1,u16 brp,u8 mode);
u8 CAN_Msg_Pend(u8 fifox);	
u8 CAN_Send_Msg(u8* msg,u8 len);						//��������
u8 CAN_Receive_Msg(u8 *buf);	

#endif 

