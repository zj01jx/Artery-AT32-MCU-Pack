/**
  ******************************************************************************
  * File   : usbd_conf.c
  * Version: V1.3.0
  * Date   : 2021-03-18
  * Brief  : USB Device configuration file
  ******************************************************************************
  */


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __USBD_CONF__H__
#define __USBD_CONF__H__

/* Includes ------------------------------------------------------------------*/
#include "usb_conf.h"

/** @defgroup USB_CONF_Exported_Defines
  * @{
  */ 
#define USBD_CFG_MAX_NUM           1
#define USBD_ITF_MAX_NUM           1

#define USB_MAX_STR_DESC_SIZ       64 

#define USBD_SELF_POWERED               

#define USBD_DYNAMIC_DESCRIPTOR_CHANGE_ENABLED 

/** @defgroup UUSB_HID_Class_Layer_Parameter
  * @{
  */ 
#define HID_IN_EP                    0x81
#define HID_IN_PACKET                8

/**
  * @}
  */ 

/** @defgroup USB_CONF_Exported_Types
  * @{
  */ 
/**
  * @}
  */ 


/** @defgroup USB_CONF_Exported_Macros
  * @{
  */ 
/**
  * @}
  */ 

/** @defgroup USB_CONF_Exported_Variables
  * @{
  */ 
/**
  * @}
  */ 

/** @defgroup USB_CONF_Exported_FunctionsPrototype
  * @{
  */ 
/**
  * @}
  */ 


#endif //__USBD_CONF__H__


