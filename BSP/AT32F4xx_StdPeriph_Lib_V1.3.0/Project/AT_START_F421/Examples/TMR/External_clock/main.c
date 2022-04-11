 /**
   ******************************************************************************
   * File   : TMR/External_Clock/main.c 
  * Version: V1.3.0
  * Date   : 2021-03-18
   * Brief  : Main program body
   ******************************************************************************
  */ 

#include "at32f4xx.h"

/** @addtogroup AT32F421_StdPeriph_Examples
  * @{
  */

/** @addtogroup TMR_External_Clock
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
TMR_ICInitType  TMR_ICInitStructure = {0};
TMR_TimerBaseInitType  TMR_TimerBaseInitStructure = {0};
TMR_OCInitType  TMR_OCInitStructure = {0};

/* Private function prototypes -----------------------------------------------*/
void RCC_Configuration(void);
void GPIO_Configuration(void);
void NVIC_Configuration(void);
/**
 **************************************************************************
 * File   : main.c
  * Version: V1.3.0
  * Date   : 2021-03-18
 * Brief  : Main program body
 **************************************************************************
 */


/* Private functions ---------------------------------------------------------*/

/**
  * @brief   Main program
  * @param  None
  * @retval None
  */
int main(void)
{
  /*!< At this stage the microcontroller clock setting is already configured,
       this is done through SystemInit() function which is called from startup
       file (startup_at32f415_xx.s) before to branch to application main.
       To reconfigure the default setting of SystemInit() function, refer to
       system_at32f4xx.c file
     */

  /* System Clocks Configuration */
  RCC_Configuration();

  /* Configure the GPIO ports */
  GPIO_Configuration();

  /* Use TMR1 generate clock to drive TMR3--------------------
  TMR1 PWM frequency = 120000000(systemclock)/144(Period+1)/1000(DIV+1) = 1 kHz
  TMR3 PWM frequency = 1000(TMR1 PWM frequency)/100(Period+1)/1(DIV+1) = 10 Hz
  ------------------------------------------------------------ */

  /* TMR1 and TMR3 counter mode configuration */
  TMR_TimeBaseStructInit(&TMR_TimerBaseInitStructure);
  TMR_TimerBaseInitStructure.TMR_Period = 119;
  TMR_TimerBaseInitStructure.TMR_DIV = 999;
  TMR_TimerBaseInitStructure.TMR_CounterMode = TMR_CounterDIR_Up;
  TMR_TimerBaseInitStructure.TMR_ClockDivision = TMR_CKD_DIV1;
  TMR_TimeBaseInit(TMR1, &TMR_TimerBaseInitStructure);

  TMR_TimerBaseInitStructure.TMR_Period = 99;
  TMR_TimerBaseInitStructure.TMR_DIV = 0;
  TMR_TimeBaseInit(TMR3, &TMR_TimerBaseInitStructure);

  /* TMR1 and TMR3 output mode configuration */
  TMR_OCStructInit(&TMR_OCInitStructure);
  TMR_OCInitStructure.TMR_OCMode = TMR_OCMode_PWM1;
  TMR_OCInitStructure.TMR_Pulse = 49;
  TMR_OCInitStructure.TMR_OCPolarity = TMR_OCPolarity_High;
  TMR_OCInitStructure.TMR_OutputState = TMR_OutputState_Enable;
  TMR_OC1Init(TMR1, &TMR_OCInitStructure);

  TMR_OC3Init(TMR3, &TMR_OCInitStructure);

  /* configure TMR3 channel2 to get clock signal */
  TMR_ICStructInit(&TMR_ICInitStructure);
  TMR_ICInitStructure.TMR_Channel = TMR_Channel_2;
  TMR_ICInitStructure.TMR_ICPolarity = TMR_ICPolarity_Rising;
  TMR_ICInitStructure.TMR_ICSelection = TMR_ICSelection_DirectTI;
  TMR_ICInitStructure.TMR_ICDIV = TMR_ICDIV_DIV1;
  TMR_ICInitStructure.TMR_ICFilter = 0x0;

  TMR_PWMIConfig(TMR3, &TMR_ICInitStructure);

  /* Select the TMR3 Input Trigger: TI2FP2 */
  TMR_SelectInputTrigger(TMR3, TMR_TRGSEL_TI2FP2);

  /* Select the slave Mode: External1 Mode */
  TMR_SelectSlaveMode(TMR3, TMR_SlaveMode_External1);

  /* TMR1 enable counter */
  TMR_Cmd(TMR1, ENABLE);
  
  /* Main Output Enable */
  TMR_CtrlPWMOutputs(TMR1, ENABLE);

  /* TMR3 enable counter */
  TMR_Cmd(TMR3, ENABLE);

  while (1);
}

/**
  * @brief  Configures the different system clocks.
  * @param  None
  * @retval None
  */
void RCC_Configuration(void)
{
  /* TMR3 clock enable */
  RCC_APB2PeriphClockCmd(RCC_APB2PERIPH_TMR1, ENABLE);
  RCC_APB1PeriphClockCmd(RCC_APB1PERIPH_TMR3, ENABLE);
  RCC_AHBPeriphClockCmd(RCC_AHBPERIPH_GPIOA | RCC_AHBPERIPH_GPIOB, ENABLE);
}

/**
  * @brief  Configure the GPIO Pins.
  * @param  None
  * @retval None
  */
void GPIO_Configuration(void)
{
  GPIO_InitType GPIO_InitStructure = {0};

  GPIO_PinAFConfig(GPIOA, GPIO_PinsSource7, GPIO_AF_1);
  GPIO_PinAFConfig(GPIOB, GPIO_PinsSource0, GPIO_AF_1);
  GPIO_PinAFConfig(GPIOA, GPIO_PinsSource8, GPIO_AF_2);
  
  /* TMR3 channel 2 pin (PA.07) configuration */
  GPIO_StructInit(&GPIO_InitStructure);
  GPIO_InitStructure.GPIO_Pins = GPIO_Pins_7;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_MaxSpeed = GPIO_MaxSpeed_50MHz;
  GPIO_InitStructure.GPIO_Pull = GPIO_Pull_NOPULL;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pins = GPIO_Pins_8;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_MaxSpeed = GPIO_MaxSpeed_50MHz;
  GPIO_InitStructure.GPIO_Pull = GPIO_Pull_NOPULL;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pins = GPIO_Pins_0;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
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
  
