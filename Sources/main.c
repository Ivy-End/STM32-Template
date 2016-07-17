#include "stm32f10x.h"
#include "peripherals_conf.h"

int main(void)
{
	LED_Init(LED_2 | LED_3);
	Beep_Init();
	SysTick_Init(1, SYSTICK_MS);
	LED_On(LED_2 | LED_3);
	Usart_Init();
	//Beep_On();
	SysTick_Delay(200, SYSTICK_MS);
	//Beep_Off();
	LED_Off(LED_2 | LED_3);
	Key_Init(KEY_S1 | KEY_S2 | KEY_S3 | KEY_S4);
	printf("Test Usart\r\n");
	while(1)
	{
		Key_Loop();
		if(Key_Detect(KEY_S1, KEY_DOWN)) { LED_Toggle(LED_2); }
		if(Key_Detect(KEY_S2, KEY_DOWN)) { LED_Toggle(LED_3); }
		if(Key_Detect(KEY_S3, KEY_DOWN)) { LED_Off(LED_2); }
		if(Key_Detect(KEY_S4, KEY_DOWN)) { LED_Off(LED_3); }
	}
}
