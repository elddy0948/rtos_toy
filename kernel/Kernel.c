#include "../include/memio.h"
#include "task.h"
#include "Kernel.h"
#include "stdio.h"

void Kernel_start(void)
{
	Kernel_task_start();
}

void Kernel_yield(void)
{
	// when task done, just call scheduler
	Kernel_task_scheduler();
}

void Kernel_send_events(uint32_t event_list)
{
	uint32_t i = 0;

	for (i = 0; i < 32; ++i)
	{
		if ((event_list >> i) & 1)
		{
			KernelEventFlag_t sending_event = KernelEventFlag_Empty;
			SET_BIT(sending_event, i);
			Kernel_event_flag_set(sending_event);
		}
	}
}

KernelEventFlag_t Kernel_wait_events(uint32_t waiting_list)
{
	uint32_t i = 0;

	for (i = 0; i < 32; ++i)
	{
		if ((waiting_list >> i) & 1)
		{
			KernelEventFlag_t waiting_event = KernelEventFlag_Empty;
			SET_BIT(waiting_event, i);
			if (Kernel_event_flag_check(waiting_event))
				return waiting_event;
		}
	}
	return KernelEventFlag_Empty;
}
