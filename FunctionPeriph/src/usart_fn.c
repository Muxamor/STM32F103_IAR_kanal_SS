/**
  ******************************************************************************
  * @file    Project/SetupPeriph/
  * @author  Ivan Neskorodev
  * @version V0.0
  * @date    27.07.2014
  * @brief   Function for work with USART
  *          
  *          
  ******************************************************************************
*/

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_usart.h"
#include "usart_fn.h"
/*----------------------------------------------------------------------------*/

/**
  * @brief  This function send a byte to the USART .
  * @param  None
  * @retval None
  */
void UART_SendBite(USART_TypeDef* USARTx, uint8_t Data)
{
  while(USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET);/*Check that registr is empty*/
  //while(!(USARTx->SR & USART_SR_TC)); 
  USART_SendData(USARTx, (uint16_t)Data);
  
}

/**
  * @brief  This function send a tring to the USART .
  * @param  None
  * @retval None
  */
void UART_SendString(USART_TypeDef* USARTx, uint8_t *Data){
  
  UART_SendBite(USARTx, '\r');
  UART_SendBite(USARTx, '\n');
   
  for(/*Empty*/; *Data != '\0' ; Data++ ){ 
    UART_SendBite(USARTx, *Data);
  }
  
}