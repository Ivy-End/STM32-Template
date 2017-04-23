#include "Beep.h"

uint8_t Beep_Status;

void Beep_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    Beep_Status = 0;
}

void Beep_On(void)
{
    if(!Beep_Status)
    {
        GPIO_SetBits(GPIOB,GPIO_Pin_8);
        Beep_Status = 1;
    }
}

void Beep_Off(void)
{    
    if(Beep_Status)
    {
        GPIO_ResetBits(GPIOB,GPIO_Pin_8);
        Beep_Status = 0;
    }
}

void Beep_Toggle(void)
{
    if(Beep_Status) { Beep_Off(); }
    else { Beep_On(); }
}
