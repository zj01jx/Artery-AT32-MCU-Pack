#include "flash.h"
#include "usart.h"
#include "iap.h"

void FLASH_Write_2KB(u32 WriteAddr, u8 *pBuffer) 
{
	u16 i, WriteData;	
	
	FLASH_Unlock();
	FLASH_ErasePage(WriteAddr);
 if(FLASH_SIZE<0x100) //1KB/P
	  FLASH_ErasePage(WriteAddr+1024);
	for(i=0; i<2048; i+=2)
	{
		WriteData = (pBuffer[i+1]<<8) + pBuffer[i];
		FLASH_ProgramHalfWord(WriteAddr, WriteData);
		WriteAddr+=2;
	}
	
	FLASH_Lock();
}

u8 FLASH_Read_Upgrade_Flag(void)
{
	if((*(u32*)IAP_UPGRADE_FLAG_ADDR)==IAP_UPGRADE_FLAG)
		return SET;
	else
		return RESET;
}
