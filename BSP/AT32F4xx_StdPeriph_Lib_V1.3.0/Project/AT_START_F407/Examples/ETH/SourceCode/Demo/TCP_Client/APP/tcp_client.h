/**
  ******************************************************************************
  * File   : ETH/TCP Client/tcp_client.h
  * Version: V1.3.0
  * Date   : 2021-03-18
  * Brief  : Header file for TCP client
             1. Define sockets of TCP server and client
             2. Declare prototype function of TCP client related
  ******************************************************************************
  */

#include "stdint.h"
#include "lwip/err.h"

#ifndef  _TCP_CLIENT_H_
#define  _TCP_CLIENT_H_

/* TCP server and client configuration*/
#define TCP_LOCAL_PORT     		1030 
#define TCP_SERVER_PORT    		1031

#define TCP_SERVER_IP   192,168,1,19        //server IP

extern struct tcp_pcb *tcp_client_pcb;

void Delay_s(unsigned long ulVal);
void TCP_Client_Init(u16_t local_port,u16_t remote_port,unsigned char a,unsigned char b,unsigned char c,unsigned char d);
err_t TCP_Client_Send_Data(struct tcp_pcb *cpcb,unsigned char *buff,unsigned int length);
struct tcp_pcb *Check_TCP_Connect(void);
#endif

