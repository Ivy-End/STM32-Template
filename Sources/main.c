#include "stm32f10x.h"
#include "peripherals_conf.h"

int main(void)
{
	LED_Init(LED_2 | LED_3);
	LED_On(LED_2 | LED_3);
	while(1);
}
