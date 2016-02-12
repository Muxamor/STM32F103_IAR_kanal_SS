#include "stm32f10x.h"
#include <stdio.h>
#include "SetupPeriphSS.h"
#include "delay_systick.h"
#include "structure.h"

#include "IC_fn.h"
#include "usart_fn.h"
#include "SPI_fn.h"
#include "global_variables.h"




//_SPI3RECIVEBUF spi3_recive_buf, *SPI3_Recive_Buf=&spi3_recive_buf;
_SPI3BUF  spi3_buf, *SPI3_Buf=&spi3_buf;
_UARTBUF uart_buf, *UART_Buf=&uart_buf;
_INTERRUPTMONITOR interrupt_monitor, *Interrupt_Monitor=&interrupt_monitor ;
_SETTINGSOFCHANNEL settings_of_channel, *Settings_Of_Channel=&settings_of_channel; 
 //RCC_ClocksTypeDef clckcheck,  *CLlock_get=&clckcheck;//для проверки настроенной частоты
uint16_t *spi3_dma_receive_buf_addr = NULL;
uint16_t *spi3_dma_transmit_buf_addr = NULL;
_PACKETDATAADC24 dataADC_FIFO[3] = {0};
u16 rx_test_ADC[13] = {0};

 
void main(){ 
  
  dataADC_FIFO[0].number_packets = 0x2004;
  dataADC_FIFO[0].number_seconds = 0x3004;
  dataADC_FIFO[0].serial_number_unit = 0x4004;
  dataADC_FIFO[0].number_channel = 0x22;
  dataADC_FIFO[0].SID_number_channel= 0x33;
  dataADC_FIFO[0].value_Fcut = 0x44;
  dataADC_FIFO[0].value_Fd = 0x55;
  dataADC_FIFO[0].value_Fdata = 0x5004;
  dataADC_FIFO[0].input_coordinates = 0x22;
  dataADC_FIFO[0].input_directon_X_Y_Z = 0x33;
  dataADC_FIFO[0].KEMS_channel = 0x6004;
  dataADC_FIFO[0].error_flug = 0x01; 
  dataADC_FIFO[0].error_saturation = 1;
  dataADC_FIFO[0].error_saturation_ADC24 = 0;
  dataADC_FIFO[0].flag_KU1 = 0;
  dataADC_FIFO[0].flag_KU2 = 0;
  dataADC_FIFO[0].flag_no_correct_data = 0;
  dataADC_FIFO[0].automatic_change_KU1_KU2 = 0;
  dataADC_FIFO[0].work_mode = 0;
  dataADC_FIFO[0].data_ADC24[0].factor_KU1 = 0x2;
  dataADC_FIFO[0].data_ADC24[0].factor_KU2 = 0x3;
  dataADC_FIFO[0].data_ADC24[0].ADC24_data0 = 0x07;
  dataADC_FIFO[0].data_ADC24[0].ADC24_data1 = 0x08;
  dataADC_FIFO[0].data_ADC24[0].ADC24_data2 = 0x09;
  dataADC_FIFO[0].data_ADC24[1].factor_KU1 = 0x4;
  dataADC_FIFO[0].data_ADC24[1].factor_KU2 = 0x5;
  dataADC_FIFO[0].data_ADC24[1].ADC24_data0 = 0x02;
  dataADC_FIFO[0].data_ADC24[1].ADC24_data1 = 0x03;
  dataADC_FIFO[0].data_ADC24[1].ADC24_data2 = 0x04;
  
  
  spi3_dma_receive_buf_addr = (uint16_t * )(rx_test_ADC);//SPI3_Buf->SPI3ReciveBuf;
  spi3_dma_transmit_buf_addr = (uint16_t * )(dataADC_FIFO); // SPI3_Buf->SPI3TransmitBuf; 
 /*----------------------------Setup Periphery--------------------------------*/
  SetupClock();
  SetupLED();
  Setup_GPIO(); // Setup DA12 and DA6
  SetupUSART();
  SetupSPI1();
  SetupSPI2();
  SetupSPI3();
 
  Setup_DMA_SPI3();
  SetupTimers();
  Setup_RTC();
  SetupInterrupt();
  /*
  SPI3_INT_BB_ON();
  SPI3_INT_BB_OFF();
  SPI3_INT_BB_ON();
  SPI3_INT_BB_OFF();
  SPI3_INT_BB_ON();
  SPI3_INT_BB_OFF();
  SPI3_INT_BB_ON();
  SPI3_INT_BB_OFF();
  SPI3_INT_BB_ON();
  SPI3_INT_BB_OFF();
  SPI3_INT_BB_ON();
  SPI3_INT_BB_OFF();
  SPI3_INT_BB_ON();
  SPI3_INT_BB_OFF();
  SPI3_INT_BB_ON();
  SPI3_INT_BB_OFF();
   */
 // Setup_IWDG();
 // RCC_GetClocksFreq(CLlock_get);//для проверки настроенной частоты
 
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
      SPI3_command_from_BB(SPI3_Buf, Settings_Of_Channel, Interrupt_Monitor);


    }
    
      
    if(Interrupt_Monitor->UART_Interrup==1){
      Interrupt_Monitor->UART_Interrup=0;
      uart_terminal_command(UART_Buf, Settings_Of_Channel );
    }
    
    if (Interrupt_Monitor->ADC_AD17_data_ready_interrupt==1 && Settings_Of_Channel->Start_stop==1 && Settings_Of_Channel->Port_to_send_data_SPI3_or_UART==0){
     
      
    
    }

    if(Interrupt_Monitor->ADC_AD17_data_ready_interrupt==1 && Settings_Of_Channel->Start_stop==1 && Settings_Of_Channel->Port_to_send_data_SPI3_or_UART==1){
      Interrupt_Monitor->ADC_AD17_data_ready_interrupt=0;
      u8 data1;
      u8 data2;
      u8 data3;
      CS_CS2_1_DA17_ON();
      SPI_Send_Data_u8( SPI1, 0x00 );
      data1=SPI_Receive_Data(SPI1);
      
      SPI_Send_Data_u8( SPI1, 0x00 );
      data2=SPI_Receive_Data(SPI1);
       
      SPI_Send_Data_u8( SPI1, 0x00 );
      data3=SPI_Receive_Data(SPI1);
      
      CS_CS2_1_DA17_OFF();
      sprintf((char *)str, "ADC: 0x%X 0x%X 0x%X", data1,data2, data3);
      UART_SendString(UART4, str);
      
    }
    
    
  }
  
}

