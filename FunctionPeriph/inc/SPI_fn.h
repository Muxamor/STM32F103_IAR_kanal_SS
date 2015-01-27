#ifndef __SPI_FN_H
#define __SPI_FN_H

#define SIZE_SPI3_BUF 2
typedef struct{

  u16 SPI3ReciveBuf[SIZE_SPI3_BUF];
  u8 SPI3_Buf_Len;
  
} _SPI3RECIVEBUF ;

void SPI_Send_Data_u16( SPI_TypeDef* SPIx, uint16_t Data );
void SPI_Send_Data_u8( SPI_TypeDef* SPIx, uint8_t Data );
uint16_t SPI_Receive_Data( SPI_TypeDef* SPIx);
void SPI3_Sent_Response_to_BB( u16 *data, u8 length, _INTERRUPTMONITOR *interrupt );
void SPI3_command_from_BB(_SPI3RECIVEBUF* SPI3_Rec_Buf, _SETTINGSOFCHANNEL *settings_channel, _INTERRUPTMONITOR *interrupt);

#endif