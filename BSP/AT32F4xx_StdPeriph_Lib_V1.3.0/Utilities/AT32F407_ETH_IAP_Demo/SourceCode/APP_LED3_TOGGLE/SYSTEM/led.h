#ifndef __LED_H
#define __LED_H	 
#include "at32f4xx.h"

#define LED_GPIO_RCC						RCC_APB2PERIPH_GPIOD	
#define LED_GPIO_PORT						GPIOD	
#define LED2_GPIO_PIN						GPIO_Pins_13
#define LED3_GPIO_PIN						GPIO_Pins_14
#define LED4_GPIO_PIN						GPIO_Pins_15

#define TOGGLE_LED(A)			LED_GPIO_PORT->OPTDT ^= A;

void LED_Init(void);
		 				    
#endif
