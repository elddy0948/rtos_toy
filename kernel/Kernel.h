#ifndef KERNEL_KERNEL_H_
#define KERNEL_KERNEL_H_

#include "../include/stdint.h"
#include "event.h"

void Kernel_start(void);
void Kernel_yield(void);

// Event API

// for sending event 
void Kernel_send_events(uint32_t event_list);

// waiting for event (don't care who sent)
KernelEventFlag_t Kernel_wait_events(uint32_t waiting_list);

#endif /* KERNEL_KERNEL_H_ */
