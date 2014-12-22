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
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "stm32f10x_usart.h"
#include "SetupPeriphSS.h"
#include "structure.h"
#include "IC_fn.h"
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
void UART_SendString(USART_TypeDef* USARTx, uint8_t *Data)
{
  
  UART_SendBite(USARTx, '\r');
  UART_SendBite(USARTx, '\n');
   
  for(/*Empty*/; *Data != '\0' ; Data++ ){ 
    UART_SendBite(USARTx, *Data);
  }
  
}

/**
  * @brief  This function analysis command from the terminal.
  * @param  None
  * @retval None
  */

void uart_terminal_command(_UARTBUF *recive_buf, _SETTINGSOFCHANNEL *settings_channel )
{
  NVIC_DisableIRQ(UART4_IRQn); /*Disable Interrupt for UART4*/
   
  u8 uart_command[UART_COMMAND_MAS_SIZE][8]= {
                                                "af1", "af2", //0,1
                                                "fcut", "swinput",//2,3
                                                "fd", "cfg",  //4,5
                                                "reboot", "help", //  6,7 
                                                "default",//8
                                                "start","stop",//9,10
                                                "spi", "uart"//11,12
                                             };
  
  u8 i;
  u8 *str_uart=recive_buf->UART_Recive_Buf;
  u8 tmp_buf[SIZE_UART_BUF];
  u8 lenght_recive_buf=0;
  u8 error_happened=0;
  s8 numder_of_command=-1;
  u8 tmp;
  u8 print_settings=0;
  
  u8 str[100];
  
    
 while(lenght_recive_buf < recive_buf->UART_Buf_Len){
   
    for(/*Empty*/; *str_uart == ' ' && i < recive_buf->UART_Buf_Len ; str_uart++ , lenght_recive_buf++ ); // remove the SPACE from the recive UARt buffer
   
    for(i=0 ; *str_uart != ' ' && i < recive_buf->UART_Buf_Len ; i++, str_uart++ , lenght_recive_buf++ ){ // read the command
      tmp_buf[i]=*str_uart;
    }
    
    tmp_buf[i]='\0';
    
    for(/*Empty*/; *str_uart == ' ' && i < recive_buf->UART_Buf_Len ; str_uart++ , lenght_recive_buf++ ); // remove the SPACE from the recive UARt buffer
   
    for(i=0; i != UART_COMMAND_MAS_SIZE; i++){   // Find the number of command
      if(!strcmp((char const* )tmp_buf,(char const* )uart_command[i])){
        numder_of_command = i;
        break;
      }
    }
    
    if(numder_of_command == -1){
      sprintf((char *)str,   " Command \"%s\" not found!", tmp_buf);
      UART_SendString(UART4, str);
    }else{
      
      switch(numder_of_command){
        
        case 0: 
        case 1:
        case 2:
        case 3:
        case 4:
          for(i=0 ; *str_uart != ' ' && i < recive_buf->UART_Buf_Len ; i++, str_uart++ , lenght_recive_buf++ ){ // read the command
            tmp_buf[i]=*str_uart;
          }
          
          if(i==0){
             error_happened=1;
          }
    
          tmp_buf[i]='\0';
          
          for( i=0; tmp_buf[i] != '\0'; i++ ){   // check that the we get the number
            if( '0' > tmp_buf[i] || tmp_buf[i]  > '9' ){
              error_happened=1;
              break;
            }
          }  
          
          tmp=(u8)atoi( (char*)tmp_buf );
          
          if(numder_of_command == 0){ // set Af1
            if( error_happened == 1 || Set_Settings_DA6( tmp ) == 1 ){
              sprintf((char *)str,   " For command \"af1\" argument \"%s\" is wrong!", tmp_buf);
              UART_SendString(UART4, str );
              error_happened=0;
            }else{
              settings_channel->Aplification_factor_1=tmp;
            }
            
          }else if(numder_of_command==1){ // set Af2
            if( error_happened==1 || Set_Settings_DA2(tmp ) == 1 ){
              sprintf((char *)str,   " For command \"af2\" argument \"%s\" is wrong!", tmp_buf);
              UART_SendString(UART4, str );
              error_happened=0;
            }else{
              settings_channel->Aplification_factor_2=tmp;
            }
            
          }else if(numder_of_command==2){ // set fcut
              if( error_happened==1 || Set_Settings_DA8(tmp ) == 1 ){
              sprintf((char *)str,   " For command \"fcut\" argument \"%s\" is wrong!", tmp_buf);
              UART_SendString(UART4, str );
              error_happened=0;
            }else{
              settings_channel->Frequency_cut_off=tmp;
              print_settings=1;
            }
            
          }else if(numder_of_command==3){ // set swinput
            if( error_happened==1 || Set_Settings_DA12(tmp ) == 1 ){
              sprintf((char *)str,   " For command \"swinput\" argument \"%s\" is wrong!", tmp_buf);
              UART_SendString(UART4, str );
              error_happened=0;
            }else{
              settings_channel->Switching_input=tmp;
            }
          }else if(numder_of_command==4){ // set fd
            if( error_happened==1 || Set_Settings_FD(tmp, settings_channel)== 1 ){ 
              sprintf((char *)str,   " For command \"fd\" argument \"%s\" is wrong!", tmp_buf);
              UART_SendString(UART4, str );
              error_happened=0;
            }else{
              settings_channel->Frequency_sampling=tmp;
              
            }
          }
          print_settings=1;
          break;
          
        case 5: // print current settings
          print_settings=1;
          break;
          
        case 6: // reboot
          while(1);
          break;
          
        case 7: // help                                                       
          UART_SendString(UART4, " ***********************************Help menu***********************************");
          UART_SendString(UART4, " *                                                                             *");
          UART_SendString(UART4, " * af1 <value>      - Ampilfication factor K1 (DA6), <value> - 0..8            *");
          UART_SendString(UART4, " * af2 <value>      - Ampilfication factor K2 (DA2), <value> - 0..12           *");
          UART_SendString(UART4, " * fcut <value>     - Cutoff frequency of the low pass filter, <value> - 0..19 *");
          UART_SendString(UART4, " * swinput <value>  - Switching input mode (DA12), <value> - 0..4              *");
          UART_SendString(UART4, " * fd <value>       - Sampling frequency, <value> - 0..6                       *");
          UART_SendString(UART4, " * cfg              - Inquiry configuration and number of channel              *");
          UART_SendString(UART4, " * default          - Default configuration                                    *");
          UART_SendString(UART4, " * reboot           - Reboot channel                                           *");
          UART_SendString(UART4, " * spi/uart         - Port to send data from ADC to SPI or UART port          *");
          UART_SendString(UART4, " * start            - Start read ADC data                                      *");
          UART_SendString(UART4, " * stop             - Stop read ADC data                                       *");
          UART_SendString(UART4, " *                                                                             *");
          UART_SendString(UART4, " *******************************************************************************");
          break;
        
        case 8: // Set deffault settings 
          Set_Default_Settings(settings_channel);
          print_settings=1;
          break;       
        case 9: // Start 
          settings_channel->Start_stop=1;
          NVIC_EnableIRQ(EXTI0_IRQn); /*Enable Interrupt for PB0 */ 
          break;  
        case 10: // Stop 
          settings_channel->Start_stop=0;
          NVIC_DisableIRQ(EXTI0_IRQn); /*Enable Interrupt for PB0 */ 
          print_settings=1;
          break; 
        case 11: // data send to SPI3 port 
          settings_channel->Port_to_send_data_SPI3_or_UART=0;
          print_settings=1;
          break;  
        case 12: // data send to UART port 
          settings_channel->Port_to_send_data_SPI3_or_UART=1;
          print_settings=1;
          break;          
          
        default:
          numder_of_command = -1;
          UART_SendString(UART4, "Command not recognized!");
          break;
             
      }
      
      numder_of_command = -1;
    }
  
 }
 
 if(print_settings==1){
    sprintf((char *)str,   "\n\r af1 %d  af2 %d  fcut %d  fd %d  swinput %d \n\r Number of channel: %d \n\r", 
                  settings_channel->Aplification_factor_1, settings_channel->Aplification_factor_2, settings_channel->Frequency_cut_off, settings_channel->Frequency_sampling, settings_channel->Switching_input, settings_channel->Numer_of_Channel);
    UART_SendString(UART4, str );
    
    if( settings_channel->Port_to_send_data_SPI3_or_UART==0){
      UART_SendString(UART4, " Port to send data is: SPI \n\r" );
    }else{
      UART_SendString(UART4, " Port to send data is: UART \n\r" );
    }
    
    print_settings=0;
 }
 
 recive_buf->UART_Buf_Len=0; 
 NVIC_EnableIRQ(UART4_IRQn); /*Enable Interrupt for UART4*/
 UART_SendString(UART4, ">");
  
                       
}
