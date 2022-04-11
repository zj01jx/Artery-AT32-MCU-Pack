 /**
  **************************************************************************
  * File   : PWR/SLEEP_USART/main.c
  * Version: V1.3.0
  * Date   : 2021-03-18
  * Brief  : Main program body
  **************************************************************************
  */
 
 /* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include "at32f4xx.h"
#include "at32_board.h"

/** @addtogroup AT32F415_StdPeriph_Examples
  * @{
  */

/** @addtogroup PWR_SLEEP_USART
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/
NVIC_InitType NVIC_InitStructure;
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
void USART1_NVIC_Config(void);

/* Private functions ---------------------------------------------------------*/

/**
 *  @brief  main function
 *  @param  None
 *  @retval None
 */
int main(void)
{
  uint32_t index = 0;
  uint32_t systick_index = 0;
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
  RCC_APB1PeriphClockCmd(RCC_APB1PERIPH_PWR, ENABLE);
  AT32_Board_Init();
  UART_Print_Init(115200);
  USART1_NVIC_Config();
  AT32_LEDn_ON(LED2);
  AT32_LEDn_ON(LED3);
  AT32_LEDn_ON(LED4);
  printf("Start\r\n");
  while (1)
  {
    AT32_LEDn_OFF(LED2);
    AT32_LEDn_OFF(LED3);
    printf("Enter Sleep Mode\r\n");
    systick_index = SysTick->CTRL;
    systick_index &= ~((uint32_t)0xFFFFFFFE);
    SysTick->CTRL &= (uint32_t)0xFFFFFFFE;

    PWR_EnterSleepMode(PWR_SLEEPEntry_WFI);
    SysTick->CTRL |= systick_index;
    printf("Wakeup From Sleepmode by USART\r\n");
    AT32_LEDn_ON(LED2);
    for(index = 0; index < 500000; index++);
  }
}

void USART1_NVIC_Config(void)
{
  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0 ;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}

/**
  * @}
  */ 

/**
  * @}
  */ 

