#include <stdio.h>
#include <stdint.h>

#include "stm32wb55xx.h"
#include "uart.h"
#include "led.h"
#include "adc.h"
#include "rcc.h"


//where did i get this from???
//israel gbati bare metal stm32

uint32_t adcVal;


int main(void){
	rcc_init();

	usart1_tx_en();

	pc0_adc_init();

	while(1){
		startConversion();
		adcVal = (uint32_t)readAdc();
		printf ("sensor value = %d \n\r", (int) adcVal);

	}
}

























