/**
  ******************************************************************************
  * File   : SRAM/extend_SRAM/EXTEND_SRAM/extend_SRAM.c
  * Version: V1.3.0
  * Date   : 2021-03-18
  * Brief  : This file contains the function extend_SRAM_test used to extend SRAM size
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "extend_SRAM.h" 
#include "at32f4xx.h"   
#include "stdio.h"

/** @addtogroup AT32F413_StdPeriph_Examples
  * @{
  */

 /** @addtogroup SRAM_Extended_SRAM
  * @{
  */

/* Private typedef -----------------------------------------------------------*/

#define TEST_RAM_SIZE  0x800

/* Private variables ---------------------------------------------------------*/



/* Private functions ---------------------------------------------------------*/
/**
  * @brief  To extend SRAM size
  * @param  None
  * @retval None
  */
void extend_SRAM(void)
{
/* Target set_SRAM_16K is selected */
#ifdef EXTEND_SRAM_16K
  // check if RAM has been set to 16K, if not, change EOPB0
  if(((UOPTB->EOPB0)&0x03)!=0x01)
  {
    /* Unlock Option Bytes Program Erase controller */
    FLASH_Unlock();
    /* Erase Option Bytes */
    FLASH_EraseUserOptionBytes();
    /* Change SRAM size to 16KB */
    FLASH_ProgramUserOptionByteData((uint32_t)&UOPTB->EOPB0,0xFD);
    NVIC_SystemReset();
  }
#endif

/* Target set_SRAM_32K is selected */
#ifdef EXTEND_SRAM_32K
  // check if RAM has been set to 32K, if not, change EOPB0
  if(((UOPTB->EOPB0)&0x03)!=0x03)
  {
    /* Unlock Option Bytes Program Erase controller */
    FLASH_Unlock();
    /* Erase Option Bytes */
    FLASH_EraseUserOptionBytes();
    /* Change SRAM size to 32KB */
    FLASH_ProgramUserOptionByteData((uint32_t)&UOPTB->EOPB0,0xFF);
    NVIC_SystemReset();
  }
 #endif

/* Target set_SRAM_64K is selected */
#ifdef EXTEND_SRAM_64K
  // check if RAM has been set to 64K, if not, change EOPB0
  if(((UOPTB->EOPB0)&0x01))  
  {
    /* Unlock Option Bytes Program Erase controller */
    FLASH_Unlock();
    /* Erase Option Bytes */
    FLASH_EraseUserOptionBytes();
    /* Change SRAM size to 64KB */
    FLASH_ProgramUserOptionByteData((uint32_t)&UOPTB->EOPB0,0xFC);
    NVIC_SystemReset();
  }
#endif
}

/**
  * @}
  */ 

/**
  * @}
  */ 
  
