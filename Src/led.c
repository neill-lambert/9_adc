
#include "led.h"

#define GPIOBEN			(1U<<1)

#define PIN5			(1U<<5)
#define LED_PIN			PIN5



void pin_5_on(void){
	RCC->AHB2ENR |= GPIOBEN;
		GPIOB->MODER |= (1U<<10);
		GPIOB->MODER &=~ (1U<<11);

	GPIOB->ODR |= LED_PIN;



}

void pin_5_off(void){
	RCC->AHB2ENR |= GPIOBEN;
		GPIOB->MODER |= (1U<<10);
		GPIOB->MODER &=~ (1U<<11);

	GPIOB->ODR &= ~LED_PIN;


}

