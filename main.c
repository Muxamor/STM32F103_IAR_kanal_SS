#include "stm32f10x.h"
#include <stdio.h>
#include "SetupPeriphSS.h"
#include "delay_systick.h"
#include "structure.h"

#include "IC_fn.h"
#include "usart_fn.h"
#include "SPI_fn.h"
#include "global_variables.h"

_SPI3BUF  spi3_buf, *SPI3_Buf=&spi3_buf;
_UARTBUF uart_buf, *UART_Buf=&uart_buf;
_INTERRUPTMONITOR interrupt_monitor, *Interrupt_Monitor=&interrupt_monitor ;
_SETTINGSOFCHANNEL settings_of_channel, *Settings_Of_Channel=&settings_of_channel; 
// RCC_ClocksTypeDef clckcheck,  *CLlock_get=&clckcheck;//��� �������� ����������� �������

_FIFO_BUF_DATA fifo_buffer , *FIFO_BUF = &fifo_buffer; 

  void main(){  
 /*----------------------------Setup Periphery--------------------------------*/
  SetupClock();
  SetupLED();
  Setup_GPIO(); // Setup DA12 and DA6
  LED_RED_ON(); 
  LED_YELLOW_ON();
  LED_GREEN_ON();
  SetupUSART();
  SetupSPI1();
  SetupSPI2();
  SetupSPI3();
  
  SetupTimers();
  Setup_RTC();
  SetupInterrupt();
  
  Setup_DMA_SPI3();
  //Setup_IWDG();
  //RCC_GetClocksFreq(CLlock_get);//��� �������� ����������� �������
  
 /*---------------------------Setup channels----------------------------------------*/   
/*
  FIFO_BUF->fifo_bufADC24[0].number_packet = 0x2004;
  FIFO_BUF->fifo_bufADC24[0].data_day = 0x1F;
  FIFO_BUF->fifo_bufADC24[0].data_month = 0x0C;
  FIFO_BUF->fifo_bufADC24[0].data_yaer = 0x7E0;
  FIFO_BUF->fifo_bufADC24[0].date_hour = 0x0E;
  FIFO_BUF->fifo_bufADC24[0].date_minute = 0x12;
  FIFO_BUF->fifo_bufADC24[0].date_second = 0x6008;
  FIFO_BUF->quant_seconds = 0x40025006;
  FIFO_BUF->fifo_bufADC24[0].number_second_big = (uint16_t)(FIFO_BUF->quant_seconds >> 16);
  FIFO_BUF->fifo_bufADC24[0].number_second_littel = (uint16_t)FIFO_BUF->quant_seconds;
  FIFO_BUF->fifo_bufADC24[0].serial_number_unit = 0x4004; //Serial number of sesmic station
  FIFO_BUF->fifo_bufADC24[0].number_channel = 0x22;//Settings_Of_Channel->Numer_of_Channel;
  FIFO_BUF->fifo_bufADC24[0].SID_number_channel= 0x33;//Settings_Of_Channel->SID_number_of_channel;
  FIFO_BUF->fifo_bufADC24[0].value_Fcut = 0x44; //Settings_Of_Channel->Frequency_cut_off;
  FIFO_BUF->fifo_bufADC24[0].value_Fd = 0x55;//Settings_Of_Channel->Frequency_sampling;
  FIFO_BUF->fifo_bufADC24[0].value_Fdata = 0x5004;//Settings_Of_Channel->Frequency_sampling_data_flow;
  FIFO_BUF->fifo_bufADC24[0].input_switch = 0x22; //Settings_Of_Channel->Switching_input;
  FIFO_BUF->fifo_bufADC24[0].input_directon_X_Y_Z = 0x33;
  FIFO_BUF->fifo_bufADC24[0].KEMS_channel = 0x6004; // //Settings_Of_Channel->KEMS_off_channel;
  FIFO_BUF->fifo_bufADC24[0].error_flug = 0x01;
  FIFO_BUF->fifo_bufADC24[0].error_saturation = 1;
  FIFO_BUF->fifo_bufADC24[0].error_saturation_ADC24 = 0;
  FIFO_BUF->fifo_bufADC24[0].flag_KU1 = 0;
  FIFO_BUF->fifo_bufADC24[0].flag_KU2 = 0;
  FIFO_BUF->fifo_bufADC24[0].flag_no_correct_data = 0;
  FIFO_BUF->fifo_bufADC24[0].automatic_change_KU1_KU2 = 0;
  FIFO_BUF->fifo_bufADC24[0].work_mode = 0;
  
  FIFO_BUF->fifo_bufADC24[0].data_ADC24_per_sec[0].factor_KU1 = 0x2;
  FIFO_BUF->fifo_bufADC24[0].data_ADC24_per_sec[0].factor_KU2 = 0x3;
  FIFO_BUF->fifo_bufADC24[0].data_ADC24_per_sec[0].ADC24_data2 = 0x07;
  FIFO_BUF->fifo_bufADC24[0].data_ADC24_per_sec[0].ADC24_data1 = 0x08;
  FIFO_BUF->fifo_bufADC24[0].data_ADC24_per_sec[0].ADC24_data0 = 0x09;
  FIFO_BUF->fifo_bufADC24[0].data_ADC24_per_sec[1].factor_KU1 = 0x4;
  FIFO_BUF->fifo_bufADC24[0].data_ADC24_per_sec[1].factor_KU2 = 0x5;
  FIFO_BUF->fifo_bufADC24[0].data_ADC24_per_sec[1].ADC24_data2 = 0x02;
  FIFO_BUF->fifo_bufADC24[0].data_ADC24_per_sec[1].ADC24_data1 = 0x03;
  FIFO_BUF->fifo_bufADC24[0].data_ADC24_per_sec[1].ADC24_data0 = 0x04;
  
  FIFO_BUF->fifo_bufADC24[0].data_ADC24_per_sec[60].factor_KU1 = 0x1;
  FIFO_BUF->fifo_bufADC24[0].data_ADC24_per_sec[60].factor_KU2 = 0x2;
  FIFO_BUF->fifo_bufADC24[0].data_ADC24_per_sec[60].ADC24_data2 = 0x03;
  FIFO_BUF->fifo_bufADC24[0].data_ADC24_per_sec[60].ADC24_data1 = 0x04;
  FIFO_BUF->fifo_bufADC24[0].data_ADC24_per_sec[60].ADC24_data0 = 0x05;
  
  FIFO_BUF->fifo_bufADC24[0].data_ADC24_per_sec[61].factor_KU1 = 0x3;
  FIFO_BUF->fifo_bufADC24[0].data_ADC24_per_sec[61].factor_KU2 = 0x4;
  FIFO_BUF->fifo_bufADC24[0].data_ADC24_per_sec[61].ADC24_data2 = 0x09;
  FIFO_BUF->fifo_bufADC24[0].data_ADC24_per_sec[61].ADC24_data1 = 0x08;
  FIFO_BUF->fifo_bufADC24[0].data_ADC24_per_sec[61].ADC24_data0 = 0x07;
  
  FIFO_BUF->fifo_bufADC24[0].data_ADC24_per_sec[62].factor_KU1 = 0x3;
  FIFO_BUF->fifo_bufADC24[0].data_ADC24_per_sec[62].factor_KU2 = 0x4;
  FIFO_BUF->fifo_bufADC24[0].data_ADC24_per_sec[62].ADC24_data2 = 0x01;
  FIFO_BUF->fifo_bufADC24[0].data_ADC24_per_sec[62].ADC24_data1 = 0x02;
  FIFO_BUF->fifo_bufADC24[0].data_ADC24_per_sec[62].ADC24_data0 = 0x03;
  
  FIFO_BUF->fifo_bufADC24[0].data_ADC24_per_sec[63].factor_KU1 = 0x8;
  FIFO_BUF->fifo_bufADC24[0].data_ADC24_per_sec[63].factor_KU2 = 0x8;
  FIFO_BUF->fifo_bufADC24[0].data_ADC24_per_sec[63].ADC24_data2 = 0x09;
  FIFO_BUF->fifo_bufADC24[0].data_ADC24_per_sec[63].ADC24_data1 = 0x04;
  FIFO_BUF->fifo_bufADC24[0].data_ADC24_per_sec[63].ADC24_data0 = 0x02;

  ReSetup_SPI3_DMA_SPI3((uint16_t*)(&(FIFO_BUF->fifo_bufADC24[0])), SPI3_Buf->SPI3ReciveBuf, 142, 2);
 
 */
//Default setting for FIFO buffer.
  FIFO_BUF->write_fifo = 0;
  FIFO_BUF->read_fifo = 0;   
  FIFO_BUF->new_circle = 0;
  FIFO_BUF->count_data_written_per_buf = 0;
  FIFO_BUF->quant_paresl_ready_send = 0;
  FIFO_BUF->quant_pakets = 0x0;
  FIFO_BUF->quant_seconds = 0x0;
  FIFO_BUF->next_second_get = 0;
  FIFO_BUF->state_after_stop = 1;
  FIFO_BUF->permit_read_ADC24 = 0;
  FIFO_BUF->miss_parsel = 0;
 // FIFO_BUF->parsel_ready_interrupt = 0;
  FIFO_BUF->transmite_parsel_ENABLE = 0;
  FIFO_BUF->parsel_was_sended=0;

 /*-------------------------------Program-------------------------------------*/
  Settings_Of_Channel->Number_of_Channel = Read_Number_of_Channel(); 
    
  //IWDG_ReloadCounter();
  u8 str[100];
  UART_SendString(UART4, "*****************************************************************************");
  UART_SendString(UART4, "*                        KTIVT seismic station                              *");
  sprintf((char *)str,   "*                        Number of Channel: %d                               *", Settings_Of_Channel->Number_of_Channel);                   
  UART_SendString(UART4, str);
  UART_SendString(UART4, "*                        Version: 0.0V Beta                                 *");
  UART_SendString(UART4, "*                            01.09.2014                                     *");
  UART_SendString(UART4, "*****************************************************************************");
 
  //Set default settings
  if(Set_Default_Settings(Settings_Of_Channel )==1){
     UART_SendString(UART4, " Initialization not possible");
  }else{
     UART_SendString(UART4, " Initialization completed");
  }
  UART_SendString(UART4, "\n>");
  
  LED_RED_OFF();
  LED_YELLOW_OFF(); 
  //LED_GREEN_OFF();
  Settings_Of_Channel->time_test_LED=0;
  
  uint8_t data0_ADC,data1_ADC,data2_ADC;


  while(1) {
    
    IWDG_ReloadCounter();
    // Parse comman from BB board
    if(Interrupt_Monitor->SPI3_Interrup_RX_Buffer_Get_Parcel==1){
      Interrupt_Monitor->SPI3_Interrup_RX_Buffer_Get_Parcel=0;
      SPI3_command_from_BB(SPI3_Buf, Settings_Of_Channel, Interrupt_Monitor, FIFO_BUF ); 
    }
    
    // Get data from ADC24 in the Start state 
    
    if(Settings_Of_Channel->Start_stop==1 && FIFO_BUF->next_second_get ==1 && Settings_Of_Channel->Port_to_send_data_SPI3_or_UART==0){
      
      FIFO_BUF->next_second_get = 0;

      if( FIFO_BUF->state_after_stop == 0){
        
        if(FIFO_BUF->quant_pakets == 0xFFFF){
          FIFO_BUF->quant_pakets = 0;
        }else{
          FIFO_BUF->quant_pakets++;
        }
        
        if(FIFO_BUF->quant_seconds == 0xFFFFFFFF){
          FIFO_BUF->quant_seconds = 0;
        }else{
          FIFO_BUF->quant_seconds++;
        }

      }
      
      if((FIFO_BUF->count_data_written_per_buf != Settings_Of_Channel->Frequency_sampling_data_flow) &&  (FIFO_BUF->miss_parsel == 0)){ //Parsel ready to sened. Prepare for new parcel
        
        FIFO_BUF->fifo_bufADC24[FIFO_BUF->write_fifo].error_flug = 1;
        FIFO_BUF->fifo_bufADC24[FIFO_BUF->write_fifo].flag_no_correct_data = 1;
      }
      
      if( FIFO_BUF->state_after_stop == 0){
        FIFO_BUF->write_fifo++; 
      }
      
      FIFO_BUF->count_data_written_per_buf=0;
      FIFO_BUF->miss_parsel = 0;
       
      if(FIFO_BUF->write_fifo == SIZE_FIFO_BUFFER){
        FIFO_BUF->write_fifo = 0; 
        FIFO_BUF->new_circle = 1;
      }
      
      if(FIFO_BUF->new_circle == 1 && FIFO_BUF->write_fifo == FIFO_BUF->read_fifo  ){ //if buffer is FULL
        
        if( FIFO_BUF->write_fifo == 0 ){
          FIFO_BUF->write_fifo = SIZE_FIFO_BUFFER-1;
          FIFO_BUF->new_circle = 0;
        }else{
          FIFO_BUF->write_fifo--;
        }
        FIFO_BUF->miss_parsel = 1;
        FIFO_BUF->permit_read_ADC24 = 0;
        
      }else{ 
        
        FIFO_BUF->permit_read_ADC24 = 1;
        
        if( FIFO_BUF->state_after_stop == 0){
          FIFO_BUF->quant_paresl_ready_send++;
        } 
        FIFO_BUF->state_after_stop = 0;
        

        FIFO_BUF->fifo_bufADC24[FIFO_BUF->write_fifo].number_packet = FIFO_BUF->quant_pakets;
        FIFO_BUF->fifo_bufADC24[FIFO_BUF->write_fifo].data_day = Settings_Of_Channel->Start_day;
        FIFO_BUF->fifo_bufADC24[FIFO_BUF->write_fifo].data_month = Settings_Of_Channel->Start_manth;
        FIFO_BUF->fifo_bufADC24[FIFO_BUF->write_fifo].data_yaer = Settings_Of_Channel->Start_year;
        FIFO_BUF->fifo_bufADC24[FIFO_BUF->write_fifo].date_hour = Settings_Of_Channel->Start_hour;
        FIFO_BUF->fifo_bufADC24[FIFO_BUF->write_fifo].date_minute = Settings_Of_Channel->Start_minute;
        FIFO_BUF->fifo_bufADC24[FIFO_BUF->write_fifo].date_second = Settings_Of_Channel->Start_second;
        FIFO_BUF->fifo_bufADC24[FIFO_BUF->write_fifo].number_second_big = (uint16_t)(FIFO_BUF->quant_seconds >> 16);
        FIFO_BUF->fifo_bufADC24[FIFO_BUF->write_fifo].number_second_littel = (uint16_t)FIFO_BUF->quant_seconds;
        FIFO_BUF->fifo_bufADC24[FIFO_BUF->write_fifo].serial_number_unit = Settings_Of_Channel->Serial_number_unit; //Serial number of sesmic station
        FIFO_BUF->fifo_bufADC24[FIFO_BUF->write_fifo].number_channel = Settings_Of_Channel->Number_of_Channel+1;
        FIFO_BUF->fifo_bufADC24[FIFO_BUF->write_fifo].SID_number_channel= Settings_Of_Channel->SID_number_channel;
        FIFO_BUF->fifo_bufADC24[FIFO_BUF->write_fifo].value_Fcut = Settings_Of_Channel->Frequency_cut_off;
        FIFO_BUF->fifo_bufADC24[FIFO_BUF->write_fifo].value_Fd = Settings_Of_Channel->Frequency_sampling;
        FIFO_BUF->fifo_bufADC24[FIFO_BUF->write_fifo].value_Fdata = Settings_Of_Channel->Frequency_sampling_data_flow;
        FIFO_BUF->fifo_bufADC24[FIFO_BUF->write_fifo].input_switch = Settings_Of_Channel->Switching_input;
        FIFO_BUF->fifo_bufADC24[FIFO_BUF->write_fifo].input_directon_X_Y_Z = Settings_Of_Channel->Coordinate_XYZ;;
        FIFO_BUF->fifo_bufADC24[FIFO_BUF->write_fifo].KEMS_channel = Settings_Of_Channel->KEMS_of_channel;
        FIFO_BUF->fifo_bufADC24[FIFO_BUF->write_fifo].error_flug = 0;
        FIFO_BUF->fifo_bufADC24[FIFO_BUF->write_fifo].error_saturation = 0;
        FIFO_BUF->fifo_bufADC24[FIFO_BUF->write_fifo].error_saturation_ADC24 = 0;
        FIFO_BUF->fifo_bufADC24[FIFO_BUF->write_fifo].flag_KU1 = 0;
        FIFO_BUF->fifo_bufADC24[FIFO_BUF->write_fifo].flag_KU2 = 0;
        FIFO_BUF->fifo_bufADC24[FIFO_BUF->write_fifo].flag_no_correct_data = 0;
        FIFO_BUF->fifo_bufADC24[FIFO_BUF->write_fifo].automatic_change_KU1_KU2 = 0; 
        FIFO_BUF->fifo_bufADC24[FIFO_BUF->write_fifo].work_mode = 0;
      }           
    }
    
     //Read data ADC24
    if (Interrupt_Monitor->ADC_AD17_data_ready_interrupt==1 && FIFO_BUF->permit_read_ADC24==1 && Settings_Of_Channel->Port_to_send_data_SPI3_or_UART==0){
      Interrupt_Monitor->ADC_AD17_data_ready_interrupt = 0;
      CS_CS2_1_DA17_ON();
      SPI_Send_Data_u8( SPI1, 0x00 );
      data2_ADC=SPI_Receive_Data(SPI1);
      
      SPI_Send_Data_u8( SPI1, 0x00 );
      data1_ADC=SPI_Receive_Data(SPI1);
       
      SPI_Send_Data_u8( SPI1, 0x00 );
      data0_ADC=SPI_Receive_Data(SPI1);
      CS_CS2_1_DA17_OFF();

      FIFO_BUF->fifo_bufADC24[FIFO_BUF->write_fifo].data_ADC24_per_sec[FIFO_BUF->count_data_written_per_buf].factor_KU1 = Settings_Of_Channel->Aplification_factor_1;
      FIFO_BUF->fifo_bufADC24[FIFO_BUF->write_fifo].data_ADC24_per_sec[FIFO_BUF->count_data_written_per_buf].factor_KU2 = Settings_Of_Channel->Aplification_factor_2;
      FIFO_BUF->fifo_bufADC24[FIFO_BUF->write_fifo].data_ADC24_per_sec[FIFO_BUF->count_data_written_per_buf].ADC24_data2 = data2_ADC;
      FIFO_BUF->fifo_bufADC24[FIFO_BUF->write_fifo].data_ADC24_per_sec[FIFO_BUF->count_data_written_per_buf].ADC24_data1 =  data1_ADC;
      FIFO_BUF->fifo_bufADC24[FIFO_BUF->write_fifo].data_ADC24_per_sec[FIFO_BUF->count_data_written_per_buf].ADC24_data0 =  data0_ADC;
      FIFO_BUF->count_data_written_per_buf++;
      
      if(FIFO_BUF->count_data_written_per_buf >= Settings_Of_Channel->Frequency_sampling_data_flow){
        
        FIFO_BUF->count_data_written_per_buf = Settings_Of_Channel->Frequency_sampling_data_flow - 1;
      }
      
    }
    
   // if(FIFO_BUF->quant_paresl_ready_send != 0 && FIFO_BUF->parsel_ready_interrupt == 0 ){
     // FIFO_BUF->parsel_ready_interrupt=1;
    //  SPI3_INT_BB_ON();
    //}
    
    if(FIFO_BUF->parsel_was_sended==1){
      ReSetup_SPI3_DMA_SPI3(SPI3_Buf->SPI3TransmitBuf, SPI3_Buf->SPI3ReciveBuf, 2, 2);  
      FIFO_BUF->parsel_was_sended=0;
      FIFO_BUF->transmite_parsel_ENABLE = 0;
   //   FIFO_BUF->parsel_ready_interrupt = 0;
      FIFO_BUF->quant_paresl_ready_send--;

      FIFO_BUF->read_fifo =  FIFO_BUF->read_fifo+1;
      if(FIFO_BUF->read_fifo == SIZE_FIFO_BUFFER){
        FIFO_BUF->read_fifo = 0; 
        FIFO_BUF->new_circle = 0;
      }
      
    }
    

         // Parse comman from UART
    if(Interrupt_Monitor->UART_Interrup==1){
      Interrupt_Monitor->UART_Interrup=0;
      uart_terminal_command(UART_Buf, Settings_Of_Channel );
    }
    
    // Get data from ADC24 and send that to the UART. Work only in a UARt mode.
    if(Interrupt_Monitor->ADC_AD17_data_ready_interrupt==1 && Settings_Of_Channel->Start_stop==1 && Settings_Of_Channel->Port_to_send_data_SPI3_or_UART==1){
      Interrupt_Monitor->ADC_AD17_data_ready_interrupt=0;
   
      CS_CS2_1_DA17_ON();
      SPI_Send_Data_u8( SPI1, 0x00 );
      data2_ADC=SPI_Receive_Data(SPI1);
      
      SPI_Send_Data_u8( SPI1, 0x00 );
      data1_ADC=SPI_Receive_Data(SPI1);
       
      SPI_Send_Data_u8( SPI1, 0x00 );
      data0_ADC=SPI_Receive_Data(SPI1);
      
      CS_CS2_1_DA17_OFF();
      sprintf((char *)str, "ADC: 0x%X 0x%X 0x%X", data2_ADC,data1_ADC,data0_ADC);
      UART_SendString(UART4, str);
      
    }
    
    
  }
  
}

