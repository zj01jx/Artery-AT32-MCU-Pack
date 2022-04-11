 /**
  ******************************************************************************
  * File   : TMR/TMR_MCO_TO_TIMER10_CH1/main.c 
  * Version: V1.3.0
  * Date   : 2021-03-18
  * Brief  : Main program body
  ******************************************************************************
  */ 

/* Includes ------------------------------------------------------------------*/
#include "at32f4xx.h"
#include <stdio.h>
#include "at32_board.h"


/** @addtogroup AT32F413_StdPeriph_Examples
  * @{
  */

/** @addtogroup TMR_MCO_TO_TIMER10_CH1
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
TMR_ICInitType  TMR_ICInitStructure;
TMR_TimerBaseInitType  TMR_TimerBaseInitStr;
__IO uint32_t TMR10Freq = 0;
__IO uint32_t Sys_Counter = 0;
__IO uint16_t CaptureNumber = 0;
__IO uint16_t IC10ReadValue1 = 0, IC10ReadValue2 = 0;
__IO uint32_t Capture = 0;
/* Private function prototypes -----------------------------------------------*/
void RCC_Configuration(void);
void GPIO_Configuration(void);
void NVIC_Configuration(void);
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program
  * @param  None
  * @retval None
  */
int main(void)
{
  /* System Clocks Configuration */
  RCC_Configuration();

  /* NVIC configuration */
  NVIC_Configuration();
  
  /* Configure the GPIO ports */
  GPIO_Configuration();
  
  /* Board.c init */
  UART_Print_Init(115200);
  
  /* MCO to tmr10*/
  RCC_MCO2TMR10(ENABLE);
  
  /* TMR10 configuration: Input Capture mode ---------------------
     The external signal is connected to TMR10 CH1 pin  
     The Rising edge is used as active edge,
     The TMR10 CCR1 is used to compute the frequency value 
  ------------------------------------------------------------ */
  TMR_TimeBaseStructInit(&TMR_TimerBaseInitStr);
  TMR_TimerBaseInitStr.TMR_CounterMode = TMR_CounterDIR_Up;
  TMR_TimerBaseInitStr.TMR_DIV = 18;
  TMR_TimerBaseInitStr.TMR_Period = 0xFFFF;
  TMR_TimeBaseInit(TMR10,&TMR_TimerBaseInitStr);
  
  TMR_ICStructInit(&TMR_ICInitStructure);
  TMR_ICInitStructure.TMR_Channel = TMR_Channel_1;
  TMR_ICInitStructure.TMR_ICPolarity = TMR_ICPolarity_Rising;
  TMR_ICInitStructure.TMR_ICSelection = TMR_ICSelection_DirectTI;
  TMR_ICInitStructure.TMR_ICDIV = TMR_ICDIV_DIV1;
  TMR_ICInitStructure.TMR_ICFilter = 0x0;
  TMR_ICInit(TMR10, &TMR_ICInitStructure);
  /* TMR enable counter */
  TMR_Cmd(TMR10, ENABLE);

  /* Enable the CC1Interrupt Request */
  TMR_INTConfig(TMR10, TMR_INT_CC1, ENABLE);

  while (1)
  {
  }
}
/**
  * @brief  Configures the different system clocks.
  * @param  None
  * @retval None
  */
void RCC_Configuration(void)
{
  /* TMR10 clock enable */
  RCC_APB2PeriphClockCmd(RCC_APB2PERIPH_TMR10, ENABLE);

  /* GPIOA and GPIOB clock enable */
  RCC_APB2PeriphClockCmd(RCC_APB2PERIPH_GPIOA, ENABLE);
  
  /* PWR and BKP clock enable */
  RCC_APB1PeriphClockCmd(RCC_APB1PERIPH_PWR,ENABLE);
}

/**
  * @brief  Configure the GPIOD Pins.
  * @param  None
  * @retval None
  */
void GPIO_Configuration(void)
{
  GPIO_InitType GPIO_InitStructure;

  /* MCO clock output pin */
  GPIO_InitStructure.GPIO_Pins =  GPIO_Pins_8;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_MaxSpeed = GPIO_MaxSpeed_50MHz;

  GPIO_Init(GPIOA, &GPIO_InitStructure);
  RCC_CLKOUTConfig(RCC_CLKOUT_PLL_Div4,RCC_MCOPRE_1);
}
/**
  * @brief  Configure the nested vectored interrupt controller.
  * @param  None
  * @retval None
  */
void NVIC_Configuration(void)
{
  NVIC_InitType NVIC_InitStructure;

  /* Enable the TMR3 global Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = TMR1_OV_TMR10_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}

#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  while (1)
  {}
}

#endif

/**
  * @}
  */ 

/**
  * @}
  */

