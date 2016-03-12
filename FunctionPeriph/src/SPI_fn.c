/**
  ******************************************************************************
  * @file    Project/SetupPeriph/
  * @author  Ivan Neskorodev
  * @version V0.0
  * @date    27.07.2014
  * @brief   Function for work with SPI
  *          
  *          
  ******************************************************************************
*/

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_spi.h"
#include "structure.h"
#include "SPI_fn.h"
#include "IC_fn.h"
#include "SetupPeriphSS.h"

/*----------------------------------------------------------------------------*/




/**
  * @brief  This function send data size of u16 to SPI .
  * @param  None
  * @retval None
  */
void SPI_Send_Data_u16( SPI_TypeDef* SPIx, uint16_t Data ){
  
  while ( SPI_I2S_GetFlagStatus(SPIx, SPI_I2S_FLAG_BSY) == SET );

  SPI_I2S_SendData(SPIx, Data);

}


/** //!!!!!!!!!!!!!!!!!!!Проверить работает или нет !!!!!!!!!!!!!!!!!!!!!!!!!!
  * @brief  This function send data size of u8 to SPI .
  * @param  None
  * @retval None
  */
void  SPI_Send_Data_u8( SPI_TypeDef* SPIx, uint8_t Data ){
  
  while ( SPI_I2S_GetFlagStatus(SPIx, SPI_I2S_FLAG_BSY) == SET );
  
   //!!!!!!!!!!!!!!!!!!!Проверить работает или нет !!!!!!!!!!!!!!!!!!!!!!!!!!
  // Возможно нужно включать выключать SPI  при перенастройки SPI_Cmd(SPI2,ENABLE);SPI_Cmd(SPI2,DISABLE);
 // SPI_DataSizeConfig(SPIx, SPI_DataSize_8b);

  while ( SPI_I2S_GetFlagStatus(SPIx, SPI_I2S_FLAG_BSY) == SET );
  
  SPI_I2S_SendData(SPIx, Data);
  
}

/**
  * @brief  This function Receive data from SPI .
  * @param  None
  * @retval None
  */
uint16_t SPI_Receive_Data( SPI_TypeDef* SPIx){
  
   while ( SPI_I2S_GetFlagStatus(SPIx, SPI_I2S_FLAG_RXNE) == RESET);
   
    return SPI_I2S_ReceiveData(SPIx);

}     


/**
  * @brief  This function send answer to SPI3 .
  * @param  None
  * @retval None
  */
void SPI3_Sent_Response_to_BB( u16 *data, u16 length,_SPI3BUF* SPI3_Buf_Trunsmit, _INTERRUPTMONITOR *interrupt ){
  
  for( u8 i=0 ; i<length; i++, data++){
    
    //while(interrupt->SPI3_Interrup_TX_Buffer_Empty==0);
        
    interrupt->SPI3_Interrup_TX_Buffer_Empty=0;
    SPI3_Buf_Trunsmit->SPI3TransmitBuf[i] = REVERSE_LE_BE_u16(*data);
   // SPI_Send_Data_u16(SPI3, REVERSE_LE_BE_u16(*data));
  }
  
  DMA_Cmd(DMA2_Channel2, DISABLE);
  DMA_Cmd(DMA2_Channel1, DISABLE);
  
  DMA_SetCurrDataCounter(DMA2_Channel2,length); 
  DMA_SetCurrDataCounter(DMA2_Channel1,length); 

  DMA_Cmd(DMA2_Channel2, ENABLE);
  DMA_Cmd(DMA2_Channel1, ENABLE);
  SPI3_INT_BB_ON();
      
  
 
    /*
  u16 answer_to_BB=0;
  
  answer_to_BB = numberOFcommand;
  answer_to_BB = answer_to_BB << 8;
  answer_to_BB = answer_to_BB | value_command;
        
  while ( SPI_I2S_GetFlagStatus(SPI3, SPI_I2S_FLAG_BSY) == SET );
  
  SPI_I2S_SendData(SPI3,answer_to_BB);
  
   SPI3_INT_BB_ON();
   
   if( pass_recive_word==PASS_RECIVE_PARCEL_SPI3){
     
     SPI_Rec_Buf->Reset_Buf=1;
   
   }else{
     
     SPI_Rec_Buf->Reset_Buf=0;
   }*/

}


/**
  * @brief  This function managment command from SPI3 .
  * @param  None
  * @retval None
  */
void SPI3_command_from_BB(_SPI3BUF* SPI3_Buf_, _SETTINGSOFCHANNEL *settings_channel, _INTERRUPTMONITOR *interrupt, _FIFO_BUF_DATA *FIFObuf){
   
 //  SPI_I2S_ITConfig(SPI3, SPI_I2S_IT_RXNE, DISABLE);
 // DMA_Cmd(DMA2_Channel2, DISABLE);
 // DMA_Cmd(DMA2_Channel1, DISABLE);
  
   u8 Error_happened=0;
   u8 Send_OK_answer=0;
   u8 Value_of_settings;
   u16 Value_of_settings_2;
   enum Command_from_BB Received_Command;
   u8 ask_buf[4];
   u16 length;
   u16 tmp;
   u8 miss_send_answer=0;
   
   
    tmp= SPI3_Buf_->SPI3ReciveBuf[0];
    Value_of_settings = (u8) tmp; 
    Received_Command = (enum Command_from_BB) (tmp>>8);
    
    Value_of_settings_2=SPI3_Buf_->SPI3ReciveBuf[1];
    
    
    
    if(Received_Command==START_command){
      
      if(Value_of_settings==0x01){
        
        settings_channel->Start_stop=1;//Start
       // NVIC_EnableIRQ(EXTI0_IRQn); /*Enable Interrupt for PB0 */ 
        Send_OK_answer=1;
        
      }else if(Value_of_settings==0x08){
        
      }else {
        Error_happened=1;
      }
      
    }else if(Received_Command==STOP_command){
      
        settings_channel->Start_stop=0;//STOP
        
        NVIC_DisableIRQ(EXTI0_IRQn); /*Enable Interrupt for PB0 */ 
        NVIC_DisableIRQ(RTC_IRQn);
        
        FIFObuf->write_fifo = 0;
        FIFObuf->read_fifo = 0;   
        FIFObuf->new_circle = 0;
        FIFObuf->count_data_written_per_buf = 0;
        FIFObuf->quant_paresl_ready_send = 0;
        FIFObuf->quant_pakets = 0;
        FIFObuf->quant_seconds = 0;
        FIFObuf->next_second_get = 0;
        FIFObuf->state_after_stop = 1;
        FIFObuf->permit_read_ADC24 = 0;
        FIFObuf->miss_parsel = 0;
        FIFObuf->parsel_ready_interrupt = 0;
        FIFObuf->transmite_parsel_ENABLE = 0;
        
        Send_OK_answer=1;
        
      
    }else if( Received_Command <= 0 || Received_Command >= MAX_COMMAND ){
      
        Error_happened=1;
       
    }else if(Received_Command <= Read_Sampling_Frequency_fd_command){
      
      switch (Received_Command){
        
        case Write_Input_Switch_command://Switching_input get and set settings
          if(Set_Settings_DA12(Value_of_settings) == 1){
            Error_happened=1;
          }else{
            settings_channel->Switching_input= Value_of_settings;
            Send_OK_answer=1;
          }
          break;
        case Read_Input_Switch_command://Switching_input send settings
          ask_buf[0]=(u8)Read_Input_Switch_command;
          ask_buf[1]=settings_channel->Switching_input;
            ask_buf[2]=00;
            ask_buf[3]=00;
            length=2;
          break;
        
        case Write_Amplification_factor_Af1_command://Aplification_factor_1 get and set settings
          if(Set_Settings_DA6(Value_of_settings) == 1){
            Error_happened=1;
          }else{
            settings_channel->Aplification_factor_1 = Value_of_settings;
            Send_OK_answer=1;
          }
          break;
        case Read_Amplification_factor_Af1_command://Aplification_factor_1 send settings
          ask_buf[0]=(u8)Read_Amplification_factor_Af1_command;
          ask_buf[1]=settings_channel->Aplification_factor_1;
            ask_buf[2]=00;
            ask_buf[3]=00;
            length=2;
          break;
      
        case Write_Cutoff_Frequency_LPF_fcut_command://Frequency_cut_off get and set settings
          if(Set_Settings_DA8(Value_of_settings)==1){
            Error_happened=1;
          }else{
            settings_channel->Frequency_cut_off=Value_of_settings;
            Send_OK_answer=1;
          }
          break;
        case Read_Cutoff_Frequency_LPF_fcut_command://Frequency_cut_off send settings
          ask_buf[0]=(u8)Read_Cutoff_Frequency_LPF_fcut_command;
          ask_buf[1]=settings_channel->Frequency_cut_off;
            ask_buf[2]=00;
            ask_buf[3]=00;
            length=2;
          break;
        
        case Write_Amplification_factor_Af2_command://Aplification_factor_2 get and set settings
          if(Set_Settings_DA2(Value_of_settings) == 1){
            Error_happened=1;
          }else{
            settings_channel->Aplification_factor_2 = Value_of_settings;
            Send_OK_answer=1;
          }
          break;
        case Read_Amplification_factor_Af2_command://Aplification_factor_2 send settings
          ask_buf[0]=(u8)Read_Amplification_factor_Af2_command;
          ask_buf[1]=settings_channel->Aplification_factor_2;
            ask_buf[2]=00;
            ask_buf[3]=00;
            length=2;
          break;
      /*
        case Write_Sampling_Frequency_fd_command://Frequency_sampling or Frequency_descritisation  get and set settings
          if(Set_Settings_FD(Value_of_settings,settings_channel ) == 1){
            Error_happened=1;
          }else{
            settings_channel->Frequency_sampling = Value_of_settings;
            Send_OK_answer=1;
          }
          break;
        case Read_Sampling_Frequency_fd_command://Frequency_sampling or Frequency_descritisation send settings
          ask_buf[0]=(u8)Read_Sampling_Frequency_fd_command;
          ask_buf[1]=settings_channel->Frequency_sampling;
            ask_buf[2]=00;
            ask_buf[3]=00;
            length=2;
          break;
        */
        default:
          Error_happened=1;
      }
      
    }else if( Received_Command >= Write_Saturation_Level_Af1_command ||  Received_Command <= Read_Frequenc_data_flow_command){
      
      switch (Received_Command){
              
          case Write_Saturation_Level_Af1_command://Switching_input get and set settings
            if(Value_of_settings==0x01){
              settings_channel->Saturation_Level_Af1_plus = Value_of_settings_2;
              Send_OK_answer=1;
            }else if(Value_of_settings==0x02){
              settings_channel->Saturation_Level_Af1_minus = Value_of_settings_2;
              Send_OK_answer=1;
            }else{
              Error_happened=1;
            }
            break;
          case Read_Saturation_Level_Af1_command:
              ask_buf[0]=(u8)Read_Saturation_Level_Af1_command;
              ask_buf[1]=0x00;
              length=2;
            if(Value_of_settings==0x01){
              ask_buf[2]= (u8)(settings_channel->Saturation_Level_Af1_plus >> 8);
              ask_buf[3]= (u8) settings_channel->Saturation_Level_Af1_plus;
            }else if(Value_of_settings==0x02){
              ask_buf[2]= (u8)(settings_channel->Saturation_Level_Af1_minus >> 8);
              ask_buf[3]= (u8) settings_channel->Saturation_Level_Af1_minus;
            } else {
              Error_happened=1;
            }
            break; 
            
          case Write_Saturation_Level_Af2_plus_command:
            settings_channel->Saturation_Level_Af2_plus = (u32)((((u32)Value_of_settings)<<16) | Value_of_settings_2);
            Send_OK_answer=1;
            break;
          case Read_Saturation_Level_Af2_plus_command:
            ask_buf[0]= (u8)Read_Saturation_Level_Af2_plus_command;
            ask_buf[1]= (u8)(settings_channel->Saturation_Level_Af2_plus >> 16);;
            ask_buf[2]= (u8)(settings_channel->Saturation_Level_Af2_plus >> 8);
            ask_buf[3]= (u8) settings_channel->Saturation_Level_Af2_plus;
            length=2;
            break;
            
          case Write_Saturation_Level_Af2_minus_command:
            settings_channel->Saturation_Level_Af2_minus = (u32)((((u32)Value_of_settings)<<16) | Value_of_settings_2);
            Send_OK_answer=1;
            break;
          case Read_Saturation_Level_Af2_minus_command:
            ask_buf[0]= (u8)Read_Saturation_Level_Af2_minus_command;
            ask_buf[1]= (u8)(settings_channel->Saturation_Level_Af2_minus >> 16);;
            ask_buf[2]= (u8)(settings_channel->Saturation_Level_Af2_minus >> 8);
            ask_buf[3]= (u8) settings_channel->Saturation_Level_Af2_minus;
            length=2;
            break;
            
          case Write_Control_Minus_Saturation_level_command:
            if(Value_of_settings==0x01){
              settings_channel->Control_Minus_Saturation_level_Af1=1;
              Send_OK_answer=1;
            }else if(Value_of_settings==0x02){
              settings_channel->Control_Minus_Saturation_level_Af1=0;
              Send_OK_answer=1;           
            }else if(Value_of_settings==0x03){
              settings_channel->Control_Minus_Saturation_level_Af2=1;
              Send_OK_answer=1;           
            }else if(Value_of_settings==0x04){
              settings_channel->Control_Minus_Saturation_level_Af2=0;
              Send_OK_answer=1;           
            }else{
              Error_happened=1;
            }
            break;
          case Read_Control_Minus_Saturation_level_command:
            ask_buf[0]=(u8)Read_Control_Minus_Saturation_level_command;
            ask_buf[1]=(settings_channel->Control_Minus_Saturation_level_Af2<<1) | settings_channel->Control_Minus_Saturation_level_Af1;
            ask_buf[2]=00;
            ask_buf[3]=00;
            length=2;
            break;
            
         case Write_ID_Channel_number:
            if( Value_of_settings==0xF0) {
              //дописать функцию записи ID во флэш
              Send_OK_answer=1; 
            } else {
              Error_happened=1;
            }
            break;
          case Read_ID_Channel_number:
            //дописать функцию чтения из флэш ID
            break;
            
          case Write_SID_Channel_number:
            settings_channel->SID_number_channel =(u8)Value_of_settings_2;
            Send_OK_answer=1;
            break;
            
          case Read_SID_Channel_number:
            ask_buf[0]=(u8)Read_SID_Channel_number;
            ask_buf[1]=settings_channel->SID_number_channel;
            ask_buf[2]=00;
            ask_buf[3]=00;
            length=2;
            break;
            
          case Write_Serial_number_unit:
            settings_channel->Serial_number_unit = Value_of_settings_2;
            Send_OK_answer=1;
            break;
            
          case Read_Serial_number_unit:
            ask_buf[0]=(u8)Read_Serial_number_unit;
            ask_buf[1]= 0x00;
            ask_buf[2]=(u8)settings_channel->Serial_number_unit;
            ask_buf[3]=(u8)(settings_channel->Serial_number_unit>>8);
            length=2;
            break;
            
          case Write_KEMS_channel:
            settings_channel->KEMS_of_channel = Value_of_settings_2;
            Send_OK_answer=1;
            break;
            
          case Read_KEMS_channel:
            ask_buf[0]=(u8)Read_KEMS_channel;
            ask_buf[1]= 0x00;
            ask_buf[2]=(u8)settings_channel->KEMS_of_channel;
            ask_buf[3]=(u8)(settings_channel->KEMS_of_channel>>8);
            length=2;
            break;
            
          case Read_Ready_command:
            ask_buf[0]=(u8)Read_Ready_command;
            ask_buf[1]=0x80; 
            ask_buf[2]=00;
            ask_buf[3]=00;
            length=2;
            //пока не выроботон критерий готовности или не готовности канала отправлять всегда готов
            break;
            
            
          case Write_Read_dataADC24://switch_buffers 
            ReSetup_SPI3_DMA_SPI3(((uint16_t*) (&(FIFObuf->fifo_bufADC24[FIFObuf->read_fifo]))),((uint16_t*) FIFObuf->rx_buff_service), SIZE_HEAD_PAKETS + (settings_channel->Frequency_sampling_data_flow*2), SIZE_HEAD_PAKETS + (settings_channel->Frequency_sampling_data_flow*2));
            FIFObuf->transmite_parsel_ENABLE = 1;
            miss_send_answer=1;
            SPI3_INT_BB_ON();
            break;
            
             
//Read_Stutus_channel=0x28,
                      
          case Write_Software_Decimation_command://
            if(Set_Settings_Fres(Value_of_settings,settings_channel ) == 1){
              Error_happened=1;
            }else{
              settings_channel->Frequency_software_decimation = Value_of_settings;
              Send_OK_answer=1;
            }
            break;
          case Read_Software_Decimation_command://
            ask_buf[0]=(u8)Read_Software_Decimation_command;
            ask_buf[1]=settings_channel->Frequency_software_decimation;
            ask_buf[2]=00;
            ask_buf[3]=00;
            length=2;
            break;
             
          case Read_Frequenc_data_flow_command:
            ask_buf[0]=(u8)Read_Frequenc_data_flow_command;
            ask_buf[1]=0x00;
            ask_buf[2]=(u8) ((settings_channel->Frequency_sampling_data_flow)>>8 );
            ask_buf[3]=(u8) (settings_channel->Frequency_sampling_data_flow);
            length=2;
            break;
            
            default:
              Error_happened=1;
        }         
            
    }         
    
    if(Send_OK_answer==1){
      
      ask_buf[0]=00;
      ask_buf[1]=01;//answer OK
      ask_buf[2]=00;
      ask_buf[3]=00;
      length=2;

      
    } else if(Error_happened==1){
      
      ask_buf[0]=00;
      ask_buf[1]=02;//answer Error
      ask_buf[2]=00;
      ask_buf[3]=00;
      length=2;
      
    } 
     
    if( miss_send_answer == 0){
      SPI3_Sent_Response_to_BB( (u16 *)ask_buf, length,SPI3_Buf_, interrupt );
    }
        
}


   