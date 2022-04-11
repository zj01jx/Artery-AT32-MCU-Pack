/**
  ******************************************************************************
  * File   : USART/DMA_Polling/main.c 
  * Version: V1.3.0
  * Date   : 2021-03-18
  * Brief  : Main program body
  ******************************************************************************
  */ 

/* Includes ------------------------------------------------------------------*/
#include "at32f4xx.h"
#include "at32_board.h"

/** @addtogroup AT32F421_StdPeriph_Examples
  * @{
  */

/** @addtogroup USART_DMA_Polling
  * @{
  */ 
  
/* Private typedef -----------------------------------------------------------*/
typedef enum { FAILED = 0, PASSED = !FAILED} TestStatus;

/* Private define ------------------------------------------------------------*/
#define TxBufferSize1   (countof(TxBuffer1) - 1)
#define TxBufferSize2   (countof(TxBuffer2) - 1)

/* Private macro -------------------------------------------------------------*/
#define countof(a)   (sizeof(a) / sizeof(*(a)))

/* Private variables ---------------------------------------------------------*/
USART_InitType USART_InitStructure;
uint8_t TxBuffer1[] = "USART DMA Polling: USART1 -> USART2 using DMA";
uint8_t TxBuffer2[] = "USART DMA Polling: USART2 -> USART1 using DMA";
uint8_t RxBuffer1[TxBufferSize2];
uint8_t RxBuffer2[TxBufferSize1];
volatile TestStatus TransferStatus1 = FAILED;
volatile TestStatus TransferStatus2 = FAILED; 

/* Private function prototypes -----------------------------------------------*/
void RCC_Configuration(void);
void GPIO_Configuration(void);
void DMA_Configuration(void);
TestStatus Buffercmp(uint8_t* pBuffer1, uint8_t* pBuffer2, uint16_t BufferLength);

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program
  * @param  None
  * @retval None
  */
int main(void)
{       
  /* System Clocks Configuration */
  RCC_Configuration();

  /* Configure the GPIO ports */
  GPIO_Configuration();

  /* Initialize Leds mounted on board */
  AT32_Board_Init();
  
  /* Configure the DMA */
  DMA_Configuration();

/* USART1 and USART2 configuration ------------------------------------------------------*/
  /* USART1 and USART2 configured as follow:
        - BaudRate = 230400 baud  
        - Word Length = 8 Bits
        - One Stop Bit
        - No parity
        - Hardware flow control disabled (RTS and CTS signals)
        - Receive and transmit enabled
  */
  USART_StructInit(&USART_InitStructure);
  USART_InitStructure.USART_BaudRate = 230400;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
  
  /* Configure USART1 */
  USART_Init(USART1, &USART_InitStructure);
  /* Configure USART2 */
  USART_Init(USART2, &USART_InitStructure);

  /* Enable USART1 DMA Rx and TX request */
  USART_DMACmd(USART1, USART_DMAReq_Rx | USART_DMAReq_Tx, ENABLE);
  /* Enable USART2 DMA Rx and TX request */
  USART_DMACmd(USART2, USART_DMAReq_Rx | USART_DMAReq_Tx, ENABLE);

  /* Enable USART1 TX DMA1 Channel */
  DMA_ChannelEnable(DMA1_Channel2, ENABLE);
  /* Enable USART1 RX DMA1 Channel */
  DMA_ChannelEnable(DMA1_Channel3, ENABLE);

  /* Enable USART2 TX DMA1 Channel */
  DMA_ChannelEnable(DMA1_Channel4, ENABLE);
  /* Enable USART2 RX DMA1 Channel */
  DMA_ChannelEnable(DMA1_Channel5, ENABLE);

  /* Enable the USART2 */
  USART_Cmd(USART1, ENABLE);
  /* Enable the USART2 */
  USART_Cmd(USART2, ENABLE);

  /* Wait until USART1 TX DMA1 Channel Transfer Complete */
  while (DMA_GetFlagStatus(DMA1_FLAG_TC2) == RESET)
  {
  }
  /* Wait until USART1 RX DMA1 Channel Transfer Complete */
  while (DMA_GetFlagStatus(DMA1_FLAG_TC3) == RESET)
  {
  }

  /* Wait until USART2 TX DMA1 Channel Transfer Complete */
  while (DMA_GetFlagStatus(DMA1_FLAG_TC4) == RESET)
  {
  }
  /* Wait until USART2 RX DMA1 Channel Transfer Complete */
  while (DMA_GetFlagStatus(DMA1_FLAG_TC5) == RESET)
  {
  }

  /* Check the received data with the send ones */
  TransferStatus1 = Buffercmp(TxBuffer2, RxBuffer1, TxBufferSize2);
  /* TransferStatus1 = PASSED, if the data transmitted from USART2 and  
     received by USART1 are the same */
  /* TransferStatus1 = FAILED, if the data transmitted from USART2 and 
     received by USART1 are different */
  TransferStatus2 = Buffercmp(TxBuffer1, RxBuffer2, TxBufferSize1);
  /* TransferStatus2 = PASSED, if the data transmitted from USART1 and  
     received by USART2 are the same */
  /* TransferStatus2 = FAILED, if the data transmitted from USART1 and 
     received by USART2 are different */

  /* Judge whether the result is correct */
  if((TransferStatus1 == PASSED)&&(TransferStatus2 == PASSED))
  {
    /*Trun on the LED*/
    AT32_LEDn_ON(LED2);
    AT32_LEDn_ON(LED3);
    AT32_LEDn_ON(LED4);
  }

  while (1)
  {
  }
}

/**
  * @brief  Configures the different system clocks.
  * @param  None
  * @retval None
  */
void RCC_Configuration(void)
{  
  /* DMA clock enable */
  RCC_AHBPeriphClockCmd(RCC_AHBPERIPH_DMA1, ENABLE);

  /* Enable GPIO clock */
  RCC_AHBPeriphClockCmd(RCC_AHBPERIPH_GPIOA, ENABLE);

  /* Enable USART1 Clock */
  RCC_APB2PeriphClockCmd(RCC_APB2PERIPH_USART1, ENABLE); 

  /* Enable USART2 Clock */
  RCC_APB1PeriphClockCmd(RCC_APB1PERIPH_USART2, ENABLE);  
}

/**
  * @brief  Configures the different GPIO ports.
  * @param  None
  * @retval None
  */
void GPIO_Configuration(void)
{
  GPIO_InitType GPIO_InitStructure;
  
  /* Connect PXx to USART1_Tx */
  GPIO_PinAFConfig(GPIOA, GPIO_PinsSource9, GPIO_AF_1);
  /* Connect PXx to USART1_Rx */
  GPIO_PinAFConfig(GPIOA, GPIO_PinsSource10, GPIO_AF_1);
  /* Connect PXx to USART2_Tx */
  GPIO_PinAFConfig(GPIOA, GPIO_PinsSource2, GPIO_AF_1);
  /* Connect PXx to USART2_Rx */
  GPIO_PinAFConfig(GPIOA, GPIO_PinsSource3, GPIO_AF_1);
  
  /* Configure USART1 Tx/Rx and USART2 Tx/Rx */
  GPIO_StructInit(&GPIO_InitStructure);
  GPIO_InitStructure.GPIO_Pins = GPIO_Pins_9 | GPIO_Pins_10 | GPIO_Pins_2 | GPIO_Pins_3;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_MaxSpeed = GPIO_MaxSpeed_50MHz;
  GPIO_InitStructure.GPIO_OutType = GPIO_OutType_PP;
  GPIO_InitStructure.GPIO_Pull = GPIO_Pull_NOPULL;
  GPIO_Init(GPIOA, &GPIO_InitStructure); 
}

/**
  * @brief  Configures the DMA.
  * @param  None
  * @retval None
  */
void DMA_Configuration(void)
{
  DMA_InitType DMA_InitStructure;

  /* USART1 TX DMA1 Channel (triggered by USART1 Tx event) Config */
  DMA_Reset(DMA1_Channel2);
  DMA_DefaultInitParaConfig(&DMA_InitStructure);
  DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&USART1->DT;
  DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)TxBuffer1;
  DMA_InitStructure.DMA_Direction = DMA_DIR_PERIPHERALDST;
  DMA_InitStructure.DMA_BufferSize = TxBufferSize1;
  DMA_InitStructure.DMA_PeripheralInc = DMA_PERIPHERALINC_DISABLE;
  DMA_InitStructure.DMA_MemoryInc = DMA_MEMORYINC_ENABLE;
  DMA_InitStructure.DMA_PeripheralDataWidth = DMA_PERIPHERALDATAWIDTH_BYTE;
  DMA_InitStructure.DMA_MemoryDataWidth = DMA_MEMORYDATAWIDTH_BYTE;
  DMA_InitStructure.DMA_Mode = DMA_MODE_NORMAL;
  DMA_InitStructure.DMA_Priority = DMA_PRIORITY_VERYHIGH;
  DMA_InitStructure.DMA_MTOM = DMA_MEMTOMEM_DISABLE;
  DMA_Init(DMA1_Channel2, &DMA_InitStructure);

  /* USART1 RX DMA1 Channel (triggered by USART1 Rx event) Config */
  DMA_Reset(DMA1_Channel3);  
  DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&USART1->DT;
  DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)RxBuffer1;
  DMA_InitStructure.DMA_Direction = DMA_DIR_PERIPHERALSRC;
  DMA_InitStructure.DMA_BufferSize = TxBufferSize2;
  DMA_Init(DMA1_Channel3, &DMA_InitStructure);
  
  /* USART2 TX DMA1 Channel (triggered by USART2 Tx event) Config */
  DMA_Reset(DMA1_Channel4);  
  DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&USART2->DT;
  DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)TxBuffer2;
  DMA_InitStructure.DMA_Direction = DMA_DIR_PERIPHERALDST;
  DMA_InitStructure.DMA_BufferSize = TxBufferSize2;  
  DMA_Init(DMA1_Channel4, &DMA_InitStructure);
  
  /* USART2 RX DMA1 Channel (triggered by USART2 Rx event) Config */
  DMA_Reset(DMA1_Channel5);  
  DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&USART2->DT;
  DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)RxBuffer2;
  DMA_InitStructure.DMA_Direction = DMA_DIR_PERIPHERALSRC;
  DMA_InitStructure.DMA_BufferSize = TxBufferSize1;
  DMA_Init(DMA1_Channel5, &DMA_InitStructure);  
}
/**
  * @brief  Compares two buffers.
  * @param  pBuffer1, pBuffer2: buffers to be compared.
  * @param  BufferLength: buffer's length
  * @retval PASSED: pBuffer1 identical to pBuffer2
  *         FAILED: pBuffer1 differs from pBuffer2
  */
TestStatus Buffercmp(uint8_t* pBuffer1, uint8_t* pBuffer2, uint16_t BufferLength)
{
  while(BufferLength--)
  {
    if(*pBuffer1 != *pBuffer2)
    {
      return FAILED;
    }

    pBuffer1++;
    pBuffer2++;
  }

  return PASSED;
}

#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {}
}

#endif

/**
  * @}
  */ 

/**
  * @}
  */ 


