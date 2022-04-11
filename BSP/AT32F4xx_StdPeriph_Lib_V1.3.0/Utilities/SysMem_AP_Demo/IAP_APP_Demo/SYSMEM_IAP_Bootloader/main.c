/**
  ******************************************************************************
  * File   : IAP_APP_Demo/SYSMEM_IAP_Bootloader/main.c
  * Version: V1.3.0
  * Date   : 2021-03-18
  * Brief  : Main program body
  ******************************************************************************
  */

#include <stdio.h>
#include "at32f4xx.h"

/** @addtogroup SYSMEM_IAP_Bootloader
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
#define APP_ADDR  0x08000000
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

typedef void (*iapfun)(void);				//����һ���������͵Ĳ���.
iapfun jump2app; 
//��ת��Ӧ�ó����
//appxaddr:�û�������ʼ��ַ.
void IAP_Load_APP(uint32_t appxaddr)
{
	if(((*(uint32_t*)appxaddr)&0x2FFF8000)==0x20000000)	//���ջ����ַ�Ƿ�Ϸ�.
	{
		jump2app=(iapfun)*(uint32_t*)(appxaddr+4);				//�û��������ڶ�����Ϊ����ʼ��ַ(��λ��ַ)		
		__set_MSP(*(uint32_t*)appxaddr);									//��ʼ��APP��ջָ��(�û��������ĵ�һ�������ڴ��ջ����ַ)
		jump2app();																		//��ת��APP.
	}
}		

/**
  * @brief  Main Function.
  * @param  None
  * @retval None
  */
int main(void)
{
  UART_Print_Init(115200);
  printf("System memory as user-defined IAP if running.\r\n");
  printf("Jump to APP.\r\n");
  IAP_Load_APP(APP_ADDR);
  for(;;)
  {

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

