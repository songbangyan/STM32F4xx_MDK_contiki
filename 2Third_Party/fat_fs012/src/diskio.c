/*-----------------------------------------------------------------------*/
/* Low level disk I/O module skeleton for FatFs     (C)ChaN, 2016        */
/*-----------------------------------------------------------------------*/
/* If a working storage control module is available, it should be        */
/* attached to the FatFs via a glue function rather than modifying it.   */
/* This is an example of glue functions to attach various exsisting      */
/* storage control modules to the FatFs module with a defined API.       */
/*-----------------------------------------------------------------------*/

#include "diskio.h"
#include "stm32f4xx.h"
#include "ffconf.h"
#include "stm324xg_eval_sdio_sd.h"

/* Definitions of physical drive number for each drive */
#define ATA		0	/* Example: Map ATA harddisk to physical drive 0 */
#define MMC		1	/* Example: Map MMC/SD card to physical drive 1 */
#define USB		2	/* Example: Map USB MSD to physical drive 2 */


/*-----------------------------------------------------------------------*/
/* Get Drive Status                                                      */
/*-----------------------------------------------------------------------*/
DSTATUS disk_status (
	BYTE drv		/* Physical drive nmuber (0) */
)
{
	if (drv) return STA_NOINIT;		/* Supports only single drive */
	return 0;
}


/*-----------------------------------------------------------------------*/
/* Inidialize a Drive                                                    */
/*-----------------------------------------------------------------------*/

DSTATUS disk_initialize (
	BYTE drv				/* Physical drive nmuber (0..) */
)
{
  NVIC_InitTypeDef NVIC_InitStructure;
  SD_Error res = SD_OK;

  /* Configure the NVIC Preemption Priority Bits */
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);

  NVIC_InitStructure.NVIC_IRQChannel = SDIO_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure); 

  NVIC_InitStructure.NVIC_IRQChannel = SD_SDIO_DMA_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  NVIC_Init(&NVIC_InitStructure);

  res =  SD_Init(); 

  if(res == SD_OK)
  {
    res = (SD_Error)0x0;
  }
  return ((DSTATUS)res);
}




/*-----------------------------------------------------------------------*/
/* Read Sector(s)                                                        */
/*-----------------------------------------------------------------------*/

DRESULT disk_read (
	BYTE pdrv,		/* Physical drive nmuber to identify the drive */
	BYTE *buff,		/* Data buffer to store read data */
	DWORD sector,	/* Sector address in LBA */
	UINT count		/* Number of sectors to read */
)
{
	SD_Error status = SD_OK;

	SD_ReadMultiBlocks(buff, sector << 9, 512, 1);

	/* Check if the Transfer is finished */
	status =  SD_WaitReadOperation();
	while(SD_GetStatus() != SD_TRANSFER_OK);

	if (status == SD_OK)
	{
		return RES_OK;
	}
	else
	{
		return RES_ERROR;
	}
}



/*-----------------------------------------------------------------------*/
/* Write Sector(s)                                                       */
/*-----------------------------------------------------------------------*/

DRESULT disk_write (
	BYTE pdrv,			/* Physical drive nmuber to identify the drive */
	const BYTE *buff,	/* Data to be written */
	DWORD sector,		/* Sector address in LBA */
	UINT count			/* Number of sectors to write */
)
{
	SD_Error status = SD_OK;

	SD_WriteMultiBlocks((BYTE *)buff, sector << 9, 512, 1);

	/* Check if the Transfer is finished */
	status = SD_WaitWriteOperation();
	while(SD_GetStatus() != SD_TRANSFER_OK);     

	if (status == SD_OK)
	{
		return RES_OK;
	}
	else
	{
		return RES_ERROR;
	}
}

DWORD get_fattime ()
{
	return	((2006UL-1980) << 25)	      // Year = 2006
			| (2UL << 21)	      // Month = Feb
			| (9UL << 16)	      // Day = 9
			| (22U << 11)	      // Hour = 22
			| (30U << 5)	      // Min = 30
			| (0U >> 1)	      // Sec = 0
			;
}


/*-----------------------------------------------------------------------*/
/* Miscellaneous Functions                                               */
/*-----------------------------------------------------------------------*/

DRESULT disk_ioctl (
	BYTE pdrv,		/* Physical drive nmuber (0..) */
	BYTE cmd,		/* Control code */
	void *buff		/* Buffer to send/receive control data */
)
{
	DRESULT res = RES_OK;
	switch (cmd) {
	

	case GET_SECTOR_COUNT :	  // Get number of sectors on the disk (DWORD)
		*(DWORD*)buff = 131072;	// 4*1024*32 = 131072
		res = RES_OK;
		break;

	case GET_SECTOR_SIZE :	  // Get R/W sector size (WORD) 
		*(WORD*)buff = 512;
		res = RES_OK;
		break;

	case GET_BLOCK_SIZE :	    // Get erase block size in unit of sector (DWORD)
		*(DWORD*)buff = 32;
		res = RES_OK;
		}
	
return res;
}

