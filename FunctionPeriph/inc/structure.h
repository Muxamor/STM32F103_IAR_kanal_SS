#ifndef __STRUCTURE
#define __STRUCTURE

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

enum Command_from_BB {Set_Input_Switch_command=0x01, 
                      Read_Input_Switch_command=0x02,
                      Set_Amplification_factor_Af1_command=0x03,
                      Read_Amplification_factor_Af1_command=0x04,
                      Set_Cutoff_Frequency_LPF_fcut_command=0x05,
                      Read_Cutoff_Frequency_LPF_fcut_command=0x06,
                      Set_Amplification_factor_Af2_command=0x07,
                      Read_Amplification_factor_Af2_command=0x08,
                      Set_Sampling_Frequency_fd_command=0x09,
                      Read_Sampling_Frequency_fd_command=0x10};


#endif