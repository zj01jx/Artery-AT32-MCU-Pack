/**
  @page TMR_Gated_Mode example
  
  @verbatim
  * File   : TMR/Gated_Mode/readme.txt 
  * Version: V1.3.0
  * Date   : 2021-03-18
  * Brief  : Description of the TMR_Gated_Mode example.
  ******************************************************************************
   @endverbatim

@par Example Description
  This demo shows how to test Gated mode with an external trigger.
  
  Gated mode test -----
    1/TMR1 is configured as Master Timer:
     - Toggle Mode is used

    2/TMR1 is configured as Slave Timer for an external Trigger connected
     to TMR1 TI2 pin (TMR1 CH2 configured as input pin):
     - The TMR1 TI2FP2 is used as Trigger Input
     - Rising edge is used to start and stop the TMR1: Gated Mode.

    * The TIMxCLK is fixed to 192 MHZ, the Prescaler is equal to 2 so the TMRx clock 
      counter is equal to 64 MHz.
      The Three Timers are running at: 
      TMRx frequency = TMRx clock counter/ 2*(TIMx_Period + 1) = 432.432 KHz. 
      
  Set-up 
  - Connect the following pins to an oscilloscope to monitor the different waveforms:
      - TIM1 CH1 (PA.08)
  
 */