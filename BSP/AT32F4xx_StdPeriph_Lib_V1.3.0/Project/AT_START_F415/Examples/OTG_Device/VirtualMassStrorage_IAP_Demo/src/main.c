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
#include "usb_dcd.h"
#include "at32_board.h"
#include "usbd_msc_core.h"
#include "usbd_usr.h"
#include "usbd_desc.h"
#include "usb_core.h"

#include "flash_if.h"
#include "FAT16.h"


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
#define OTG_FS_DCTL  *((__IO uint32_t *)0x50000804)
uint8_t g_u8jumpflag = 0;
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
void Set_USBOTGClock(void);
void loop_msdStatus(void);
void USB_Reset(void);
/**
  * @brief  Main Function.
  * @param  None
  * @retval None
  */
int main(void)
{
  AT32_Board_Init();
  if ( AT32_BUTTON_State(BUTTON_WAKEUP) == 0x00)
  {
      /*Check Flag*/
       //if ( (AT_ReadOptionByte() & 0x1) == 0)
      {
          /*Jump to User Code*/
          IAP_Jump(FLASH_START_ADDR);
      }
  }
  
  Set_USBOTGClock();
  
  USB_Device_Init(&USB_OTG_dev,
            USB_OTG_FS_CORE_ID,
            &USER_desc, 
            &USBD_MSC_cb, 
            &USER_cb);
  
  msd_UpStatus = UPGRADE_READY;
  while ( 1 )
  {
    loop_msdStatus();
    if (g_u8jumpflag == 1)
    {
      g_u8jumpflag = 0;
      IAP_Jump(FLASH_START_ADDR);
    }
    Delay_ms(1000);
    AT32_LEDn_Toggle(LED4);
  }
}

/**
  * @brief  loop msdStaus and create status file
  *         if download success or faild, need reset usb and return status file to PC
  * @param  None
  * @retval None
  */
void loop_msdStatus(void)
{
    static uint8_t msdTmp = UPGRADE_READY;
    if ( msdTmp == msd_UpStatus)
        return;
    else
        msdTmp = msd_UpStatus;
    
    switch (msd_UpStatus)
    {
        case UPGRADE_READY:
            FATSetStatusFileName("Ready");
            break;
        case UPGRADE_SUCCESS:
            FATSetStatusFileName("Success");
            msd_UpStatus = UPGREDE_DONE;
            USB_Reset();
            break;
        case UPGRADE_FAILED:
            FATSetStatusFileName("Failed");
            msd_UpStatus = UPGREDE_DONE;
            USB_Reset();
            break;
        case UPGRADE_LARGE:
            FATSetStatusFileName("Large");
            msd_UpStatus = UPGREDE_DONE;
            USB_Reset();
            break;
        case UPGRADE_UNKNOWN:
            FATSetStatusFileName("Unknown");
//            msd_UpStatus = UPGREDE_DONE;
//            USB_Reset();
            break;
        case UPGREDE_DONE:
            break;
        default:
            break;
    }
}

/**
  * @brief  handles USB Reset
  * @param  None
  * @retval None.
  */
void USB_Reset(void)
{
    Delay_ms(1000);
    Delay_ms(1000);
    OTG_FS_DCTL |= 0x2;
    Delay_ms(1000);
    Delay_ms(1000);
    OTG_FS_DCTL &= ~0x2;
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

