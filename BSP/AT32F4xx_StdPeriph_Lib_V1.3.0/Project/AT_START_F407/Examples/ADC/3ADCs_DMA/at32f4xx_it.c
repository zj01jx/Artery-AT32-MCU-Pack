/**
  ******************************************************************************
  * File   : ADC/3ADCs_DMA/at32f4xx_it.c
  * Version: V1.3.0
  * Date   : 2021-03-18
  * Brief  : Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and peripherals
  *          interrupt service routine.
  ******************************************************************************
  */ 

/* Includes ------------------------------------------------------------------*/
#include "at32f4xx_it.h"
#include "at32_board.h"
extern __IO uint32_t Adc1_Trigger_Times;
extern __IO uint32_t Adc3_Trigger_Times;
extern __IO uint32_t ADC1_RegularConvertedValueTab[3];
extern __IO uint16_t ADC3_RegularConvertedValueTab[3];
/** @addtogroup AT32F407_StdPeriph_Examples
  * @{
  */

/** @addtogroup ADC_3ADCs_DMA
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

void DMA1_Channel1_IRQHandler(void)
{
  if(DMA_GetFlagStatus(DMA1_FLAG_TC1)!= RESET) 
  {
    Adc1_Trigger_Times++;
    DMA_ClearFlag(DMA1_FLAG_TC1);
    printf("ADC1_Trigger_Times = %d\r\n",Adc1_Trigger_Times);
    printf("ADC1_RegularConvertedValueTab[0] = 0x%x\r\n",ADC1_RegularConvertedValueTab[0]);
    printf("ADC1_RegularConvertedValueTab[1] = 0x%x\r\n",ADC1_RegularConvertedValueTab[1]);
    printf("ADC1_RegularConvertedValueTab[2] = 0x%x\r\n",ADC1_RegularConvertedValueTab[2]);
  }
}

void DMA2_Channel4_5_IRQHandler(void)
{
  if(DMA_GetFlagStatus(DMA2_FLAG_TC5)!= RESET) 
  {
    Adc3_Trigger_Times++;
    DMA_ClearFlag(DMA2_FLAG_TC5);
    printf("ADC3_Trigger_Times = %d\r\n",Adc3_Trigger_Times);
    printf("ADC3_RegularConvertedValueTab[0] = 0x%x\r\n",ADC3_RegularConvertedValueTab[0]);
    printf("ADC3_RegularConvertedValueTab[1] = 0x%x\r\n",ADC3_RegularConvertedValueTab[1]);
    printf("ADC3_RegularConvertedValueTab[2] = 0x%x\r\n",ADC3_RegularConvertedValueTab[2]);
  }
}

/**
  * @}
  */ 

/**
  * @}
  */ 

