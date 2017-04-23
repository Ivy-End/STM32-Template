#ifndef _ADS1118_H_
#define _ADS1118_H_

#include "stm32f10x.h"

void ADS1118_CS_Set(void);
void ADS1118_CS_Reset(void);
void ADS1118_Init(void);
uint8_t ADS1118_Send(uint8_t Data);
void ADS1118_Delay(uint32_t Count);
uint32_t ADS1118_Read(uint16_t Config);

#endif
