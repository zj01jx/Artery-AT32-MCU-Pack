/**
  ******************************************************************************
  * File   : Project_L0/readme.txt 
  * Version: V1.3.0
  * Date   : 2021-03-18
  * Brief  : readme
  ******************************************************************************
  */
 
@par Example Description 

  This project (STEP1 of the sLib example) describes how to generate an execute-only IP-Code (using compiler options), place and protect it 
  (protection using sLib) in some preferred sectors in internal flash memory.
  The FIR Filter algorithm from CMSIS library is chosen as an example of IP-Code to be protected.
  Enabling sLib is managed by software in SLIB_Enable() function.
  The IP-Code function FIR_lowpass_filter()is called in main.c file.
  Note that symbol definition file have to be generated in SLIP-IP-Code-XO project configuration described below, it has to be used in
  customer project Project_L1.
  
  Because the AT32F421 does not have FPU, so the software floating-point library will be used for floating-point arithmetic operation.
  
  However, some functions in the prebuilt library have literal-pool. So these functions can not be placed in the sLib I-Bus protected area ( sLib-code-area).

  These functions are then placed in the I/D-Bus protected area (sLib-readonly-area) . Please refer to the application note for more detailed 
  
  description.
        
  
  With the SLIP-IP-Code-XO project configurations, the compiler is configured to generate an execute-only IP-Code avoiding any data read from 
  it (avoiding literal pools and branch tables), and all thes used software floting-point library functions are placed in the  sLib-mix-area.
  
  
  @note The IP-Code and IP-Data are placed in page 52 to page 63 (address 0x0800D000 ~ 0x0800FFFF) which will be protected.
  
        Activating the sLib on these pages is completed by SLIB_Enable() function descripes in main file.

 @note The application needs to ensure that the SysTick time base is always set to 1 millisecond to have correct operation.
 
 
@par Directory contents 

  - Project_L0/src/main.c                             Main program
  - Project_L0/src/system_at32f4xx.c                     AT32F4xx system clock configuration file
  - Project_L0/src/at32f4xx_it.c                         Interrupt handlers 
  - Project_L0/src/math_helper.c                         Calculation of SNR 
  - Project_L0/src/arm_fir_data.c                        Contains FIR_Filter's Input signal and Reference output signal computed with MATLAB
  - Project_L0/inc/at32f4xx_it.h                         Interrupt handlers header file
  - Project_L0/inc/fir_filter.h                          FIR-Filter SLIB protected IP-Code header file
  - Project_L0/inc/math_helper.h                         math_helper header file

FIR Filter files representing the IP-Code to be protected
  - Project_L0/src/fir_filter.c                          File containing global FIR Low Pass Filter function   
  - Project_L0/src/arm_fir_f32.c                         File containing FIR Filter basic function from CMSIS lib
  - Project_L0/src/arm_fir_init_f32.c                    File containing FIR Filter Initialization function from CMSIS lib
  - Project_L0/src/fir_coefficient.c                     File containing FIR Coefficients generated using fir1() MATLAB function.
  
  
@par Hardware and Software environment  

  - This example runs on AT32F421C8T7 devices.
  - This example has been tested with AT-START-F421 V1.0 board.
  - This example has been tested with the following toolchain:
      - Keil MDK-ARM uVision V5.23.0.0 
      - IAR Embedded Workbench V7.40.3

@par Generating symbol definition file 
	Generating symbol definition file is mandatory for Project_L1 and the provided file must be replaced by the newly generated. 
	To generate symbol definition file required for Project_L1, click on Rebuild all button then symbol definition file is created. 
        - For MDK-ARM toolchain: fir_filter_symbol.txt symbol definition file is created inProject_L0\MDK_V5\SLIB-IP-CODE-XO.
          It must be modified by deleting all lines and keeping only FIR-Filter IP-Code functions (please follow the provided fir_filter_symbol.txt file
          in Project_L1\MDK_V5). Once modified, copy it to Project_L1\MDK_V5 and replace the existing file.

@par How to use it ? 

Before running this project the following conditions must be met:
- The same toolchain and compiler version must be used for both projects in Project_L0 and Project_L1: for instance if MDK-ARM V5.23 is used 
  in Project_L0 then it must be used for Project_L1 too.
- Check if any Read out protection, write protection or sLib protection is enabled, if yes disable this protection 

In order to make the program work, you must do the following :

Configurate the compiler to generate an execute only IP-Code avoiding any data read from it (literal pools and branch tables) . 
	1. Open project located in Project_L0 directory and choose your preferred toolchain 
	2. Select the SLIB-IP-Code-XO project configuration
	3. Rebuild all files. 
	4. Run the example following the sequence below:
		(a) Power on the board then load the code, WHITE LED should toggle continuously, if not press RESET button;
        (b) Press the user button key to execute the IP-code called in main.c file,
		(c) If "USE_SLIB_FUNCTION" is defined and SLIB is never enabled, go to step (e). 
        (d) If the IP-Code is successfully executed, the GREEN LED should toggle continuously. Else the RED LED toggles continuously.  
		(e) If "USE_SLIB_FUNCTION" is defined and SLIB is never enabled, the the SLIB_Enable() function will set SLIB configuration once the
            IP-Code is correctly executed. The GREEN LED will toggle some time and then a system rest is executed to activate SLIB. 
            The code will run to step (b) again.            

 */ 



