#include "key.h"

uint8_t KeyValue;

void Key_Init(uint8_t Key)
{
    uint16_t GPIO_Pin = 0x00;
    GPIO_InitTypeDef GPIO_InitStructure;
    if((Key & KEY_S1) || (Key & KEY_S2) || (Key & KEY_S3))
    {
        if(Key & KEY_S1) { GPIO_Pin |= GPIO_Pin_4; }
        if(Key & KEY_S2) { GPIO_Pin |= GPIO_Pin_3; }
        if(Key & KEY_S3) { GPIO_Pin |= GPIO_Pin_2; }

        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
        GPIO_Init(GPIOE, &GPIO_InitStructure);
    }
    if(Key & KEY_S4)
    {
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
        GPIO_Init(GPIOA, &GPIO_InitStructure);
    }
}

uint8_t Key_Read(uint8_t Key)
{
    if(Key == KEY_S1) { return GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4); }
    else if(Key == KEY_S2) { return GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3); }
    else if(Key == KEY_S3) { return GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_2); }
    else if(Key == KEY_S4) { return GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0); }
	else { return 2; }
}

uint8_t Key_Scan(void)
{
	if(Key_Read(KEY_S1) == 0) { return KEY_S1; }
	if(Key_Read(KEY_S2) == 0) { return KEY_S2; }
	if(Key_Read(KEY_S3) == 0) { return KEY_S3; }
	if(Key_Read(KEY_S4) == 1) { return KEY_S4; }
	return KEY_NULL;
}

void Key_Loop(void)
{
	static uint8_t KeyState		= KEY_STATE_INIT;
	static uint8_t KeyCount		= 0;
	static uint8_t KeyLast		= KEY_NULL;
	uint8_t KeyTmp = KEY_NULL;
	
	KeyTmp = Key_Scan();
	
	switch(KeyState)
	{
		case KEY_STATE_INIT:
			if(KeyTmp != KEY_NULL)
			{ KeyState = KEY_STATE_WOBBLE; }
			break;
		case KEY_STATE_WOBBLE:
			KeyState = KEY_STATE_PRESS;
			break;
		case KEY_STATE_PRESS:
			if(KeyTmp != KEY_NULL)
			{
				KeyLast = KeyTmp;
				KeyTmp |= KEY_DOWN;
				KeyState = KEY_STATE_LONG;
			}
			else { KeyState = KEY_STATE_INIT; }
			break;
		case KEY_STATE_LONG:
			if(KeyTmp != KEY_NULL)
			{
				if(++KeyCount > KEY_LONG_PERIOD)
				{
					KeyCount = 0;
					KeyTmp |= KEY_LONG;
					KeyState = KEY_STATE_CONTINUE;
				}
			}
			else { KeyState = KEY_STATE_RELEASE; }
			break;
		case KEY_STATE_CONTINUE:
			if(KeyTmp != KEY_NULL)
			{
				if(++KeyCount > KEY_CONTINUE_PERIOD)
				{
					KeyCount = 0;
					KeyTmp |= KEY_CONTINUE;
				}
			}
			else { KeyState = KEY_STATE_RELEASE; }
			break;
		case KEY_STATE_RELEASE:
			KeyLast |= KEY_UP;
			KeyTmp = KeyLast;
			KeyState = KEY_STATE_INIT;
			break;
		default:
			break;
	}
	KeyValue = KeyTmp;
}

uint8_t Key_Detect(uint8_t Key, uint8_t Status)
{
    return (KeyValue == (Key | Status));
}
