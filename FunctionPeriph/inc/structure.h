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

#endif