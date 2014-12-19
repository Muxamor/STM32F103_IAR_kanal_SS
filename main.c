#include "stm32f10x.h"
#include <stdio.h>
#include "SetupPeriphSS.h"
#include "delay_systick.h"
#include "structure.h"
#include "IC_fn.h"
#include "usart_fn.h"
#include "SPI_fn.h"




_UARTBUF uart_buf, *UART_Buf=&uart_buf;
_SPI3RECIVEBUF spi3_recive_buf, *SPI3_Recive_Buf=&spi3_recive_buf;
_INTERRUPTMONITOR interrupt_monitor, *Interrupt_Monitor=&interrupt_monitor ;
_SETTINGSOFCHANNEL settings_of_channel, *Settings_Of_Channel=&settings_of_channel; 

void main()
{ 
    
 
 /*----------------------------Setup Periphery--------------------------------*/
  SetupClock();
  SetupLED();
  Setup_GPIO(); // Setup DA12 and DA6
  SetupUSART();
  SetupSPI1();
  SetupSPI2();
  SetupSPI3();
  SetupTimers();
  Setup_RTC();
  SetupInterrupt();
 // Setup_IWDG();
  
  Settings_Of_Channel->Numer_of_Channel = Read_Number_of_Channel();
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
     
  LED_RED_OFF();
  LED_YELLOW_OFF();
  LED_GREEN_OFF();
 // 
   
  //IWDG_ReloadCounter();
  u8 str[100];
  UART_SendString(UART4, "*****************************************************************************");
  UART_SendString(UART4, "*                        KTIVT seismic station                              *");
  sprintf((char *)str,   "*                        Number of Channel: %d                               *", Settings_Of_Channel->Numer_of_Channel);                   
  UART_SendString(UART4, str);
  UART_SendString(UART4, "*                        Version: 0.0V Beta                                 *");
  UART_SendString(UART4, "*                            01.09.2014                                     *");
  UART_SendString(UART4, "*****************************************************************************");
  //Set default settings
  if(Set_Default_Settings(Settings_Of_Channel)==1){
     UART_SendString(UART4, " Initialization not possible");
  }else{
     UART_SendString(UART4, " Initialization completed");
  }
  UART_SendString(UART4, "\n>");

 
  while(1) {
    
    IWDG_ReloadCounter();
    
    if(Interrupt_Monitor->SPI3_Interrup_RX_Buffer_Get_Parcel==1){
      Interrupt_Monitor->SPI3_Interrup_RX_Buffer_Get_Parcel=0;
      SPI3_command_from_BB(SPI3_Recive_Buf, Settings_Of_Channel );
    }
      
    if(Interrupt_Monitor->UART_Interrup==1){
      Interrupt_Monitor->UART_Interrup=0;
      uart_terminal_command(UART_Buf, Settings_Of_Channel );
    }

    if(Interrupt_Monitor->ADC_AD17_data_ready_interrupt==1 && Settings_Of_Channel->Start_stop==1){
      Interrupt_Monitor->ADC_AD17_data_ready_interrupt=0;
      u16 data1;
      u8 data2;
      
      SPI_Send_Data_u16( SPI1, 0x00 );
      data1=SPI_Receive_Data(SPI1); 
      
      SPI_Send_Data_u8( SPI1, 0x00 );
      data2=SPI_Receive_Data(SPI1);
      
      sprintf((char *)str, "ADC: %X%X", data1,data2);
      UART_SendString(UART4, str);
      
    }
    
    
  }
  
}

