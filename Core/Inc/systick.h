#ifndef SYSTICK_H
#define SYSTICK_H

#include "stm32f1xx.h"

#ifndef __RTOS__

void systick_init(void);
void SysTick_Handler(void);
void delay_ms(uint32_t ticks);

#endif

#endif
