/**
  ******************************************************************************
  * File   : run_in_SysMem/SysMem/run_in_SysMem.c
  * Version: V1.3.0
  * Date   : 2021-03-18
  * Brief  : This file contains the function SysMem_run used to check the LED toggle in SysMem
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "run_in_SysMem.h"
#include "at32f4xx.h"  
#include "at32_board.h"

/** @addtogroup AT32F415_StdPeriph_Examples
  * @{
  */

/** @addtogroup SysMem_AP_EXAMPLE
  * @{
  */

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Check the LED toggle in SysMem
  * @param  None
  * @retval None
  */
void SysMem_run(void)
{
  /* Init LED */
  AT32_Board_Init();    
  while(1)
  {
    /* Toggle LED2 */
    AT32_LEDn_Toggle(LED2);
    Delay_ms(100);
  }
}


/**
  * @}
  */ 

/**
  * @}
  */ 
  
