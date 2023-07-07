/*
 * adc.h
 *
 *  Created on: 20 Dec 2021
 *      Author: neillsyard
 */

#ifndef ADC_H_
#define ADC_H_

#include <stdint.h>

void pc0_adc_init(void);
void startConversion(void);
uint32_t readAdc(void);


#endif /* ADC_H_ */
