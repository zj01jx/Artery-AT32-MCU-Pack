/**
  ******************************************************************************
  * File   : ERTC/ERTC_LSI/at32f4xx_it.c 
  * Version: V1.3.0
  * Date   : 2021-03-18
  * Brief  : Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and peripherals
  *          interrupt service routine.
  ******************************************************************************
  */ 

/* Includes ------------------------------------------------------------------*/
#include "at32f4xx.h"
#include "at32f4xx_it.h"
#include "at32_board.h"


/** @addtogroup AT32F415_StdPeriph_Examples
  * @{
  */

/** @addtogroup ERTC_LSI
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
extern __IO uint32_t uwPeriodValue;
extern __IO uint32_t uwCaptureNumber;
uint16_t tmpCC4[2] = {0, 0};

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
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
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

/**
  * @brief  This function handles ERTC Wakeup global interrupt request.
  * @param  None
  * @retval None
  */
void ERTC_WKUP_IRQHandler(void)
{
  if(ERTC_GetINTStatus(ERTC_INT_WAT) != RESET)
  {
    /* Toggle on LED2 */
    AT32_LEDn_Toggle(LED2);
    ERTC_ClearINTPendingBINT(ERTC_INT_WAT);
    EXTI_ClearIntPendingBit(EXTI_Line22);
    printf("wake int\r\n");
  } 
}

/**
  * @brief  This function handles TMR5 global interrupt request.
  * @param  None
  * @retval None
  */
void TMR5_GLOBAL_IRQHandler(void)
{
  if (TMR_GetINTStatus(TMR5, TMR_INT_CC4) != RESET)
  {    
    /* Get the Input Capture value */
    tmpCC4[uwCaptureNumber++] = TMR_GetCapture4(TMR5);
   
    /* Clear CC4 Interrupt pending bit */
    TMR_ClearITPendingBit(TMR5, TMR_INT_CC4);

    if (uwCaptureNumber >= 2)
    {
      /* Compute the period length */
      uwPeriodValue = (uint16_t)(0xFFFF - tmpCC4[0] + tmpCC4[1] + 1);
    }
  }
}


/**
  * @}
  */ 

/**
  * @}
  */ 

