#ifndef KERNEL_MSG_H_
#define KERNEL_MSG_H_

#define MSG_Q_SIZE_BYTE 512

#include "stdint.h"

// using 3 queues
typedef enum KernelMsgQueue_t
{
	KernelMsgQueue_Task0,
	KernelMsgQueue_Task1,
	KernelMsgQueue_Task2,
	KernelMsgQueue_Num,
} KernelMsgQueue_t;

typedef struct KernelCirQueue_t
{
	uint32_t front;
	uint32_t rear;
	uint8_t Queue[MSG_Q_SIZE_BYTE];
} KernelCirQueue_t;

void Kernel_msgQueue_init(void);
bool Kernel_msgQueue_is_empty(KernelMsgQueue_t queueName);
bool Kernel_msgQueue_is_full(KernelMsgQueue_t queueName);
bool Kernel_msgQueue_enqueue(KernelMsgQueue_t queueName, uint8_t data);
bool Kernel_msgQueue_dequeue(KernelMsgQueue_t queueName, uint8_t* out_data);

#endif /* KERNEL_MSG_H_ */
