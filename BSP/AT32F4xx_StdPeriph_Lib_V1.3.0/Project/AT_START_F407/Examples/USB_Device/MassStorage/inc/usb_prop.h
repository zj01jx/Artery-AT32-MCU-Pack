/**
  ******************************************************************************
  * File   : USB_Device/MassStorage/inc/usb_prop.h
  * Version: V1.3.0
  * Date   : 2021-03-18
  * Brief  : All processing related to Mass Storage Demo (Endpoint 0)
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __USB_PROP_H
#define __USB_PROP_H
/* Exported constants --------------------------------------------------------*/
#define Mass_Storage_GetConfiguration          NOP_Process
/* #define Mass_Storage_SetConfiguration          NOP_Process*/
#define Mass_Storage_GetInterface              NOP_Process
#define Mass_Storage_SetInterface              NOP_Process
#define Mass_Storage_GetStatus                 NOP_Process
/* #define Mass_Storage_ClearFeature              NOP_Process*/
#define Mass_Storage_SetEndPointFeature        NOP_Process
#define Mass_Storage_SetDeviceFeature          NOP_Process
/*#define Mass_Storage_SetDeviceAddress          NOP_Process*/

/* MASS Storage Requests*/
#define GET_MAX_LUN                0xFE
#define MASS_STORAGE_RESET         0xFF
#define LUN_DATA_LENGTH            1

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void MASS_init(void);
void MASS_Reset(void);
void Mass_Storage_SetConfiguration(void);
void Mass_Storage_ClearFeature(void);
void Mass_Storage_SetDeviceAddress (void);
void MASS_Status_In (void);
void MASS_Status_Out (void);
RESULT MASS_Data_Setup(uint8_t);
RESULT MASS_NoData_Setup(uint8_t);
RESULT MASS_Get_Interface_Setting(uint8_t Interface, uint8_t AlternateSetting);
uint8_t *MASS_GetDeviceDescriptor(uint16_t );
uint8_t *MASS_GetConfigDescriptor(uint16_t);
uint8_t *MASS_GetStringDescriptor(uint16_t);
uint8_t *Get_Max_Lun(uint16_t Length);


#endif /* __USB_PROP_H */


