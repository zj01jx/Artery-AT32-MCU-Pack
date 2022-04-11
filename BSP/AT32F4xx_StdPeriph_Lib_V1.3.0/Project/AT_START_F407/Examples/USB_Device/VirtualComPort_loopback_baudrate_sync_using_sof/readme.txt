/**
  @page USB VirtualComPort_loopback example
  
  @verbatim
  ******************** (C) COPYRIGHT 2018 ArteryTek ****************************
  * File   : USB_Device/VirtualComPort_loopback/readme.txt 
  * Version: V1.3.0
  * Date   : 2021-03-18
  * Brief  : Description of the USB VirtualComPort_loopback example.
  ******************************************************************************
   @endverbatim

@par Example Description 

  The aim of this example is to read data from and write data to USB devices using the CDC protocol.
  It makes the USB device look like a serial port (NO serial cable connectors:You can see the data
  transferred to and from via USB instead of USB-to-USART bridge connection).
  - OUT transfers: receive the data from the PC to AT32
  - IN transfers: to send the data recived from the AT32 to the PC
  Note:  The PC Virtual Com Port Driver must use Artery_VirtualCOM_Driver
 

 * <h3><center>&copy; COPYRIGHT 2018 ArteryTek</center></h3>
 */