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
  This demo is based on the AT-START-F421 board.
  This example shows how to configure external interrupt lines.
  In this example, 2 EXTI lines (EXTI0 and EXTI9) are configured to generate an interrupt on 
  each rising or falling edge. In the interrupt routine a led connected to a specific GPIO pin is toggled.
  LED2-->GPIOF Pin6
  LED3-->GPIOF Pin7
  LED4-->GPIOB Pin11
 
  */

