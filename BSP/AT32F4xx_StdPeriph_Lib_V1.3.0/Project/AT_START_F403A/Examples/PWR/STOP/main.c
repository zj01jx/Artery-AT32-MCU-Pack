 /**
  **************************************************************************
  * File   : PWR/STOP/main.c
  * Version: V1.3.0
  * Date   : 2021-03-18
  * Brief  : Main program body
  **************************************************************************
  */
 
 /* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include "at32f4xx.h"
#include "at32_board.h"

/** @addtogroup AT32F403A_StdPeriph_Examples
  * @{
  */

/** @addtogroup PWR_STOP
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
GPIO_InitType GPIO_InitStructure;
EXTI_InitType EXTI_InitStructure;
NVIC_InitType NVIC_InitStructure = {0};
ErrorStatus HSEStartUpStatus;

/* Private function prototypes -----------------------------------------------*/
void SYSCLKConfig_STOP(void);
void EXTI_Configuration(void);
void RTC_Configuration(void);
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
  uint32_t systick_index = 0;
  GPIO_StructInit(&GPIO_InitStructure);
  EXTI_StructInit(&EXTI_InitStructure);      
  AT32_Board_Init();
  AT32_LEDn_ON(LED2);
  AT32_LEDn_ON(LED3);
  AT32_LEDn_ON(LED4);
  
  RCC_APB1PeriphClockCmd(RCC_APB1PERIPH_PWR | RCC_APB1PERIPH_BKP, ENABLE);
  EXTI_Configuration();
  RTC_Configuration();
  NVIC_Configuration();
  while (1)
  {
    RTC_ClearFlag(RTC_FLAG_PACE);
    while(RTC_GetFlagStatus(RTC_FLAG_PACE) == RESET);
    RTC_SetAlarmValue(RTC_GetCounter()+ 3);
    RTC_WaitForLastTask();
    AT32_LEDn_OFF(LED2);
    systick_index = SysTick->CTRL;
    systick_index &= ~((uint32_t)0xFFFFFFFE);
    SysTick->CTRL &= (uint32_t)0xFFFFFFFE;
    PWR_EnterSTOPMode(PWR_Regulator_ON, PWR_STOPEntry_WFI);
    SysTick->CTRL |= systick_index;
    SYSCLKConfig_STOP();
    AT32_LEDn_ON(LED2);
    for(index = 0; index < 500000; index++);
  }
}

/**
  * @brief  Configures system clock after wake-up from STOP: enable HSE, PLL and select PLL as system clock source.
  * @param  None
  * @retval None
  */
void SYSCLKConfig_STOP(void)
{
  RCC_HSEConfig(RCC_HSE_ENABLE);
  HSEStartUpStatus = RCC_WaitForHSEStable();
  if(HSEStartUpStatus == SUCCESS)
  {
    RCC_PLLCmd(ENABLE);
    while(RCC_GetFlagStatus(RCC_FLAG_PLLSTBL) == RESET)
    {
    }
    RCC_SYSCLKConfig(RCC_SYSCLKSelction_PLL);
    while(RCC_GetSYSCLKSelction() != 0x08)
    {
    }
  }
}

/**
  * @brief  Configures EXTI Line 17(RTC Alarm) to generate an interrupt on rising edge.
  * @param  None
  * @retval None
  */
void EXTI_Configuration(void)
{
  EXTI_ClearIntPendingBit(EXTI_Line17);
  EXTI_InitStructure.EXTI_Line = EXTI_Line17;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
  EXTI_InitStructure.EXTI_LineEnable = ENABLE;
  EXTI_Init(&EXTI_InitStructure);
}

/**
  * @brief  Configures RTC clock source and prescaler.
  * @param  None
  * @retval None
  */
void RTC_Configuration(void)
{
  PWR_BackupAccessCtrl(ENABLE);
  BKP_Reset();
  RCC_LSICmd(ENABLE);
  while(RCC_GetFlagStatus(RCC_FLAG_LSISTBL) == RESET)
  {
  }
  RCC_RTCCLKConfig(RCC_RTCCLKSelection_LSI);
  RCC_RTCCLKCmd(ENABLE);

  RTC_WaitForSynchro();
  RTC_SetDIV(32767);
  RTC_WaitForLastTask();
  RTC_INTConfig(RTC_INT_ALA, ENABLE);
  RTC_WaitForLastTask();
}

/**
  * @brief  Configures NVIC and Vector Table base location.
  * @param  None
  * @retval None
  */
void NVIC_Configuration(void)
{
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
  NVIC_InitStructure.NVIC_IRQChannel = RTCAlarm_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
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

