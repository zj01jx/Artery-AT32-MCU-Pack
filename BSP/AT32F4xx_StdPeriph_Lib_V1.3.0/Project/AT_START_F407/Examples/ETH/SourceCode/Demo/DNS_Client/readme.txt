/**
  ******************************************************************************
  *  File   : ETH/DNS_Client/readme.txt
  * Brief  : AT32F407 ETH test
  ******************************************************************************
  ******************************************************************************
  */
 
  @Description
  This demo is based on the AT-START-F407 board for ETH to implement simple
  DNS client.
  User can enter input domain name in hostname of function DNS_Test, it will
  print IP of domain name if it parsed successfully.
  Remind the board should connect to router that connected to internet, and
  DHCP is required in this demo.(LWIP_DNS and LWIP_DHCP should be 1.)
  
