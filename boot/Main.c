#include "stdint.h"

// Hal
#include "HalUart.h"
#include "HalInterrupt.h"
#include "HalTimer.h"

// Lib
#include "stdio.h"
#include "stdlib.h"

// Kernel
#include "task.h"
#include "Kernel.h"
#include "event.h"

static void Hw_init(void);
static void Kernel_init(void);

static void Printf_test(void);
static void Timer_test(void);

static void Test_critical_section(uint32_t p, uint32_t taskID);

void User_task0(void);
void User_task1(void);
void User_task2(void);

int main(void)
{
	Hw_init();

	Printf_test();
	// Timer_test();

	Kernel_init();

	while (1)
		;

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
	Kernel_event_flag_init();
	Kernel_msgQueue_init();
	Kernel_sem_init(1);

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
	char *str = "printf pointer test";
	char *nullptr = 0;
	uint32_t i = 5;

	// check which timer clock using now
	uint32_t *sysctrl0 = (uint32_t *)0x10001000;

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
		delay(1); // 1s
	}
}

static uint32_t shared_value;

static void Test_critical_section(uint32_t p, uint32_t taskID)
{
	Kernel_lock_sem();
	debug_printf("User Task #%u Send=%u\n", taskID, p);
	shared_value = p;
	Kernel_yield();
	debug_printf("\nYield!\n");
	delay(1);

	debug_printf("User Task #%u Shared Value=%u\n", taskID, shared_value);
	Kernel_unlock_sem();
}

void User_task0(void)
{
	uint32_t local = 0;
	debug_printf("User Task #0 SP=0x%x\n", &local);

	uint8_t cmdBuffer[16];
	uint32_t cmdBufferIndex = 0;
	uint8_t uartch = 0;

	while (true)
	{
		KernelEventFlag_t handle_event = Kernel_wait_events(KernelEventFlag_UartIn | KernelEventFlag_CmdOut);
		switch (handle_event)
		{
		case KernelEventFlag_UartIn:
			Kernel_receive_message(KernelMsgQueue_Task0, &uartch, 1);
			if (uartch == '\r')
			{
				cmdBuffer[cmdBufferIndex] = '\0';
				Kernel_send_message(KernelMsgQueue_Task1, &cmdBufferIndex, 1);
				Kernel_send_message(KernelMsgQueue_Task1, cmdBuffer, cmdBufferIndex);
				Kernel_send_events(KernelEventFlag_CmdIn);
				cmdBufferIndex = 0;
			}
			else
			{
				cmdBuffer[cmdBufferIndex] = uartch;
				cmdBufferIndex++;
				cmdBufferIndex %= 16;
			}
			break;
		case KernelEventFlag_CmdOut:
			Test_critical_section(5, 0);
			break;
		}
		Kernel_yield();
	}
}

void User_task1(void)
{
	uint32_t local = 0;

	debug_printf("User Task #1 SP=0x%x\n", &local);

	uint8_t cmdlen = 0;
	uint8_t cmd[16] = {0};

	while (true)
	{
		KernelEventFlag_t handle_event = Kernel_wait_events(KernelEventFlag_CmdIn);
		switch (handle_event)
		{
		case KernelEventFlag_CmdIn:
			memclr(cmd, 16);
			Kernel_receive_message(KernelMsgQueue_Task1, &cmdlen, 1);
			Kernel_receive_message(KernelMsgQueue_Task1, cmd, cmdlen);
			debug_printf("\nRecv cmd : %s\n", cmd);
			break;
		}
		Kernel_yield();
	}
}

void User_task2(void)
{
	uint32_t local = 0;

	debug_printf("User Task #2 SP=0x%x\n", &local);

	while (true)
	{
		Kernel_yield();
	}
}
