/*
 * Copyright (c) 2002-2007 Apple Inc. All rights reserved.
 */

#ifndef _ARM_UCONTEXT_H_
#define _ARM_UCONTEXT_H_

#include <mach/arm/_types.h>

#ifndef _POSIX_C_SOURCE
struct mcontext {
	struct arm_exception_state	es;
	struct arm_thread_state		ss;
	struct arm_vfp_state		fs;
};
#define ARM_MCONTEXT_SIZE	(ARM_THREAD_STATE_COUNT + ARM_VFP_STATE_COUNT + ARM_EXCEPTION_STATE_COUNT) * sizeof(int)
#else /* _POSIX_C_SOURCE */
struct __darwin_mcontext {
	struct __darwin_arm_exception_state	es;
	struct __darwin_arm_thread_state	ss;
	struct __darwin_arm_vfp_state		fs;
};
#endif /* _POSIX_C_SOURCE */

#ifndef _MCONTEXT_T
#define _MCONTEXT_T
typedef __darwin_mcontext_t		mcontext_t;
#endif

#endif /* _ARM_UCONTEXT_H_ */
