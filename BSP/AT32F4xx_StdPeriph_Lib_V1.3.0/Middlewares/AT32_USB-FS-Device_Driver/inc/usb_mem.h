/**
  ******************************************************************************
  * File   : usb_mem.h 
  * Version: V1.3.0
  * Date   : 2021-03-18
  * Brief  : Utility prototypes functions for memory/PMA transfers
  ******************************************************************************
  */


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __USB_MEM_H
#define __USB_MEM_H

/* Includes ------------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void UserToPMABufferCopy(uint8_t *pbUsrBuf, uint16_t wPMABufAddr, uint16_t wNBytes);
void PMAToUserBufferCopy(uint8_t *pbUsrBuf, uint16_t wPMABufAddr, uint16_t wNBytes);

/* External variables --------------------------------------------------------*/

#endif  /*__USB_MEM_H*/


