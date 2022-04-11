/**
  ******************************************************************************
  * File   : main.c
  * Version: V1.3.0
  * Date   : 2021-03-18
  * Brief  : Main program body
  ******************************************************************************
  */

#include <stdio.h>
#include "at32f4xx.h"
#include "at32_board.h"

#include "usbd_cdc_core_loopback.h"
#include "usbd_usr.h"
#include "usbd_desc.h"
#include "usbd_cdc_vcp.h"
#include "usbd_core.h"

/** @addtogroup AT32F415_StdPeriph_Examples
  * @{
  */

/** @addtogroup OTG_Device_VCP_Loopback
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
USB_OTG_CORE_HANDLE    USB_OTG_dev;
uint8_t Rxbuffer[64]; 
//__IO uint32_t receive_count =1;
uint16_t recvLen, sendLen;
uint8_t usb_recvBuffer[256];
uint8_t usb_sendBuffer[256];
extern __IO uint32_t  data_sent;
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
void     RS232_SYNC_Reset(void);
uint16_t RS232RX_SYNC_GetRXBytesNeeded(void);
void TMR2_Init() //1ms
{
  TMR_TimerBaseInitType  TMR_TMReBaseStructure;
  uint16_t        PrescalerValue = 3;//(uint16_t) (SystemCoreClock / 12000000) - 1;
  NVIC_InitType   NVIC_InitStructure;
  RCC_ClockType   RCC_Clocks;
  
  RCC_GetClocksFreq(&RCC_Clocks);
  
  RCC_APB1PeriphClockCmd(RCC_APB1PERIPH_TMR2, ENABLE);

  /* Enable the TMR2 global Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = TMR2_GLOBAL_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;

  NVIC_Init(&NVIC_InitStructure);  
  
  /* TMRe base configuration */
  TMR_TimeBaseStructInit(&TMR_TMReBaseStructure);
  TMR_TMReBaseStructure.TMR_Period = RCC_Clocks.APB1CLK_Freq/2000-1;
  TMR_TMReBaseStructure.TMR_DIV = 0;
  TMR_TMReBaseStructure.TMR_ClockDivision = 0;
  TMR_TMReBaseStructure.TMR_CounterMode = TMR_CounterDIR_Up;

  TMR_TimeBaseInit(TMR2, &TMR_TMReBaseStructure);

  /* Prescaler configuration */
  TMR_DIVConfig(TMR2, PrescalerValue, TMR_DIVReloadMode_Immediate);

  /* TMR IT enable */
  TMR_INTConfig(TMR2, TMR_INT_Overflow, ENABLE);

  /* TMR2 enable counter */
  TMR_Cmd(TMR2, ENABLE);
}

void TMR2_GLOBAL_IRQHandler(void)
{
  if (TMR_GetINTStatus(TMR2, TMR_INT_Overflow) != RESET)
  {
    uint16_t recv = RS232RX_SYNC_GetRXBytesNeeded();
    recv = CDC_Receive_DATA(usb_recvBuffer, recv);
    if(recv){
      CDC_Send_DATA(usb_recvBuffer, recv);
    }else{
    }
    TMR_ClearITPendingBit(TMR2, TMR_INT_Overflow);
  }
}

void Set_USBOTGClock(void);
/**
  * @brief  Main Function.
  * @param  None
  * @retval None
  */
int main(void)
{
  AT32_Board_Init();
  
  Set_USBOTGClock();
  
  USB_Device_Init(&USB_OTG_dev,
            USB_OTG_FS_CORE_ID,
            &USER_desc, 
            &USB_DEVICE_CDC_cb, 
            &USER_cb);
	RS232_SYNC_Reset();
  TMR2_Init();  

  while ( 1 )
  {
    //
  }
}


/**
  * @brief  Set USB Prescaler
  *         Set and cleared by software to generate 48MHz USB Clock 
  * @param  None
  * @retval None
  */
void Set_USBOTGClock(void)
{
  switch (SystemCoreClock)
  {
    case 48000000:
      RCC_USBCLKConfig(RCC_USBCLKSelection_PLL_Div1);
      break;
    case 72000000:
      RCC_USBCLKConfig(RCC_USBCLKSelection_PLL_Div1_5);
      break;
    case 96000000:
      RCC_USBCLKConfig(RCC_USBCLKSelection_PLL_Div2);
      break;
    case 120000000:
      RCC_USBCLKConfig(RCC_USBCLKSelection_PLL_Div2_5);
      break;
    case 144000000:
      RCC_USBCLKConfig(RCC_USBCLKSelection_PLL_Div3);
      break;
    default:
        break;
  }
   RCC_AHBPeriphClockCmd(RCC_AHBPERIPH_USB, ENABLE) ;  
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

