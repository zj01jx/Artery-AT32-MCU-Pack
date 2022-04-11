/**
 @page  CAN Normal mode Transmit and receive data example
 @verbatim
  * File   : CAN/CAN_Normal/readme.txt
  * Version: V1.3.0
  * Date   : 2021-03-18
  * Brief  : Description of the CAN Normal mode Transmit and receive data example.
  ********************************************************************************************
 @endverbatiom

@par Example Desctiption
  This demo is based on the AT-START-F413 board,in this demo,CAN work in Normal mode.
  LED4 toggle when transmit CAN data.LED2(CAN1 used)/LED3(CAN2 used) toggle when receive CAN data
  User can use USBCAN to transmit and receive data.
  LED2-->GPIOC Pin2
  LED3-->GPIOC Pin3
  LED4-->GPIOC Pin5
 
@note
 ¡î¡î¡î	AT32_F413 contain both CAN1 and CAN2.
 ¡î¡î¡î	In main.c line 46:The following one of the define AT32_USE_CAN1 and AT32_USE_CAN2 must be choose
 ¡î¡î¡î	In main.c line 51:The following one of the define CAN1_NOREMAP and CAN1_REMAP10 must be choose
 ¡î¡î¡î	In main.c line 74:The following one of the define CAN2x_REMAP0 and CAN2x_REMAP1 must be choose
 
  */

