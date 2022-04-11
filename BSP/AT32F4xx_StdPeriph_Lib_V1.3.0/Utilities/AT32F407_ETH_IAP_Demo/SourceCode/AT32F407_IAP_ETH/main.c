/**
 ******************************************************************************
 * @file        main.c
 * @brief       eht iap demo
 * @date        2019-01-04
 * @version     V1.1.2
 ******************************************************************************
 */
 
/* Includes -----------------------------------------------------------------*/
#include "at32_board.h"
#include "main.h"
#include "flash.h"
#include "iap.h"
#include "eth_config.h"
#include "tftpserver.h"
#include "httpserver.h"

/** @addtogroup AT32F407_StdPeriph_Examples
  * @{
  */

/** @addtogroup ETH_Telnet
  * @{
  */ 
  
/* Gloable variables ---------------------------------------------------------*/
__IO uint32_t LocalTime = 0; /* this variable is used to create a time reference incremented by 10ms */
uint32_t timingdelay;
unsigned char tcp_rec_flag = 0;
ErrorStatus HSEStartUpStatus;

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
	
	if(*(uint32_t*)USER_FLASH_FIRST_PAGE_ADDRESS != 0xFFFFFFFF)
  {
    IAP_Load_APP(USER_FLASH_FIRST_PAGE_ADDRESS);
  }
  /* Setup AT32 system (clocks, Ethernet, GPIO, NVIC)*/
  Status = System_Setup();
  while(Status == ETH_DRIVER_FAIL);
  /* Initilaize the LwIP satck ip地址设置，mac设置，*/
  LwIP_Init();
  
#ifdef USE_IAP_HTTP
    /* Initialize the webserver module */
    IAP_httpd_init();
#endif
  
#ifdef USE_IAP_TFTP    
    /* Initialize the TFTP server */
    IAP_tftpd_init();
#endif
  
  while(1)
	{         
      /* check if any packet received */
      if (ETH_GetRxPktSize())
      { 
        /* process received ethernet packet */
        LwIP_Pkt_Handle();
      }
      /* handle periodic timers for LwIP */
      LwIP_Periodic_Handle(LocalTime);
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


