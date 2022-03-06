#ifndef _LIBDISPATCH_CORE_F_
#define _LIBDISPATCH_CORE_F_

#include <Availability.h>
#include <sys/cdefs.h>
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

__BEGIN_DECLS

__OSX_AVAILABLE_STARTING(__MAC_10_6,__IPHONE_NA)
DISPATCH_PUBLIC_API DISPATCH_NONNULL1 DISPATCH_NONNULL3
void
dispatch_apply_f(dispatch_queue_t dq, size_t iterations, void *context, void (*work)(void *, size_t));

typedef void (*dispatch_basic_function_t)(void *);

__OSX_AVAILABLE_STARTING(__MAC_10_6,__IPHONE_NA)
DISPATCH_PUBLIC_API DISPATCH_NONNULL1 DISPATCH_NONNULL3
long
dispatch_async_f(dispatch_queue_t dq, void *context, dispatch_basic_function_t work);

__OSX_AVAILABLE_STARTING(__MAC_10_6,__IPHONE_NA)
DISPATCH_PUBLIC_API DISPATCH_NONNULL1 DISPATCH_NONNULL3
void
dispatch_sync_f(dispatch_queue_t dq, void *context, dispatch_basic_function_t work);

__END_DECLS

#endif
