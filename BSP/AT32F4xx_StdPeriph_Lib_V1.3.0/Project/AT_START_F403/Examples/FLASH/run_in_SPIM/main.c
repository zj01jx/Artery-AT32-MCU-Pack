/**
  ******************************************************************************
  * File   : FLASH/run_in_SPIM/main.c 
  * Version: V1.3.0
  * Date   : 2021-03-18
  * Brief  : Main program body
  ******************************************************************************
  */ 
  
/* Includes ------------------------------------------------------------------*/
#include "run_in_SPIM.h"
#include "at32f4xx.h"
#include "at32_board.h"
#include <stdio.h>

/** @addtogroup AT32F403_StdPeriph_Examples
  * @{
  */

/** @addtogroup FLASH_Run_In_SPIM
  * @{
  */

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Configures the ext.flash
  * @param  None
  * @retval None
  */
void FLASH_InitExtFlash(void)
{
  GPIO_InitType GPIO_InitStructure;
  
  /* Enable ext.flash GPIO clock */
  RCC_APB2PeriphClockCmd(RCC_APB2PERIPH_AFIO|RCC_APB2PERIPH_GPIOA|RCC_APB2PERIPH_GPIOB, ENABLE);
  
  /* Configure ext.flash pin */
  GPIO_StructInit(&GPIO_InitStructure);
  GPIO_InitStructure.GPIO_Pins = GPIO_Pins_8|GPIO_Pins_11|GPIO_Pins_12;
  GPIO_InitStructure.GPIO_MaxSpeed = GPIO_MaxSpeed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  
  GPIO_InitStructure.GPIO_Pins = GPIO_Pins_1|GPIO_Pins_6|GPIO_Pins_7;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
  
  GPIO_PinsRemapConfig(GPIO_Remap_EXT_FLASH, ENABLE);
  
  /* In this example, use on-board EN25QH128A as ext.flash */
  FLASH->B3SEL = FLASH_BANK3_TYPE2;
  
  /* Unlock the ext.flash program erase controller */  
  while (BIT_READ(FLASH->STS3, FLASH_STS_BSY));
  FLASH->FCKEY3 = FLASH_KEY1;
  FLASH->FCKEY3 = FLASH_KEY2;
  while (BIT_READ(FLASH->CTRL3, FLASH_CTRL_LCK));
  
  /* If the data written to ext.flash need to be scrambled, please specify the scrambled range */
  FLASH->DA = 0;  
  
  return;
}

/**
  * @brief  Main program
  * @param  None
  * @retval None
  */
int main(void)
{ 

  UART_Print_Init(115200);
  printf("this message is running in bank1.\r\n");
  
  /* Configures the ext.flash */
  FLASH_InitExtFlash();
  
  /* Check the LED toggle in SPIM */
  printf("check the LED toggle in SPIM.\r\n");
  SPIM_run();    
}

/**
  * @}
  */ 

/**
  * @}
  */ 

