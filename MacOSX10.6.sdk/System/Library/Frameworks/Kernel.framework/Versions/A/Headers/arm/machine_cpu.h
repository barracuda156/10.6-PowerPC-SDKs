/*
 * Copyright (c) 2007 Apple Inc. All rights reserved.
 */
#ifndef _ARM_MACHINE_CPU_H_
#define _ARM_MACHINE_CPU_H_

#include <mach/mach_types.h>
#include <mach/boolean.h>
#include <kern/kern_types.h>
#include <pexpert/pexpert.h>
#include <arm/cpu_data_internal.h>

extern void cpu_machine_init(void);

extern kern_return_t cpu_register(int *slot_nump);

extern void cpu_signal_handler(void);

extern void cpu_doshutdown(void (*doshutdown)(processor_t), processor_t processor);

extern void cpu_idle(void);
extern void cpu_idle_exit(void);

extern void cpu_machine_idle_init(boolean_t from_boot);

extern void arm_init_cpu(__unused boot_args *args);

extern void arm_init_idle_cpu(__unused boot_args *args);

extern void init_cpu_timebase(boolean_t enable_fiq);

#define cpu_pause() do {} while (0)	/* Not for this architecture */

#endif /* _ARM_MACHINE_CPU_H_ */
