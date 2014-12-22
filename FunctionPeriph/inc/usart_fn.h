#ifndef __USART_FN
#define __USART_FN


#define UART_COMMAND_MAS_SIZE 13

#define SIZE_UART_BUF 30

typedef struct{

  u8 UART_Recive_Buf[SIZE_UART_BUF];
  u8 UART_Buf_Len;
  
} _UARTBUF;


void UART_SendBite(USART_TypeDef* USARTx, uint8_t Data);
void UART_SendString(USART_TypeDef* USARTx, uint8_t *Data);
void uart_terminal_command(_UARTBUF *recive_buf, _SETTINGSOFCHANNEL *settings_channel );





#endif