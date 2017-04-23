#include "Keyboard.h"

uint32_t KeyboardValue;

void Keyboard_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOF, ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
    GPIO_Init(GPIOF, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(GPIOF, &GPIO_InitStructure);
}

uint32_t Keyboard_Scan(void)
{
    GPIO_ResetBits(GPIOF, GPIO_Pin_5);
    GPIO_ResetBits(GPIOF, GPIO_Pin_6);
    GPIO_ResetBits(GPIOF, GPIO_Pin_7);
    GPIO_SetBits(GPIOF, GPIO_Pin_4);
    if(GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_0)) { return KEYBOARD_S1; }
    if(GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_1)) { return KEYBOARD_S5; }
    if(GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_2)) { return KEYBOARD_S9; }
    if(GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_3)) { return KEYBOARD_S13; }
    
    GPIO_ResetBits(GPIOF, GPIO_Pin_4);
    GPIO_ResetBits(GPIOF, GPIO_Pin_6);
    GPIO_ResetBits(GPIOF, GPIO_Pin_7);
    GPIO_SetBits(GPIOF, GPIO_Pin_5);
    if(GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_0)) { return KEYBOARD_S2; }
    if(GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_1)) { return KEYBOARD_S6; }
    if(GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_2)) { return KEYBOARD_S10; }
    if(GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_3)) { return KEYBOARD_S14; }
    
    GPIO_ResetBits(GPIOF, GPIO_Pin_4);
    GPIO_ResetBits(GPIOF, GPIO_Pin_5);
    GPIO_ResetBits(GPIOF, GPIO_Pin_7);
    GPIO_SetBits(GPIOF, GPIO_Pin_6);
    if(GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_0)) { return KEYBOARD_S3; }
    if(GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_1)) { return KEYBOARD_S7; }
    if(GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_2)) { return KEYBOARD_S11; }
    if(GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_3)) { return KEYBOARD_S15; }
    
    GPIO_ResetBits(GPIOF, GPIO_Pin_4);
    GPIO_ResetBits(GPIOF, GPIO_Pin_5);
    GPIO_ResetBits(GPIOF, GPIO_Pin_6);
    GPIO_SetBits(GPIOF, GPIO_Pin_7);
    if(GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_0)) { return KEYBOARD_S4; }
    if(GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_1)) { return KEYBOARD_S8; }
    if(GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_2)) { return KEYBOARD_S12; }
    if(GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_3)) { return KEYBOARD_S16; }
	
	return KEYBOARD_NULL;
}

void Keyboard_Loop(void)
{
	static uint32_t KeyboardState		= KEYBOARD_STATE_INIT;
	static uint32_t KeyboardCount		= 0;
	static uint32_t KeyboardLast		= KEYBOARD_NULL;
	uint32_t KeyboardTmp = KEYBOARD_NULL;
	
	KeyboardTmp = Keyboard_Scan();
	
	switch(KeyboardState)
	{
		case KEYBOARD_STATE_INIT:
			if(KeyboardTmp != KEYBOARD_NULL)
			{ KeyboardState = KEYBOARD_STATE_WOBBLE; }
			break;
		case KEYBOARD_STATE_WOBBLE:
			KeyboardState = KEYBOARD_STATE_PRESS;
			break;
		case KEYBOARD_STATE_PRESS:
			if(KeyboardTmp != KEYBOARD_NULL)
			{
				KeyboardLast = KeyboardTmp;
				KeyboardTmp |= KEYBOARD_DOWN;
				KeyboardState = KEYBOARD_STATE_LONG;
			}
			else { KeyboardState = KEYBOARD_STATE_INIT; }
			break;
		case KEYBOARD_STATE_LONG:
			if(KeyboardTmp != KEYBOARD_NULL)
			{
				if(++KeyboardCount > KEYBOARD_LONG_PERIOD)
				{
					KeyboardCount = 0;
					KeyboardTmp |= KEYBOARD_LONG;
					KeyboardState = KEYBOARD_STATE_CONTINUE;
				}
			}
			else { KeyboardState = KEYBOARD_STATE_RELEASE; }
			break;
		case KEYBOARD_STATE_CONTINUE:
			if(KeyboardTmp != KEYBOARD_NULL)
			{
				if(++KeyboardCount > KEYBOARD_CONTINUE_PERIOD)
				{
					KeyboardCount = 0;
					KeyboardTmp |= KEYBOARD_CONTINUE;
				}
			}
			else { KeyboardState = KEYBOARD_STATE_RELEASE; }
			break;
		case KEYBOARD_STATE_RELEASE:
			KeyboardLast |= KEYBOARD_UP;
			KeyboardTmp = KeyboardLast;
			KeyboardState = KEYBOARD_STATE_INIT;
			break;
		default:
			break;
	}
	KeyboardValue = KeyboardTmp;
}

uint8_t Keyboard_Detect(uint32_t Key, uint32_t Status)
{
    return (KeyboardValue == (Key | Status));
}
