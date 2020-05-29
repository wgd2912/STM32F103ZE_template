/*-----------------------------------------------------------------------*/
/* Low level disk I/O module skeleton for FatFs     (C)ChaN, 2016        */
/*-----------------------------------------------------------------------*/
/* If a working storage control module is available, it should be        */
/* attached to the FatFs via a glue function rather than modifying it.   */
/* This is an example of glue functions to attach various exsisting      */
/* storage control modules to the FatFs module with a defined API.       */
/*-----------------------------------------------------------------------*/

#include "diskio.h"		/* FatFs lower layer API */
#include "stm32_eval_sdio_sd.h"
/* Definitions of physical drive number for each drive */
//#define DEV_RAM		0	/* Example: Map Ramdisk to physical drive 0 */
//#define DEV_MMC		1	/* Example: Map MMC/SD card to physical drive 1 */
//#define DEV_USB		2	/* Example: Map USB MSD to physical drive 2 */
#define DEV_SD 0

/*-----------------------------------------------------------------------*/
/* Get Drive Status                                                      */
/*-----------------------------------------------------------------------*/

DSTATUS disk_status (
	BYTE pdrv		/* Physical drive nmuber to identify the drive */
)
{
	return RES_OK;
}



/*-----------------------------------------------------------------------*/
/* Inidialize a Drive                                                    */
/*-----------------------------------------------------------------------*/

DSTATUS disk_initialize (
	BYTE pdrv				/* Physical drive nmuber to identify the drive */
)
{
	DSTATUS stat;
	int result;

	switch (pdrv) {
	case DEV_SD :
		result = SD_Init();

		// translate the reslut code here

		return stat;

	}
	return STA_NOINIT;
}



/*-----------------------------------------------------------------------*/
/* Read Sector(s)                                                        */
/*-----------------------------------------------------------------------*/

DRESULT disk_read (
	BYTE pdrv,		/* Physical drive nmuber to identify the drive */
	BYTE *buff,		/* Data buffer to store read data */
	DWORD sector,	/* Start sector in LBA */
	UINT count		/* Number of sectors to read */
)
{
	int res;
	switch (pdrv) {
	case DEV_SD :
		// translate the arguments here

		res = SD_ReadMultiBlocks(buff, sector*512, 512, count);
		res = SD_WaitReadOperation();
		while(SD_GetStatus() != SD_TRANSFER_OK);
		// translate the reslut code here

		return (DRESULT)res;
	}

	return RES_PARERR;
}



/*-----------------------------------------------------------------------*/
/* Write Sector(s)                                                       */
/*-----------------------------------------------------------------------*/

DRESULT disk_write (
	BYTE pdrv,			/* Physical drive nmuber to identify the drive */
	const BYTE *buff,	/* Data to be written */
	DWORD sector,		/* Start sector in LBA */
	UINT count			/* Number of sectors to write */
)
{
	int result;

	switch (pdrv) {
	case DEV_SD :
		// translate the arguments here

		result = SD_WriteMultiBlocks((u8 *)buff, sector*512, 512,count);
		result = SD_WaitWriteOperation();
		// translate the reslut code here
		while(SD_GetStatus() != SD_TRANSFER_OK);
		return (DRESULT)result;
	}

	return RES_PARERR;
}

extern SD_CardInfo SDCardInfo;
/*-----------------------------------------------------------------------*/
/* Miscellaneous Functions                                               */
/*-----------------------------------------------------------------------*/

DRESULT disk_ioctl (
	BYTE pdrv,		/* Physical drive nmuber (0..) */
	BYTE cmd,		/* Control code */
	void *buff		/* Buffer to send/receive control data */
)
{
	DRESULT res;
	int result;

	switch (pdrv) {
	case DEV_SD :

		// Process of the command for the RAM drive

		// Process of the command for the RAM drive
        switch(cmd)
        {
            case CTRL_SYNC:
                    res = RES_OK; 
                    break;
            case GET_SECTOR_SIZE:
                    *(DWORD*)buff = 512; 
                    res = RES_OK;
                    break;   
            case GET_BLOCK_SIZE:
                    *(WORD*)buff = SDCardInfo.CardBlockSize;
                    res = RES_OK;
                    break;   
            case GET_SECTOR_COUNT:
                    *(DWORD*)buff = SDCardInfo.CardCapacity/512;
                    res = RES_OK;
                    break;
            default:
                    res = RES_PARERR;
                    break;
        }
		return res;
	}
	return RES_PARERR;
}

//获得时间
//User defined function to give a current time to fatfs module      */
//31-25: Year(0-127 org.1980), 24-21: Month(1-12), 20-16: Day(1-31) */                                                                                                                                                                                                                                          
//15-11: Hour(0-23), 10-5: Minute(0-59), 4-0: Second(0-29 *2) */                                                                                                                                                                                                                                                
DWORD get_fattime (void)
{                
    return 0;
}

