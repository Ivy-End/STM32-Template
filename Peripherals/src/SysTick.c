#include "SysTick.h"

uint32_t Time_Unit;
static __IO uint32_t Time_Delay;

void SysTick_Init(uint32_t Time, uint32_t Unit)
{
    if(SysTick_Config(SystemCoreClock / Time / Unit)) { while(1); }
	SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
    Time_Unit = Time * Unit;
}

void SysTick_Delay(uint32_t Time, uint32_t Unit)
{
    Time_Delay = Time * Unit / Time_Unit;
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;
	while(Time_Delay != 0);
}

void SysTick_Decrement(void)
{
	if(Time_Delay != 0) { Time_Delay--; }
}
