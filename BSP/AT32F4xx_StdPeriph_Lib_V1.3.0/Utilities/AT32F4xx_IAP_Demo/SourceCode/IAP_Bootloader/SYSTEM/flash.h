#ifndef __FLASH_H__
#define __FLASH_H__
#include "sys.h"  

// 所选AT32的FLASH SIZE(单位为KByte)
#define FLASH_SIZE  (*((uint32_t*)0x1FFFF7E0))    /* Read from flash capacity register */

#if defined (AT32F403xx) || defined (AT32F403Axx) || defined (AT32F407xx)
		#define SRAM_SIZE 		224
#elif defined AT32F413xx
		#define SRAM_SIZE 		64
#elif defined AT32F415xx
		#define SRAM_SIZE 		32
#elif defined AT32F421xx
		#define SRAM_SIZE 		16
#endif
u8 FLASH_Read_Upgrade_Flag(void);
void FLASH_Write_2KB(u32 WriteAddr, u8 *pBuffer);

#endif
