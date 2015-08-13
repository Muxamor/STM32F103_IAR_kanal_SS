#ifndef __USART_FN_H
#define __USART_FN_H

#define UART_COMMAND_MAS_SIZE 13


void UART_SendBite(USART_TypeDef* USARTx, uint8_t Data);
void UART_SendString(USART_TypeDef* USARTx, uint8_t *Data);
void uart_terminal_command(_UARTBUF *recive_buf, _SETTINGSOFCHANNEL *settings_channel );

#endif