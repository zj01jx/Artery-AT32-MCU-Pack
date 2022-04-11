/**
  @page TMR_Parallel_Synchro example
  
  @verbatim
  * File   : TMR/Parallel_Synchro/readme.txt 
  * Version: V1.3.0
  * Date   : 2021-03-18
  * Brief  : Description of the TMR_Parallel_Synchro example.
  ******************************************************************************
   @endverbatim

@par Example Description 
    This demo is based on the AT-START-F403A board,in this demo,PA6 ,PA0 and PB6 output pwm waveform.
    The TMRxCLK is fixed to 240   MHz, the TMR2 counter clock is 240 MHz.
    The Master TMRer TMR2 is running at 750 KHz and the duty cycle
    is equal to 25%
    The TMR3 is running:
    - At (TMR2 frequency)/ (TMR3 period + 1) = 75 KHz and a duty cycle
    equal to TMR3_CCR1/(TMR3_ARR + 1) = 30%
    The TMR4 is running:
    - At (TMR2 frequency)/ (TMR4 period + 1) = 150 KHz and a duty cycle
    equal to TMR4_CCR1/(TMR4_ARR + 1) = 60%  
	
 */

