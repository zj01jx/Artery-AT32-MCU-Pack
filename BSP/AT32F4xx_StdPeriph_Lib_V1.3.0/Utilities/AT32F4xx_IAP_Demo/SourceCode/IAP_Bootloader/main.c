/**
  ******************************************************************************
  * File   : main.c 
  * Version: V1.3.0
  * Date   : 2021-03-18
  * Brief  : Main program body
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "at32f4xx.h"
#include "led.h"
#include "usart.h"
#include "flash.h"
#include "iap.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program
  * @param  None
  * @retval None
  */
int main(void)
{
  SystemCoreClockUpdate();

  if(FLASH_Read_Upgrade_Flag() == RESET)                       // �z��IAP_UPGRADE_FLAG�Ƿ�����, ��δ�����t���D���Ñ�APP
  {
    if(((*(vu32*)(APP_START_ADDR+4))&0xFF000000)==0x08000000)  // �ж�APP��ʼ��ַ�Ƿ�Ϊ0x08xxxxxx.
    IAP_Load_APP(APP_START_ADDR);                              // ִ��APP����
  }

  UART_Init(115200);                                           // ��ʼ������, ���ڸ��� APP ����
  if(FLASH_Read_Upgrade_Flag() != RESET)
    Back_Ok();                                                 // ����λ������OK

  LED_Init();                                                  // ����LED2���ڷ�ת
  while(1)
  {
    IAP_Upgrade_APP_Handle();
  }
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

  /* Infinite loop */
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

