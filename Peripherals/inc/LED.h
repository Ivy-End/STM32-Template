#ifndef _LED_H_
#define _LED_H_

#include "stm32f10x.h"

#define LED_2       0x01
#define LED_3       0x02

void LED_Init(uint8_t LED);
void LED_On(uint8_t LED);
void LED_Off(uint8_t LED);
void LED_Toggle(uint8_t LED);

#endif
