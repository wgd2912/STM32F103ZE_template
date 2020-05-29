#include "sdio_test.h"
#include "stm32_eval_sdio_sd.h"
#include "stdio.h"
#include "string.h"
#include "ffconf.h"
#include "ff.h"

/** @addtogroup SDIO_uSDCard
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
typedef enum {FAILED = 0, PASSED = !FAILED} TestStatus;

/* Private define ------------------------------------------------------------*/
#define BLOCK_SIZE            512 /* Block Size in Bytes */

#define NUMBER_OF_BLOCKS      32  /* For Multi Blocks operation (Read/Write) */
#define MULTI_BUFFER_SIZE    (BLOCK_SIZE * NUMBER_OF_BLOCKS)

#define SD_OPERATION_ERASE          0
#define SD_OPERATION_BLOCK          1
#define SD_OPERATION_MULTI_BLOCK    2 
#define SD_OPERATION_END            3

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
uint8_t Buffer_Block_Tx[BLOCK_SIZE], Buffer_Block_Rx[BLOCK_SIZE];
uint8_t Buffer_MultiBlock_Tx[MULTI_BUFFER_SIZE], Buffer_MultiBlock_Rx[MULTI_BUFFER_SIZE];
volatile TestStatus EraseStatus = FAILED, TransferStatus1 = FAILED, TransferStatus2 = FAILED;
SD_Error Status = SD_OK;
__IO uint32_t SDCardOperation = SD_OPERATION_ERASE;

void Fill_Buffer(uint8_t *pBuffer, uint32_t BufferLength, uint32_t Offset);
TestStatus Buffercmp(uint8_t* pBuffer1, uint8_t* pBuffer2, uint32_t BufferLength);
TestStatus eBuffercmp(uint8_t* pBuffer, uint32_t BufferLength);



/**
  * @brief  Tests the SD card erase operation.
  * @param  None
  * @retval None
  */
void SD_EraseTest(void)
{
  /*------------------- Block Erase ------------------------------------------*/
  if (Status == SD_OK)
  {
    /* Erase NumberOfBlocks Blocks of WRITE_BL_LEN(512 Bytes) */
    Status = SD_Erase(0x00, (BLOCK_SIZE * NUMBER_OF_BLOCKS));
  }

  if (Status == SD_OK)
  {
    Status = SD_ReadMultiBlocks(Buffer_MultiBlock_Rx, 0x00, BLOCK_SIZE, NUMBER_OF_BLOCKS);

    /* Check if the Transfer is finished */
    Status = SD_WaitReadOperation();

    /* Wait until end of DMA transfer */
    while(SD_GetStatus() != SD_TRANSFER_OK);
  }

  /* Check the correctness of erased blocks */
  if (Status == SD_OK)
  {
    EraseStatus = eBuffercmp(Buffer_MultiBlock_Rx, MULTI_BUFFER_SIZE);
  }
  
  if(EraseStatus == PASSED)
  {
    printf("擦除测试成功\r\n");
  }
  else
  {
    printf("擦除测试失败\r\n");    
  }
}

/**
  * @brief  Tests the SD card Single Blocks operations.
  * @param  None
  * @retval None
  */
void SD_SingleBlockTest(void)
{
  /*------------------- Block Read/Write --------------------------*/
  /* Fill the buffer to send */
  Fill_Buffer(Buffer_Block_Tx, BLOCK_SIZE, 0x320F);

  if (Status == SD_OK)
  {
    /* Write block of 512 bytes on address 0 */
    Status = SD_WriteBlock(Buffer_Block_Tx, 0x00, BLOCK_SIZE);
    /* Check if the Transfer is finished */
    Status = SD_WaitWriteOperation();
    while(SD_GetStatus() != SD_TRANSFER_OK);
  }

  if (Status == SD_OK)
  {
    /* Read block of 512 bytes from address 0 */
    Status = SD_ReadBlock(Buffer_Block_Rx, 0x00, BLOCK_SIZE);
    /* Check if the Transfer is finished */
    Status = SD_WaitReadOperation();
    while(SD_GetStatus() != SD_TRANSFER_OK);
  }

  /* Check the correctness of written data */
  if (Status == SD_OK)
  {
    TransferStatus1 = Buffercmp(Buffer_Block_Tx, Buffer_Block_Rx, BLOCK_SIZE);
  }
  
  if(TransferStatus1 == PASSED)
  {
    printf("单块测试成功\r\n");
  }
  else
  {
    printf("单块测试失败\r\n");  
  }
}

/**
  * @brief  Tests the SD card Multiple Blocks operations.
  * @param  None
  * @retval None
  */
void SD_MultiBlockTest(void)
{
  /*--------------- Multiple Block Read/Write ---------------------*/
  /* Fill the buffer to send */
  Fill_Buffer(Buffer_MultiBlock_Tx, MULTI_BUFFER_SIZE, 0x0);

  if (Status == SD_OK)
  {
    /* Write multiple block of many bytes on address 0 */
    Status = SD_WriteMultiBlocks(Buffer_MultiBlock_Tx, 0x00, BLOCK_SIZE, NUMBER_OF_BLOCKS);
    /* Check if the Transfer is finished */
    Status = SD_WaitWriteOperation();
    while(SD_GetStatus() != SD_TRANSFER_OK);
  }

  if (Status == SD_OK)
  {
    /* Read block of many bytes from address 0 */
    Status = SD_ReadMultiBlocks(Buffer_MultiBlock_Rx, 0x00, BLOCK_SIZE, NUMBER_OF_BLOCKS);
    /* Check if the Transfer is finished */
    Status = SD_WaitReadOperation();
    while(SD_GetStatus() != SD_TRANSFER_OK);
  }

  /* Check the correctness of written data */
  if (Status == SD_OK)
  {
    TransferStatus2 = Buffercmp(Buffer_MultiBlock_Tx, Buffer_MultiBlock_Rx, MULTI_BUFFER_SIZE);
  }
  
  if(TransferStatus2 == PASSED)
  {
    printf("多模块测试成功\r\n");
  }
  else
  {
    printf("多模块测试失败\r\n");  
  }
}

/**
  * @brief  Compares two buffers.
  * @param  pBuffer1, pBuffer2: buffers to be compared.
  * @param  BufferLength: buffer's length
  * @retval PASSED: pBuffer1 identical to pBuffer2
  *         FAILED: pBuffer1 differs from pBuffer2
  */
TestStatus Buffercmp(uint8_t* pBuffer1, uint8_t* pBuffer2, uint32_t BufferLength)
{
  while (BufferLength--)
  {
    if (*pBuffer1 != *pBuffer2)
    {
      return FAILED;
    }

    pBuffer1++;
    pBuffer2++;
  }

  return PASSED;
}

/**
  * @brief  Fills buffer with user predefined data.
  * @param  pBuffer: pointer on the Buffer to fill
  * @param  BufferLength: size of the buffer to fill
  * @param  Offset: first value to fill on the Buffer
  * @retval None
  */
void Fill_Buffer(uint8_t *pBuffer, uint32_t BufferLength, uint32_t Offset)
{
  uint16_t index = 0;

  /* Put in global buffer same values */
  for (index = 0; index < BufferLength; index++)
  {
    pBuffer[index] = index + Offset;
  }
}

/**
  * @brief  Checks if a buffer has all its values are equal to zero.
  * @param  pBuffer: buffer to be compared.
  * @param  BufferLength: buffer's length
  * @retval PASSED: pBuffer values are zero
  *         FAILED: At least one value from pBuffer buffer is different from zero.
  */
TestStatus eBuffercmp(uint8_t* pBuffer, uint32_t BufferLength)
{
  while (BufferLength--)
  {
    /* In some SD Cards the erased state is 0xFF, in others it's 0x00 */
    if ((*pBuffer != 0xFF) && (*pBuffer != 0x00))
    {
      return FAILED;
    }

    pBuffer++;
  }

  return PASSED;
}

void Sd_Test(void)
{
  SD_Error Status = SD_OK;
  uint8_t str[32] = "1234567890\r\n";
  
  /* Write multiple block of many bytes on address 0 */
  Status = SD_WriteMultiBlocks((u8 *)str, 0, BLOCK_SIZE, 1);
  /* Check if the Transfer is finished */
  Status = SD_WaitWriteOperation();
  while(SD_GetStatus() != SD_TRANSFER_OK);
  
  /* Read block of many bytes from address 0 */
  Status = SD_ReadMultiBlocks(str, 0, BLOCK_SIZE, 1);
  /* Check if the Transfer is finished */
  Status = SD_WaitReadOperation();
  while(SD_GetStatus() != SD_TRANSFER_OK);
  
  printf("%s", str);
}

void add_fatfs_SD_test(void)
{
	DIR dir;
	FATFS *pfs;
	DWORD fre_clust, fre_sect, tot_sect;
	u8 res_sd;
	FIL fnew;
	UINT fnum;
	
	u8 WriteBuffer[100] = "正常测试SD读写功能\r\n";
	u8 ReadBuffer[100];
	
	printf("\r\n*************************设备信息获取*************************\r\n");
	//获取设备信息和空簇大小
	res_sd = f_getfree("0:", &fre_clust, &pfs);
	
	//计算得到总的扇区个数和空扇区个数
	tot_sect = (pfs->n_fatent - 2) * pfs->csize;
	fre_sect = fre_clust * pfs->csize;
	
	printf("设备总空间：%10lu KB\r\n可用空间  ：%10lu KB。\r\n", tot_sect*4, fre_sect*4);
	
	printf("\r\n*************************文件定位和格式化写入功能测试***************************\r\n");
	//打开文件，若不存在就创建
	res_sd = f_open(&fnew, "0:FatFs多项功能测试文件.txt", FA_CREATE_ALWAYS | FA_WRITE | FA_READ);
	//文件打开成功
	if(res_sd == FR_OK)
	{
		printf("打开文件成功！开始读取数据！\r\n");
		res_sd= f_write(&fnew, WriteBuffer, sizeof(WriteBuffer), &fnum);
		
		if(res_sd == FR_OK)
		{
			printf("数据写入成功！\r\n");
			printf("数据：%s\r\n", WriteBuffer);
			//文件定位,定位到文件末尾，f_size获取文件大小
			res_sd = f_lseek(&fnew, f_size(&fnew) - 1);
			if(res_sd == FR_OK)
			{
				//在原文件中追加一行内容
				f_printf(&fnew, "在原文件中追加一行内容。\n");
				f_printf(&fnew, "设备总空间：%10lu KB\r\n可用空间：%10lu KB。\r\n", tot_sect*4, fre_sect*4);
				
				//文件定位到起始位置
				res_sd = f_lseek(&fnew, 0);
				
				if(res_sd == FR_OK)
				{
					//打开文件，若不存在就创建
					res_sd = f_open(&fnew, "0:FatFs多项功能测试文件.txt", FA_OPEN_EXISTING | FA_READ);
					//文件打开成功
					if(res_sd == FR_OK)
					{
						printf("打开文件成功！开始读取数据！\r\n");
						res_sd= f_read(&fnew, ReadBuffer, sizeof(ReadBuffer), &fnum);
						
						if(res_sd == FR_OK)
						{
							printf("数据读取成功！\r\n");
							printf("数据：%s\r\n", ReadBuffer);
						}
						else
						{
							printf("数据读取失败！\r\n");
						}
						
						//关闭文件
						f_close(&fnew);
					}
				}
			}
		}
		else
		{
			printf("数据读取失败！\r\n");
		}
		
		//关闭文件
		f_close(&fnew);
	}
	printf("\r\n*************************目录创建和重命名功能测试***************************\r\n");
	//尝试打开目录
	res_sd = f_opendir(&dir, "0:TestDir");
	if(res_sd != FR_OK)
	{
		//打开目录失败，开始创建目录
		res_sd = f_mkdir("0:TestDir");
	}
	else
	{
		//如果目录已经存在，关闭它
		res_sd = f_closedir(&dir);
		//删除文件
		f_unlink("0:FatFs读写测试文件.txt");
	}
	
	if(res_sd == FR_OK)
	{
		//重命名并移动文件
		res_sd = f_rename("0:FatFs多项功能测试文件.txt", "0:/TestDir/FatFs多项功能测试文件.txt");
		
		if(res_sd == FR_OK)
		{
			printf("重命名并移动文件成功！\r\n");
		}
		else
		{
			printf("重命名并移动文件失败！\r\n");
		}
	}
}

	
//	if(SD_Init() == SD_OK)
//	{
//		printf("SD卡初始化成功\r\n");
//		Sd_Test();
//		switch(SDCardInfo.CardType)
//		{
//			case SDIO_STD_CAPACITY_SD_CARD_V1_1:printf("Card Type:SDSC V1.1\r\n");break;
//			case SDIO_STD_CAPACITY_SD_CARD_V2_0:printf("Card Type:SDSC V2.0\r\n");break;
//			case SDIO_HIGH_CAPACITY_SD_CARD:printf("Card Type:SDHC V2.0\r\n");break;
//			case SDIO_MULTIMEDIA_CARD:printf("Card Type:MMC Card\r\n");break;
//		}	
//		printf("Card ManufacturerID:%d\r\n",SDCardInfo.SD_cid.ManufacturerID);	//制造商ID
//		printf("Card RCA:%d\r\n",SDCardInfo.RCA);								//卡相对地址
//		printf("Card Capacity:%d MB\r\n",(u32)(SDCardInfo.CardCapacity>>20));	//显示容量
//		printf("Card BlockSize:%d\r\n\r\n",SDCardInfo.CardBlockSize);			//显示块大小
//	}
//	SD_EraseTest();
//	SD_SingleBlockTest();
//	SD_MultiBlockTest();
	/*1.注册驱动器*/ 
//	res=f_mount (& fp, "0", 1); // 注册工作区，驱动器号 0 
//	if(res==FR_OK)
//	{ 
//		printf("成功注册工作区\r\n"); 
//	}
//	else if(res==FR_INVALID_DRIVE) 
//	{
//		printf("注册失败\r\n"); 
//	} 
	//初始化SD卡
//	if(SD_Init() == SD_OK)
//		printf("SD卡初始化成功，即将挂载SD卡。\r\n");
//	//挂载SD卡	
//	if(f_mount(&fs, "0:", 1) == FR_OK)
//		printf("文件系统挂载成功...\r\n");	
//	add_fatfs_SD_test();




