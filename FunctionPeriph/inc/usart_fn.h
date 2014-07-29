#ifndef __USART_FN
#define __USART_FN

void UART_SendBite(USART_TypeDef* USARTx, uint8_t Data);
void UART_SendString(USART_TypeDef* USARTx, uint8_t *Data);

#endif