/**
  ******************************************************************************
  * File   : ETH/HTTP Server/main.c
  * Version: V1.3.0
  * Date   : 2021-03-18
  * Brief  : HTTP server function test
  ******************************************************************************
  */

/* Includes -----------------------------------------------------------------*/
#include "at32_board.h"
#include "main.h"
#include "eth_config.h"
#include "at32f4xx_rcc.h"

/** @addtogroup AT32F407_StdPeriph_Examples
  * @{
  */

/** @addtogroup ETH_HTTP_Server
  * @{
  */
/* Gloable variables ---------------------------------------------------------*/
__IO uint32_t LocalTime = 0; /* this variable is used to create a time reference incremented by 10ms */
uint32_t timingdelay;

/* Gloable functions ---------------------------------------------------------*/
/**
  * @brief  Main Function.
  * @param  None
  * @retval None
  */
int main(void)
{
    uint32_t Status;
    /* --------BSP Init ------------------------------------------------*/
    AT32_Board_Init();
    UART_Print_Init(115200);
  
    /* Setup AT32 system (clocks, Ethernet, GPIO, NVIC) */
    Status = System_Setup();
    while(Status == ETH_DRIVER_FAIL);
  
    /* ADC configuration */
    ADC_Configuration();
  
    /* Initilaize the LwIP satck ip地址设置，mac设置，*/
    LwIP_Init();
    httpd_init();
  
    while(1)
    { 
        System_Periodic_Handle();//作为服务器的例行事件服务，主要是更新TCP timers
        Delay(100);
    }
}

/**
  * @brief  Configures the ADC.
  * @param  None
  * @retval None
  */
void ADC_Configuration(void)
{
  ADC_InitType ADC_InitStructure;
  
  /* Enable ADC1 clock */
  RCC_APB2PeriphClockCmd(RCC_APB2PERIPH_ADC1, ENABLE);

  /* ADC1 Configuration ------------------------------------------------------*/
  ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
  ADC_InitStructure.ADC_ScanMode = DISABLE;
  ADC_InitStructure.ADC_ContinuousMode = ENABLE;
  ADC_InitStructure.ADC_ExternalTrig = ADC_ExternalTrig_None;
  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
  ADC_InitStructure.ADC_NumOfChannel = 1;
  ADC_Init(ADC1, &ADC_InitStructure);

  /* ADC1 regular channel14 configuration */ 
  ADC_RegularChannelConfig(ADC1, ADC_Channel_4, 1, ADC_SampleTime_239_5);

  /* Enable ADC1 */
  ADC_Ctrl(ADC1, ENABLE);

  /* Enable ADC1 reset calibration register */   
	ADC_RstCalibration(ADC1);
	/* Check the end of ADC1 reset calibration register */
	while(ADC_GetResetCalibrationStatus(ADC1));

	/* Start ADC1 calibration */
	ADC_StartCalibration(ADC1);
	/* Check the end of ADC1 calibration */
	while(ADC_GetCalibrationStatus(ADC1));
  /* Start ADC1 Software Conversion */ 
  ADC_SoftwareStartConvCtrl(ADC1, ENABLE);  
}
/**
  * @brief  Inserts a delay time.
  * @param  nCount: number of 10ms periods to wait for.
  * @retval None
  */
void Delay(uint32_t nCount)
{
  /* Capture the current local time */
  timingdelay = LocalTime + nCount;  

  /* wait until the desired delay finish */  
  while(timingdelay > LocalTime)
  {     
  }
}

/**
  * @brief  Updates the system local time
  * @param  None
  * @retval None
  */
void Time_Update(void)
{
  LocalTime += SYSTEMTICK_PERIOD_MS;
}

/**
  * @brief  Handles the periodic tasks of the system
  * @param  None
  * @retval None
  */
void System_Periodic_Handle(void)
{
  /* LwIP periodic services are done here */
  LwIP_Periodic_Handle(LocalTime);
}


#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *   where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {}
}
#endif


