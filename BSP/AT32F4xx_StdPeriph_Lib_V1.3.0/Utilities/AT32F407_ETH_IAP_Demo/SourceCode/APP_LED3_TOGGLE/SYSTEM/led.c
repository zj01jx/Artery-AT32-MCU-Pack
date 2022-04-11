#include "led.h"

u8 TIME2_IRA_CNT=0;
u8 GetDaraFromUSART_Flag=0;

void LED_Init(void)
{
	GPIO_InitType GPIO_InitStructure;
 
  RCC_APB2PeriphClockCmd(LED_GPIO_RCC, ENABLE);

  /* LED Initial */
  GPIO_InitStructure.GPIO_Pins = LED2_GPIO_PIN | LED3_GPIO_PIN | LED4_GPIO_PIN;
  GPIO_InitStructure.GPIO_MaxSpeed = GPIO_MaxSpeed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT_PP;
  GPIO_Init(LED_GPIO_PORT, &GPIO_InitStructure);
	GPIO_SetBits(LED_GPIO_PORT, LED2_GPIO_PIN | LED3_GPIO_PIN | LED4_GPIO_PIN);
}
