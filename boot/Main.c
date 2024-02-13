#include "../include/stdint.h"

// Hal
#include "../hal/HalUart.h"
#include "../hal/HalInterrupt.h"
#include "../hal/HalTimer.h"

// Lib
#include "../lib/stdio.h"
#include "../lib/stdlib.h"

// Kernel
#include "../kernel/task.h"
#include "../kernel/Kernel.h"

static void Hw_init(void);
static void Kernel_init(void);

static void Printf_test(void);
static void Timer_test(void);

void User_task0(void);
void User_task1(void);
void User_task2(void);

int main(void)
{
	Hw_init();

	Printf_test();
	Timer_test();

	Kernel_init();
	
	while(1);

	return 0;
}

static void Hw_init(void)
{
	Hal_interrupt_init();
  Hal_uart_init();
	Hal_timer_init();
}

static void Kernel_init(void)
{
	uint32_t taskID;

	Kernel_task_init();
	taskID = Kernel_task_create(User_task0);

	if (NOT_ENOUGH_TASK_NUM == taskID)
		putstr("Task0 creation failed.\n");

	taskID = Kernel_task_create(User_task1);
	if (NOT_ENOUGH_TASK_NUM == taskID)
		putstr("Task1 creation failed.\n");

	taskID = Kernel_task_create(User_task2);
	if (NOT_ENOUGH_TASK_NUM == taskID)
		putstr("Task2 creation failed.\n");

	Kernel_start();
}

static void Printf_test(void)
{
	char* str = "printf pointer test";
	char* nullptr = 0;
	uint32_t i = 5;
	
	// check which timer clock using now
	uint32_t* sysctrl0 = (uint32_t*) 0x10001000;

	debug_printf("%s\n", "Hello printf");
	debug_printf("output string pointer: %s\n", str);
	debug_printf("%s is null pointer, %u number\n", nullptr, 10);
	debug_printf("%u = 5\n", i);
	debug_printf("dec=%u hex=%x\n", 0xff, 0xff);
	debug_printf("print zero %u\n", 0);
	debug_printf("SYSCTRL0 %x\n", *sysctrl0);
}

static void Timer_test(void)
{
	for (uint32_t i = 0; i < 5; ++i)
	{
		debug_printf("current count : %u\n", Hal_timer_get_1ms_counter());
		delay(1);	// 1s
	}
}

void User_task0(void)
{
	uint32_t local = 0;

	while(1)
	{
		debug_printf("User Task #0 SP=0x%x\n", &local);
		Kernel_yield();
	}
}

void User_task1(void)
{
	uint32_t local = 0;

	while(1)
	{
		debug_printf("User Task #1 SP=0x%x\n", &local);
		Kernel_yield();
	}
}

void User_task2(void)
{
	uint32_t local = 0;

	while(1)
	{
		debug_printf("User Task #2 SP=0x%x\n", &local);
		Kernel_yield();
	}
}
