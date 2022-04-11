/**
  @page ADC_2ADCs_DMA 2 ADCs DMA example
  
  @verbatim
  * File   : ADC/2ADCs_DMA/readme.txt 
  * Version: V1.3.0
  * Date   : 2021-03-18
  * Brief  : Description of the 2ADCs DMA example.
  ******************************************************************************
   @endverbatim

@par Example Description 

This example describes how to use the 2 ADCs in independent conversions. 
Two of them; ADC1 is transferring continuously converted data using DMA
while ADC2 converted data are stored using End of conversion interrupt.

ADC1 is configured to convert continuously ADC channel14. Each time an end of
conversion occurs the DMA1 transfers, in circular mode, the converted data from 
ADC1 DR register to the ADC1_ConvertedValue variable.

ADC2 is configured to convert continuously ADC channel13. Each time an end of
conversion occurs an end of conversion interrupt is generated and inside the
interrupt routine the converted data are read from ADC2 DR register and stored
into the ADC2_ConvertedValue variable.

The ADCs clocks are set to 24 MHz.

The result of ADC1 and ADC2 conversion is monitored through the three
variables: ADC1ConvertedValue and ADC2ConvertedValue.

 */
