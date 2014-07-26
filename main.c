#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_usart.h"
#include "misc.h"

#define LED_GREEN_ON();             GPIO_ResetBits(GPIOC, GPIO_Pin_3); 
#define LED_GREEN_OFF();            GPIO_SetBits(GPIOC, GPIO_Pin_3); 

#define LED_RED_ON();               GPIO_ResetBits(GPIOC, GPIO_Pin_4); 
#define LED_RED_OFF();              GPIO_SetBits(GPIOC, GPIO_Pin_4);

#define LED_YELLOW_ON();            GPIO_ResetBits(GPIOA, GPIO_Pin_1); 
#define LED_YELLOW_OFF();           GPIO_SetBits(GPIOA, GPIO_Pin_1);


void SetupClock(void);
void SetupUSART(void);
void SetupLED(void);
void UART_SendBite(USART_TypeDef* USARTx, uint8_t Data);

void delay_ms (u16 delay_time);
void delay_s (u16 delay_time);
void delay_us (u16 delay_time);

u16 delay_count=0;




int main()
{
 
  SetupClock();
  SetupUSART();
  SetupLED();
  
  
  LED_RED_ON();
   delay_ms(200);
  LED_YELLOW_ON();
   delay_ms(200);
  LED_GREEN_ON();
   delay_ms(200);
  
   LED_RED_OFF();
   delay_ms(200);
  LED_YELLOW_OFF();
   delay_ms(200);
  LED_GREEN_OFF();
   delay_ms(200);
  LED_RED_ON();
  LED_YELLOW_ON();
  LED_GREEN_ON();
  delay_ms(200);
  LED_RED_OFF();
  LED_YELLOW_OFF();
  LED_GREEN_OFF();
  delay_ms(200);
  LED_RED_ON();
  LED_YELLOW_ON();
  LED_GREEN_ON();
  
  u8 i;
  u8 str[]="******:)Za";
  
    for(i=0; str[i]!='\0' ; i++ ){ 
      UART_SendBite(UART4, str[i]);
  
    }
    if(str[i]=='\0'){
      UART_SendBite(UART4, '\n');
      UART_SendBite(UART4, '\r');
    
    }
while(1);
  //return 0;
}



void SetupClock(void)
{
      RCC_DeInit ();                    /* RCC system reset(for debug purpose)*/
      RCC_HSEConfig (RCC_HSE_ON);       /* Enable HSE                         */

      /* Wait till HSE is ready                                               */
      while (RCC_GetFlagStatus(RCC_FLAG_HSERDY) == RESET);

   
      RCC_HCLKConfig   (RCC_SYSCLK_Div1);   /* HCLK   = SYSCLK                */
      RCC_PCLK2Config  (RCC_HCLK_Div1);     /* PCLK2  = HCLK                  */
      RCC_PCLK1Config  (RCC_HCLK_Div2);     /* PCLK1  = HCLK/2                */
      RCC_ADCCLKConfig (RCC_PCLK2_Div4);    /* ADCCLK = PCLK2/4               */

      /* PLLCLK = 16MHz/2 * 9 = 72 MHz   0x00010000                                        */
      RCC_PLLConfig (RCC_PLLSource_HSE_Div2, RCC_PLLMul_9);

      RCC_PLLCmd (ENABLE);                  /* Enable PLL                     */

      /* Wait till PLL is ready                                               */
      while (RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET);

      /* Select PLL as system clock source                                    */
      RCC_SYSCLKConfig (RCC_SYSCLKSource_PLLCLK);

      /* Wait till PLL is used as system clock source                         */
      while (RCC_GetSYSCLKSource() != 0x08);


}

void SetupLED(void){
  
  GPIO_InitTypeDef  GPIO_InitStructure;
  
  /* Enable GPIOC clock                                                   */
   RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
   RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
   
   GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_3|GPIO_Pin_4;
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
   GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
   GPIO_Init(GPIOC, &GPIO_InitStructure);

   GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_1;
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
   GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
   GPIO_Init(GPIOA, &GPIO_InitStructure);
   
   GPIO_SetBits(GPIOC, GPIO_Pin_3|GPIO_Pin_4); //Diode is off
   GPIO_SetBits(GPIOA, GPIO_Pin_1);            //Diode is off

}


void SetupUSART(void)
{
      GPIO_InitTypeDef  GPIO_InitStructure;
      USART_InitTypeDef USART_InitStructure;
      
      /* Enable  UART4  clock                                                      */
      RCC_APB1PeriphClockCmd (RCC_APB1Periph_UART4, ENABLE);

      /* Enable GPIOC clock                                                   */
      RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);

      /* Configure UART4 Rx (PC11) as input floating                         */
      GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_11;
      GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN_FLOATING;
      GPIO_Init(GPIOC, &GPIO_InitStructure);

      /* Configure UART4 Tx (PC10) as alternate function push-pull            */
      GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_10;
      GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
      GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;
      GPIO_Init(GPIOC, &GPIO_InitStructure);

      /* USART1 configured as follow:
            - BaudRate = 115200 baud
            - Word Length = 8 Bits
            - One Stop Bit
            - No parity
            - Hardware flow control disabled (RTS and CTS signals)
            - Receive and transmit enabled
            - USART Clock disabled
            - USART CPOL: Clock is active low
            - USART CPHA: Data is captured on the middle
            - USART LastBit: The clock pulse of the last data bit is not output to
                             the SCLK pin
      */
      USART_InitStructure.USART_BaudRate            = 115200;
      USART_InitStructure.USART_WordLength          = USART_WordLength_8b;
      USART_InitStructure.USART_StopBits            = USART_StopBits_1;
      USART_InitStructure.USART_Parity              = USART_Parity_No ;
      USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
      USART_InitStructure.USART_Mode                = USART_Mode_Rx | USART_Mode_Tx;
      USART_Init(UART4, &USART_InitStructure);
      
      NVIC_PriorityGroupConfig (NVIC_PriorityGroup_1);
      NVIC_InitTypeDef NVCI_Init_Struct;
      NVCI_Init_Struct.NVIC_IRQChannel=UART4_IRQn; 
      NVCI_Init_Struct.NVIC_IRQChannelPreemptionPriority=1;
      NVCI_Init_Struct.NVIC_IRQChannelSubPriority=3;
      NVCI_Init_Struct.NVIC_IRQChannelCmd=ENABLE;
      NVIC_Init(&NVCI_Init_Struct);
      NVIC_EnableIRQ(UART4_IRQn);
      USART_ITConfig(UART4, USART_IT_RXNE, ENABLE);
      
      USART_Cmd(UART4, ENABLE);
      
      
}


void UART_SendBite(USART_TypeDef* USARTx, uint8_t Data)
{
  while(USART_GetFlagStatus(UART4, USART_FLAG_TC) == RESET);
  //while(!(USARTx->SR & USART_SR_TC)); // whait before bite was send
  USART_SendData(USARTx, (uint16_t)Data);
  
}




void delay_s ( u16 delay_time ){
   SysTick_Config(SystemCoreClock/1000); //enable and set call interrupts evry 1 ms 
   delay_count = delay_time*1000;
   while(delay_count!=0);
   
   SysTick->CTRL  = 0; // disable the SysTick counter and interrupts
}


void delay_ms ( u16 delay_time ){
   SysTick_Config(SystemCoreClock/1000); //enable and set call interrupts evry 1 ms 
   delay_count = delay_time;
   while(delay_count!=0);
   
   SysTick->CTRL  = 0; // disable the SysTick counter and interrupts
}


void delay_us ( u16 delay_time ){
   SysTick_Config(SystemCoreClock/1000000); //enable and set call interrupts evry 1 ms 
   delay_count = delay_time;
   while(delay_count!=0);
   
   SysTick->CTRL  = 0; // disable the SysTick counter and interrupts
}


void UART4_IRQHandler(void){
  
  if(USART_GetITStatus(UART4, USART_IT_RXNE)){
    USART_ClearITPendingBit(UART4,  USART_IT_RXNE );
    USART_SendData(UART4,  USART_ReceiveData(UART4));
  }
}


void SysTick_Handler(void){
  
  if(delay_count>0){
    delay_count--;
  }


}

