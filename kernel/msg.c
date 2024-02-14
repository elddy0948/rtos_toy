#include "stdint.h"
#include "stdbool.h"
#include "../lib/stdlib.h"
#include "msg.h"

static KernelCirQueue_t sMsgQueue[KernelMsgQueue_Num];

void Kernel_msgQueue_init()
{
	for (uint32_t i = 0; i < KernelMsgQueue_Num; ++i)
	{
		sMsgQueue[i].front = 0;
		sMsgQueue[i].rear = 0;
		
		memclr(sMsgQueue[i].Queue, MSG_Q_SIZE_BYTE);	
	}
}

bool Kernel_msgQueue_is_empty(KernelMsgQueue_t queueName)
{
	if (queueName >= KernelMsgQueue_Num)
		return false;

	if (sMsgQueue[queueName].front == sMsgQueue[queueName].rear)
		return true;

	return false;
}

bool Kernel_msgQueue_is_full(KernelMsgQueue_t queueName)
{
	if (queueName >= KernelMsgQueue_Num)
		return false;

	if (((sMsgQueue[queueName].rear + 1) % MSG_Q_SIZE_BYTE) == sMsgQueue[queueName].front)
		return true;

	return false;
}

bool Kernel_msgQueue_enqueue(KernelMsgQueue_t queueName, uint8_t data)
{
	if (queueName >= KernelMsgQueue_Num)
		return false;

	if (Kernel_msgQueue_is_full(queueName))
		return false;

	sMsgQueue[queueName].rear++;
	sMsgQueue[queueName].rear %= MSG_Q_SIZE_BYTE;

	uint32_t idx = sMsgQueue[queueName].rear;
	sMsgQueue[queueName].Queue[idx] = data;

	return true;
}

bool Kernel_msgQueue_dequeue(KernelMsgQueue_t queueName, uint8_t *out_data)
{
	if (queueName >= KernelMsgQueue_Num)
		return false;
	if (Kernel_msgQueue_is_empty(queueName))
		return false;

	sMsgQueue[queueName].front++;
	sMsgQueue[queueName].front %= MSG_Q_SIZE_BYTE;

	uint32_t idx = sMsgQueue[queueName].front;
	*out_data = sMsgQueue[queueName].Queue[idx];
	
	return true;
}

