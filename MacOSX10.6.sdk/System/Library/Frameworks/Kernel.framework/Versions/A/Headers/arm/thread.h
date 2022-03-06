/*
 * Copyright (c) 2007 Apple Inc. All rights reserved.
 */
/*
 * @OSF_COPYRIGHT@
 */
/* 
 * Mach Operating System
 * Copyright (c) 1991,1990,1989 Carnegie Mellon University
 * All Rights Reserved.
 * 
 * Permission to use, copy, modify and distribute this software and its
 * documentation is hereby granted, provided that both the copyright
 * notice and this permission notice appear in all copies of the
 * software, derivative works or modified versions, and any portions
 * thereof, and that both notices appear in supporting documentation.
 * 
 * CARNEGIE MELLON ALLOWS FREE USE OF THIS SOFTWARE IN ITS "AS IS"
 * CONDITION.  CARNEGIE MELLON DISCLAIMS ANY LIABILITY OF ANY KIND FOR
 * ANY DAMAGES WHATSOEVER RESULTING FROM THE USE OF THIS SOFTWARE.
 * 
 * Carnegie Mellon requests users of this software to return to
 * 
 *  Software Distribution Coordinator  or  Software.Distribution@CS.CMU.EDU
 *  School of Computer Science
 *  Carnegie Mellon University
 *  Pittsburgh PA 15213-3890
 * 
 * any improvements or extensions that they make and grant Carnegie Mellon
 * the rights to redistribute these changes.
 */
/*
 */

#ifndef	_ARM_THREAD_H_
#define _ARM_THREAD_H_

#include <mach/mach_types.h>
#include <mach/boolean.h>
#include <mach/arm/vm_types.h>
#include <mach/thread_status.h>


/*
 * vector floating point saved state
 */
struct arm_vfpsaved_state {
	uint32_t	r[64];
	uint32_t	fpscr;
};

struct facility_context {
	struct arm_vfpsaved_state	*VFPsave;					/* The vfp savearea */
	struct arm_saved_state		*VFPlevel;					/* The vfp context level */
	unsigned int				VFPcpu;
};

/*
 * Maps state flavor to number of words in the state:
 */
__private_extern__ unsigned int _MachineStateCount[];


extern struct arm_saved_state		*get_user_regs(thread_t);
extern struct arm_saved_state		*find_user_regs(thread_t);
extern struct arm_saved_state		*find_kern_regs(thread_t);
extern struct arm_vfpsaved_state	*find_user_vfp(thread_t);
extern arm_debug_state_t                *find_debug_state(thread_t);



extern void *act_thread_csave(void);
extern void act_thread_catt(void *ctx);
extern void act_thread_cfree(void *ctx);

/*
 * Return address of the function that called current function, given
 *	address of the first parameter of current function.
 */
#define	GET_RETURN_PC(addr)	(((vm_offset_t *)0))

/*
 * Defining this indicates that MD code will supply an exception()
 * routine, conformant with kern/exception.c (dependency alert!)
 * but which does wonderfully fast, machine-dependent magic.
 */
#define MACHINE_FAST_EXCEPTION 1

#endif	/* _ARM_THREAD_H_ */
