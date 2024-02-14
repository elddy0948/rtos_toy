#include "stdlib.h"

#include "../hal/HalTimer.h"

void delay(uint32_t ms)
{
	uint32_t goal = Hal_timer_get_1ms_counter() + ms;

	// wait for reach goal time
	while (goal != Hal_timer_get_1ms_counter());
}

void memclr(void *dst, uint32_t count)
{
	uint8_t* d = (uint8_t*)dst;

	while (count--)
	{
		*d++ = 0;
	}
}
