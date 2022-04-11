/**
 @page  EXTI Config example
 @verbatim
  * File   : EXTI\EXTI_Config/readme.txt
  * Version: V1.3.0
  * Date   : 2021-03-18
  * Brief  : Description of the EXTI Config example.
  ********************************************************************************************
 @endverbatiom

@par Example Desctiption
  This demo is based on the AT-START-F403A board.
  This example shows how to configure external interrupt lines.
  In this example, 2 EXTI lines (EXTI0 and EXTI9) are configured to generate an interrupt on 
  each rising or falling edge. In the interrupt routine a led connected to a specific GPIO pin is toggled.
  LED2-->GPIOD Pin13
  LED3-->GPIOD Pin14
  LED4-->GPIOD Pin15
 
  */

