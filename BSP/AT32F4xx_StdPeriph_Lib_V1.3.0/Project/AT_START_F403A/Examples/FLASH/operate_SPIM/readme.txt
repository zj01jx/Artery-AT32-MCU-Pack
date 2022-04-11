/**
  @page FLASH_operate_SPIM operate SPIM example
  
  @verbatim
  * File   : FLASH/operate_SPIM/readme.txt 
  * Version: V1.3.0
  * Date   : 2021-03-18
  * Brief  : Description of the operate SPIM example.
  ******************************************************************************
   @endverbatim

@par Example Description 

External SPI flash pin:
SPIF_SCK    : PB1
SPIF_CS     : PA8
SPIF_TX     : PB10
SPIF_RX     : PB11
SPIF_HOLD_N : PB6
SPIF_WP_N   : PB7

This demo is based on the AT-START-F403A board, using on-board EN25QH128A as ext.flash ,code will erase,write and read ext.flash one page.If everything ok,usart will print success message.	

 */

