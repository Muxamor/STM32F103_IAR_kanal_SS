/**
  ******************************************************************************
  * @file    Project/FunctionPeriph/src/
  * @author  Ivan Neskorodev
  * @version V0.0
  * @date    27.07.2014
  * @brief   Function  delay s, ms, us. 
  *          
  *          
  ******************************************************************************
*/

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "delay_systick.h"

uint16_t delay_count=0;


void delay_s ( uint16_t delay_time ){
   SysTick_Config(SystemCoreClock/1000); //enable and set call interrupts evry 1 ms 
   delay_count = delay_time*1000;
   while(delay_count!=0);
   
   SysTick->CTRL  = 0; // disable the SysTick counter and interrupts
}


void delay_ms ( uint16_t delay_time ){
   SysTick_Config(SystemCoreClock/1000); //enable and set call interrupts evry 1 ms 
   delay_count = delay_time;
   while(delay_count!=0);
   
   SysTick->CTRL  = 0; // disable the SysTick counter and interrupts
}


void delay_us ( uint16_t delay_time ){
   SysTick_Config(SystemCoreClock/1000000); //enable and set call interrupts evry 1 ms 
   delay_count = delay_time;
   while(delay_count!=0);
   
   SysTick->CTRL  = 0; // disable the SysTick counter and interrupts
}

void delay_counter_down(void){
  if(delay_count>0){
    delay_count--;
  }
}
