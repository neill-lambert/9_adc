#include "stm32wb55xx.h"
#include "adc.h"


#define ADC1EN  	(1U<<13) 	//on RCC_AHB2ENR
#define GPIOCEN		(1U<<2)
#define ADC_CH1		(1U<<6)
#define ADC_EN		(1U<<0)
#define ADC_CR_START	(1U<<2)	//on ADC_CR
#define ADC_EOC		(1U<<2) //on ADC_ISR


void pc0_adc_init(void){


	//disable adc en
	ADC1->CR &= ~(ADC_EN);

	//enable clock access GPIOC pin
	RCC->AHB2ENR |= GPIOCEN;

	//configure ADC module
	//select HSI16 as sysclk source?? ck this pg 225 ref manual. not sure!!!!
	// also chk RCC_CFGR->MCOSEL

	//2.5 adc is deep power down mode by default, lets exit that... (ref man p.423)
		ADC1->CR &= ~(ADC_CR_DEEPPWD); //this belongs in adc.c
		// vr enable
		ADC1->CR |= ADC_CR_ADVREGEN; //this belongs in adc.c


	//enable clock access to ADC
	//(disabled for trial)
	//RCC->AHB2ENR |= ADC1EN;

	//enable pll  RCC_PLLCFGR ???? rm 1531

	// select pllsai1rclk as adc clock
	RCC->CCIPR |= RCC_CCIPR_ADCSEL_0; 	//chk this: 01: PLLSAI1 “R” clock (PLLSAI1RCLK) selected as ADC clock


	//set PC0 to analog mode GPIOC MODER
	GPIOC->MODER |= (1U<<0);
	GPIOC->MODER |= (1U<<1);

	//what about additional function???




	//configure ADC prescalar
	ADC1_COMMON->CCR = 0; //reset

	ADC1_COMMON->CCR |= (ADC_CCR_PRESC_3 | ADC_CCR_PRESC_1);
	//ADC_CCR |= CKMODE;
	ADC1_COMMON->CCR |= ~(ADC_CCR_CKMODE_0); //this should be zero???

	//sequence and length parameters
	ADC1->SQR1 = ADC_CH1;
	//length = zero to bit 0-3 sqr1
	ADC1->SQR1 &= ~(1U<<0);
	ADC1->SQR1 &= ~(1U<<1);
	ADC1->SQR1 &= ~(1U<<2);
	ADC1->SQR1 &= ~(1U<<3);

	//continuous mode
	//ADC1->CFGR |= ADC_CFGR_CONT;

	//scan and resolution
	//ADC1->CFGR


	//enable ADC
	ADC1->CR = ADC_EN;
}

void startConversion(void){
		ADC1->CR |= ADC_CR_START;
}
uint32_t readAdc(void){
	while(!(ADC1->ISR & ADC_EOC)){}
		return (ADC1->DR);
}
