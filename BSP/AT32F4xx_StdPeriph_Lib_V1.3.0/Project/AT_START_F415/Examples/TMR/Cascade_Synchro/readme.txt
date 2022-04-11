/**
  @page TMR_Cascade_Synchro example
  
  @verbatim
  * File   : TMR/Cascade_Synchro/readme.txt 
  * Version: V1.3.0
  * Date   : 2021-03-18
  * Brief  : Description of the TMR_Cascade_Synchro example.
  ******************************************************************************
   @endverbatim

@par Example Description
  This demo shows how to synchronize TMR peripherals in cascade mode.
  In this example three timers are used:
  
  Timers synchronisation in cascade mode:
  1/TMR2 is configured as Master Timer:
  - PWM Mode is used
  - The TMR2 Update event is used as Trigger Output  
  
  2/TMR3 is slave for TMR2 and Master for TMR4,
  - PWM Mode is used
  - The ITR1(TMR2) is used as input trigger 
  - Gated mode is used, so start and stop of slave counter
    are controlled by the Master trigger output signal(TMR2 update event).
  - The TIM3 Update event is used as Trigger Output. 
  
  3/TMR4 is slave for TIM3,
  - PWM Mode is used
  - The ITR2(TMR3) is used as input trigger
  - Gated mode is used, so start and stop of slave counter  are controlled by the
    Master trigger output signal(TMR3 update event).
  
  The Master Timer TMR2 is running at TMR2 frequency :
  TIM2 frequency = (TMR2 counter clock)/ (TMR2 period + 1) = 561.8 KHz 
  and the duty cycle = TMR2_CCR1/(TMR2_ARR + 1) = 25%.

  The TMR3 is running at:
  (TMR2 frequency)/ (TMR3 period + 1) = 140.4 KHz and a duty cycle equal 
  to TMR3_CCR1/(TMR3_ARR + 1) = 25%

  The TMR4 is running at:
  (TMR3 frequency)/ (TMR4 period + 1) = 35.16 KHz and a duty cycle equal 
  to TMR4_CCR1/(TMR4_ARR + 1) = 25%  

o The TIMxCLK is fixed to 144 MHz, the TMR2 counter clock is 144 MHz.
  So TMR2 frequency = 561.8 KHz,
  TMR3 is running at 140.4 KHz,
  and TMR4 is running at 35.16 KHz
  
  Set-up 
    - Connect the following pins to an oscilloscope to monitor the different 
      waveforms:
        - TMR2 CH1 (PA.00) 
        - TMR3 CH1 (PA.06)
        - TMR4 CH1 (PB.06)
 */