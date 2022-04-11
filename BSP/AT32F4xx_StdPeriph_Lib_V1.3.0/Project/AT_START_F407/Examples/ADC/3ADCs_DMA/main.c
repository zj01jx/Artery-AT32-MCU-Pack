/**
  ******************************************************************************
  * File   : ADC/3ADCs_DMA/main.c 
  * Version: V1.3.0
  * Date   : 2021-03-18
  * Brief  : Main program body
  ******************************************************************************
  */ 

/* Includes ------------------------------------------------------------------*/
#include "at32f4xx.h"
#include "at32_board.h"

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
ADC_InitType ADC_InitStructure;
DMA_InitType DMA_InitStructure;
NVIC_InitType NVIC_InitStructure;
TMR_TimerBaseInitType  TMR_TimeBaseStructure;
__IO uint32_t ADC1_RegularConvertedValueTab[3];
__IO uint16_t ADC3_RegularConvertedValueTab[3];
__IO uint32_t Adc1_Trigger_Times = 0;
__IO uint32_t Adc3_Trigger_Times = 0;

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
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
  AT32_Board_Init();
  UART_Print_Init(115200);
	RCC_Configuration();
  NVIC_Configuration();
	/* GPIO configuration ------------------------------------------------------*/
	GPIO_Configuration();
  TMR_TimeBaseStructInit(&TMR_TimeBaseStructure); 
	TMR_TimeBaseStructure.TMR_Period            = 4999;       
	TMR_TimeBaseStructure.TMR_DIV               = (SystemCoreClock/10000)-1;      
	TMR_TimeBaseStructure.TMR_ClockDivision     = 0x0;    
	TMR_TimeBaseStructure.TMR_CounterMode       = TMR_CounterDIR_Up;  
	TMR_TimeBaseStructure.TMR_RepetitionCounter = 0x0000;
	TMR_TimeBaseInit(TMR1, &TMR_TimeBaseStructure);
  TMR_SelectOutputTrigger(TMR1, TMR_TRGOSource_Update);

	/* DMA1 channel1 configuration ----------------------------------------------*/
	DMA_Reset(DMA1_Channel1);
	DMA_DefaultInitParaConfig(&DMA_InitStructure);
	DMA_InitStructure.DMA_PeripheralBaseAddr    = (uint32_t)&ADC1->RDOR;
	DMA_InitStructure.DMA_MemoryBaseAddr        = (uint32_t)ADC1_RegularConvertedValueTab;
	DMA_InitStructure.DMA_Direction             = DMA_DIR_PERIPHERALSRC;
	DMA_InitStructure.DMA_BufferSize            = 3;
	DMA_InitStructure.DMA_PeripheralInc         = DMA_PERIPHERALINC_DISABLE;
	DMA_InitStructure.DMA_MemoryInc             = DMA_MEMORYINC_ENABLE;
	DMA_InitStructure.DMA_PeripheralDataWidth   = DMA_PERIPHERALDATAWIDTH_WORD;
	DMA_InitStructure.DMA_MemoryDataWidth       = DMA_MEMORYDATAWIDTH_WORD;
	DMA_InitStructure.DMA_Mode                  = DMA_MODE_CIRCULAR;
	DMA_InitStructure.DMA_Priority              = DMA_PRIORITY_HIGH;
	DMA_InitStructure.DMA_MTOM                  = DMA_MEMTOMEM_DISABLE;
	DMA_Init(DMA1_Channel1, &DMA_InitStructure);  
	DMA_INTConfig(DMA1_Channel1, DMA_INT_TC, ENABLE);
	DMA_ChannelEnable(DMA1_Channel1, ENABLE);

	/* DMA2 channel5 configuration ----------------------------------------------*/
	DMA_Reset(DMA2_Channel5);
	DMA_DefaultInitParaConfig(&DMA_InitStructure);
	DMA_InitStructure.DMA_PeripheralBaseAddr    = (uint32_t)&ADC3->RDOR;
	DMA_InitStructure.DMA_MemoryBaseAddr        = (uint32_t)ADC3_RegularConvertedValueTab;
	DMA_InitStructure.DMA_Direction             = DMA_DIR_PERIPHERALSRC;
	DMA_InitStructure.DMA_BufferSize            = 3;
	DMA_InitStructure.DMA_PeripheralInc         = DMA_PERIPHERALINC_DISABLE;
	DMA_InitStructure.DMA_MemoryInc             = DMA_MEMORYINC_ENABLE;
	DMA_InitStructure.DMA_PeripheralDataWidth   = DMA_PERIPHERALDATAWIDTH_HALFWORD;
	DMA_InitStructure.DMA_MemoryDataWidth       = DMA_MEMORYDATAWIDTH_HALFWORD;
	DMA_InitStructure.DMA_Mode                  = DMA_MODE_CIRCULAR;
	DMA_InitStructure.DMA_Priority              = DMA_PRIORITY_HIGH;
	DMA_InitStructure.DMA_MTOM                  = DMA_MEMTOMEM_DISABLE;
	DMA_Init(DMA2_Channel5, &DMA_InitStructure);  
	DMA_INTConfig(DMA2_Channel5, DMA_INT_TC, ENABLE);
	DMA_ChannelEnable(DMA2_Channel5, ENABLE);

	/* ADC1 configuration ------------------------------------------------------*/
	ADC_StructInit(&ADC_InitStructure);
	ADC_InitStructure.ADC_Mode              = ADC_Mode_RegSimult;
	ADC_InitStructure.ADC_ScanMode          = ENABLE;
	ADC_InitStructure.ADC_ContinuousMode    = DISABLE;
	ADC_InitStructure.ADC_ExternalTrig      = ADC_ExternalTrig_TMR1_TRGO;
	ADC_InitStructure.ADC_DataAlign         = ADC_DataAlign_Right;
	ADC_InitStructure.ADC_NumOfChannel      = 3;
	ADC_Init(ADC1, &ADC_InitStructure);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 1, ADC_SampleTime_239_5);
  ADC_RegularChannelConfig(ADC1, ADC_Channel_2, 2, ADC_SampleTime_239_5);
  ADC_RegularChannelConfig(ADC1, ADC_Channel_3, 3, ADC_SampleTime_239_5);
  ADC_ExternalTrigConvCtrl(ADC1, ENABLE);
	ADC_DMACtrl(ADC1, ENABLE);

	/* ADC2 configuration ------------------------------------------------------*/
	ADC_StructInit(&ADC_InitStructure);
	ADC_InitStructure.ADC_Mode              = ADC_Mode_Independent;
	ADC_InitStructure.ADC_ScanMode          = ENABLE;
	ADC_InitStructure.ADC_ContinuousMode    = DISABLE;
	ADC_InitStructure.ADC_ExternalTrig      = ADC_ExternalTrig_None;
	ADC_InitStructure.ADC_DataAlign         = ADC_DataAlign_Right;
	ADC_InitStructure.ADC_NumOfChannel      = 3;
	ADC_Init(ADC2, &ADC_InitStructure);
	ADC_RegularChannelConfig(ADC2, ADC_Channel_2, 1, ADC_SampleTime_239_5);
  ADC_RegularChannelConfig(ADC2, ADC_Channel_3, 2, ADC_SampleTime_239_5);
  ADC_RegularChannelConfig(ADC2, ADC_Channel_1, 3, ADC_SampleTime_239_5);
  ADC_ExternalTrigConvCtrl(ADC2, ENABLE);
	
	/* ADC3 configuration ------------------------------------------------------*/
	ADC_StructInit(&ADC_InitStructure);
	ADC_InitStructure.ADC_Mode              = ADC_Mode_Independent;
	ADC_InitStructure.ADC_ScanMode          = ENABLE;
	ADC_InitStructure.ADC_ContinuousMode    = DISABLE;
	ADC_InitStructure.ADC_ExternalTrig      = ADC_ExternalTrig_TMR1_TRGO;
	ADC_InitStructure.ADC_DataAlign         = ADC_DataAlign_Right;
	ADC_InitStructure.ADC_NumOfChannel      = 3;
	ADC_Init(ADC3, &ADC_InitStructure);
	ADC_RegularChannelConfig(ADC3, ADC_Channel_10, 1, ADC_SampleTime_239_5);
  ADC_RegularChannelConfig(ADC3, ADC_Channel_11, 2, ADC_SampleTime_239_5);
  ADC_RegularChannelConfig(ADC3, ADC_Channel_12, 3, ADC_SampleTime_239_5);
  ADC_ExternalTrigConvCtrl(ADC3, ENABLE);
	ADC_DMACtrl(ADC3, ENABLE);
	
	ADC_Ctrl(ADC1, ENABLE);
	ADC_Ctrl(ADC2, ENABLE);
	ADC_RstCalibration(ADC1);
	while(ADC_GetResetCalibrationStatus(ADC1));
	ADC_StartCalibration(ADC1);
	while(ADC_GetCalibrationStatus(ADC1));   
	ADC_RstCalibration(ADC2);
	while(ADC_GetResetCalibrationStatus(ADC2));
	ADC_StartCalibration(ADC2);
	while(ADC_GetCalibrationStatus(ADC2));

	ADC_Ctrl(ADC3, ENABLE);  
	ADC_RstCalibration(ADC3);
	while(ADC_GetResetCalibrationStatus(ADC3));
	ADC_StartCalibration(ADC3);
	while(ADC_GetCalibrationStatus(ADC3));

	TMR_Cmd(TMR1, ENABLE);
  while(Adc1_Trigger_Times < 10);
  TMR_Cmd(TMR1, DISABLE);

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
	/* ADCCLK = PCLK2/6 */
	RCC_ADCCLKConfig(RCC_APB2CLK_Div6);
	
	/* Enable peripheral clocks ------------------------------------------------*/
	/* Enable DMA1 and DMA2 clocks */
	RCC_AHBPeriphClockCmd(RCC_AHBPERIPH_DMA1 | RCC_AHBPERIPH_DMA2, ENABLE);

	RCC_APB2PeriphClockCmd(	RCC_APB2PERIPH_ADC1 | RCC_APB2PERIPH_ADC2 | RCC_APB2PERIPH_TMR1 |
													RCC_APB2PERIPH_ADC3 | RCC_APB2PERIPH_GPIOA | RCC_APB2PERIPH_GPIOC, ENABLE);
}

/**
	* @brief  Configures the different GPIO ports.
	* @param  None
	* @retval None
	*/
void GPIO_Configuration(void)
{
	GPIO_InitType GPIO_InitStructure;

	GPIO_StructInit(&GPIO_InitStructure);
  GPIO_InitStructure.GPIO_Pins = GPIO_Pins_1 | GPIO_Pins_2 | GPIO_Pins_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_ANALOG;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pins = GPIO_Pins_0 | GPIO_Pins_1 | GPIO_Pins_2;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_ANALOG;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
}

/**
	* @brief  Configures the nvic.
	* @param  None
	* @retval None
	*/
void NVIC_Configuration(void)
{
  NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel1_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0 ;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
  NVIC_InitStructure.NVIC_IRQChannel = DMA2_Channel4_5_IRQn;
  NVIC_Init(&NVIC_InitStructure);
}

/**
	* @}
	*/ 

/**
	* @}
	*/ 

