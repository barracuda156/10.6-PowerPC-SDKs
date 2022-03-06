#ifndef _LIBDISPATCH_EVENTS_F_
#define _LIBDISPATCH_EVENTS_F_

#include <Availability.h>
#include <sys/cdefs.h>
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

__BEGIN_DECLS


typedef void (*dispatch_event_callback_function_t)(void *, dispatch_event_t);
typedef void (*dispatch_source_finalizer_function_t)(void *, dispatch_source_t);

__OSX_AVAILABLE_STARTING(__MAC_10_6,__IPHONE_NA)
DISPATCH_PUBLIC_API DISPATCH_MALLOC DISPATCH_WARN_RESULT DISPATCH_NONNULL1 DISPATCH_NONNULL4
dispatch_source_t
dispatch_source_timer_create_f(dispatch_queue_t q,
	uint64_t nanoseconds,
	uint64_t flags,
	void *c_context,
	dispatch_source_attr_t attr,
	dispatch_event_callback_function_t callback);

__OSX_AVAILABLE_STARTING(__MAC_10_6,__IPHONE_NA)
DISPATCH_PUBLIC_API DISPATCH_MALLOC DISPATCH_WARN_RESULT DISPATCH_NONNULL1 DISPATCH_NONNULL4
dispatch_source_t
dispatch_source_signal_create_f(dispatch_queue_t q,
	sigset_t signals,
	void *c_context,
	dispatch_source_attr_t attr,
	dispatch_event_callback_function_t callback);

__OSX_AVAILABLE_STARTING(__MAC_10_6,__IPHONE_NA)
DISPATCH_PUBLIC_API DISPATCH_MALLOC DISPATCH_WARN_RESULT
dispatch_source_t
dispatch_source_mig_create_f(dispatch_queue_t q,
	mach_port_t mport, 
	size_t max_reply_size,
	dispatch_mig_callback_t mig_callback,
	dispatch_source_attr_t attr,
	dispatch_event_callback_function_t callback);

__OSX_AVAILABLE_STARTING(__MAC_10_6,__IPHONE_NA)
DISPATCH_PUBLIC_API DISPATCH_MALLOC DISPATCH_WARN_RESULT DISPATCH_NONNULL1 DISPATCH_NONNULL5
dispatch_source_t
dispatch_source_read_create_f(dispatch_queue_t q,
	int descriptor,
	void *c_context,
	dispatch_source_attr_t attr,
	dispatch_event_callback_function_t callback);

__OSX_AVAILABLE_STARTING(__MAC_10_6,__IPHONE_NA)
DISPATCH_PUBLIC_API DISPATCH_MALLOC DISPATCH_WARN_RESULT DISPATCH_NONNULL1 DISPATCH_NONNULL5
dispatch_source_t
dispatch_source_write_create_f(dispatch_queue_t q,
	int descriptor, 
	void *c_context,
	dispatch_source_attr_t attr,
	dispatch_event_callback_function_t callback);

__OSX_AVAILABLE_STARTING(__MAC_10_6,__IPHONE_NA)
DISPATCH_PUBLIC_API DISPATCH_MALLOC DISPATCH_WARN_RESULT DISPATCH_NONNULL1 DISPATCH_NONNULL6
dispatch_source_t
dispatch_source_vnode_create_f(dispatch_queue_t q,
	int descriptor,
	uint64_t flags,
	void *c_context,
	dispatch_source_attr_t attr,
	dispatch_event_callback_function_t callback);

__OSX_AVAILABLE_STARTING(__MAC_10_6,__IPHONE_NA)
DISPATCH_PUBLIC_API DISPATCH_MALLOC DISPATCH_WARN_RESULT DISPATCH_NONNULL1 DISPATCH_NONNULL6
dispatch_source_t
dispatch_source_proc_create_f(dispatch_queue_t q,
	pid_t pid,
	uint64_t flags, 
	void *c_context,
	dispatch_source_attr_t attr,
	dispatch_event_callback_function_t callback);

__OSX_AVAILABLE_STARTING(__MAC_10_6,__IPHONE_NA)
DISPATCH_PUBLIC_API DISPATCH_MALLOC DISPATCH_WARN_RESULT 
dispatch_source_t
dispatch_source_machport_create_f(dispatch_queue_t q,
	mach_port_t mport,
	uint64_t flags, 
	void *c_context,
	dispatch_source_attr_t attr,
	dispatch_event_callback_function_t callback);

__END_DECLS

#endif
