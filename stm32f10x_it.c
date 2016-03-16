/**
  ******************************************************************************
  * @file    Project/STM32F10x_StdPeriph_Template/stm32f10x_it.c 
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_it.h"
#include "structure.h"  
#include "usart_fn.h"
#include "SPI_fn.h"
#include "SetupPeriphSS.h"
#include "global_variables.h"
#include "delay_systick.h"
    


/** @addtogroup STM32F10x_StdPeriph_Template
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */

void SysTick_Handler(void){
 
  delay_counter_down();
  
}

//extern _INTERRUPTMONITOR *Interrupt_Monitor;
//extern _SETTINGSOFCHANNEL  *Settings_Of_Channel;
//extern _FIFO_BUF_DATA *FIFO_BUF;
/**
  * @brief  This function handles  RTC evry one second interrupt request.
  * @param  None
  * @retval None
  */
void RTC_IRQHandler(void){
  
  if( RTC_GetITStatus(RTC_IT_SEC) != RESET ){
        
    RTC_ClearITPendingBit(RTC_IT_SEC);
    RTC_WaitForLastTask();
    
      if(FIFO_BUF->state_after_stop==1){
        if( EXTI_GetITStatus(EXTI_Line0) != RESET ){
          EXTI_ClearITPendingBit(EXTI_Line0);
        }
     
        NVIC_EnableIRQ(EXTI0_IRQn); /*Enable Interrupt for PB0 */ 
      }
      
      FIFO_BUF->next_second_get = 1;
      
      if(Settings_Of_Channel->time_test_LED==0) {
        LED_YELLOW_ON(); // LED_GREEN_ON();
        Settings_Of_Channel->time_test_LED=1;
      } else {
        LED_YELLOW_OFF(); 
        Settings_Of_Channel->time_test_LED=0;
      }
    
    
  }
}

/**
  * @brief  This function fro Sync from BBB.
  * @param  None
  * @retval None
  */
void EXTI9_5_IRQHandler(void){
  
  if( EXTI_GetITStatus(EXTI_Line9) != RESET ){
    EXTI_ClearITPendingBit(EXTI_Line9);
    if(Settings_Of_Channel->Got_Sync_START==0){
      Settings_Of_Channel->Got_Sync_START=1;
      RTC_WaitForLastTask();
      RTC_ClearITPendingBit(RTC_IT_SEC);
      RTC_SetCounter(0); // Пока не вижу необходимости обнулять счетчик
      RTC_WaitForLastTask();
      NVIC_EnableIRQ(RTC_IRQn);
      
    }
  }
  
}



/**
  * @brief  This function handles  PB0 interrupt request.
  * @param  None
  * @retval None
  */
void EXTI0_IRQHandler(void){
  
  if( EXTI_GetITStatus(EXTI_Line0) != RESET ){
    EXTI_ClearITPendingBit(EXTI_Line0);
    
    Settings_Of_Channel->Frequency_software_decimation_count_down--;
       
    if(Settings_Of_Channel->Frequency_software_decimation_count_down==0){
      Interrupt_Monitor->ADC_AD17_data_ready_interrupt=1;
      Settings_Of_Channel->Frequency_software_decimation_count_down=Settings_Of_Channel->Frequency_software_decimation_count;
    }
    
  }
  
}



//extern _UARTBUF *UART_Buf;
/**
  * @brief  This function handles  UART4 interrupt request.
  * @param  None
  * @retval None
  */
void UART4_IRQHandler(void){
  
  u8 tmp;

 
  if(USART_GetITStatus(UART4, USART_IT_RXNE)){
    USART_ClearITPendingBit(UART4,  USART_IT_RXNE );
    tmp=USART_ReceiveData(UART4);
    UART_Buf->UART_Recive_Buf[UART_Buf->UART_Buf_Len]=tmp;
    
    if(tmp=='\r'){
      Interrupt_Monitor->UART_Interrup=1;
      UART_Buf->UART_Recive_Buf[UART_Buf->UART_Buf_Len]=' ';
        
    }else{
      if(tmp==0x7f){
        if(UART_Buf->UART_Buf_Len!=0){
          UART_Buf->UART_Buf_Len--;
          UART_Buf->UART_Recive_Buf[UART_Buf->UART_Buf_Len]=' ';
          UART_SendBite(UART4, 127); // 127 is delet command for terminal
        }
      }else{
        UART_Buf->UART_Buf_Len++;
        UART_SendBite(UART4, tmp);
      }
    }
    
    if(UART_Buf->UART_Buf_Len>(SIZE_UART_BUF-1)){
      UART_Buf->UART_Buf_Len=(SIZE_UART_BUF-1);
      UART_SendBite(UART4, 127);
    }
    
  }
      
}

//extern _SPI3RECIVEBUF *SPI3_Recive_Buf;
/**
  * @brief  This function handles SPI3 interrupt request.
  * @param  None
  * @retval None
  */
void SPI3_IRQHandler(void){
  while(1);
  /*
  if(SPI_I2S_GetITStatus(SPI3, SPI_I2S_IT_TXE)==SET){
      
    Interrupt_Monitor->SPI3_Interrup_TX_Buffer_Empty=1;
    SPI_Send_Data_u16(SPI3,0xABCD);// For clear a interrupt flag TXE
    SPI3_INT_BB_OFF();
    
  }else if(SPI_I2S_GetITStatus(SPI3, SPI_I2S_IT_RXNE)==SET){
     
    SPI3_Buf->SPI3ReciveBuf[SPI3_Buf->SPI3_Buf_Len]=SPI_Receive_Data(SPI3);
     
    if(SPI3_Buf->SPI3ReciveBuf[0]==0x0000){
        
      SPI3_Buf->SPI3_Buf_Len=0;
      LED_RED_OFF();
              
    } else {
     
      SPI3_Buf->SPI3_Buf_Len++;
        
      if( SPI3_Buf->SPI3_Buf_Len==2 ){
          
          SPI3_Buf->SPI3_Buf_Len=0;          
          Interrupt_Monitor->SPI3_Interrup_RX_Buffer_Get_Parcel=1; // Recive parsel
          LED_RED_ON();// Удалить в релизе
          
        }
        
    }
            
      
   }*/ /*else if(SPI_I2S_GetITStatus(SPI3, SPI_I2S_IT_ERR)==SET){
     ///Произошла ошибка
     Interrupt_Monitor-> SPI3_Interrup_ERROR_Occurred=1;
     
   }
     */
   
}


//DMA_SPI3_TX
void DMA2_Channel2_IRQHandler (void){
  while(1);
  /*
  if(DMA_GetITStatus(DMA2_FLAG_TC2)==SET){
    
    DMA_ClearITPendingBit(DMA2_FLAG_TC2);
    SPI3_INT_BB_OFF();
    Interrupt_Monitor->SPI3_Interrup_TX_Buffer_Empty=1;

    if( FIFO_BUF->transmite_parsel_ENABLE == 1){
      ReSetup_SPI3_DMA_SPI3(SPI3_Buf->SPI3TransmitBuf, SPI3_Buf->SPI3ReciveBuf, 2, 2);    
      FIFO_BUF->transmite_parsel_ENABLE = 0;
      FIFO_BUF->parsel_ready_interrupt = 0;
      FIFO_BUF->quant_paresl_ready_send--;
      FIFO_BUF->read_fifo++; 
       
      if(FIFO_BUF->read_fifo == SIZE_FIFO_BUFFER){
        FIFO_BUF->read_fifo = 0; 
        FIFO_BUF->new_circle = 0;
      }
    }
      
  }*/
}     

//DMA_SPI3_RX
void DMA2_Channel1_IRQHandler (void){
  
  if(DMA_GetITStatus(DMA2_FLAG_TC1) == SET){
    DMA_ClearITPendingBit(DMA2_FLAG_TC1);
    SPI3_INT_BB_OFF();
    Interrupt_Monitor->SPI3_Interrup_TX_Buffer_Empty=1;
    
    if(FIFO_BUF->transmite_parsel_ENABLE == 0){
      
      if(SPI3_Buf->SPI3ReciveBuf[0]==0x0000 ){
      
        DMA_Cmd(DMA2_Channel2, DISABLE);
        DMA_Cmd(DMA2_Channel1, DISABLE);
  
        DMA_SetCurrDataCounter(DMA2_Channel2,2); 
        DMA_SetCurrDataCounter(DMA2_Channel1,2); 

        DMA_Cmd(DMA2_Channel2, ENABLE);
        DMA_Cmd(DMA2_Channel1, ENABLE);
      
        SPI3_Buf->SPI3_Buf_Len=0;
      }else{
        Interrupt_Monitor->SPI3_Interrup_RX_Buffer_Get_Parcel=1; 
      }
    
    }else if(FIFO_BUF->transmite_parsel_ENABLE == 1){
       FIFO_BUF->parsel_was_sended=1;
      // ReSetup_SPI3_DMA_SPI3(SPI3_Buf->SPI3TransmitBuf, SPI3_Buf->SPI3ReciveBuf, 2, 2);  
      
    }else{
    
      while(1);
    }
 
  }



} 




/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
