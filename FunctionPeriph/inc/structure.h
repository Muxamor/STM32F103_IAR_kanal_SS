#ifndef __STRUCTURE_H
#define __STRUCTURE_H

// Endianess definitions

#define REVERSE_LE_BE_u32(A) \
	((((u32)(A) & 0xff000000) >> 24) | \
            (((u32)(A) & 0x00ff0000) >> 8)  | \
            (((u32)(A) & 0x0000ff00) << 8)  | \
            (((u32)(A) & 0x000000ff) << 24))

#define REVERSE_LE_BE_u16(A) \
	((((u16)(A) & 0xff00) >> 8) | \
             (((u16)(A) & 0x00ff) << 8))


 typedef struct{
   
  u8 UART_Interrup                      :1;
  u8 ADC_AD17_data_ready_interrupt      :1;
  u8 SPI3_Interrup_TX_Buffer_Empty      :1;
  u8 SPI3_Interrup_RX_Buffer_Get_Parcel :1;
  u8 SPI3_Interrup_ERROR_Occurred       :1;
  u8 :3;

  
  
} _INTERRUPTMONITOR;


 typedef struct{
  
  u8 Numer_of_Channel;
  u8 Aplification_factor_1;
  u8 Aplification_factor_2;
  u8 Frequency_cut_off;
  u8 Switching_input;
  u8 Frequency_sampling;
  u16 Frequency_sampling_number;
  u8 Frequency_sampling_count_for_UART;
  u8 Freq_sampling_count_down_for_UART;
  u8 Port_to_send_data_SPI3_or_UART;
  u8 Start_stop;
  
  
  u8 time_test_LED;
} _SETTINGSOFCHANNEL;

enum Command_from_BB {Write_Input_Switch_command=0x01, 
                      Read_Input_Switch_command=0x02,
                      Write_Amplification_factor_Af1_command=0x03,
                      Read_Amplification_factor_Af1_command=0x04,
                      Write_Cutoff_Frequency_LPF_fcut_command=0x05,
                      Read_Cutoff_Frequency_LPF_fcut_command=0x06,
                      Write_Amplification_factor_Af2_command=0x07,
                      Read_Amplification_factor_Af2_command=0x08,
                      Write_Sampling_Frequency_fd_command=0x09,
                      Read_Sampling_Frequency_fd_command=0x0A,
                      Write_Saturation_Level_Af1_command=0x0B,
                      Read_Saturation_Level_Af1_command=0x0C,
                      Write_Saturation_Level_Af2_plus_command=0x0D,
                      Write_Saturation_Level_Af2_minus_command=0x0F,
                      Read_Saturation_Level_Af2_plus_command=0x0E,
                      Read_Saturation_Level_Af2_minus_command=0x10,
                      Write_Control_Negative_Saturation_level_command=0x11,
                      Read_Control_Negative_Saturation_level_command=0x12,
                      
                      Read_Ready_command=0x20,
                      
                      MAX_COMMAND
                      };







#endif