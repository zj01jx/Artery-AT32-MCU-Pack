/**
  @page ADC_3ADCs_DMA 3 ADCs DMA example
  
  @verbatim
  * File   : ADC/3ADCs_DMA/readme.txt 
  * Version: V1.3.0
  * Date   : 2021-03-18
  * Brief  : Description of the 3ADCs DMA example.
  ******************************************************************************
   @endverbatim

@par Example Description 

This example describes how to use the the same trigger source trigger 3 ADCs. 
   ADC1_RegularConvertedValueTab[0] <---> (ADC2_Channel_2<<16) | ADC1_Channel_1
   ADC1_RegularConvertedValueTab[1] <---> (ADC2_Channel_3<<16) | ADC1_Channel_2
   ADC1_RegularConvertedValueTab[2] <---> (ADC2_Channel_1<<16) | ADC1_Channel_3
   ADC3_RegularConvertedValueTab[0] <--->  ADC3_Channel_10
   ADC3_RegularConvertedValueTab[1] <--->  ADC3_Channel_11
   ADC3_RegularConvertedValueTab[2] <--->  ADC3_Channel_12

 */
