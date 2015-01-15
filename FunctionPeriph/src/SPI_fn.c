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
void SPI_Send_Data_u8( SPI_TypeDef* SPIx, uint8_t Data ){
  
  while ( SPI_I2S_GetFlagStatus(SPIx, SPI_I2S_FLAG_BSY) == SET );
  
   //!!!!!!!!!!!!!!!!!!!Проверить работает или нет !!!!!!!!!!!!!!!!!!!!!!!!!!
  // Возможно нужно включать выключать SPI  при перенастройки SPI_Cmd(SPI2,ENABLE);SPI_Cmd(SPI2,DISABLE);
  SPI_DataSizeConfig(SPIx, SPI_DataSize_8b);

  SPI_I2S_SendData(SPIx, Data);
  
  while ( SPI_I2S_GetFlagStatus(SPIx, SPI_I2S_FLAG_BSY) == SET );
  
  SPI_DataSizeConfig(SPIx, SPI_DataSize_16b);

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
void SPI3_Answer_Of_Command( u8 numberOFcommand, u8 value_command ){
  
  u16 answer_to_BB=0;
  
  answer_to_BB = numberOFcommand;
  answer_to_BB = answer_to_BB << 8;
  answer_to_BB = answer_to_BB | value_command;
        
  while ( SPI_I2S_GetFlagStatus(SPI3, SPI_I2S_FLAG_BSY) == SET );
  
  SPI_I2S_SendData(SPI3,answer_to_BB);
  
   SPI3_INT_BB_ON();

}


/**
  * @brief  This function managment command from SPI3 .
  * @param  None
  * @retval None
  */
void SPI3_command_from_BB(_SPI3RECIVEBUF* SPI3_Rec_Buf, _SETTINGSOFCHANNEL *settings_channel){
   
   SPI_I2S_ITConfig(SPI3, SPI_I2S_IT_RXNE, DISABLE);
  
   u8 Error_happened=0;
   u8 Send_OK_answer=0;
   u8 Value_of_settings;
   u16 tmp;
   enum Command_from_BB Received_Command;
   
    tmp= SPI3_Rec_Buf->SPI3ReciveBuf[0];
    Value_of_settings = (u8) tmp; 
    Received_Command = (enum Command_from_BB) (tmp>>8);
    
    if( Received_Command <= 0 || Received_Command >= MAX_COMMAND ){
      
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
          SPI3_Answer_Of_Command((u8)Read_Input_Switch_command, settings_channel->Switching_input );
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
          SPI3_Answer_Of_Command( (u8)Read_Amplification_factor_Af1_command, settings_channel->Aplification_factor_1);
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
          SPI3_Answer_Of_Command( (u8)Read_Cutoff_Frequency_LPF_fcut_command, settings_channel->Frequency_cut_off);
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
          SPI3_Answer_Of_Command( (u8)Read_Amplification_factor_Af2_command, settings_channel->Aplification_factor_2);
          break;
      
        case Write_Sampling_Frequency_fd_command://Frequency_sampling or Frequency_descritisation  get and set settings
          if(Set_Settings_FD(Value_of_settings,settings_channel ) == 1){
            Error_happened=1;
          }else{
            settings_channel->Frequency_sampling = Value_of_settings;
            Send_OK_answer=1;
          }
          break;
        case Read_Sampling_Frequency_fd_command://Frequency_sampling or Frequency_descritisation send settings
          SPI3_Answer_Of_Command( (u8)Read_Sampling_Frequency_fd_command, settings_channel->Frequency_sampling);
          break;
        
        default:
          Error_happened=1;
      }
      
    } else {
    
    } 
       
    
    if(Send_OK_answer==1){
      SPI3_Answer_Of_Command(00,01);//SEND answer OK
    } else if(Error_happened==1){
      SPI3_Answer_Of_Command(00,02);//Error command
    }
    
    SPI_I2S_ITConfig(SPI3, SPI_I2S_IT_RXNE, ENABLE);

}


   