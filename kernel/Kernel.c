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

bool Kernel_send_message(KernelMsgQueue_t queueName, void *data, uint32_t count)
{
	uint8_t* d = (uint8_t*)data;
	
	for (uint32_t i = 0; i < count; ++i)
	{
		if (Kernel_msgQueue_enqueue(queueName, *d) == false)
		{
			for (uint32_t j = 0; j < i; ++j)
			{
				uint8_t rollback;
				Kernel_msgQueue_dequeue(queueName, &rollback);
			}
			return false;
		}
		d++;	
	}
	return true;
}

uint32_t Kernel_receive_message(KernelMsgQueue_t queueName, void *data, uint32_t count)
{
	uint8_t* d = (uint8_t*)data;
	for (uint32_t i = 0; i < count; ++i)
	{
		if (Kernel_msgQueue_dequeue(queueName, d) == false)
			return i;
		d++;
	}

	return count;
}
