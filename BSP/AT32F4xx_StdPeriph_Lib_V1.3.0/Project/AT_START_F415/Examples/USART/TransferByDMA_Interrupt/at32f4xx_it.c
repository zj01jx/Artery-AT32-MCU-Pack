/**
  ******************************************************************************
  * File   : USART/DMA_Polling/at32f4xx_it.c
  * Version: V1.3.0
  * Date   : 2021-03-18
  * Brief  : Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and peripherals
  *          interrupt service routine.
  ******************************************************************************
  */ 

/* Includes ------------------------------------------------------------------*/
#include "at32f4xx_it.h"
extern uint8_t USART2_DMA_Status;
extern uint8_t USART3_DMA_Status;
/** @addtogroup AT32F415_StdPeriph_Examples
  * @{
  */

/** @addtogroup USART_DMA_Polling
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSV_Handler exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
}

void DMA1_Channel2_IRQHandler(void)
{
  if(DMA_GetFlagStatus(DMA1_FLAG_TC2))
  {
    DMA_ClearFlag(DMA1_FLAG_TC2);
    DMA_ChannelEnable(DMA1_Channel2, DISABLE);
  }
}

void DMA1_Channel3_IRQHandler(void)
{
  if(DMA_GetFlagStatus(DMA1_FLAG_TC3))
  {
      USART3_DMA_Status = 1;
      DMA_ClearFlag(DMA1_FLAG_TC3);
      DMA_ChannelEnable(DMA1_Channel3, DISABLE);
  }
}

void DMA1_Channel6_IRQHandler(void)
{
  if(DMA_GetFlagStatus(DMA1_FLAG_TC6))
  {
    USART2_DMA_Status = 1;
    DMA_ClearFlag(DMA1_FLAG_TC6);
    DMA_ChannelEnable(DMA1_Channel6, DISABLE);
  }
}

void DMA1_Channel7_IRQHandler(void)
{
  if(DMA_GetFlagStatus(DMA1_FLAG_TC7))
  {
    DMA_ClearFlag(DMA1_FLAG_TC7);
    DMA_ChannelEnable(DMA1_Channel7, DISABLE);
  }
}
/**
  * @}
  */ 

/**
  * @}
  */ 




