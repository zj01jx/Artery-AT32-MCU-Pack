/**
  ******************************************************************************
  * File   : USB_Device/VirtualMassStorage_IAP_Demo/src/scsi_data.c
  * Version: V1.3.0
  * Date   : 2021-03-18
  * Brief  : Initialization of the SCSI data
  ******************************************************************************
  */


/* Includes ------------------------------------------------------------------*/
#include "usb_scsi.h"
#include "memory.h"

/** @addtogroup AT32F407_StdPeriph_Examples
  * @{
  */

/** @addtogroup USB_VirtualMassStrorage_IAP_Demo
  * @{
  */ 
uint8_t Page00_Inquiry_Data[] =
  {
    0x00, /* PERIPHERAL QUALIFIER & PERIPHERAL DEVICE TYPE*/
    0x00,
    0x00,
    0x00,
    0x00 /* Supported Pages 00*/
  };
  
uint8_t Standard_Inquiry_Data[] =
  {
    0x00,          /* Direct Access Device */
    0x80,          /* RMB = 1: Removable Medium */
    0x02,

    36 - 4,          /* Additional Length */
    0x00,          /* SCCS = 1: Storage Controller Component */
    0x00,
    0x00,
    /* Vendor Identification */
    'A', 'T', '3', '2', 'F', '4', 'x', 'x',
    /* Product Identification */
    'I', 'A', 'P', ' ', 'B', 'o', 'o', 't', 'l',
    'o', 'd', 'e', 'r', ' ', ' ', ' ',
    /* Product Revision Level */
    '1', '.', '0', ' '
  };


uint8_t Standard_Inquiry_Data2[] =
  {
    0x00,          /* Direct Access Device */
    0x80,          /* RMB = 1: Removable Medium */
    0x02,

    36 - 4,          /* Additional Length */
    0x00,          /* SCCS = 1: Storage Controller Component */
    0x00,
    0x00,
    /* Vendor Identification */
    'A', 'T', ' ', ' ', ' ', ' ', ' ', ' ',
    /* Product Identification */
    'N', 'A', 'N', 'D', ' ', 'F', 'l', 'a', 's', 'h', ' ',
    'D', 'i', 's', 'k', ' ',
    /* Product Revision Level */
    '1', '.', '0', ' '
  };
/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
uint8_t Mode_Sense6_data[] =
  {
    0x03,
    0x00,
    0x00,
    0x00,
  };

/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/

uint8_t Mode_Sense10_data[] =
  {
    0x00,
    0x06,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00
  };
uint8_t Scsi_Sense_Data[] =
  {
    0x70, /*RespCode*/
    0x00, /*SegmentNumber*/
    NO_SENSE, /* Sens_Key*/
    0x00,
    0x00,
    0x00,
    0x00, /*Information*/
    0x0A, /*AdditionalSenseLength*/
    0x00,
    0x00,
    0x00,
    0x00, /*CmdInformation*/
    NO_SENSE, /*Asc*/
    0x00, /*ASCQ*/
    0x00, /*FRUC*/
    0x00, /*TBD*/
    0x00,
    0x00 /*SenseKeySpecific*/
  };
uint8_t ReadCapacity10_Data[] =
  {
    /* Last Logical Block */
    0,
    0,
    0,
    0,

    /* Block Length */
    0,
    0,
    0,
    0
  };

uint8_t ReadFormatCapacity_Data [] =
  {
    0x00,
    0x00,
    0x00,
    0x08, /* Capacity List Length */

    /* Block Count */
    0,
    0,
    0,
    0,

    /* Block Length */
    0x02,/* Descriptor Code: Formatted Media */
    0,
    0,
    0
  };
/**
  * @}
  */ 

/**
  * @}
  */


