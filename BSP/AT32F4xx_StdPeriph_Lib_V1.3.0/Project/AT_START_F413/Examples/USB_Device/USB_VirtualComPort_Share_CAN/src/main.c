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

uint8_t usb_recvBuffer[256];
uint8_t usb_sendBuffer[256];
uint16_t recvLen, sendLen;

#define CANx     CAN1

/*Remap CAN TX & RX*/
#define CANx_TX    GPIO_Pins_9
#define CANx_RX    GPIO_Pins_8
#define CANx_TX_GPIO_CLK_ENABLE()       RCC_APB2PeriphClockCmd(RCC_APB2PERIPH_GPIOB, ENABLE);
#define CANx_RX_GPIO_CLK_ENABLE()       RCC_APB2PeriphClockCmd(RCC_APB2PERIPH_GPIOB, ENABLE);
#define CANx_TX_GPIO_PORT               GPIOB
#define CANx_RX_GPIO_PORT               GPIOB
#define CANx_CLK_ENABLE()              	RCC_APB1PeriphClockCmd(RCC_APB1PERIPH_CAN1, ENABLE);
CanRxMsg RxMessage = {0};
void CAN1_Demo(void);
static void CAN_transmit_data(void);
void CAN_Rx_Data(void);


void CAN1_Demo(void)
{
  CAN_InitType        	CAN_InitStructure;
  CAN_FilterInitType  	CAN_FilterInitStructure = {0};
  GPIO_InitType GPIO_InitStructure;
  GPIO_StructInit(&GPIO_InitStructure);
	CAN_StructInit(&CAN_InitStructure);
  
  
  CANx_TX_GPIO_CLK_ENABLE(); 
	CANx_RX_GPIO_CLK_ENABLE();
  
  /*Remap*/
  RCC_APB2PeriphClockCmd(RCC_APB2PERIPH_AFIO, ENABLE);
  GPIO_PinsRemapConfig(GPIO_Remap1_CAN1,ENABLE);
  
	GPIO_InitStructure.GPIO_Pins = CANx_TX;
	GPIO_InitStructure.GPIO_MaxSpeed = GPIO_MaxSpeed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	
	GPIO_Init(CANx_TX_GPIO_PORT, &GPIO_InitStructure);	

	GPIO_InitStructure.GPIO_Pins = CANx_RX;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_PU;	
	GPIO_Init(CANx_RX_GPIO_PORT, &GPIO_InitStructure);
	CANx_CLK_ENABLE();

  CAN_InitStructure.CAN_TTC = DISABLE;			
	CAN_InitStructure.CAN_ABO = ENABLE;			
	CAN_InitStructure.CAN_AWU = ENABLE;			
	CAN_InitStructure.CAN_NART = DISABLE;			
	CAN_InitStructure.CAN_RFL = DISABLE;		 	
	CAN_InitStructure.CAN_TFP = DISABLE;			
	CAN_InitStructure.CAN_Mode = CAN_Mode_LoopBack;
	CAN_InitStructure.CAN_SJW = CAN_SJW_1tq;				
	CAN_InitStructure.CAN_BS1 = CAN_BS1_8tq;
	CAN_InitStructure.CAN_BS2 = CAN_BS2_3tq;	
	CAN_InitStructure.CAN_Prescaler = 2;
	CAN_Init(CANx, &CAN_InitStructure);    ///<SYSCLK=192M,  APB1CLK=24M, CAN Baudrate=（192/8）*1000K）/（（1+1）*（3+7+2）） = 1000K
   
   CAN_FilterInitStructure.CAN_FilterNumber=0;	
	CAN_FilterInitStructure.CAN_FilterMode=CAN_FilterMode_IdMask; 	
	CAN_FilterInitStructure.CAN_FilterScale=CAN_FilterScale_32bit; 	
	CAN_FilterInitStructure.CAN_FilterIdHigh=0x0;	
	CAN_FilterInitStructure.CAN_FilterIdLow=0x0;
	CAN_FilterInitStructure.CAN_FilterMskIdHigh=0x0;
	CAN_FilterInitStructure.CAN_FilterMskIdLow=0x0;
	CAN_FilterInitStructure.CAN_FilterFIFOAssignment=CAN_FIFO0;
	CAN_FilterInitStructure.CAN_FilterActivation=ENABLE;
	CAN_FilterInit(CANx, &CAN_FilterInitStructure);
	
  CAN_INTConfig(CANx,CAN_INT_RFP0,ENABLE);
  
}


/**
 *	@brief  CAN transmit data.SID=0x400,Standard identifier,Data frame,data D0~D7 all 0xA5 
 *	@param  None
 *	@retval None
 */
static void CAN_transmit_data(void)
{
    uint8_t TransmitMailbox;
    uint32_t i = 0;
    CanTxMsg TxMessage;
    TxMessage.Data[0] = 0xA5;
    TxMessage.Data[1] = 0xA5;
    TxMessage.Data[2] = 0xA5;
    TxMessage.Data[3] = 0xA5;
    TxMessage.Data[4] = 0xA5;
    TxMessage.Data[5] = 0xA5;
    TxMessage.Data[6] = 0xA5;
    TxMessage.Data[7] = 0xA5;
    
	TxMessage.StdId = 0x400;			
	TxMessage.ExtId = 0;			
	TxMessage.IDT = CAN_Id_Standard;
	TxMessage.RTR = CAN_RTR_Data;		
	TxMessage.DLC = 8;
    TransmitMailbox = CAN_Transmit(CANx, &TxMessage);
    while((CAN_TransmitStatus(CAN1, TransmitMailbox) != CANTXOK) && (i != 0xFFFF))
    {
        i++;
    }
}


void CAN_Rx_Data(void)
{
    if (CAN_GetINTStatus (CANx,CAN_INT_RFOV0) == SET ) 
    {
        CAN_ClearINTPendingBit (CAN1, CAN_INT_RFOV0);
    }
    if (CAN_GetINTStatus (CANx,CAN_INT_RFFU0) == SET ) 
    {
        CAN_ClearINTPendingBit (CAN1, CAN_INT_RFFU0);
    }
    if (CAN_GetINTStatus (CANx,CAN_INT_RFP0) == SET )
    {
        CAN_Receive(CANx, CAN_FIFO0, &RxMessage);
        if ( RxMessage.StdId == 0X400 )
            AT32_LEDn_Toggle(LED2);
    }
}

/** @addtogroup AT32F413_StdPeriph_Examples
  * @{
  */

/** @addtogroup USB_VirtualComPort_loopback
  * @{
  */ 
int main(void)
{		
    /*AT START F4xx board initialize
    * Include LED, Button
    */
    AT32_Board_Init();
    
    /*USB GPIO configure*/
    AT32_USB_GPIO_init();
    
  
    /*Remap USB Interrupt*/
    RCC_USBINTRemap(ENABLE);
  
    /*初始化 USB Interrut
    USB 使用新的低优先级中断号：USB_LP_IRQn = 74
                高优先级中断号：USB_HP_IRQn = 73
  
    CAN1 中断号：
         TX： USB_HP_CAN1_TX_IRQn =  19
         RX：USB_LP_CAN1_RX0_IRQn =  20
  
     Note：中断初始化之后，中断处理函数需要一并修改。
    */
 	  USB_Interrupts_Config();    
    
    /*Set USB Clock, USB Clock must 48MHz*/
    Set_USBClock();
    
    /*Enable USB 768 Byte Mode*/
    Set_USB768ByteMode();
  
    /*Init CAN1*/
    CAN1_Demo();
  
    /* USB protocol and register initialize*/
 	  USB_Init();
    
   	while(1)
	  {
        recvLen = CDC_Receive_DATA(usb_recvBuffer, 256);
        if ( recvLen > 0 )
        {  /*recvive data from USB*/
    
            /*Send data to PC Host*/
            sendLen = CDC_Send_DATA(usb_recvBuffer, recvLen);
            AT32_LEDn_Toggle(LED3);

        }else
        {
            /*no data recv*/
            Delay_ms(100);
            AT32_LEDn_Toggle(LED4);
            CAN_transmit_data();
        }

	  }	   										    			    
}

/**
  * @}
  */

/**
  * @}
  */




















