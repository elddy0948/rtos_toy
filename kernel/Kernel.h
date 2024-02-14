#ifndef KERNEL_KERNEL_H_
#define KERNEL_KERNEL_H_

#include "../include/stdint.h"
#include "event.h"
#include "msg.h"

void Kernel_start(void);
void Kernel_yield(void);

// Event API

// for sending event 
void Kernel_send_events(uint32_t event_list);

// waiting for event (don't care who sent)
KernelEventFlag_t Kernel_wait_events(uint32_t waiting_list);

// Message API
bool Kernel_send_message(KernelMsgQueue_t queueName, void* data, uint32_t count);
uint32_t Kernel_receive_message(KernelMsgQueue_t queueName, void* data, uint32_t count);

#endif /* KERNEL_KERNEL_H_ */
