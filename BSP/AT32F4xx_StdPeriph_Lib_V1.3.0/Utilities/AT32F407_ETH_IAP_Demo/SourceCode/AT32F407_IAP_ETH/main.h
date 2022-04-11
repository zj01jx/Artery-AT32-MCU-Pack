/**
 ******************************************************************************
 * @file        ETH/iperf/main.h
 * @brief       This file contains all the functions prototypes for the 
                ethernet function
 * @date        2019-01-04
 * @version     V1.1.2
 ******************************************************************************
 */


#ifndef __MAIN_H
#define __MAIN_H

#include "stdio.h"
#include "at32f4xx_eth.h"
#include "at32f4xx_rtc.h"
#include "at32f4xx_pwr.h"
#include "netconf.h"
#include "lwip/tcp.h"

/* Static IP Address definition ***********************************************/
#define IP_ADDR0   192
#define IP_ADDR1   168
#define IP_ADDR2   1
#define IP_ADDR3   7
   
/* NETMASK definition *********************************************************/
#define NETMASK_ADDR0   255
#define NETMASK_ADDR1   255
#define NETMASK_ADDR2   255
#define NETMASK_ADDR3   0

/* Gateway Address definition *************************************************/
#define GW_ADDR0   192
#define GW_ADDR1   168
#define GW_ADDR2   1
#define GW_ADDR3   187

#define SYSTEMTICK_PERIOD_MS  10
#define USE_IAP_TFTP   /* enable IAP using TFTP */
#define USE_IAP_HTTP   /* enable IAP using HTTP */

#define USERID       "user"
#define PASSWORD     "at32"
#define LOGIN_SIZE   (15+ sizeof(USERID) + sizeof(PASSWORD))
	
void Time_Update(void);
void Delay(uint32_t nCount);
void System_Periodic_Handle(void);
void SYSCLKConfig_STOP(void);
#endif
