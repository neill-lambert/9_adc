


#ifndef UART_H_
#define UART_H_

#include "stm32wb55xx.h"

void usart1_tx_en (void);
void usart1_rxtx_en (void);
char uart1_read(void);
void uart1_write(int ch);
void uart1_print(int ch);




#endif /* UART_H_ */
