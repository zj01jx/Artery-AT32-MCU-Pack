/**
  ******************************************************************************
  * File   : USB_Device/VirtualComPort_loopback/src/main.c
  * Version: V1.3.0
  * Date   : 2021-03-18
  * Brief  : VirtualComPort loopback Demo main file
  ******************************************************************************
  */
#include "usb_lib.h"
#include "hw_config.h"
#include "usb_pwr.h"
#include "at32_board.h"
#include <stdio.h>

uint8_t usb_recvBuffer[256];
uint8_t usb_sendBuffer[256];
uint16_t recvLen, sendLen;


/** @addtogroup AT32F403A_StdPeriph_Examples
  * @{
  */

/** @addtogroup USB_VirtualComPort_loopback
  * @{
  */ 
void     RS232_SYNC_Reset();
uint16_t RS232RX_SYNC_GetRXBytesNeeded();
void TMR2_Init() //1ms
{
  TMR_TimerBaseInitType  TMR_TMReBaseStructure;
  TMR_OCInitType  TMR_OCInitStructure;
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



uint8_t  LED_Period = 0;
void TMR2_GLOBAL_IRQHandler(void)
{
  LED_Period++;
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

int main(void)
{		
    /*AT START F4xx board initialize
    * Include LED, Button
    */
    AT32_Board_Init();
    
    /*USB GPIO configure*/
    AT32_USB_GPIO_init();
    
    /*Enable USB Interrut*/
 	USB_Interrupts_Config();    
    
    /*Set USB Clock, USB Clock must 48MHz and clock source is HSE or HSI*/
    Set_USBClock(USBCLK_FROM_HSI);
    
    /* USB protocol and register initialize*/
 	USB_Init();
	RS232_SYNC_Reset();
    TMR2_Init();
    
   	while(1)
	  {
        {
            /*no data recv*/
        }
	  }	   										    			    
}

/**
  * @}
  */

/**
  * @}
  */




















