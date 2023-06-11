#ifndef _LIB_DISPATCH_EVENTS_
#define _LIB_DISPATCH_EVENTS_

#if !defined(__BLOCKS__)
#error "Libdispatch requires Blocks."
#elif defined(__cplusplus)
#error "Libdispatch requires Blocks, and Blocks are not currently supported in C++"
#endif

#include <dispatch.h>
#include <mach/port.h>
#include <mach/message.h>
#include <sys/signal.h>

/*!
 * @header
 *
 * Libdispatch provides a suite of interfaces for monitoring low-level
 * event sources (Unix descriptors, Mach ports, signals, etc.) and
 * submitting event callbacks to dispatch queues when activity occurs.
 *
 * Event callbacks are delivered to the current dispatch queue at the
 * time of the source's creation.  It is recommended to use dispatch_call()
 * to submit a work function that performs initialization for a queue
 * (such as the creation of dispatch sources).
 *
 * When a dispatch queue is deleted, all dispatch sources which deliver
 * event callbacks to that queue will be scheduled for deletion as well.
 *
 * Note on CoreFoundation and Foundation integration:
 *
 * CF/NSRunLoop callbacks may safely use these interfaces.
 * Callback functions will be invoked as if they were registered directly
 * with the CFRunLoop or NSRunLoop in the common modes.
 */

/*!
 * @typedef     dispatch_source_t
 *
 * @abstract
 * Dispatch sources are used to track external sources of events,
 * and invoke event callbacks on dispatch queues.  The current
 * dispatch queue at the time the source is created will receive
 * the event callbacks.
 *
 * Deleting a dispatch queue will implicitly schedule the
 * deletion of all dispatch sources associated with the queue.
 */
typedef struct dispatch_source_s *dispatch_source_t;

/*!
 * @typedef dispatch_source_attr_t
 *
 * @abstract
 * Extended attributes for dispatch sources.  Unused for now.
 */

typedef struct dispatch_source_attr_s *dispatch_source_attr_t;

/*!
 * @typedef		dispatch_event_t
 *
 * @abstract
 * Structure containing event data from a dispatch event source.
 * Passed as an argument to dispatch_event_callback_t callbacks. 
 */
typedef struct dispatch_event_s *dispatch_event_t;

/*!
 * @function	dispatch_source_get_machport
 *
 * @abstract
 * Returns the Mach port associated with this dispatch source,
 * or MACH_PORT_NULL if not a Mach port source.
 *
 * @param	source
 * The result of passing NULL in this parameter is undefined.
 */
DISPATCH_PUBLIC_API DISPATCH_NONNULL_ALL DISPATCH_WARN_RESULT
mach_port_t
dispatch_source_get_machport(dispatch_source_t source);

/*!
 * @function	dispatch_source_get_descriptor
 *
 * @abstract
 * Returns the Unix descriptor associated with this dispatch source,
 * or -1 if not a Unix descriptor source.
 *
 * @param	source
 * The result of passing NULL in this parameter is undefined.
 */
DISPATCH_PUBLIC_API DISPATCH_NONNULL_ALL DISPATCH_WARN_RESULT
int
dispatch_source_get_descriptor(dispatch_source_t source);

/*!
 * @function dispatch_source_get_pid
 * 
 * @abstract
 * Returns the process ID associated with this dispatch source,
 * or -1 if not a process source.
 *
 * @param	source
 * The result of passing NULL in this parameter is undefined.
 */
DISPATCH_PUBLIC_API DISPATCH_NONNULL_ALL DISPATCH_WARN_RESULT
pid_t
dispatch_source_get_pid(dispatch_source_t source);

/*!
 * @function dispatch_source_get_flags
 *
 * @abstract
 * Returns the event flags set on the source at creation time.
 *
 * @discussion
 * Flags are interpreted differently based on the source type,
 * and may be the values found in:
 * dispatch_source_timer_flags_t
 * dispatch_source_proc_flags_t
 * dispatch_source_vnode_flags_t
 * dispatch_source_machport_flags_t
 * sigset_t
 * 
 * @param	source
 * The result of passing NULL in this parameter is undefined.
 */
DISPATCH_PUBLIC_API DISPATCH_NONNULL_ALL DISPATCH_WARN_RESULT
uint64_t
dispatch_source_get_flags(dispatch_source_t source);

/*!
 * @function dispatch_source_get_context
 *
 * @abstract
 * Returns the application-defined context associated with
 * this dispatch source.
 *
 * @param	source
 * The result of passing NULL in this parameter is undefined.
 */
DISPATCH_PUBLIC_API DISPATCH_NONNULL_ALL DISPATCH_WARN_RESULT
void*
dispatch_source_get_context(dispatch_source_t source);

/*!
 * @function	dispatch_source_suspend
 *
 * @abstract
 * Disables the invocation of event callbacks from a dispatch
 * source.
 *
 * @discussion
 * A suspension reference count is maintained on the dispatch
 * source, and suspension of event callbacks occurs whenever
 * this reference count is non-zero.
 *
 * If the dispatch source is subsequently resumed, an event
 * callback will be delivered which summarizes the activity
 * that occurred while the source was suspended.
 *
 * @param	source
 * The result of passing NULL in this parameter is undefined.
 *
 * @result
 * Returns the total number of suspensions (after increment).
 */
DISPATCH_PUBLIC_API DISPATCH_NONNULL_ALL
size_t
dispatch_source_suspend(dispatch_source_t source);

/*!
 * @function	dispatch_source_resume
 *
 * @abstract
 * Enables the invocation of event callbacks from a dispatch
 * source.
 *
 * @discussion
 * Reduces the suspension reference count on the dispatch
 * source.  When the reference count reaches zero, event
 * callback delivery is re-enabled.
 * 
 * The result of calling this function on a dispatch source
 * which currently has a suspension reference count of zero
 * is undefined.
 *
 * @param	source
 * The result of passing NULL in this parameter is undefined.
 *
 * @result
 * Returns the total number of suspensions (after decrement).
 */
DISPATCH_PUBLIC_API DISPATCH_NONNULL_ALL
size_t
dispatch_source_resume(dispatch_source_t source);

/*!
 * @function	dispatch_source_get_suspend_count
 *
 * @abstract
 * Returns the current suspension reference count of the
 * dispatch source.
 *
 * @param	source
 * The result of passing NULL in this parameter is undefined.
 *
 * @result
 * Returns the total number of suspensions.
 */
DISPATCH_PUBLIC_API DISPATCH_NONNULL_ALL DISPATCH_PURE DISPATCH_WARN_RESULT
size_t
dispatch_source_get_suspend_count(dispatch_source_t source);

/*!
 * @function	dispatch_source_delete
 *
 * @abstract
 * Schedules a dispatch source for deletion.
 *
 * @discussion
 * Calling this function schedules the dispatch source for deletion.
 * After any oustanding event callbacks return, the deletion callback
 * will be invoked.  The dispatch source will be freed after the
 * deletion callback returns.  At that point any references to the
 * dispatch source will be invalid.
 *
 * If the dispatch queue on which the source is created is deleted,
 * an implicit call to dispatch_source_delete is made.
 *
 * The result of calling this function more than once with the same
 * dispatch source is undefined.
 *
 * @param	source
 * The dispatch source to delete.
 * The result of passing NULL in this parameter is undefined.
 */
DISPATCH_PUBLIC_API DISPATCH_NONNULL_ALL
void
dispatch_source_delete(dispatch_source_t source);

/*!
 * @function dispatch_event_get_source
 *
 * @abstract
 * Returns the dispatch source that generated the event.
 *
 * @param	event
 * The result of passing NULL in this parameter is undefined.
 *
 * @result
 * The dispatch source that generated the event.
 */
DISPATCH_PUBLIC_API DISPATCH_NONNULL_ALL DISPATCH_WARN_RESULT
dispatch_source_t
dispatch_event_get_source(dispatch_event_t event);

/*!
 * @function dispatch_event_get_flags
 *
 * @abstract
 * Returns flags describing the event.
 *
 * @discussion
 * Flags are interpreted differently based on the event type,
 * and may be the values found in:
 * dispatch_source_timer_flags_t
 * dispatch_source_proc_flags_t
 * dispatch_source_vnode_flags_t
 * dispatch_source_machport_flags_t
 * sigset_t
 *
 * @param	event
 * The result of passing NULL in this parameter is undefined.
 *
 * @result
 * The flags describing the event.
 */
DISPATCH_PUBLIC_API DISPATCH_NONNULL_ALL DISPATCH_WARN_RESULT
uint64_t
dispatch_event_get_flags(dispatch_event_t event);

/*!
 * @function dispatch_event_get_bytes_available
 *
 * @abstract
 * Returns the estimated number of bytes available on
 * a Unix descriptor.
 *
 * @discussion
 * For Unix descriptor read events, this value is the
 * estimated number of bytes waiting to be read from
 * the Unix descriptor.
 *
 * For Unix descriptor write events, this value is the
 * estimated number of bytes that may be written to the
 * Unix descriptor.
 *
 * For other event types, zero will be returned.
 *
 * @param	event
 * The result of passing NULL in this parameter is undefined.
 *
 * @result
 * The number of bytes available.
 */
DISPATCH_PUBLIC_API DISPATCH_NONNULL_ALL DISPATCH_WARN_RESULT
size_t
dispatch_event_get_bytes_available(dispatch_event_t event);

/*!
 * @typedef	dispatch_source_deletion_t
 *
 * @abstract
 * The prototype of the dispatch source deletion callback.
 *
 * @discussion
 * Sources may be scheduled for deletion by the application
 * via a call to dispatch_source_delete().  Sources will
 * also be scheduled for deletion when the dispatch queue
 * they deliver events to is scheduled for deletion.
 * Finally, sources may also be scheduled for deletion if
 * libdispatch is unable to successfully register the
 * underlying object to be monitored.
 *
 * By the time this deletion callback has been invoked, no
 * more event callbacks from the source will be delivered.
 * Receipt of this callback is an opportunity for the application
 * to release any resources associated with the source's context.
 * The source itself will be freed when the deletion callback
 * returns, and its reference will subsequently become invalid.
 */
typedef void (^dispatch_source_deletion_t)(dispatch_source_t source);

/*!
 * @typedef	dispatch_event_callback_t
 *
 * @abstract
 * The prototype of the dispatch source event callback.
 *
 * @discussion
 * When a change to the object monitored by a dispatch
 * source occurs, libdispatch will invoke the event callback
 * on the current dispatch queue (at the time the source was
 * created).
 *
 * @param event
 * A reference to the event that occurred.
 */
typedef void (^dispatch_event_callback_t)(dispatch_event_t event);

/*!
 * @function	dispatch_descriptor_close
 *
 * @abstract
 * Provides a simple wrapper that allows the application to close
 * a Mach port and automatically delete any dispatch source that
 * may be associated with the Mach port.
 *
 * @discussion
 * Without using this function, it is necessary for any dispatch
 * sources associated with the Unix descriptor to be scheduled for
 * deletion, and for the source's deletion callback to be delivered,
 * before it is safe to dispose of the Unix descriptor.  Otherwise the
 * Unix descriptor may potentially recycled by the kernel, leading to
 * internal inconsistencies in libdispatch.
 *
 * It is always safe to call dispatch_descriptor_close() instead of
 * close(), even if no dispatch sources are associated with the Unix
 * descriptor.  The underlying call to close() may occur after
 * dispatch_descriptor_close() returns.
 *
 * @param	descriptor
 * The Unix descriptor to close().
 */
DISPATCH_PUBLIC_API
void
dispatch_descriptor_close(int descriptor);

/*!
 * @function	dispatch_machport_close
 *
 * @abstract
 * Provides a simple wrapper that allows the application to close
 * a Mach port and automatically delete any dispatch source that
 * may be associated with the Mach port.
 *
 * @discussion
 * Without using this function, it is necessary for any dispatch
 * sources associated with the Mach port to be scheduled for
 * deletion, and for the source's deletion callback to be delivered,
 * before it is safe to dispose of the Mach port.  Otherwise the
 * Mach port may potentially recycled by the kernel, leading to
 * internal inconsistencies in libdispatch.
 *
 * It is always safe to call dispatch_machport_close() instead of
 * mach_port_mod_ref(), even if no dispatch sources are associated
 * with the Unix descriptor.
 *
 * @param	mport
 * The Mach port to drop the receive right on.
 *
 * @result
 * The return result of mach_port_mod_ref().
 */
DISPATCH_PUBLIC_API
kern_return_t
dispatch_machport_close(mach_port_t mport);

/*!
 * @enum	dispatch_source_timer_flags_t
 *
 * @const	DISPATCH_TIMER_INTERVAL
 * Fires the timer on the specified nanosecond interval.
 *
 * @const	DISPATCH_TIMER_ONESHOT
 * Fire the timer once, on or after the specified
 * number of nanoseconds from now.
 *
 * @const	DISPATCH_TIMER_ABSOLUTE
 * Fire the timer once, on or after the specified
 * number of nanoseconds from January 1, 1970 (GMT).
 * If the specified absolute time has already passed,
 * the timer will fire immediately.
 */
enum {
	DISPATCH_TIMER_INTERVAL	= 0x0,
	DISPATCH_TIMER_ONESHOT	= 0x1,
	DISPATCH_TIMER_ABSOLUTE	= 0x3,
};

/*!
 * @function	dispatch_source_timer_new
 *
 * @abstract
 * Periodically invokes a callback on the current dispatch
 * queue.
 *
 * @discussion
 * A best effort attempt is made to invoke the callback
 * at the specified time; however, actual invocation may
 * occur at a later time.
 * Interval timers are re-scheduled before the callback is invoked.
 *
 * @param	nanoseconds
 * The nanosecond interval for the timer.  Interpretation of
 * this value depends on the flags specified. 
 *
 * @param	flags
 * The flags describing the behavior of the timer
 * (see dispatch_source_timer_flags_t).
 *
 * @param	callback
 * A callback function to be called when a Unix signal is received.
 *
 * Note on Blocks: libdispatch will perform a Block_copy() on
 * the callback function Block, and will perform a Block_release()
 * after the callback function has returned.
 *
 * @param	deletion
 * A deletion function to be called when the source is deleted.
 * This parameter is optional and may be NULL.
 *
 * Note on Blocks: libdispatch will perform a Block_copy() on
 * the deletion function Block, and will perform a Block_release()
 * after the deletion function has returned.
 *
 * @param	context
 * An application defined context to be associated with the source.
 * This parameter is optional and may be NULL.
 *
 * @param	attr
 * Future attribute and policy extensions. Pass NULL for now.
 *
 * @result
 * On success, a new dispatch source is returned, otherwise NULL.
 */
DISPATCH_PUBLIC_API DISPATCH_MALLOC DISPATCH_WARN_RESULT /* DISPATCH_NONNULL3 */
dispatch_source_t
dispatch_source_timer_new(uint64_t nanoseconds,
	uint64_t flags,
	dispatch_event_callback_t callback,
	dispatch_source_deletion_t deletion,
	void* context,
	dispatch_source_attr_t attr);

/*!
 * @function	dispatch_source_signal_new
 *
 * @abstract
 * Monitors the current process for Unix signals and makes
 * callbacks to the current dispatch queue when signals are
 * received.
 *
 * @discussion
 * Unlike traditional Unix signal delivery, this method does not
 * interrupt the current thread of execution, and therefore the
 * callback function is not restricted in which interfaces it may
 * use.
 *
 * Any signal generated by the kernel due to either an invalid
 * instruction stream or invalid data access is not supported by
 * this interface.
 *
 * The result of monitoring the same signals from multiple
 * dispatch sources is undefined.
 *
 * @param	signals
 * The set of Unix signals to monitor, represented as a bit mask.
 *
 * @param	callback
 * A callback function to be called when a Unix signal is received.
 *
 * Note on Blocks: libdispatch will perform a Block_copy() on
 * the callback function Block, and will perform a Block_release()
 * after the callback function has returned.
 *
 * @param	deletion
 * A deletion function to be called when the source is deleted.
 * This parameter is optional and may be NULL.
 *
 * Note on Blocks: libdispatch will perform a Block_copy() on
 * the deletion function Block, and will perform a Block_release()
 * after the deletion function has returned.
 *
 * @param	context
 * An application defined context to be associated with the source.
 * This parameter is optional and may be NULL.
 *
 * @param	attr
 * Future attribute and policy extensions. Pass NULL for now.
 *
 * @result
 * On success, a new dispatch source is returned, otherwise NULL.
 */
DISPATCH_PUBLIC_API DISPATCH_MALLOC DISPATCH_WARN_RESULT /* DISPATCH_NONNULL2 */
dispatch_source_t
dispatch_source_signal_new(sigset_t signals,
	dispatch_event_callback_t callback,
	dispatch_source_deletion_t deletion,
	void* context,
	dispatch_source_attr_t attr);

/*!
 * @typedef	dispatch_mig_callback_t
 *
 * @abstract
 * The signature of a function that handles Mach message delivery and
 * response.
 */
typedef boolean_t (*dispatch_mig_callback_t)(mach_msg_header_t *message, mach_msg_header_t *reply);

/*!
 * @function	dispatch_source_mig_new
 *
 * @abstract
 * Monitors a Mach port for messages and makes callbacks to the
 * current dispatch event queue.
 *
 * @discussion
 * This dispatch source is designed for use in combination with
 * MIG (Mach Interface Generator).
 *
 * The semantics of using the MIG dispatch source are identical
 * to the use of mach_msg_server(), specifically:
 *
 * 1) Libdispatch will not send the reply message if the "return
 * code" of the reply message is MIG_NO_REPLY.
 *
 * 2) If the return value of the callback is false OR the "return
 * code" within the reply message is both non-zero and not
 * MIG_NO_REPLY, then libdispatch will deallocate the out-of-line
 * data and out-of-line ports supplied in the incoming message
 * before sending the reply message. 
 *
 * The result of monitoring the same Mach port from multiple
 * dispatch sources is undefined.
 *
 * @param	mport
 * The Mach port (receive right) to monitor.
 *
 * @param	max_reply_size
 * The maximum size of a reply message used by this port
 * (not including Mach message trailers).
 *
 * @param	mig_callback
 * A callback function to be called when a message is delivered
 * to the Mach port.
 *
 * Note on Blocks: libdispatch will perform a Block_copy() on
 * the callback function Block, and will perform a Block_release()
 * after the callback function has returned.
 *
 * @param	deletion
 * A deletion function to be called when the source is deleted.
 * This parameter is optional and may be NULL.
 *
 * Note on Blocks: libdispatch will perform a Block_copy() on
 * the deletion function Block, and will perform a Block_release()
 * after the deletion function has returned.
 *
 * @param	context
 * An application defined context to be associated with the source.
 * This parameter is optional and may be NULL.
 *
 * @param	attr
 * Future attribute and policy extensions. Pass NULL for now.
 *
 * @result
 * On success, a new dispatch source is returned, otherwise NULL.
 */
DISPATCH_PUBLIC_API DISPATCH_MALLOC DISPATCH_WARN_RESULT
dispatch_source_t
dispatch_source_mig_new(mach_port_t mport, 
	size_t max_reply_size,
	dispatch_mig_callback_t mig_callback,
	dispatch_source_deletion_t deletion,
	void* context,
	dispatch_source_attr_t attr);

/*!
 * @function	dispatch_source_read_new
 *
 * @abstract
 * Monitors a Unix descriptor (i.e. file descriptor or socket) for
 * changes and makes callbacks to the current dispatch queue when
 * more data may be read from the Unix descriptor.
 *
 * @discussion
 * The result of monitoring the same Unix descriptor from multiple
 * dispatch sources is undefined.
 *
 * @param	descriptor
 * The Unix descriptor (i.e. file descriptor or socket) to monitor.
 *
 * @param	callback
 * A callback function to be called when more data may be read from
 * the Unix descriptor.
 *
 * Note on Blocks: libdispatch will perform a Block_copy() on
 * the callback function Block, and will perform a Block_release()
 * after the callback function has returned.
 *
 * @param	deletion
 * A deletion function to be called when the source is deleted.
 * This parameter is optional and may be NULL.
 *
 * Note on Blocks: libdispatch will perform a Block_copy() on
 * the deletion function Block, and will perform a Block_release()
 * after the deletion function has returned.
 *
 * @param	context
 * An application defined context to be associated with the source.
 * This parameter is optional and may be NULL.
 *
 * @param	attr
 * Future attribute and policy extensions. Pass NULL for now.
 *
 * @result
 * On success, a new dispatch source is returned, otherwise NULL.
 */
DISPATCH_PUBLIC_API DISPATCH_MALLOC DISPATCH_WARN_RESULT /* DISPATCH_NONNULL2 */
dispatch_source_t
dispatch_source_read_new(int descriptor,
	dispatch_event_callback_t callback,
	dispatch_source_deletion_t deletion,
	void* context,
	dispatch_source_attr_t attr);

/*!
 * @function	dispatch_source_write_new
 *
 * @abstract
 * Monitors a Unix descriptor (i.e. file descriptor or socket) for
 * changes and makes callbacks to the current dispatch queue when
 * more data may be written to the Unix descriptor.
 *
 * @discussion
 * The result of monitoring the same Unix descriptor from multiple
 * dispatch sources is undefined.
 *
 * @param	descriptor
 * The Unix descriptor (i.e. file descriptor or socket) to monitor.
 *
 * @param	callback
 * A callback function to be called when more data may be written to
 * the Unix descriptor.
 *
 * Note on Blocks: libdispatch will perform a Block_copy() on
 * the callback function Block, and will perform a Block_release()
 * after the callback function has returned.
 *
 * @param	deletion
 * A deletion function to be called when the source is deleted.
 * This parameter is optional and may be NULL.
 *
 * Note on Blocks: libdispatch will perform a Block_copy() on
 * the deletion function Block, and will perform a Block_release()
 * after the deletion function has returned.
 *
 * @param	context
 * An application defined context to be associated with the source.
 * This parameter is optional and may be NULL.
 *
 * @param	attr
 * Future attribute and policy extensions. Pass NULL for now.
 *
 * @result
 * On success, a new dispatch source is returned, otherwise NULL.
 */
DISPATCH_PUBLIC_API DISPATCH_MALLOC DISPATCH_WARN_RESULT /* DISPATCH_NONNULL2 */
dispatch_source_t
dispatch_source_write_new(int descriptor, 
	dispatch_event_callback_t callback,
	dispatch_source_deletion_t deletion,
	void* context,
	dispatch_source_attr_t attr);

/*!
 * @enum	dispatch_source_vnode_flags_t
 *
 * @const	DISPATCH_VNODE_DELETE
 * The filesystem object was deleted from the namespace.
 *
 * @const	DISPATCH_VNODE_WRITE
 * The filesystem object data changed.
 *
 * @const	DISPATCH_VNODE_EXTEND
 * The filesystem object changed in size.
 *
 * @const	DISPATCH_VNODE_ATTRIB
 * The filesystem object metadata changed.
 *
 * @const	DISPATCH_VNODE_LINK
 * The filesystem object link count changed.
 *
 * @const	DISPATCH_VNODE_RENAME
 * The filesystem object was renamed in the namespace.
 *
 * @const	DISPATCH_VNODE_REVOKE
 * The filesystem object was revoked.
 */
enum {
	DISPATCH_VNODE_DELETE	= 0x1,
	DISPATCH_VNODE_WRITE	= 0x2,
	DISPATCH_VNODE_EXTEND	= 0x4,
	DISPATCH_VNODE_ATTRIB	= 0x8,
	DISPATCH_VNODE_LINK	= 0x10,
	DISPATCH_VNODE_RENAME	= 0x20,
	DISPATCH_VNODE_REVOKE	= 0x40,
};

/*!
 * @function	dispatch_source_vnode_new
 *
 * @abstract
 * Monitors a VFS node (filesystem object) for changes and makes
 * callbacks to the current dispatch queue.
 *
 * @discussion
 * The VFS node dispatch source monitors a Unix descriptor reference
 * to a VFS node (filesystem object) for changes, and makes callbacks
 * to the current dispatch queue.
 *
 * The result of monitoring the same Unix descriptor from multiple
 * VFS node dispatch sources is undefined.
 * The result of monitoring Unix descriptors not associated with
 * VFS nodes (i.e. sockets, pipes, and fifos) is undefined.
 *
 * @param	descriptor
 * The Unix descriptor (file descriptor) of the VFS node to monitor.
 *
 * @param	flags
 * Which events are to be monitored on the VFS node
 * (see dispatch_source_vnode_flags_t).
 *
 * @param	callback
 * A callback function to be called when the VFS node state changes.
 *
 * Note on Blocks: libdispatch will perform a Block_copy() on
 * the callback function Block, and will perform a Block_release()
 * after the callback function has returned.
 *
 * @param	deletion
 * A deletion function to be called when the source is deleted.
 * This parameter is optional and may be NULL.
 *
 * Note on Blocks: libdispatch will perform a Block_copy() on
 * the deletion function Block, and will perform a Block_release()
 * after the deletion function has returned.
 *
 * @param	context
 * An application defined context to be associated with the source.
 * This parameter is optional and may be NULL.
 *
 * @param	attr
 * Future attribute and policy extensions. Pass NULL for now.
 *
 * @result
 * On success, a new dispatch source is returned, otherwise NULL.
 */
DISPATCH_PUBLIC_API DISPATCH_MALLOC DISPATCH_WARN_RESULT /* DISPATCH_NONNULL3 */
dispatch_source_t
dispatch_source_vnode_new(int descriptor,
	uint64_t flags,
	dispatch_event_callback_t callback,
	dispatch_source_deletion_t deletion,
	void* context,
	dispatch_source_attr_t attr);

/*!
 * @enum	dispatch_source_proc_flags_t
 *
 * @const	DISPATCH_PROC_EXIT
 * The process has exited (perhaps cleanly, perhaps not).
 *
 * @const	DISPATCH_PROC_FORK
 * The process has created one or more child processes.
 *
 * @const	DISPATCH_PROC_EXEC
 * The process has become another executable image via
 * exec*() or posix_spawn*().
 *
 * @const	DISPATCH_PROC_REAP
 * The process has been reaped by the parent process via
 * wait*().
 *
 * @const	DISPATCH_PROC_SIGNAL
 * A Unix signal was delivered to the process.
 */
enum {
	DISPATCH_PROC_EXIT	= 0x80000000,
	DISPATCH_PROC_FORK	= 0x40000000,
	DISPATCH_PROC_EXEC	= 0x20000000,
	DISPATCH_PROC_REAP	= 0x10000000,
	DISPATCH_PROC_SIGNAL	= 0x08000000,
};

/*!
 * @function	dispatch_source_proc_new
 *
 * @abstract
 * Monitors a Unix process for changes and makes callbacks to the
 * current dispatch queue.
 *
 * @discussion
 * In order to avoid ambiguity when process IDs recycle,
 * the process dispatch source will be implicitly deleted after
 * the process has been collected by its parent.  As a result,
 * applications should be prepared to receive a deletion
 * callback for the source after the callback for
 * DISPATCH_PROC_REAP has been delivered (if requested).
 *
 * @param	pid
 * The Unix process ID to monitor.
 *
 * @param	flags
 * Which events are to be monitored on the Mach port
 * (see dispatch_source_proc_flags_t).
 *
 * @param	callback
 * A callback function to be called when the process state changes.
 *
 * Note on Blocks: libdispatch will perform a Block_copy() on
 * the callback function Block, and will perform a Block_release()
 * after the callback function has returned.
 *
 * @param	deletion
 * A deletion function to be called when the source is deleted.
 * This parameter is optional and may be NULL.
 *
 * Note on Blocks: libdispatch will perform a Block_copy() on
 * the deletion function Block, and will perform a Block_release()
 * after the deletion function has returned.
 *
 * @param	context
 * An application defined context to be associated with the source.
 * This parameter is optional and may be NULL.
 *
 * @param	attr
 * Future attribute and policy extensions. Pass NULL for now.
 *
 * @result
 * On success, a new dispatch source is returned, otherwise NULL.
 */

DISPATCH_PUBLIC_API DISPATCH_MALLOC DISPATCH_WARN_RESULT /* DISPATCH_NONNULL3 */
dispatch_source_t
dispatch_source_proc_new(pid_t pid,
	uint64_t flags, 
	dispatch_event_callback_t callback,
	dispatch_source_deletion_t deletion,
	void* context,
	dispatch_source_attr_t attr);


/*!
 * @enum	dispatch_machport_flags_t
 *
 * @const	DISPATCH_MACHPORT_READABLE
 * The port has messages enqueued on it.
 *
 * @const	DISPATCH_MACHPORT_DEAD
 * The receive right on the remote end was destroyed.
 *
 * @const	DISPATCH_MACHPORT_DESTROYED
 * The receive right would have been destroyed.
 *
 * @const	DISPATCH_MACHPORT_NOSENDERS
 * The receive right has no outstanding send or send-once rights.
 */
enum {
	DISPATCH_MACHPORT_READABLE	= 0x1,
	DISPATCH_MACHPORT_DEAD		= 0x2,
	DISPATCH_MACHPORT_DESTROYED	= 0x4,
	DISPATCH_MACHPORT_NOSENDERS	= 0x8,
};

/*!
 * @function	dispatch_source_machport_new
 *
 * @abstract
 * Monitors a Mach port for changes and makes callbacks to the
 * current dispatch event queue.
 *
 * @param	mport
 * The Mach port to monitor.
 *
 * @param	flags
 * Which events are to be monitored on the Mach port
 * (see dispatch_machport_flags_t).
 *
 * @param	callback
 * A callback function to be called when the Mach port changes.
 *
 * Note on Blocks: libdispatch will perform a Block_copy() on
 * the callback function Block, and will perform a Block_release()
 * after the callback function has returned.
 *
 * @param	deletion
 * A deletion function to be called when the source is deleted.
 * This parameter is optional and may be NULL.
 *
 * Note on Blocks: libdispatch will perform a Block_copy() on
 * the deletion function Block, and will perform a Block_release()
 * after the deletion function has returned.
 *
 * @param	context
 * An application defined context to be associated with the source.
 * This parameter is optional and may be NULL.
 *
 * @param	attr
 * Future attribute and policy extensions. Pass NULL for now.
 *
 * @result
 * On success, a new dispatch source is returned, otherwise NULL.
 */
DISPATCH_PUBLIC_API DISPATCH_MALLOC DISPATCH_WARN_RESULT 
dispatch_source_t
dispatch_source_machport_new(mach_port_t mport,
	uint64_t flags, 
	dispatch_event_callback_t callback,
	dispatch_source_deletion_t deletion,
	void* context,
	dispatch_source_attr_t attr);

#endif
