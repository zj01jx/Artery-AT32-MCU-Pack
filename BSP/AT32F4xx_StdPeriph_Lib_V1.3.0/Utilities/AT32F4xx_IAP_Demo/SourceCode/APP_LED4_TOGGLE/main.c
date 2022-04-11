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
#include "usart.h"
#include "iap.h"
#include "led.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
const u8 buffer[1024]={0x55};
u32 buf1;

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program
  * @param  None
  * @retval None
  */
int main(void)
{
	IAP_Init();
	LED_Init();							// TIM2中断观察LED Toggle
	Uart_Init(115200);			// 用于与上位机通信 切换到IAP Update状态
	
	buf1=buffer[0];		// 测试大文件下载
	
	while(1)
	{
		IAP_Command_Handle();
	}
}

/**
  * @}
  */

/**
  * @}
  */

