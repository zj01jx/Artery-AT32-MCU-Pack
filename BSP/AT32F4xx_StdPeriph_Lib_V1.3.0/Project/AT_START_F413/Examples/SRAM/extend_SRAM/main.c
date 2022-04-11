/**
  ******************************************************************************
  * File   : SRAM/extend_SRAM/main.c 
  * Version: V1.3.0
  * Date   : 2021-03-18
  * Brief  : Main program body
  ******************************************************************************
  */ 
  
/* Includes ------------------------------------------------------------------*/
#include "extend_SRAM.h"
#include "at32f4xx.h"
#include "at32_board.h"
#include <stdio.h>

/** @addtogroup AT32F413_StdPeriph_Examples
  * @{
  */

 /** @addtogroup SRAM_Extended_SRAM
  * @{
  */

/* Private functions ---------------------------------------------------------*/
/**
  * @brief  Main program
  * @param  None
  * @retval None
  */
int main(void)
{ 
  /* USART1 configured as follow:
        - BaudRate = 115200 baud  
        - Word Length = 8 Bits
        - One Stop Bit
        - No parity
        - Hardware flow control disabled (RTS and CTS signals)
        - Receive and transmit enabled
  */
  UART_Print_Init(115200);
  
  /* Check EOPB0 */
 	
#ifdef EXTEND_SRAM_16K

  if(((UOPTB->EOPB0)&0x03)==0x01)
  {
  	  printf("Extend 16KB SRAM success.\r\n");
  } else {
  	  printf("Extend 16KB SRAM failed.\r\n");
  }		  
#endif

#ifdef EXTEND_SRAM_32K

  if(((UOPTB->EOPB0)&0x03)==0x03)
  {
  	  printf("Extend 32KB SRAM success.\r\n");
  } else {
  	  printf("Extend 32KB SRAM failed.\r\n");
  }		  
#endif

#ifdef EXTEND_SRAM_64K

  if(!((UOPTB->EOPB0)&0x01))
  {
  	 printf("Extend 64KB SRAM success.\r\n");
  } else {
  	 printf("Extend 64KB SRAM failed.\r\n");
  }		  
#endif

  while(1)
  {
  }   
}


/**
  * @}
  */ 

/**
  * @}
  */ 
  
