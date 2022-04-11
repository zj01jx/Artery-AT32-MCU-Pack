/**
  @page ADC_ADC1_DMA ADC1 DMA example
  
  @verbatim
  * File   : ADC/ADC1_DMA/readme.txt 
  * Version: V1.3.0
  * Date   : 2021-03-18
  * Brief  : Description of the ADC1 DMA example.
  ******************************************************************************
   @endverbatim

@par Example Description 

This example describes how to use the ADC1 and DMA to transfer continuously 
converted data from ADC1 to memory.
The ADC1 is configured to scan convert continuously channel1/channel2/channel3.
Each time an end of conversion occurs the DMA transfers, in circular mode, the
converted data from ADC1 DR register to the ADC_RegularConvertedValueTab array.
   ADC_RegularConvertedValueTab[0] <---> ADC_Channel_1
   ADC_RegularConvertedValueTab[1] <---> ADC_Channel_2
   ADC_RegularConvertedValueTab[2] <---> ADC_Channel_3

 */
