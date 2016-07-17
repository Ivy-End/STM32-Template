#include "stm32f10x.h"
#include "peripherals_conf.h"

int main(void)
{
	LED_Init(LED_2 | LED_3);
	SysTick_Init(1, SYSTICK_MS);
	LED_On(LED_2 | LED_3);
	SysTick_Delay(1000, SYSTICK_MS);
	LED_Toggle(LED_3);
	while(1);
}
