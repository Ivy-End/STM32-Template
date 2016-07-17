#ifndef _USART_H_
#define _USART_H_

#include "stm32f10x.h"
#include "stdio.h"

void Usart_Init(void);
int fputc(int ch, FILE *f);

#endif
