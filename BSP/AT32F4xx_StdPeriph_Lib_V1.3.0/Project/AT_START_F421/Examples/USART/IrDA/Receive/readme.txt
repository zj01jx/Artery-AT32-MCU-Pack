/**
  @page USART IrDA Receive example
  
  @verbatim
  * File   : USART/IrDA/Receive/readme.txt 
  * Version: V1.3.0
  * Date   : 2021-03-18
  * Brief  : Description of the USART IrDA Receive example.
  ******************************************************************************
   @endverbatim

@par Example Description 

  This demo provides a basic communication USART1 IrDA receive mode. Three leds
  are used to show 0xAA byte is received.
  
  - BaudRate = 115200 baud  
  - Word Length = 8 Bits
  - One Stop Bit
  - No parity
  - Hardware flow control disabled (RTS and CTS signals)
  - Receive and transmit enabled
  
  The USART IrDA example provides two IrDA program: transmitter&receiver and 
  requires two boards to be able to run the full demonstration:
  - one board will act as IrDA transmitter
  - one board will act as IrDA receiver
  Set-up 
    - Use an IrDA transceiver connected to the USART3 Tx/Rx pin

 */