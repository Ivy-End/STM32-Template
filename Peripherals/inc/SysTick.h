#ifndef _SYSTICK_H_
#define _SYSTICK_H_

#include "stm32f10x.h"

#define SYSTICK_MS   1000
#define SYSTICK_US   1000000

void SysTick_Init(uint32_t Time, uint32_t Unit);
void SysTick_Delay(uint32_t Time, uint32_t Unit);
void SysTick_Decrement(void);

#endif
