#ifndef _LIBDISPATCH_PUBLIC_
#define _LIBDISPATCH_PUBLIC_

#include <sys/cdefs.h>
#include <Availability.h>
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

__BEGIN_DECLS

#if !defined(__BLOCKS__)
#error "Libdispatch requires Blocks"
#endif

#ifdef __GNUC__
#define DISPATCH_PUBLIC_API	__attribute__((__nothrow__,__visibility__("default")))
#define DISPATCH_NONNULL1	__attribute__((__nonnull__(1)))
#define DISPATCH_NONNULL2	__attribute__((__nonnull__(2)))
#define DISPATCH_NONNULL3	__attribute__((__nonnull__(3)))
#define DISPATCH_NONNULL4	__attribute__((__nonnull__(4)))
#define DISPATCH_NONNULL5	__attribute__((__nonnull__(5)))
#define DISPATCH_NONNULL6	__attribute__((__nonnull__(6)))
#define DISPATCH_NONNULL_ALL	__attribute__((__nonnull__))
#define DISPATCH_SENTINEL	__attribute__((__sentinel__))
#define DISPATCH_PURE		__attribute__((__pure__))
#define DISPATCH_WARN_RESULT	__attribute__((__warn_unused_result__))
#define DISPATCH_MALLOC		__attribute__((__malloc__))
#else
/*! @parseOnly */
#define DISPATCH_PUBLIC_API
/*! @parseOnly */
#define DISPATCH_NONNULL1
/*! @parseOnly */
#define DISPATCH_NONNULL2
/*! @parseOnly */
#define DISPATCH_NONNULL3
/*! @parseOnly */
#define DISPATCH_NONNULL4
/*! @parseOnly */
#define DISPATCH_NONNULL5
/*! @parseOnly */
#define DISPATCH_NONNULL6
/*! @parseOnly */
#define DISPATCH_NONNULL_ALL
/*! @parseOnly */
#define DISPATCH_SENTINEL
/*! @parseOnly */
#define DISPATCH_PURE
/*! @parseOnly */
#define DISPATCH_WARN_RESULT
/*! @parseOnly */
#define DISPATCH_MALLOC
#endif

#define LIBDISPATCH_VERSION 20080909

#ifndef _LIBDISPATCH_BUILDING_LIBDISPATCH_
#include <dispatch/core.h>
#include <dispatch/events.h>
#endif /* !_LIBDISPATCH_BUILDING_LIBDISPATCH_ */

__END_DECLS

#endif
