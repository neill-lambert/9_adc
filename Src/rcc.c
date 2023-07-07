#include "stm32wb55xx.h"
#include "rcc.h"

#define PLLN	 32
#define PLLP	 2
#define PLLM	 1


void rcc_init(){

	// 1. set hse/ msi/ hsi and wait til ready
	RCC->CR |= RCC_CR_MSION;	//MSI_ON
	while (!(RCC->CR & RCC_CR_MSIRDY)); // wait til msi ready

	//2. power enable clock and voltage regulator
	RCC->AHB2ENR |= RCC_AHB2ENR_ADCEN; //try commenting/uncommenting this
	//2.5 adc deeppwr enable is in adc.c
	// but lets enable it here in case we need to...
	ADC1->CR &= ~(ADC_CR_DEEPPWD); //this belongs in adc.c
			// vr enable
	ADC1->CR |= ADC_CR_ADVREGEN; //this belongs in adc.c
	//3.configure flash prefetch and latency settings.

	// see rm p77 for flash latency info
	// see rm p109 flash_acr registers
	FLASH->ACR = (1<<8) | (1<<9)| (1<<10)| (FLASH_ACR_LATENCY_0WS);

	//4 .configure prescalars hclk pclk pclk2.
	RCC->CFGR &= ~(1<<7) | ~(1<<6) | ~(1<<5) | ~(1<<4); // HPRE zero to 4th bit up to 7th bit
	RCC->CFGR &= ~(1<<13) | ~(1<<12) | ~(1<<11);
	RCC->CFGR &= ~(1<<10) | ~(1<<9) | ~(1<<8);


	//5. configure main pll.
	RCC->PLLCFGR |= (1<<0); // MSI AS CLOCK
	// ALSO PLLP, N, M
	RCC->PLLCFGR |= (1<<17); // PLLP
	RCC->PLLCFGR |= (PLLN<<8);

	RCC->CR |= (RCC_CR_PLLSAI1ON); // pll sai on/ready.
	while (!(RCC->CR % (RCC_CR_PLLSAI1RDY)));
	RCC->CR |= (RCC_CR_MSIPLLEN); //this wont happen unless lseon is enabled rm p223

	//6. enable pll, wait for ready.
	RCC->CR |= (1U<<24); //PLL_ON
	while (!(RCC->CR & (1<<25)));
	//7. select clock source, wait for ready.
		//system clock source???
		//select MSI as sysclk source?? <q> this pg 225 ref manual. not sure!!!!
		//RCC->CFGR MCOSEL (27:24) TO 0010
	RCC->CFGR &= ~(1U<<0); // 00 TO SW (MSI = SYSTEM CLOCK)
	RCC->CFGR &= ~(1U<<1);
	//while(!(RCC->CFGR & ((0<<2) & (0<<3)))); // read 00 from SWstatus bits 3:2




}

