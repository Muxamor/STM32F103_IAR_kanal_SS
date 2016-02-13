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

              
#define SIZE_SPI3_BUF 2
typedef struct{

  u16 SPI3ReciveBuf[SIZE_SPI3_BUF];
  u16 SPI3TransmitBuf[SIZE_SPI3_BUF];
  u8 SPI3_Buf_Len;
  
} _SPI3BUF;

#define SIZE_UART_BUF 30

typedef struct{

  u8 UART_Recive_Buf[SIZE_UART_BUF];
  u8 UART_Buf_Len;
  
} _UARTBUF;

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
  u8 Frequency_sampling;//Fd
  u16 Frequency_sampling_value;//Fd
  u8 Frequency_software_decimation;//Fres
  u8 Frequency_software_decimation_count;//Fres
  u8 Frequency_software_decimation_count_down;//Fres
  u16 Frequency_sampling_data_flow;//Fdata
  u16 Saturation_Level_Af1_plus;
  u16 Saturation_Level_Af1_minus;
  u32 Saturation_Level_Af2_plus;
  u32 Saturation_Level_Af2_minus;
  
  
  u8 Control_Minus_Saturation_level_Af1;
  u8 Control_Minus_Saturation_level_Af2;
  u8 Port_to_send_data_SPI3_or_UART;
  u8 Start_stop;
  
  
  u8 time_test_LED;
  
  u8 SID_number_of_channel;
  u16 KEMS_off_channel;
  
  
} _SETTINGSOFCHANNEL;



typedef struct{
  
  u8 ADC24_data2;
  u8 factor_KU1:4;
  u8 factor_KU2:4;
  
  u8 ADC24_data1;
  u8 ADC24_data0;

}_ONECOUNTDATAADC24;


typedef struct{

  u16 number_packets;
  u16 number_seconds;
  u16 serial_number_unit;
  
  u8  SID_number_channel;
  u8  number_channel;
  
  u8  value_Fd;
  u8  value_Fcut;
  
  u16 value_Fdata;
  
  u8  input_directon_X_Y_Z;
  u8  input_coordinates;
  
  u16 KEMS_channel;
  
  u8:1;
  u8  error_saturation:1;
  u8  error_saturation_ADC24:1;
  u8  flag_KU1:1;
  u8  flag_KU2:1;
  u8  flag_no_correct_data:1;
  u8  automatic_change_KU1_KU2:1;
  u8  work_mode:1;
  u8  error_flug;
 
  _ONECOUNTDATAADC24 data_ADC24_per_sec[4096];
  
}_PACKETDATAADC24;
              
              
#define SIZE_FIFO_BUFFER 3

typedef struct{
              
  _PACKETDATAADC24 fifo_bufADC24[SIZE_FIFO_BUFFER];
  u8 write_fifo;
  u8 read_fifo;
    
  u8 new_circle:1;  // new circle in FIFO buffer
  u8 miss_parsel:1; //miss parcel 
 // u8 new_data_packets:1; // =1 new parsel 0= old parsel
  u8:6;
  
  u8 quant_paresl_ready_send;        
  u16 count_data_written_per_buf;
              
}_FIFO_BUF_DATA;



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
                      Read_Saturation_Level_Af2_plus_command=0x0E,
                      Write_Saturation_Level_Af2_minus_command=0x0F,
                      Read_Saturation_Level_Af2_minus_command=0x10,
                      Write_Control_Minus_Saturation_level_command=0x11,
                      Read_Control_Minus_Saturation_level_command=0x12,
                      Write_ID_Channel_number=0x13,
                      Read_ID_Channel_number=0x14,
                      Write_SID_Channel_number=0x15,
                      Read_SID_Channel_number=0x16,
                      
                      Read_Ready_command=0x20,
                      START_STOP_command=0x21,
                      
                      Write_Software_Decimation_command=0x31,
                      Read_Software_Decimation_command=0x32,
                      Read_Frequenc_data_flow_command=0x34,
                   
                      MAX_COMMAND
                      };







#endif