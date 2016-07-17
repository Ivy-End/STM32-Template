#include "LED.h"

uint8_t LED_Status;

void LED_Init(uint8_t LED)
{
	GPIO_InitTypeDef GPIO_InitStructure;
    if(LED & LED_2) { RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE); }
    if(LED & LED_3) { RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); }
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	if(LED & LED_2) { GPIO_Init(GPIOE, &GPIO_InitStructure); }
	if(LED & LED_2) { GPIO_Init(GPIOB, &GPIO_InitStructure); }

    LED_Status = 0x00;
}

void LED_On(uint8_t LED)
{
    if((LED & LED_2) && !(LED_Status & LED_2)) { GPIO_ResetBits(GPIOE, GPIO_Pin_5); }
    if((LED & LED_3) && !(LED_Status & LED_3)) { GPIO_ResetBits(GPIOB, GPIO_Pin_5); }
    LED_Status |= LED;
}

void LED_Off(uint8_t LED)
{
    if((LED & LED_2) && (LED_Status & LED_2)) { GPIO_SetBits(GPIOE, GPIO_Pin_5); }
    if((LED & LED_3) && (LED_Status & LED_3)) { GPIO_SetBits(GPIOB, GPIO_Pin_5); }
    LED_Status &= ~LED;
}

void LED_Toggle(uint8_t LED)
{
    if(LED & LED_2)
    {
        if(LED_Status & LED_2) { GPIO_SetBits(GPIOE, GPIO_Pin_5); }
        else { GPIO_ResetBits(GPIOE, GPIO_Pin_5); }
    }
    if(LED & LED_3)
    {
        if(LED_Status & LED_3) { GPIO_SetBits(GPIOB, GPIO_Pin_5); }
        else { GPIO_ResetBits(GPIOB, GPIO_Pin_5); }
    }
    LED_Status ^= LED;
}
