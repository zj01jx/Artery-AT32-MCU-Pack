/**
  ******************************************************************************
  * @file    flash_if.c
  * @version V1.1.2
  * @date    2019-01-04
  * @brief   FLASH read and write API
  ******************************************************************************
  */
#include "flash_if.h"
#include "at32f4xx_flash.h"
#include "at32f4xx_crc.h"
/** @addtogroup AT32F403_StdPeriph_Examples
  * @{
  */

/** @addtogroup USB_VirtualMassStrorage_IAP_Demo
  * @{
  */ 
  
  /** @addtogroup Exported_macro
  * @{
  */

#define BIT_SET(REG, BIT)                       ((REG) |= (BIT))

#define BIT_CLEAR(REG, BIT)                     ((REG) &= ~(BIT))

#define BIT_READ(REG, BIT)                      ((REG) & (BIT))

#define REG_CLEAR(REG)                          ((REG) = (0x0))

#define REG_WRITE(REG, VAL)                     ((REG) = (VAL))

#define REG_READ(REG)                           ((REG))

#define REG_CHANGE(REG, CLEARMASK, SETMASK)     REG_WRITE((REG), (((REG_READ(REG)) & (~(CLEARMASK))) | (SETMASK)))

/**
  * @}
  */

uint32_t AT_FLASH_PAGE_SIZE = FLASH_PAGE2K_SIZE;
uint32_t AT_FLASH_SIZE = 0;
uint32_t AT_FLASH_PAGE_MASK = FLASH_PAGE2K_ALIGNED_MASK;
uint32_t FLASH_FIRMWARE_LENGTH = 0;
uint32_t FLASH_WRCRCValue = 0;
uint32_t FLASH_RDCRCValue = 0;

#define SET_MSP(dwValue) __ASM volatile ("msr msp, "#dwValue)
void (*pfTarget)(void); 
/**
  * @brief  init flash information
  * @param  None
  * @retval None
  */

void AT_FLASH_Init(void)
{
    uint32_t FlashS = *(uint32_t *)0x1FFFF7E0;
    AT_FLASH_SIZE = FlashS << 10;
    
    /*if flash size < 256K Byte, page size is 1k Byte*/
    if ( FlashS < 0x100)
    {
        AT_FLASH_PAGE_SIZE = FLASH_PAGE1K_SIZE;
        AT_FLASH_PAGE_MASK = FLASH_PAGE1K_ALIGNED_MASK;
    }else
    {   /*flash size >= 256K byte, page size is 2kByte*/
        AT_FLASH_PAGE_SIZE = FLASH_PAGE2K_SIZE;
        AT_FLASH_PAGE_MASK = FLASH_PAGE2K_ALIGNED_MASK;
    }
}

/**
  * @brief  Writes data to the FLASH. In this function, the number of
  *         WRITE cycles are reduced, using Page WRITE sequence.
  * @param  Wdata: pointer to the buffer  containing the data to be written
  *         to the FLASH.
  * @param  Address: FLASH's internal address to write to.
  * @param  NumByteToWrite: number of bytes to write to the FLASH.
   * @retval Status: 0 OK, 1 Faild, 2 CRC Faild
  */
uint8_t AT_FLASH_WriteBuffer(uint32_t Address, uint8_t *Wdata, uint32_t NumByteToWrite)
{
    uint32_t *dwBuffer, dwFlashAddr, BufCRC = 0, RdCRC = 0, BaseAddr = Address, Write_Len = NumByteToWrite;
    uint32_t dwNumByte, dwRemainByte, dwLastWordMask = 0xFFFFFFFF;
    dwNumByte = NumByteToWrite / sizeof(uint32_t);
    dwRemainByte = NumByteToWrite % sizeof(uint32_t);
    
    if ( (Address + NumByteToWrite) > (FLASH_BASE_ADDR + AT_FLASH_SIZE) )
        return 1;
    
    
    if ( (Address & AT_FLASH_PAGE_MASK ) == 0 )
    {
        FLASH_Unlock();
        if ( AT_FLASH_PAGE_MASK == FLASH_PAGE2K_ALIGNED_MASK )
        {
              if ( NumByteToWrite > FLASH_PAGE2K_SIZE)
              {
                  for ( Write_Len = NumByteToWrite; Write_Len >= FLASH_PAGE2K_SIZE; Write_Len -= FLASH_PAGE2K_SIZE)
                  {
                      if ( BaseAddr < FLASH_BASE_ADDR + AT_FLASH_SIZE)
                          FLASH_ErasePage(BaseAddr);
                      BaseAddr += FLASH_PAGE2K_SIZE;
                  }
                  if ( Write_Len > 0)
                  {
                      FLASH_ErasePage(BaseAddr);
                  }
               }else
              {
                  FLASH_ErasePage(BaseAddr);
              }
        }else
        {
            if ( NumByteToWrite > FLASH_PAGE1K_SIZE)
            {
                for ( Write_Len = NumByteToWrite; Write_Len >= FLASH_PAGE1K_SIZE; Write_Len -= FLASH_PAGE1K_SIZE)
                {
                    if ( BaseAddr < FLASH_BASE_ADDR + AT_FLASH_SIZE)
                        FLASH_ErasePage(BaseAddr);
                    BaseAddr += FLASH_PAGE1K_SIZE;
                }
                if ( Write_Len > 0)
                {
                      FLASH_ErasePage(BaseAddr);
                }
            }else
            {
                FLASH_ErasePage(BaseAddr);
            }
        }
      
        FLASH_Lock();
    }
    if ( dwRemainByte)
    {
        dwNumByte ++;
        dwLastWordMask <<= (dwRemainByte * 8);
    }
    
    dwBuffer = (uint32_t *)Wdata +  (dwNumByte - 1);
    dwFlashAddr = (Address + (dwNumByte - 1) * sizeof(uint32_t));
    if ( dwRemainByte )
    {
        *dwBuffer |= dwLastWordMask;
    }
    FLASH_Unlock();
    while ( dwNumByte -- )
    {
        FLASH_ProgramWord(dwFlashAddr, *dwBuffer--);
        dwFlashAddr -= 4;
    }
    FLASH_Lock();
    
    BufCRC = AT_CalculateCRC_Buffer((uint32_t *)Wdata, NumByteToWrite);
    RdCRC = AT_CalculateCRC_Flash(Address, NumByteToWrite);
    if ( BufCRC != RdCRC )
        return 2;
    return 0;
}

/**
  * @brief  Reads a block of data from the FLASH.
  * @param  Rdata: pointer to the buffer that receives the data read from the FLASH.
  * @param  Address: FLASH's internal address to read from.
  * @param  NumByteToRead: number of bytes to read from the FLASH.
  * @retval None
  */
void AT_FLASH_ReadBuffer(uint32_t Address, uint8_t *Rdata, uint32_t NumByteToRead)
{
    uint32_t i;
    for ( i = 0; i < NumByteToRead; i ++ )
    {
        Rdata[i] = *(uint8_t *)Address;
        Address ++;
    }
}

/**
  * @brief  Read flash data Calculate CRC.
  * @param  dwAddr: Flash Base Addr.
  * @param  NumByteToCrc: number of bytes to Calculate CRC.
  * @retval None
  */
uint32_t AT_CalculateCRC_Flash(uint32_t dwAddr, uint32_t NumByteToCrc)
{
    uint32_t i = 0, TmpCrc = 0, dwNumByte = NumByteToCrc / sizeof(uint32_t), RemainByte = NumByteToCrc % (sizeof (uint32_t ));
    uint32_t *pwAddr = (uint32_t *)dwAddr;
    if ( RemainByte )
    {
        dwNumByte += 1;
    }
    /*Enable CRC Clock*/
    BIT_SET(RCC->AHBEN, RCC_AHBEN_CRCEN);
    /*Reset CRC*/
    CRC_ResetDT();
    
    for ( i = 0; i < dwNumByte; i ++ )
    {
        TmpCrc = CRC_CalculateCRC(*pwAddr++);
    }
    /*Reset CRC*/
    CRC_ResetDT();
    /*Disable CRC clock*/
    BIT_CLEAR(RCC->AHBEN, RCC_AHBEN_CRCEN);
    return TmpCrc;
    
}
/**
  * @brief  Calculate buffer CRC.
  * @param  buffer: pointer to the buffer that need Calculate CRC.
  * @param  NumByteToCrc: number of bytes to Calculate CRC.
  * @retval None
  */
uint32_t AT_CalculateCRC_Buffer(uint32_t *buffer, uint32_t NumByteToCrc)
{
    uint32_t i = 0, TmpCrc = 0, dwNumByte = NumByteToCrc / sizeof(uint32_t), RemainByte = NumByteToCrc % (sizeof (uint32_t ));
    /*Enable CRC Clock*/
    BIT_SET(RCC->AHBEN, RCC_AHBEN_CRCEN);
    /*Reset CRC*/
    CRC_ResetDT();
    
    if ( RemainByte )
    {
        dwNumByte += 1;
        buffer[dwNumByte - 1] |= 0xFFFFFFFF << ( RemainByte * 8);
    }
    
    for ( i = 0; i < dwNumByte; i ++ )
    {
        TmpCrc = CRC_CalculateCRC(*buffer++);
    }
    /*Reset CRC*/
    CRC_ResetDT();
    /*Disable CRC clock*/
    BIT_CLEAR(RCC->AHBEN, RCC_AHBEN_CRCEN);
    return TmpCrc;
}

 /**
  * @brief  Jump to User Code
  * @param  dwAddr: User Code Start Address.
  * @retval None
  */
void IAP_Jump(uint32_t dwAddr)
{
    uint32_t dwStkPtr, dwJumpAddr;
    uint32_t i = 0;
    dwStkPtr = *(uint32_t *)dwAddr;
    dwJumpAddr = *(uint32_t *)(dwAddr + sizeof(uint32_t));
    if ( (dwStkPtr < SRAM_BASE) || ((dwStkPtr & 0xFF000000) != SRAM_BASE || (dwJumpAddr < FLASH_START_ADDR) || ((dwJumpAddr & 0xFF000000) != FLASH_BASE)) )
        return;
    for ( i = 0; i < 1000000; i ++)
       __NOP();

    RCC->APB2RST = 0xFFFFFFFF;
    RCC->APB2RST = 0;
    RCC->APB1RST = 0xFFFFFFFF;
    RCC->APB1RST = 0;
    RCC->AHBRST = 0xFFFFFFFF;
    RCC->AHBRST = 0;
    RCC->AHBEN &= ~RCC_AHBPERIPH_USB;
    RCC->APB2EN = 0;
    RCC->APB1EN = 0;
    
    SET_MSP(dwStkPtr);
    pfTarget = (void (*)(void))dwJumpAddr;
    pfTarget();

    
}

typedef struct
{
  __IO uint16_t RDP;
  __IO uint16_t USER;
  __IO uint16_t Data0;
  __IO uint16_t Data1;
  __IO uint16_t WRP0;
  __IO uint16_t WRP1;
  __IO uint16_t WRP2;
  __IO uint16_t WRP3;
  __IO uint16_t EOPB0;
  __IO uint16_t EOPB1;
  __IO uint16_t HID[4];
  __IO uint32_t Reserved;
  __IO uint32_t BANK3SCRKEY[4];
} OB_TypeDef1;

 /**
  * @brief  Write flag to optionbyte
  * @param  Flag
  * @retval None
  */
void AT_WriteOptionByte(uint8_t Flag)
{
//    OB_TypeDef tUobType;
//    uint16_t wHalfWordLength = sizeof ( OB_TypeDef), *UobData = (uint16_t *)(&tUobType);
//    uint32_t UobAddr = OB_BASE + 2, i;
//    tUobType = *OB;
//    tUobType.HID[0] = Flag;
//    FLASH_Unlock();  
//    FLASH_EraseOptionBytes();
//    UobData++;
//    for ( i = 0; i < ((wHalfWordLength >> 1) - 1); i ++, UobData++)
//    {
//        FLASH_ProgramOptionByteData(UobAddr, *(uint8_t *)UobData);
//        UobAddr += 2;
//    }
//    FLASH_Lock();
}


 /**
  * @brief  read flag from optionbyte
  * @param  None
  * @retval flag
  */
uint8_t AT_ReadOptionByte(void)
{
//    return (uint8_t)UOPTB->HID[0];
  return 0;
}
/**
  * @}
  */ 

/**
  * @}
  */



