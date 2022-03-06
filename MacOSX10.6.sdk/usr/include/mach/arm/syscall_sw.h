/*
 * Copyright (c) 2007 Apple Inc. All rights reserved.
 */
/*
 * FILE_ID: syscall_sw.h
 */

#ifndef	_MACH_ARM_SYSCALL_SW_H_
#define _MACH_ARM_SYSCALL_SW_H_

#include <mach/machine/vm_param.h>
#include <architecture/arm/asm_help.h>

/* 0 to 4 args are already loaded in r0-r3 */
#define _kernel_trap_0to4(trap_name, trap_number) \
	mov		r12, # ## trap_number			/* load syscall number */ ; \
	swi		#SWI_SYSCALL					; \
	bx		lr								/* return */ ;

#define _kernel_trap_5(trap_name, trap_number) \
	mov		ip, sp							/* save pointer to args */ ; \
	stmfd	sp!, { r4-r5 }					/* save r4-r5, keep stack 64-bit aligned */; \
	ldr		r4, [ ip ]						/* load arg 5 */ ; \
	mov		r12, # ## trap_number			/* load syscall number */ ; \
	swi		#SWI_SYSCALL					; \
	ldmfd	sp!, { r4-r5 }					/* restore r4-r5 */ ;\
	bx		lr								/* return */ ;

#define _kernel_trap_6to9(trap_name, trap_number, save_regs, arg_regs) \
	mov		ip, sp							/* save pointer to args */ ; \
	stmfd	sp!, { save_regs }				/* callee saved regs */; \
	ldmia	ip, { arg_regs }				/* load arg registers (above r0-r3) */ ;\
	mov		r12, # ## trap_number			/* load syscall number */ ; \
	swi		#SWI_SYSCALL					; \
	ldmfd	sp!, { save_regs }	 			/* restore callee saved regs */ ;\
	bx		lr								/* return */ ;

#define COMMA ,

#define _kernel_trap_0(trap_name, trap_number) _kernel_trap_0to4(trap_name, trap_number)
#define _kernel_trap_1(trap_name, trap_number) _kernel_trap_0to4(trap_name, trap_number)
#define _kernel_trap_2(trap_name, trap_number) _kernel_trap_0to4(trap_name, trap_number)
#define _kernel_trap_3(trap_name, trap_number) _kernel_trap_0to4(trap_name, trap_number)
#define _kernel_trap_4(trap_name, trap_number) _kernel_trap_0to4(trap_name, trap_number)
/* _kernel_trap_5 defined above */
#define _kernel_trap_6(trap_name, trap_number) _kernel_trap_6to9(trap_name, trap_number, r4-r5, r4-r5)
/* need to save r8 not just for alignment but because mach_msg_trap overwrites the eighth argument */
#define _kernel_trap_7(trap_name, trap_number) _kernel_trap_6to9(trap_name, trap_number, r4-r6 COMMA r8, r4-r6)
#define _kernel_trap_8(trap_name, trap_number) _kernel_trap_6to9(trap_name, trap_number, r4-r6 COMMA r8, r4-r6 COMMA r8)
/* there is only one nine-argument trap (mach_msg_overwrite_trap) and it doesn't use the ninth argument */
#define _kernel_trap_9(trap_name, trap_number) _kernel_trap_8(trap_name, trap_number)

/* select the appropriate trap macro based off the number of args */
#define kernel_trap(trap_name, trap_number, num_args) \
	LEAF(_##trap_name, 0)	\
	_kernel_trap_##num_args(trap_name, trap_number)

#endif	/* _MACH_ARM_SYSCALL_SW_H_ */
