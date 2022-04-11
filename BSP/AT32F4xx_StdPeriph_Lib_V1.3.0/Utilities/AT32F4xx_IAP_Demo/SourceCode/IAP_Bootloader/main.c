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

  if(FLASH_Read_Upgrade_Flag() == RESET)                       // 檢查IAP_UPGRADE_FLAG是否置起, 若未置起則跳轉到用戶APP
  {
    if(((*(vu32*)(APP_START_ADDR+4))&0xFF000000)==0x08000000)  // 判断APP起始地址是否为0x08xxxxxx.
    IAP_Load_APP(APP_START_ADDR);                              // 执行APP代码
  }

  UART_Init(115200);                                           // 初始化傳口, 用于更新 APP 内容
  if(FLASH_Read_Upgrade_Flag() != RESET)
    Back_Ok();                                                 // 向上位机返回OK

  LED_Init();                                                  // 用于LED2周期翻转
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

