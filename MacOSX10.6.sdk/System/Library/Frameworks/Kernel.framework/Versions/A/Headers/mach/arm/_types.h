/*
 * Copyright (c) 2006-2007 Apple Inc. All rights reserved.
 *
 * @APPLE_OSREFERENCE_LICENSE_HEADER_START@
 * 
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. The rights granted to you under the License
 * may not be used to create, or enable the creation or redistribution of,
 * unlawful or unlicensed copies of an Apple operating system, or to
 * circumvent, violate, or enable the circumvention or violation of, any
 * terms of an Apple operating system software license agreement.
 * 
 * Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this file.
 * 
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 * 
 * @APPLE_OSREFERENCE_LICENSE_HEADER_END@
 */
/*
 * @OSF_COPYRIGHT@
 */

#ifndef	_MACH_ARM__TYPES_H_
#define	_MACH_ARM__TYPES_H_

/*
 * arm_thread_state is the structure that is exported to user threads for 
 * use in status/mutate calls.  This structure should never change.
 *
 */

#if !__DARWIN_UNIX03
struct arm_thread_state
#else /* __DARWIN_UNIX03 */
struct __darwin_arm_thread_state
#endif /* __DARWIN_UNIX03 */
{
	uint32_t	r[13];		/* General purpose register r0-r12 */
	uint32_t	sp;		/* Stack pointer r13 */
	uint32_t	lr;		/* Link regisster r14 */
	uint32_t	pc;		/* Program counter r15 */
	uint32_t	cpsr;		/* Current program status register */
};

/* This structure should be double-word aligned for performance */

#if !__DARWIN_UNIX03
struct arm_vfp_state
#else /* __DARWIN_UNIX03 */
struct __darwin_arm_vfp_state
#endif /* __DARWIN_UNIX03 */
{
	uint32_t	r[32];
	uint32_t	fpscr;
};

/*
 * arm_exception_state
 */

#if !__DARWIN_UNIX03
struct arm_exception_state
#else /* __DARWIN_UNIX03 */
struct __darwin_arm_exception_state
#endif /* __DARWIN_UNIX03 */
{
        uint32_t	exception;		/* number of arm exception taken */
        uint32_t        fsr;			/* Fault status */
        uint32_t        far;			/* Virtual Fault Address */
};

#endif /* _MACH_ARM__TYPES_H_ */
