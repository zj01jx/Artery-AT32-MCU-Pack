#include "flash.h"
#include "usart.h"
#include "iap.h"

void FLASH_Write_2KB(u32 WriteAddr, u8 *pBuffer) 
{
	u16 i, WriteData;	
	
	FLASH_Unlock();
	FLASH_ErasePage(WriteAddr);
#if (PAGE_SIZE==1024)
	FLASH_ErasePage(WriteAddr+1024);
#endif

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

/**
  * @brief  This function writes a data buffer in flash (data are 32-bit aligned).
  * @note   After writing data buffer, the flash content is checked.
  * @param  FlashAddress: start address for writing data buffer
  * @param  Data: pointer on data buffer
  * @param  DataLength: length of data buffer (unit is 32-bit word)   
  * @retval 0: Data successfully written to Flash memory
  *         1: Error occurred while writing data in Flash memory
  *         2: Written Data in flash memory is different from expected one
  */
uint32_t FLASH_If_Write(__IO uint32_t* FlashAddress, uint32_t* Data ,uint16_t DataLength)
{
  uint32_t i = 0;

  for (i = 0; (i < DataLength) && (*FlashAddress <= (USER_FLASH_END_ADDRESS-4)); i++)
  {
    /* Device voltage range supposed to be [2.7V to 3.6V], the operation will
       be done by word */ 
    if (FLASH_ProgramWord(*FlashAddress, *(uint32_t*)(Data+i)) == FLASH_PRC_DONE)
    {
     /* Check the written value */
      if (*(uint32_t*)*FlashAddress != *(uint32_t*)(Data+i))
      {
        /* Flash content doesn't match SRAM content */
        return(2);
      }
      /* Increment FLASH destination address */
      *FlashAddress += 4;
    }
    else
    {
      /* Error occurred while writing data in Flash memory */
      return (1);
    }
  }

  return (0);
}
