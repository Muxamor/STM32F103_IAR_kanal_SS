#ifndef __SPI_FN
#define __SPI_FN

#define SIZE_SPI3_BUF 3
typedef struct{

  u16 SPI3_Recive_Buf[SIZE_SPI3_BUF];
  u8 SPI3_Buf_Len;
  
} _SPI3RECIVEBUF ;

void SPI_Send_Data_u16( SPI_TypeDef* SPIx, uint16_t Data );
void SPI_Send_Data_u8( SPI_TypeDef* SPIx, uint8_t Data );
uint16_t SPI_Receive_Data( SPI_TypeDef* SPIx);
void SPI3_Answer_Of_Command( u8 numberOFcommand, u8 value_command );
void SPI3_command_from_BB(_SPI3RECIVEBUF* SPI3_Res_Buf, _SETTINGSOFCHANNEL *settings_channel);

#endif