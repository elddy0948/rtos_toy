#include "../include/stdint.h"
#include "Kernel.h"
#include "task.h"

void Kernel_start(void)
{
	Kernel_task_start();
}

void Kernel_yield(void)
{
	// when task done, just call scheduler 
	Kernel_task_scheduler();
}
