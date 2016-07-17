#ifndef _SYSTEMTICK_H_
#define _SYSTEMTICK_H_

#include "stm32f10x.h"

#define SYSTEMTICK_MS   1000
#define SYSTEMTICK_US   1000000

void SystemTick_Init(uint8_t Time, uint8_t Unit);
void SystemTick_Delay(uint8_t Time, uint8_t Unit);

#endif
