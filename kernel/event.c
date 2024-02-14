// Include
#include "../include/stdint.h"
#include "../include/stdbool.h"

// Kernel
#include "./event.h"

static uint32_t sEventFlag;

void Kernel_event_flag_init(void)
{
	// event flag initialize
	sEventFlag = 0x00000000;
}

void Kernel_event_flag_set(KernelEventFlag_t event)
{
	// set occured event bit
	sEventFlag |= (uint32_t)event;
}

void Kernel_event_flag_clear(KernelEventFlag_t event)
{
	// clear event bit
	sEventFlag &= ~((uint32_t)event);
}

bool Kernel_event_flag_check(KernelEventFlag_t event)
{
	if (sEventFlag & (uint32_t)event)
	{
		// if event flag is more than 0 
		Kernel_event_flag_clear(event);
		return true;
	}

	return false;
}
