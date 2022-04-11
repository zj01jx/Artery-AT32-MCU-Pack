 /**
  **************************************************************************
  * File   : PWR/SLEEP/main.c
  * Version: V1.3.0
  * Date   : 2021-03-18
  * Brief  : Main program body
  **************************************************************************
  * @brief     : 
  */
 
 /* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include "at32f4xx.h"
#include "at32_board.h"

/** @addtogroup AT32F413_StdPeriph_Examples
  * @{
  */

/** @addtogroup PWR_SLEEP
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
GPIO_InitType GPIO_InitStructure;
TMR_TimerBaseInitType  TMR_TMReBaseStructure;
NVIC_InitType NVIC_InitStructure = {0};

/* Private function prototypes -----------------------------------------------*/

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
  GPIO_StructInit(&GPIO_InitStructure);     
  AT32_Board_Init();
  AT32_LEDn_ON(LED2);
  AT32_LEDn_ON(LED3);
  AT32_LEDn_ON(LED4);

  RCC_APB1PeriphClockCmd(RCC_APB1PERIPH_PWR | RCC_APB1PERIPH_TMR2, ENABLE);

  TMR_TimeBaseStructInit(&TMR_TMReBaseStructure);
  TMR_TMReBaseStructure.TMR_Period = 65535;
  TMR_TMReBaseStructure.TMR_DIV = 5860;
  TMR_TMReBaseStructure.TMR_ClockDivision = 0;
  TMR_TMReBaseStructure.TMR_CounterMode = TMR_CounterDIR_Up;
  TMR_TimeBaseInit(TMR2, &TMR_TMReBaseStructure);

  TMR_INTConfig(TMR2, TMR_INT_Overflow, ENABLE);

  NVIC_InitStructure.NVIC_IRQChannel = TMR2_GLOBAL_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;

  NVIC_Init(&NVIC_InitStructure);
  TMR_Cmd(TMR2, ENABLE);
  while (1)
  {
    AT32_LEDn_OFF(LED2);
    systick_index = SysTick->CTRL;
    systick_index &= ~((uint32_t)0xFFFFFFFE);
    SysTick->CTRL &= (uint32_t)0xFFFFFFFE;
    
    PWR_EnterSleepMode(PWR_SLEEPEntry_WFI);
    SysTick->CTRL |= systick_index;
    AT32_LEDn_ON(LED2);
    for(index = 0; index < 500000; index++);
  }
}


/**
  * @}
  */ 

/**
  * @}
  */ 

