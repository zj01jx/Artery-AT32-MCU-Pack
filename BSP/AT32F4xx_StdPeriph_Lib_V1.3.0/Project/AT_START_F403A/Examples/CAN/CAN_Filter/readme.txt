/**
 @page  CAN Receive Filter example
 @verbatim
  * File   : CAN/CAN_Filter/readme.txt
  * Version: V1.3.0
  * Date   : 2021-03-18
  * Brief  : Description of the CAN Normal mode Transmit and receive data example.
  ********************************************************************************************
 @endverbatiom

@par Example Desctiption
  This demo is based on the AT-START-F403A board,in this demo,CAN work in Normal mode
  and config Extended identfier and Standard identfier filter.
  LED4 toggle when transmit CAN data.LED2 toggle when receive CAN data
  User can use USBCAN to transmit and receive data.
 
@note
 ����	In main.c line 46:The following one of the define AT32_USE_CAN1 must be choose
 ����	In main.c line 51:The following one of the define CAN1_NOREMAP and CAN1_REMAP10 and CAN1_REMAP11 must be choose
 
  */

