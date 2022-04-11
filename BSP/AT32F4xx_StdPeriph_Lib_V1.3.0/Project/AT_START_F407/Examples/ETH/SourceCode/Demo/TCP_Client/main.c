/**
  ******************************************************************************
  * File   : ETH/TCP Client/main.c
  * Version: V1.3.0
  * Date   : 2021-03-18
  * Brief  : TCP server function test
  ******************************************************************************
  */

/* Includes -----------------------------------------------------------------*/
#include "at32_board.h"
#include "main.h"
#include "eth_config.h"

/** @addtogroup AT32F407_StdPeriph_Examples
  * @{
  */

/** @addtogroup ETH_TCP_Server
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
  unsigned char tcp_data[] = "TCP client experiment!\n";
  struct tcp_pcb *pcb;
  uint32_t Status;
	/* --------BSP Init ------------------------------------------------*/
  AT32_Board_Init();
  UART_Print_Init(115200);
  /* Setup AT32 system (clocks, Ethernet, GPIO, NVIC)*/
  Status = System_Setup();
  while(Status == ETH_DRIVER_FAIL);
  
  /* Initilaize LwIP satck, IP configuration and MAC configuration*/
  LwIP_Init();
  /* Initialize TCP client module */
  TCP_Client_Init(TCP_LOCAL_PORT,TCP_SERVER_PORT,TCP_SERVER_IP);  //Initialize TCP client
  while(1)
  {         
      pcb = Check_TCP_Connect();
      if(pcb != 0)
      {	
        TCP_Client_Send_Data(pcb,tcp_data,sizeof(tcp_data));      //Send data to TCP server actively
      }
      Delay_s(0xfffff);											                      //necessary delay
      System_Periodic_Handle();									                  //Update TCP timers
  }
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

/**
  * @}
  */

/**
  * @}
  */


