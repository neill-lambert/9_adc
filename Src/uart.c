#include "uart.h"



#define GPIOAEN			(1U<<0)
#define GPIOBEN			(1U<<1)



#define USART1EN		(1U<<14)

#define CR1_TE 			(1U<<3)
#define CR1_RE			(1U<<2)
#define CR1_UE 			(1U<<0)

#define CR3_OVRDIS		(1U<<12)

#define ISR_TXE 		(1U<<7)
#define ISR_RXNE		(1U<<5)

#define SYS_FREQ 		4000000
#define APB2_FREQ		SYS_FREQ
#define UART_BAUDRATE 	115200


static void 	uart_set_baudrate(USART_TypeDef *USARTx, uint32_t PeriphClk, uint32_t BaudRate);
static uint16_t compute_uart_bd (uint32_t PeriphClk, uint32_t BaudRate);

void uart1_write(int ch);
char uart1_read(void);
void uart1_print(int ch);


//re-implement putchar
int __io_putchar( int ch){
	uart1_write(ch);
		return ch;
}


void usart1_rxtx_en (void){
	/* configure uart gpio pin:
	 * enable gpio clk access
	 * set pb6 to af
	 * set pb6 to function type usart1_tx af7
	 * (usart1tx af pb6 af7) datasheet table 18
	 *
	 *
	 * configure uart module:
	 * enable uart clk access
	 * configure baud/transfer direction
	 * enable uart module
	 */
	RCC->AHB2ENR |= GPIOBEN;

	GPIOB->MODER &= ~(1U<<12);
	GPIOB->MODER |=   (1U<<13);

	GPIOB->AFR[0]  |= (1U<<24);
	GPIOB->AFR[0]  |= (1U<<25);
	GPIOB->AFR[0]  |= (1U<<26);
	GPIOB->AFR[0]  &= ~(1U<<27);

	//set pb7 to af
	//and to function type usart1 rx af7
	GPIOB->MODER &= ~(1U<<14);
	GPIOB->MODER |=   (1U<<15);

	GPIOB->AFR[0]  |= (1U<<28);
	GPIOB->AFR[0]  |= (1U<<29);
	GPIOB->AFR[0]  |= (1U<<30);
	GPIOB->AFR[0]  &= ~(1U<<31);

	//configure led op pin

	GPIOB->MODER |= (1U<<10);
	GPIOB->MODER &=~ (1U<<11);

	RCC->APB2ENR |= USART1EN;

	uart_set_baudrate(USART1, APB2_FREQ, UART_BAUDRATE);

	USART1->CR1 = (CR1_TE | CR1_RE);
	//remember to enable uart last
	USART1->CR1	|= CR1_UE;


}


void usart1_tx_en (void){
	/* configure uart gpio pin:
	 * enable gpio clk access
	 * set pb6 to af
	 * set pb6 to function type usart1_tx af7
	 * (usart1tx af pb6 af7) datasheet table 18
	 *
	 *
	 * configure uart module:
	 * enable uart clk access
	 * configure baud/transfer direction
	 * enable uart module
	 */
	RCC->AHB2ENR |= GPIOBEN;

	GPIOB->MODER &= ~(1U<<12);
	GPIOB->MODER |=   (1U<<13);

	GPIOB->AFR[0]  |= (1U<<24);
	GPIOB->AFR[0]  |= (1U<<25);
	GPIOB->AFR[0]  |= (1U<<26);
	GPIOB->AFR[0]  &= ~(1U<<27);

	RCC->APB2ENR |= USART1EN;

	uart_set_baudrate(USART1, APB2_FREQ, UART_BAUDRATE);

	USART1->CR1 = CR1_TE ;
	USART1->CR1	|= CR1_UE;


}

char uart1_read(void){

	while(!(USART1->ISR & ISR_RXNE)){}//ref manual 1118

	char read_val = USART1->RDR; //needs to reset flag on rxne

	USART1->ICR |= (1U<<3); //clears ORE??

	//watch moserial DOESNT send any cr nl info!!!!!!!!!!!

	return read_val;
	//return USART1->RDR;
}

void uart1_write(int ch){
	while(!(USART1->ISR & ISR_TXE)){}

	USART1->TDR = (ch & 0xFF);


}

static void 	uart_set_baudrate(USART_TypeDef *USARTx, uint32_t PeriphClk, uint32_t BaudRate){
	USARTx->BRR = compute_uart_bd (PeriphClk, BaudRate);
}

static uint16_t compute_uart_bd (uint32_t PeriphClk, uint32_t BaudRate){
	return ((PeriphClk + (BaudRate/2U))/BaudRate);
}
