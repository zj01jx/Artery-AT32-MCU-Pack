/**
 @page  CAN Loopback mode Transmit data example
 @verbatim
  * File   : CAN/CAN_Loopback/readme.txt
  * Version: V1.3.0
  * Date   : 2021-03-18
  * Brief  : Description of the CAN Loopback mode Transmit data example.
  ********************************************************************************************
 @endverbatiom

@par Example Desctiption
 This demo is based on the AT-START-F413 board,in this demo,CAN work in LoopBack mode.
 LED4 toggle when transmit CAN data.
 User can use USBCAN to receive data.
 User can check register CAN->ESTS and CAN->TSTS to affirm no error causing when disconnect CAN_RX pin.
 LED2-->GPIOC Pin2
 LED3-->GPIOC Pin3
 LED4-->GPIOC Pin5
 
@note
 ¡î¡î¡î	AT32_F413 contain both CAN1 and CAN2.
 ¡î¡î¡î	In main.c line 46:The following one of the define AT32_USE_CAN1 and AT32_USE_CAN2 must be choose
 ¡î¡î¡î	In main.c line 51:The following one of the define CAN1_NOREMAP and CAN1_REMAP10 must be choose
 ¡î¡î¡î	In main.c line 74:The following one of the define CAN2x_REMAP0 and CAN2x_REMAP1 must be choose
 
  */
 