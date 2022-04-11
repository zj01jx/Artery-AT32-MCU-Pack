/**
  **************************************************************************
  * File   : PWR/PVD/main.c
  * Version: V1.3.0
  * Date   : 2021-03-18
  * Brief  : Main program body
  **************************************************************************
  * @brief     : Initializes and turn on LED.Configure PVD and EXTI.
  *              Then if monitor a PVD event,an interrupt on PVD will happen,and it will cause a Toggle on LED2 and LED3 and LED4.
  */
 
 /* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include "at32f4xx.h"
#include "at32_board.h"

/** @addtogroup AT32F413_StdPeriph_Examples
  * @{
  */

/** @addtogroup PWR_PVD
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
GPIO_InitType GPIO_InitStructure;
EXTI_InitType EXTI_InitStructure;
NVIC_InitType NVIC_InitStructure = {0};

/* Private function prototypes -----------------------------------------------*/
void EXTI_Configuration(void);
void NVIC_Configuration(void);

/* Private functions ---------------------------------------------------------*/

/**
 *  @brief  main function
 *  @param  None
 *  @retval None
 */
int main(void)
{
  uint32_t index = 0;
  GPIO_StructInit(&GPIO_InitStructure);
  EXTI_StructInit(&EXTI_InitStructure);
  AT32_Board_Init();
  AT32_LEDn_ON(LED2);
  AT32_LEDn_ON(LED3);
  AT32_LEDn_ON(LED4);
  
  RCC_APB1PeriphClockCmd(RCC_APB1PERIPH_PWR | RCC_APB1PERIPH_BKP, ENABLE);
  PWR_PVDLevelConfig(PWR_PVDS_2V9);
  PWR_PVDCtrl(ENABLE);

  EXTI_Configuration();
  for(index = 0; index < 2000; index++);

  EXTI_ClearIntPendingBit(EXTI_Line16);
  NVIC_ClearPendingIRQ(PVD_IRQn);
  NVIC_Configuration();
  while (1)
  {
  }
}

/**
  * @brief  EXTI Configuration.Configures EXTI Line 16.
  * @param  None
  * @retval None
  */
void EXTI_Configuration(void)
{
  EXTI_ClearIntPendingBit(EXTI_Line16);
  EXTI_InitStructure.EXTI_Line        = EXTI_Line16;
  EXTI_InitStructure.EXTI_Mode        = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger     = EXTI_Trigger_Rising_Falling;
  EXTI_InitStructure.EXTI_LineEnable  = ENABLE;
  EXTI_Init(&EXTI_InitStructure);
}

/**
  * @brief  NVIC Configuration.Configures NVIC and Vector Table base location.
  * @param  None
  * @retval None
  */
void NVIC_Configuration(void)
{
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
  NVIC_InitStructure.NVIC_IRQChannel                      = PVD_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority    = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority           = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd                   = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}

/**
  * @}
  */ 

/**
  * @}
  */ 

