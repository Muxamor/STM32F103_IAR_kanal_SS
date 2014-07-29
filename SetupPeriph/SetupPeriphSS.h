#ifndef __SETUPPERIPHSS_H
#define __SETUPPERIPHSS_H

#define LED_GREEN_ON();             GPIO_ResetBits(GPIOC, GPIO_Pin_3); 
#define LED_GREEN_OFF();            GPIO_SetBits(GPIOC, GPIO_Pin_3); 

#define LED_RED_ON();               GPIO_ResetBits(GPIOC, GPIO_Pin_4); 
#define LED_RED_OFF();              GPIO_SetBits(GPIOC, GPIO_Pin_4);

#define LED_YELLOW_ON();            GPIO_ResetBits(GPIOA, GPIO_Pin_1); 
#define LED_YELLOW_OFF();           GPIO_SetBits(GPIOA, GPIO_Pin_1);


void SetupClock(void);
void SetupUSART(void);
void SetupInterrupt(void);
void SetupLED(void);

#endif