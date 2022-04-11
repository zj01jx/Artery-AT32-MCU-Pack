/**
 **************************************************************************
 * File Name    : main.c
 * Description  : None
 * Date         : 2021-02-22
 * Version      : V1.0.0
 **************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include "at32_board.h"
#include "FreeRTOS.h"
#include "task.h"

/** @addtogroup AT32Fxx_StdPeriph_Templates
  * @{
  */

/** @addtogroup FreeRTOS_Demo
  * @{
  */
/* Private define ------------------------------------------------------------*/
TaskHandle_t LED2_Handler;
TaskHandle_t LED3_Handler;
/* Private function prototypes -----------------------------------------------*/

/* Private functions ---------------------------------------------------------*/

/* LED2 task */
void LED2_task_Function(void *pvParameters);
/* LED3 task */
void LED3_task_Function(void *pvParameters);

int main(void)
{
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
  
  /*Configure LED2/3 in AT_START_BOARD*/
  AT32_LEDn_Init(LED2);
  AT32_LEDn_Init(LED3);
  AT32_LEDn_OFF(LED2);
  AT32_LEDn_OFF(LED3);
  
  UART_Print_Init(115200);
  
  /* Enter critical */
  taskENTER_CRITICAL(); 

  /* Create LED2 task */
  if(xTaskCreate((TaskFunction_t )LED2_task_Function,     
                 (const char*    )"LED2_task",   
                 (uint16_t       )512, 
                 (void*          )NULL,
                 (UBaseType_t    )2,
                 (TaskHandle_t*  )&LED2_Handler) != pdPASS)
  {
    printf("LED2 task could not be created as there was insufficient heap memory remaining.\r\n");
  }        
  else
  {
    printf("LED2 task was created successfully.\r\n");
  }
  /* Create LED3 task */
  if(xTaskCreate((TaskFunction_t )LED3_task_Function,     
                 (const char*    )"LED3_task",   
                 (uint16_t       )512, 
                 (void*          )NULL,
                 (UBaseType_t    )2,
                 (TaskHandle_t*  )&LED3_Handler) != pdPASS) 
  {
    printf("LED3 task could not be created as there was insufficient heap memory remaining.\r\n");
  }
  else
  {
    printf("LED3 task was created successfully.\r\n");
  }
 
  /* Exit critical */            
  taskEXIT_CRITICAL();      
              
  /* Start Scheduler */            
  vTaskStartScheduler(); 
}

/* LED2 task function */
void LED2_task_Function(void *pvParameters)
{
  while(1)
  {
    AT32_LEDn_Toggle(LED2);
    vTaskDelay(1000);
  }
}

/* LED3 task function */
void LED3_task_Function(void *pvParameters)
{
  while(1)
  {
    AT32_LEDn_Toggle(LED3);
    vTaskDelay(500);
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
