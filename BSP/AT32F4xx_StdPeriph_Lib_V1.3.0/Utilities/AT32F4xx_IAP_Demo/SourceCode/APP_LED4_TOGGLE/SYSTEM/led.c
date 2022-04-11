#include "led.h"

// LED IO ³õÊ¼»¯
#if defined (AT_START_F403_V1_2) || defined (AT_START_F403A_V1_0) || defined (AT_START_F407_V1_0)
	#define LED_GPIO_RCC						RCC_APB2PERIPH_GPIOD	
	#define LED_GPIO_PORT						GPIOD	
	#define LED2_GPIO_PIN						GPIO_Pins_13
	#define LED3_GPIO_PIN						GPIO_Pins_14
	#define LED4_GPIO_PIN						GPIO_Pins_15
#elif defined (AT_START_F413_V1_0) || defined (AT_START_F415_V1_0)
	#define LED_GPIO_RCC						RCC_APB2PERIPH_GPIOC	
	#define LED_GPIO_PORT						GPIOC	
	#define LED2_GPIO_PIN						GPIO_Pins_2
	#define LED3_GPIO_PIN						GPIO_Pins_3
	#define LED4_GPIO_PIN						GPIO_Pins_5
#elif defined (AT_START_F421_V1_0)
	#define LED2_GPIO_RCC						RCC_AHBPERIPH_GPIOF	
	#define LED2_GPIO_PORT						GPIOF	
	#define LED2_GPIO_PIN						GPIO_Pins_6
	#define LED3_GPIO_RCC						RCC_AHBPERIPH_GPIOF	
	#define LED3_GPIO_PORT						GPIOF	
	#define LED3_GPIO_PIN						GPIO_Pins_7
	#define LED4_GPIO_RCC						RCC_AHBPERIPH_GPIOB	
	#define LED4_GPIO_PORT						GPIOB	
	#define LED4_GPIO_PIN						GPIO_Pins_11
 #define TOGGLE_LED2(A)			LED2_GPIO_PORT->OPTDT ^= A;
 #define TOGGLE_LED3(A)			LED3_GPIO_PORT->OPTDT ^= A;
 #define TOGGLE_LED4(A)			LED4_GPIO_PORT->OPTDT ^= A; 
#endif

#define TOGGLE_LED(A)			LED_GPIO_PORT->OPTDT ^= A;

u8 TIME2_IRA_CNT=0;
u8 GetDaraFromUSART_Flag=0;

void LED_Init(void)
{
#ifdef AT32F421xx
  GPIO_InitType GPIO_InitStructure;
  NVIC_InitType NVIC_InitStructure;
	 TMR_TimerBaseInitType TMR_TimeBaseStructure;	
 
  RCC_APB1PeriphClockCmd(RCC_APB1PERIPH_TMR3, ENABLE);	 
  RCC_AHBPeriphClockCmd(LED2_GPIO_RCC, ENABLE); 
  RCC_AHBPeriphClockCmd(LED3_GPIO_RCC, ENABLE); 
  RCC_AHBPeriphClockCmd(LED4_GPIO_RCC, ENABLE);  
  /* LED Initial */
  GPIO_InitStructure.GPIO_Pins = LED2_GPIO_PIN;
  GPIO_InitStructure.GPIO_MaxSpeed = GPIO_MaxSpeed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OutType = GPIO_OutType_PP;
  GPIO_InitStructure.GPIO_Pull = GPIO_Pull_NOPULL;
  GPIO_Init(LED2_GPIO_PORT, &GPIO_InitStructure);
  GPIO_InitStructure.GPIO_Pins = LED3_GPIO_PIN;
  GPIO_Init(LED3_GPIO_PORT, &GPIO_InitStructure);
  GPIO_InitStructure.GPIO_Pins = LED4_GPIO_PIN;
  GPIO_Init(LED4_GPIO_PORT, &GPIO_InitStructure);
	 GPIO_SetBits(LED2_GPIO_PORT, LED2_GPIO_PIN);
	 GPIO_SetBits(LED3_GPIO_PORT, LED3_GPIO_PIN);
	 GPIO_SetBits(LED4_GPIO_PORT, LED4_GPIO_PIN);  
  /* Enable the TMR3 global Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = TMR3_GLOBAL_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;	
  NVIC_Init(&NVIC_InitStructure);
   /* Time base configuration */
  TMR_TimeBaseStructInit(&TMR_TimeBaseStructure);
  TMR_TimeBaseStructure.TMR_Period = 5000;
  TMR_TimeBaseStructure.TMR_DIV = SystemCoreClock/10000;
  TMR_TimeBaseStructure.TMR_ClockDivision = 0;
  TMR_TimeBaseStructure.TMR_CounterMode = TMR_CounterDIR_Up;
  TMR_TimeBaseStructure.TMR_RepetitionCounter=0;
  TMR_INTConfig(TMR3,TMR_INT_Overflow,ENABLE);
  TMR_TimeBaseInit(TMR3, &TMR_TimeBaseStructure);
  
  TMR_Cmd(TMR3,ENABLE); 
#else
  GPIO_InitType GPIO_InitStructure;
  NVIC_InitType NVIC_InitStructure;
	 TMR_TimerBaseInitType TMR_TimeBaseStructure;	
 
  RCC_APB1PeriphClockCmd(RCC_APB1PERIPH_TMR2, ENABLE);	
	 RCC_APB2PeriphClockCmd(LED_GPIO_RCC, ENABLE);

  /* LED Initial */
  GPIO_InitStructure.GPIO_Pins = LED2_GPIO_PIN | LED3_GPIO_PIN | LED4_GPIO_PIN;
  GPIO_InitStructure.GPIO_MaxSpeed = GPIO_MaxSpeed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT_PP;
  GPIO_Init(LED_GPIO_PORT, &GPIO_InitStructure);
	 GPIO_SetBits(LED_GPIO_PORT, LED2_GPIO_PIN | LED3_GPIO_PIN | LED4_GPIO_PIN);
	
  /* Enable the TMR2 global Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = TMR2_GLOBAL_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;	
  NVIC_Init(&NVIC_InitStructure);
	
  /* Time base configuration */
	TMR_TimeBaseStructInit(&TMR_TimeBaseStructure);
	TMR_TimeBaseStructure.TMR_Period = 5000;
 TMR_TimeBaseStructure.TMR_DIV = SystemCoreClock/10000;
 TMR_TimeBaseStructure.TMR_ClockDivision = 0;
 TMR_TimeBaseStructure.TMR_CounterMode = TMR_CounterDIR_Up;
	TMR_TimeBaseStructure.TMR_RepetitionCounter=0;
	TMR_INTConfig(TMR2,TMR_INT_Overflow,ENABLE);
 TMR_TimeBaseInit(TMR2, &TMR_TimeBaseStructure);
	
	TMR_Cmd(TMR2,ENABLE);
#endif
}
#ifdef AT32F421xx
void TMR3_GLOBAL_IRQHandler(void)
{
  if(TMR_GetINTStatus(TMR3, TMR_INT_Overflow) != RESET)
  {	
		  TOGGLE_LED4(LED4_GPIO_PIN);
    TMR_ClearITPendingBit(TMR3, TMR_INT_Overflow);
  }
}
#else
void TMR2_GLOBAL_IRQHandler(void)
{
  if(TMR_GetINTStatus(TMR2, TMR_INT_Overflow) != RESET)
  {	
		  TOGGLE_LED(LED4_GPIO_PIN);
    TMR_ClearITPendingBit(TMR2, TMR_INT_Overflow);
  }
}
#endif


