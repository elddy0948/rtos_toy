#ifndef HAL_RVPB_INTERRUPT_H_
#define HAL_RVPB_INTERRUPT_H_

#include "stdint.h"

typedef union CpuControl_t
{
  uint32_t all;
  struct
  {
    uint32_t Enable:1;
    uint32_t Reserved:31;
  } bits;
} CpuControl_t;

typedef union PriorityMask_t
{
  uint32_t all;
  struct
  {
    uint32_t Reserved:4;
    uint32_t Prioritymask:4;
    uint32_t reserved:24;
  } bits;
} PriorityMask_t;

typedef union BinaryPoint_t
{
  uint32_t all;
  struct
  {
    uint32_t Binarypoint:3;
    uint32_t Reserved:29;
  } bits;
} BinaryPoint_t;

typedef union InterruptAck_t
{
  uint32_t all;
  struct
  {
    uint32_t InterruptID:10;
    uint32_t CPUsourceID:3;
    uint32_t Reserved:19;
  } bits;
} InterruptAck_t;

typedef union EndOfInterrupt_t
{
  uint32_t all;
  struct
  {
    uint32_t InterruptID:10;
    uint32_t CPUsourceID:3;
    uint32_t Reserved:19;
  } bits;
} EndOfInterrupt_t;

typedef union RunningInterrupt_t
{
  uint32_t all;
  struct
  {
    uint32_t Reserved:4;
    uint32_t Priority:4;
    uint32_t reserved:24;
  } bits;
} RunningInterrupt_t;

typedef union HighestPendingInterrupt_t
{
  uint32_t all;
  struct
  {
    uint32_t InterruptID:10;
    uint32_t CPUsourceID:3;
    uint32_t Reserved:19;
  } bits;
} HighestPendingInterrupt_t;

typedef union DistributorControl_t
{
  uint32_t all;
  struct
  {
    uint32_t Enabled:1;
    uint32_t Reserved:31;
  } bits;
} DistributorControl_t;

typedef union ControllerType_t
{
  uint32_t all;
  struct
  {
    uint32_t IDlinesNumber:5;
    uint32_t CPUnumber:3;
    uint32_t Reserved:24;
  } bits;
} ControllerType_t;

typedef struct GicCput_t
{
  CpuControl_t cpucontrol;                        // 0x000
  PriorityMask_t prioritymask;                    // 0x004
  BinaryPoint_t binarypoint;                      // 0x008
  InterruptAck_t interruptack;                    // 0x00C
  EndOfInterrupt_t endofinterrupt;                // 0x010
  RunningInterrupt_t runninginterrupt;            // 0x014
  HighestPendingInterrupt_t highestpendinterrupt; // 0x018
} GicCput_t;

typedef struct GicDist_t
{
  DistributorControl_t    distributorctrl;  // 0x000
  ControllerType_t        controllertype;   // 0x004
  uint32_t                reserved0[62];    // 0x008 - 0x0FC
  uint32_t                reserved1;        // 0x100
  uint32_t                setenable1;       // 0x104
  uint32_t                setenable2;       // 0x108
  uint32_t                reserved2[29];    // 0x10C - 0x17C
  uint32_t                reserved3;        // 0x180
  uint32_t                clearenable1;     // 0x184
  uint32_t                clearenable2;     // 0x188
} GicDist_t;


#define GIC_CPU_BASE 0x1E000000
#define GIC_DIST_BASE 0x1E001000

#define GIC_PRIORITY_MASK_NONE 0xF

#define GIC_IRQ_START 32
#define GIC_IRQ_END 95

#endif /* HAL_RVPB_INTERRUPT_H_ */
