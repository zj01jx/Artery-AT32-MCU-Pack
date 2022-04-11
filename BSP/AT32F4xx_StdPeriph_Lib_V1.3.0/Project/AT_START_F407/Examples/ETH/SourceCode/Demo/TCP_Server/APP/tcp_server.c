/**
  ******************************************************************************
  * File   : ETH/TCP_Server/tcp_server.c
  * Version: V1.3.0
  * Date   : 2021-03-18
  * Brief  : implement tcp layer function
  ******************************************************************************
  */
#include "main.h"

/**
  * @brief  receive and transmit TCP data
  * @param  arg:
  * @param  pcb:
  * @param  p:
  * @param  err:            
  * @retval ERR_OK: receive and transmit TCP data done
  */
static err_t tcp_server_recv(void *arg, struct tcp_pcb *pcb,struct pbuf *p,err_t err)
{
  char* pPrintBuf;
	if(p != NULL)
	{
    pPrintBuf = (char*)malloc(p->tot_len * sizeof(char));
    memset(pPrintBuf, 0, p->tot_len * sizeof(char));
    strncpy(pPrintBuf, p->payload, p->tot_len);
		tcp_recved(pcb, p->tot_len);				                      //Get data length; tot_len: length of tcp data block
		/*******************return received data*******************/
    printf("[%s][%u] %s\n", __func__, __LINE__, pPrintBuf);
		tcp_write(pcb,p->payload,p->tot_len,TCP_WRITE_FLAG_COPY); //payload is starting position of TCP data block
		tcp_output(pcb);
	}
	else
	{
		tcp_close(pcb); 											                    //TCP server shouldn't close this session actively
	}
	pbuf_free(p); 											                        //free the TCP segment
  free(pPrintBuf);
	err = ERR_OK;
	return err;
}

/**
  * @brief  callback function for receiving data
  * @param  arg:
  * @param  pcb:
  * @param  err:            
  * @retval ERR_OK: receive and transmit TCP data done
  */
static err_t tcp_server_accept(void *arg,struct tcp_pcb *pcb,err_t err)
{
	tcp_setprio(pcb, TCP_PRIO_MIN); 		                        //set the priority of callback function, if there are multiple session exist, this function must be called
	tcp_recv(pcb,tcp_server_recv); 			                        //set callbacl function for TCP segments come in
	err = ERR_OK;
	return err;
}

/**
  * @brief  Initialize TCP server
  * @param  None            
  * @retval None
  */
void TCP_server_init(void)
{
	struct tcp_pcb *pcb;
	err_t err;
	/*****************************************************/
	pcb = tcp_new(); 								                            //create TCP protocol control block for communication
	if (!pcb)
	{
		return ;
	}
	err = tcp_bind(pcb,IP_ADDR_ANY,TCP_LOCAL_PORT); 	          //bind local IP and port for TCP server
	if(err != ERR_OK)
	{
		return ;
	}
	pcb = tcp_listen(pcb); 							                        //entering listening status
	tcp_accept(pcb,tcp_server_accept); 			                    //set callback function for connection requestion

}
