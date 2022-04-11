/**
  ******************************************************************************
  * File   : TMR/TMR_MCO_TO_TIMER10_CH1/at32f4xx_it.c
  * Version: V1.3.0
  * Date   : 2021-03-18
  * Brief  : Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and peripherals
  *          interrupt service routine.
  ******************************************************************************
  */


/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include "at32f4xx_it.h"

/** @addtogroup AT32F413_StdPeriph_Examples
  * @{
  */

/** @addtogroup TMR_MCO_TO_TIMER10_CH1
  * @{
  */ 

extern int Sys_Counter;


/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
extern __IO uint16_t IC10ReadValue1, IC10ReadValue2;
extern __IO uint32_t Capture;
extern __IO uint16_t CaptureNumber ;
extern __IO uint32_t TMR10Freq ;
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
  {}
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
  {}
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
  {}
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
  {}
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{}

/**
  * @brief  This function handles PendSV_Handler exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
  Sys_Counter++;
}

/******************************************************************************/
/*            AT32F4xx Peripherals Interrupt Handlers                        */
/******************************************************************************/
/**
  * @brief  This function handles TMR10 global interrupt request.
  * @param  None
  * @retval None
  */
void TMR1_OV_TMR10_IRQHandler(void)
{ 
    /* Clear TMR10 Capture compare interrupt pending bit */
    TMR10->STS = (uint16_t)~TMR_INT_CC1;
    if(CaptureNumber == 0)
    {
      /* Get the Input Capture value */
      IC10ReadValue1 = TMR10->CC1;
      CaptureNumber = 1;
    }
    else if(CaptureNumber == 1)
    {
      /* Get the Input Capture value */
      IC10ReadValue2 = TMR10->CC1; 
      CaptureNumber = 2;
      TMR10->DIE &= (uint16_t)~TMR_INT_CC1;
    }
    if( CaptureNumber == 2)
    {
      Capture = (IC10ReadValue2 - IC10ReadValue1); 
      /* Frequency computation */ 
      TMR10Freq = (uint32_t) SystemCoreClock / Capture;
      CaptureNumber = 0;
      printf("%d\r\n",TMR10Freq);
      TMR10Freq = 0;
      TMR10->DIE |= TMR_INT_CC1;
    }
}


/**
  * @}
  */ 

/**
  * @}
  */


