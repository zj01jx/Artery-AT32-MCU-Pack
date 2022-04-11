/**
  ******************************************************************************
  * File   : ETH/TCP Client/main.h
  * Version: V1.3.0
  * Date   : 2021-03-18
  * Brief  : This file contains all the functions prototypes for the 
                ethernet function
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
#include "APP/tcp_client.h"

#define SYSTEMTICK_PERIOD_MS  10

void Time_Update(void);
void Delay(uint32_t nCount);
void System_Periodic_Handle(void);
#endif
