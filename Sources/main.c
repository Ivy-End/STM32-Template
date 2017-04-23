#include "stm32f10x.h"
#include "peripherals_conf.h"

uint32_t ConversionValue;
float ad;
uint16_t count=0x8283;

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
	Keyboard_Init();
	//LCD_Init();	
	ADS1118_Init();
  while(1) 
	{		 
		
		printf("准备完毕 开始转换！\n");
		ADS1118_CS_Reset();
		while(!GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_6));
	    ConversionValue = ADS1118_Read(count);//8283  
		ADS1118_CS_Set();
        printf(" The  Value is 0X%08x ,%08d\n",ConversionValue,ConversionValue);
		ad=	ConversionValue*4.096/32768;
		printf("AD=%fV\n",ad);
		SysTick_Delay(1000, SYSTICK_MS);	
//		Keyboard_Loop();
//		//LCD_Clear(Color_White);
//		//LCD_Set_ForeColor(Color_Red);  	
//		//if(Keyboard_Scan() == KEYBOARD_S1) { LCD_Show_String(30,50,200,16,16, "Key Board Test");	}
//		if(Keyboard_Detect(KEYBOARD_S1, KEYBOARD_DOWN)) { printf("S1\r\n"); }
//		if(Keyboard_Detect(KEYBOARD_S2, KEYBOARD_DOWN)) { printf("S2\r\n"); }
//		if(Keyboard_Detect(KEYBOARD_S3, KEYBOARD_DOWN)) { printf("S3\r\n"); }
//		if(Keyboard_Detect(KEYBOARD_S4, KEYBOARD_DOWN)) { printf("S4\r\n"); }
//		if(Keyboard_Detect(KEYBOARD_S5, KEYBOARD_DOWN)) { printf("S5\r\n"); }
//		if(Keyboard_Detect(KEYBOARD_S6, KEYBOARD_DOWN)) { printf("S6\r\n"); }
//		if(Keyboard_Detect(KEYBOARD_S7, KEYBOARD_DOWN)) { printf("S7\r\n"); }
//		if(Keyboard_Detect(KEYBOARD_S8, KEYBOARD_DOWN)) { printf("S8\r\n"); }
//		if(Keyboard_Detect(KEYBOARD_S9, KEYBOARD_DOWN)) { printf("S9\r\n"); }
//		if(Keyboard_Detect(KEYBOARD_S10, KEYBOARD_DOWN)) { printf("S10\r\n"); }
//		if(Keyboard_Detect(KEYBOARD_S11, KEYBOARD_DOWN)) { printf("S11\r\n"); }
//		if(Keyboard_Detect(KEYBOARD_S12, KEYBOARD_DOWN)) { printf("S12\r\n"); }
//		if(Keyboard_Detect(KEYBOARD_S13, KEYBOARD_DOWN)) { printf("S13\r\n"); }
//		if(Keyboard_Detect(KEYBOARD_S14, KEYBOARD_DOWN)) { printf("S14\r\n"); }
//		if(Keyboard_Detect(KEYBOARD_S15, KEYBOARD_DOWN)) { printf("S15\r\n"); }
//		if(Keyboard_Detect(KEYBOARD_S16, KEYBOARD_DOWN)) { printf("S16\r\n"); }
//		//LCD_Set_ForeColor(Color_Green);  
//		//LCD_Show_String(30,70,200,16,16, "TFT-LCD test");	
//		//LCD_Set_ForeColor(Color_Blue);  
//		//LCD_Show_String(30,90,200,16,16, "www.doflye.net");
//		//LCD_Draw_Circle(100,180,20);	
//		//SysTick_Delay(1000, SYSTICK_MS);	

	} 
}
