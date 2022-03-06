/*
 * Copyright (c) 2007 Apple Inc. All rights reserved.
 */
/*
 * @OSF_COPYRIGHT@
 */

#ifndef	_ARM_MACHINE_ROUTINES_H_
#define	_ARM_MACHINE_ROUTINES_H_

#include <mach/mach_types.h>
#include <mach/boolean.h>
#include <kern/kern_types.h>
#include <pexpert/pexpert.h>

#include <sys/appleapiopts.h>

/* Interrupt handling */

/* Initialize Interrupts */
void    ml_init_interrupt(void);

/* Get Interrupts Enabled */
boolean_t ml_get_interrupts_enabled(void);

/* Set Interrupts Enabled */
boolean_t ml_set_interrupts_enabled(boolean_t enable);

/* Check if running at interrupt context */
boolean_t ml_at_interrupt_context(void);

/* Generate a fake interrupt */
void ml_cause_interrupt(void);

/* Type for the Time Base Enable function */
typedef void (*time_base_enable_t)(cpu_id_t cpu_id, boolean_t enable);

/* Type for the Processor Idle function */
typedef void (*processor_idle_t)(cpu_id_t cpu_id, boolean_t enter);

/* Type for the IPI Hander */
typedef void (*ipi_handler_t)(void);

/* Struct for ml_processor_register */
struct ml_processor_info {
	cpu_id_t			cpu_id;
	boolean_t			boot_cpu;
	vm_offset_t			start_paddr;
	boolean_t			supports_nap;
	uint32_t			l2cr_value;
	time_base_enable_t		time_base_enable;
	processor_idle_t		processor_idle;
	uint32_t			powergate_stub_addr;
	uint32_t			powergate_stub_length;
	uint32_t			powergate_latency;
};

typedef struct ml_processor_info ml_processor_info_t;

/* Register a processor */                      
kern_return_t	ml_processor_register(
	ml_processor_info_t	*ml_processor_info,
	processor_t			*processor,
	ipi_handler_t		*ipi_handler);



/* Initialize Interrupts */
void ml_install_interrupt_handler(
    void *nub,
    int source,
    void *target,
    IOInterruptHandler handler,
    void *refCon);


unsigned int ml_get_entropie(
	void);

void ml_read_entropy_buffer(
	char *buffer,
	unsigned int *count);

#ifdef __APPLE_API_UNSTABLE
vm_offset_t
ml_static_ptovirt(
	vm_offset_t);

/* PCI config cycle probing */
boolean_t ml_probe_read(
	vm_offset_t paddr,
	unsigned int *val);
boolean_t ml_probe_read_64(
	addr64_t paddr,
	unsigned int *val);

/* Read physical address byte */
unsigned int ml_phys_read_byte(
	vm_offset_t paddr);
unsigned int ml_phys_read_byte_64(
	addr64_t paddr);

/* Read physical address half word */
unsigned int ml_phys_read_half(
	vm_offset_t paddr);
unsigned int ml_phys_read_half_64(
	addr64_t paddr);

/* Read physical address word*/
unsigned int ml_phys_read(
	vm_offset_t paddr);
unsigned int ml_phys_read_64(
	addr64_t paddr);
unsigned int ml_phys_read_word(
	vm_offset_t paddr);
unsigned int ml_phys_read_word_64(
	addr64_t paddr);

/* Read physical address double word */
unsigned long long ml_phys_read_double(
	vm_offset_t paddr);
unsigned long long ml_phys_read_double_64(
	addr64_t paddr);

/* Write physical address byte */
void ml_phys_write_byte(
	vm_offset_t paddr, unsigned int data);
void ml_phys_write_byte_64(
	addr64_t paddr, unsigned int data);

/* Write physical address half word */
void ml_phys_write_half(
	vm_offset_t paddr, unsigned int data);
void ml_phys_write_half_64(
	addr64_t paddr, unsigned int data);

/* Write physical address word */
void ml_phys_write(
	vm_offset_t paddr, unsigned int data);
void ml_phys_write_64(
	addr64_t paddr, unsigned int data);
void ml_phys_write_word(
	vm_offset_t paddr, unsigned int data);
void ml_phys_write_word_64(
	addr64_t paddr, unsigned int data);

/* Write physical address double word */
void ml_phys_write_double(
	vm_offset_t paddr, unsigned long long data);
void ml_phys_write_double_64(
	addr64_t paddr, unsigned long long data);

void ml_static_mfree(
	vm_offset_t,
	vm_size_t);

/* virtual to physical on wired pages */
vm_offset_t ml_vtophys(
	vm_offset_t vaddr);

/* Struct for ml_cpu_get_info */
struct ml_cpu_info {
	unsigned long		vector_unit;
	unsigned long		cache_line_size;
	unsigned long		l1_icache_size;
	unsigned long		l1_dcache_size;
	unsigned long		l2_settings;
	unsigned long		l2_cache_size;
	unsigned long		l3_settings;
	unsigned long		l3_cache_size;
};

typedef struct ml_cpu_info ml_cpu_info_t;

/* Get processor info */
void ml_cpu_get_info(ml_cpu_info_t *ml_cpu_info);

#endif /* __APPLE_API_UNSTABLE */

#ifdef __APPLE_API_PRIVATE

/* Zero bytes starting at a physical address */
void bzero_phys(
	addr64_t phys_address,
	uint32_t length);

void bzero_phys_nc(addr64_t src64, vm_size_t bytes);

void ml_thread_policy(
	thread_t thread,
	unsigned policy_id,
	unsigned policy_info);

#define MACHINE_GROUP					0x00000001
#define MACHINE_NETWORK_GROUP			0x10000000
#define MACHINE_NETWORK_WORKLOOP		0x00000001
#define MACHINE_NETWORK_NETISR			0x00000002

/* Initialize the maximum number of CPUs */
void ml_init_max_cpus(
	unsigned int max_cpus);

/* Return the maximum number of CPUs set by ml_init_max_cpus() */
unsigned int ml_get_max_cpus(
	void);

extern void	ml_cpu_up(void);
extern void	ml_cpu_down(void);
extern void	ml_arm_sleep(void);


extern	uint32_t	arm_debug_read_dscr(void);

extern int	set_be_bit(void);
extern int	clr_be_bit(void);
extern int	be_tracing(void);

#endif /* __APPLE_API_PRIVATE */

#endif /* _ARM_MACHINE_ROUTINES_H_ */
