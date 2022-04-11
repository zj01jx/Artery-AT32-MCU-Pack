#include "iap.h"
#include "usart.h"
#include "flash.h"
#include "led.h"

CMD_DATA_STEP cmd_data_flag=CMD_DATA_IDLE;
CMD_CTR_STEP cmd_ctr_flag=CMD_CTR_IDLE;
u8 update_status=UPDATE_PRE;
CMD_DATA_STRUCT cmd_data_struct;
iapfun jump2app;

//跳转到应用程序段
//appxaddr:用户代码起始地址.
#pragma O0                                                                              //IAP_Load_APP不进行优化
void IAP_Load_APP(u32 appxaddr)
{
    if( ((*(vu32*)appxaddr)-0x20000000) < (SRAM_SIZE*1024) )    //检查栈顶地址是否合法.
    {
        jump2app=(iapfun)*(vu32*)(appxaddr+4);              //用户代码区第二个字为程序开始地址(复位地址)        
        MSR_MSP(*(vu32*)appxaddr);                                      //初始化APP堆栈指针(用户代码区的第一个字用于存放栈顶地址)
        jump2app();                                                                     //跳转到APP.
    }
}       
