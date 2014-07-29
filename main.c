#include "stm32f10x.h"
#include <stdio.h>
#include "SetupPeriphSS.h"
#include "delay_systick.h"
#include "usart_fn.h"



int main()
{
 /*----------------------------Setup Periphery--------------------------------*/
  SetupClock();
  SetupLED();
  SetupUSART();
  SetupInterrupt();
 /*---------------------------------------------------------------------------*/   
  
 /*-------------------------------Program-------------------------------------*/

  LED_RED_ON();
      delay_ms(150);
  LED_YELLOW_ON();
      delay_ms(150);
  LED_GREEN_ON();
      delay_ms(150);
  
  LED_RED_OFF();
      delay_ms(150);
  LED_YELLOW_OFF();
      delay_ms(150);
  LED_GREEN_OFF();
      delay_ms(150);
      
  LED_RED_ON();
  LED_YELLOW_ON();
  LED_GREEN_ON();
   
  u8 str[]="*************************KTIVT seismic station ******************************";
  UART_SendString(UART4, str);
  
  sprintf((char *)str,"Chanel Number: %d", 1);
  UART_SendString(UART4, str);
  
 
while(1);
  //return 0;
}



