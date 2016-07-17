#ifndef _KEY_H_
#define _KEY_H_

#include "stm32f10x.h"

#define KEY_S1	    0x0E
#define KEY_S2	    0x0D
#define KEY_S3	    0x0B
#define KEY_S4	    0x07
#define KEY_NULL	0x0F

#define KEY_LONG_PERIOD		100
#define KEY_CONTINUE_PERIOD	25

#define KEY_UP				0x10
#define KEY_CONTINUE		0x20
#define KEY_LONG			0x40
#define KEY_DOWN			0x80

#define KEY_STATE_INIT		0x01
#define KEY_STATE_WOBBLE	0x02
#define KEY_STATE_PRESS		0x03
#define KEY_STATE_LONG		0x04
#define KEY_STATE_CONTINUE	0x05
#define KEY_STATE_RELEASE	0x06

void Key_Init(uint8_t Key);
uint8_t Key_Read(uint8_t Key);
uint8_t Key_Scan(void);
void Key_Loop(void);
uint8_t Key_Detect(uint8_t Key, uint8_t Status);

#endif
