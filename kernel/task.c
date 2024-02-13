#include "../include/ARMv7AR.h"
#include "task.h"

static KernelTaskControlBlock_t sTask_list[MAX_TASK_NUM];
static uint32_t sAllocated_tcb_index;
static uint32_t sCurrent_tcb_index;

// For context switching
static KernelTaskControlBlock_t* sCurrentTaskControlBlock;
static KernelTaskControlBlock_t* sNextTaskControlBlock;

static KernelTaskControlBlock_t* Scheduler_round_robin_algorithm(void);
static __attribute__ ((naked)) void Save_context(void);
static __attribute__ ((naked)) void Restore_context(void);

void Kernel_task_init(void)
{
	sAllocated_tcb_index = 0;
	sCurrent_tcb_index = 0;

	for (uint32_t i = 0; i < MAX_TASK_NUM; ++i)
	{
		sTask_list[i].stack_base = (uint8_t*)(TASK_STACK_START + (i * USR_TASK_STACK_SIZE));
		sTask_list[i].sp = (uint32_t)sTask_list[i].stack_base + USR_TASK_STACK_SIZE - 4;
		sTask_list[i].sp -= sizeof(KernelTaskContext_t);

		KernelTaskContext_t* context = (KernelTaskContext_t*)sTask_list[i].sp;

		context->pc = 0;
		context->spsr = ARM_MODE_BIT_SYS;
	}
}

void Kernel_task_start()
{
	sNextTaskControlBlock = &sTask_list[sCurrent_tcb_index];
	Restore_context();
}

uint32_t Kernel_task_create(KernelTaskFunc_t startFunc)
{
	KernelTaskControlBlock_t* new_tcb = &sTask_list[sAllocated_tcb_index++];

	if (sAllocated_tcb_index > MAX_TASK_NUM)
		return NOT_ENOUGH_TASK_NUM;

	KernelTaskContext_t* context = (KernelTaskContext_t*)new_tcb->sp;
	context->pc = (uint32_t)startFunc;

	return (sAllocated_tcb_index - 1);
}

static KernelTaskControlBlock_t* Scheduler_round_robin_algorithm(void)
{
	sCurrent_tcb_index++;
	sCurrent_tcb_index %= sAllocated_tcb_index;
	return &sTask_list[sCurrent_tcb_index];
}

__attribute__ ((naked)) void Kernel_task_context_switching(void)
{
	__asm__ ("B Save_context");
	__asm__ ("B Restore_context");
}

// Task schedule with round robin algorithm
void Kernel_task_scheduler(void)
{
	sCurrentTaskControlBlock = &sTask_list[sCurrent_tcb_index];
	sNextTaskControlBlock = Scheduler_round_robin_algorithm();
	Kernel_task_context_switching();
}

static __attribute__ ((naked)) void Save_context(void)
{
	// Saving current task context
	__asm__ ("PUSH {lr}");
	__asm__ ("PUSH {r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, r10, r11, r12}");
	__asm__ ("MRS r0, cpsr");
	__asm__ ("PUSH {r0}");
	
	// Save current task stack pointer into the current Task Control Block
	__asm__ ("LDR r0, =sCurrentTaskControlBlock");
	__asm__ ("LDR r0, [r0]");
	__asm__ ("STMIA r0!, {sp}");
}

static __attribute__ ((naked)) void Restore_context(void)
{
	// Restore next task stack pointer from the next Task Control Block
	__asm__ ("LDR r0, =sNextTaskControlBlock");
	__asm__ ("LDR r0, [r0]");
	__asm__ ("LDMIA r0!, {sp}");

	// Restore next task context from the next task stack
	__asm__ ("POP {r0}");
	__asm__ ("MSR cpsr, r0");
	__asm__ ("POP {r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, r10, r11, r12}");
	__asm__ ("POP {pc}");
}
