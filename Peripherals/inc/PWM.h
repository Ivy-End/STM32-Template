#ifndef _PWM_H_
#define _PWM_H_

// Using TIM3 to generate PWM

#include "stm32f10x.h"

void PWM_Init(void);
void PWM_GPIO_Init(void);
void PWM_Mode_Init(void);

#endif