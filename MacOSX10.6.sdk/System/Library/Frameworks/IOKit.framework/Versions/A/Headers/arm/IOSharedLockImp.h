/*
 * Copyright (c) 1998-2000 Apple Computer, Inc. All rights reserved.
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
 * Copyright (c) 1998 Apple Computer, Inc.  All rights reserved. 
 *
 * HISTORY
 *
 */

/* 	Copyright (c) 1992 NeXT Computer, Inc.  All rights reserved. 
 *
 * EventShmemLock.h -	Shared memory area locks for use between the
 *			WindowServer and the Event Driver.
 *
 *
 * HISTORY
 * 29 April 1992    Mike Paquette at NeXT
 *      Created. 
 *
 * Multiprocessor locks used within the shared memory area between the
 * kernel and event system.  These must work in both user and kernel mode.
 * The locks are defined in an include file so they get exported to the local
 * include file area.
 *
 * This is basically a ripoff of the spin locks under the cthreads packages.
 */

#ifndef _IOKIT_IOSHAREDLOCKIMP_H
#define _IOKIT_IOSHAREDLOCKIMP_H

#include <architecture/arm/asm_help.h>

/* 
 * void
 * ev_lock(p)
 *	int *p;
 *
 * Lock the lock pointed to by p.  Spin (possibly forever) until the next
 * lock is available.
 */
	TEXT

LEAF(_ev_lock, 0)
LEAF(_IOSpinLock, 0)
	mov	r1, #1		/* locked value */
	swp	r1, r1, [r0]	/* swap the lock */
	cmp	r1, #0		/* test for unlocked */
	bne	_IOSpinLock	/* try again if locked */
	bx	lr
END(_ev_lock)

/*
 * void
 * ev_unlock(p)
 *	int *p;
 *
 * Unlock the lock pointed to by p.
 */
LEAF(_ev_unlock, 0)
LEAF(_IOSpinUnlock, 0)
	mov	r1, #0		/* unlocked value */
	str	r1, [r0]	/* store the lock */
	bx	lr
END(_ev_unlock)



/*
 * int
 * ev_try_lock(p)
 *	int *p;
 *
 * Try to lock p.  Return zero if not successful.
 */

LEAF(_ev_try_lock, 0)
LEAF(_IOTrySpinLock, 0)
	mov	r1, #1		/* locked value */
	swp	r1, r1, [r0]	/* swap the lock */
	cmp	r1, #0		/* test for unlocked */
	movne	r0, #0		/* was lock, return 0 */
	moveq	r0, #1		/* was not locked, return 1 */
	bx	lr
END(_ev_try_lock)


#endif /* ! _IOKIT_IOSHAREDLOCKIMP_H */
