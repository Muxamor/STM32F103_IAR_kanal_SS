#ifndef __SETUPPERIPHSS_H
#define __SETUPPERIPHSS_H

/*For ON/OFF LED need to use function:                                        */
#define LED_GREEN_ON()              GPIO_ResetBits(GPIOC, GPIO_Pin_3) 
#define LED_GREEN_OFF()            GPIO_SetBits(GPIOC, GPIO_Pin_3) 

#define LED_RED_ON()               GPIO_ResetBits(GPIOC, GPIO_Pin_4) 
#define LED_RED_OFF()              GPIO_SetBits(GPIOC, GPIO_Pin_4)

#define LED_YELLOW_ON()            GPIO_ResetBits(GPIOA, GPIO_Pin_1) 
#define LED_YELLOW_OFF()           GPIO_SetBits(GPIOA, GPIO_Pin_1)

/*For ON/OFF Chip selest for DA14, DA2, DA10  need to use function:                           */  
#define CS_CS1_3_DA14_OFF()  GPIO_SetBits(GPIOC, GPIO_Pin_6)    // OFF chip select for DA14 IC 
#define CS_CS1_3_DA14_ON()   GPIO_ResetBits(GPIOC, GPIO_Pin_6)  // ON chip select for DA14 IC 
                                                                                   
#define CS_CS1_2_DA2_OFF()   GPIO_SetBits(GPIOC, GPIO_Pin_7)    // OFF chip select for DA2 IC  
#define CS_CS1_2_DA2_ON()    GPIO_ResetBits(GPIOC, GPIO_Pin_7)  // ON chip select for DA2 IC  
                                                                                    
#define CS_CS1_1_DA10_OFF()  GPIO_SetBits(GPIOC, GPIO_Pin_8)    // OFF chip select for DA10 IC 
#define CS_CS1_1_DA10_ON()   GPIO_ResetBits(GPIOC, GPIO_Pin_8)  // ON chip select for DA10 IC

/*For ON/OFF Chip selest for DA17  need to use function:                           */  
#define CS_CS2_1_DA17_OFF()  GPIO_SetBits(GPIOA, GPIO_Pin_4)     // OFF chip select for DA17 IC 
#define CS_CS2_1_DA17_ON()   GPIO_ResetBits(GPIOA, GPIO_Pin_4)  // ON chip select for DA17 IC

 /* For Ser/Reset INT for BB board need to use function:                    */
#define SPI3_INT_BB_OFF() GPIO_ResetBits(GPIOC, GPIO_Pin_5);
#define SPI3_INT_BB_ON()  GPIO_SetBits(GPIOC, GPIO_Pin_5);


#define Set_SYNC2_DA17()     GPIO_SetBits(GPIOB, GPIO_Pin_1)    // Set bit for SYNC2
#define Reset_SYNC2_DA17()   GPIO_ResetBits(GPIOB, GPIO_Pin_1)  // Reset bit for SYNC2


  



void SetupClock(void);
void SetupUSART(void);
void SetupSPI1(void);
void SetupSPI2(void);
void SetupSPI3(void);
void Setup_DMA_SPI3(void);
void SetupTimers(void);
void Setup_RTC(void);
void Setup_I2C(void);
void SetupInterrupt(void);
void SetupLED(void);
void Setup_GPIO(void);
void Setup_IWDG(void);


#endif