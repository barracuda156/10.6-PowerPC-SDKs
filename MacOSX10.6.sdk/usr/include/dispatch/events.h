#ifndef _LIBDISPATCH_EVENTS_
#define _LIBDISPATCH_EVENTS_

#ifndef _LIBDISPATCH_PUBLIC_
#error "Please #include <dispatch/dispatch.h> instead of this file directly."
#endif

#include <mach/port.h>
#include <mach/message.h>
#include <sys/signal.h>

/*!
 * @header
 * Libdispatch provides a suite of interfaces for monitoring low-level system
 * objects (Unix descriptors, Mach ports, Unix signals, VFS nodes, etc.) for
 * activity and automatically submits event handler Blocks to dispatch queues
 * when such activity occurs.
 *
 * Dispatch sources hold a reference to their target dispatch queue; therefore
 * all sources targeting a queue must be released before the target queue will
 * be deallocated.
 *
 * Cancelling a dispatch source with dispatch_source_cancel() will also release
 * the source's reference to its target queue after the cancellation event has
 * been delivered.  See dispatch_event_get_error() for a discussion of
 * cancellation events.
 *
 * Event handler Blocks for a dispatch source need not be re-entrant safe as
 * the block will not be submitted until any previous invocation of the block
 * has finished.
 *
 * A typical event handler should begin by checking dispatch_event_get_error()
 * to determine whether any errors occurred during source registration, re-
 * registration, or if the source was canceled by an explicit call to
 * dispatch_source_cancel().  If an error occurs, no further events will be
 * delivered by the source, and the application may wish to release all
 * references.
 *
 * The system holds a reference on a dispatch source for the duration of an
 * event handler Block's execution, allowing patterns like the following:
 *
 *     dispatch_source_t timer;
 *     timer = dispatch_source_timer_create(DISPATCH_TIMER_INTERVAL,
 *         1 * NSEC_PER_SEC, 0, NULL, dispatch_get_main_queue(),
 *         ^(dispatch_event_t event) {
 *             int do_again = 0;
 *             if (dispatch_event_get_error(event, NULL) == 0) {
 *                 do_again = my_periodic_task();
 *             }
 *             if (!do_again) {
 *                 // error occurred or job is done, release the timer
 *                 dispatch_source_release(dispatch_event_get_source(event));
 *             }
 *         });
 *     // timer will release itself when done
 *     timer = NULL;
 *
 * Note on CoreFoundation and Foundation integration:
 *
 * Callouts from a CFRunLoop or NSRunLoop may safely use these interfaces, in
 * which case event handler Blocks will be scheduled with the current run loop
 * in the common modes.
 */

/*!
 * @typedef     dispatch_source_t
 *
 * @abstract
 * Dispatch sources are used to automatically submit event handler Blocks to
 * dispatch queues when external events occur.
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
 * Passed as an argument to dispatch_event_handler_t event handler Blocks. 
 */
typedef struct dispatch_event_s *dispatch_event_t;

/*!
 * @typedef	dispatch_event_handler_t
 *
 * @abstract
 * The prototype of a dispatch source event handler Block.
 *
 * @discussion
 * When a change to the object monitored by a dispatch source occurs, the system
 * will submit the source's event handler Block to the target dispatch queue.
 *
 * @param event
 * A reference to the event that occurred.
 */
typedef void (^dispatch_event_handler_t)(dispatch_event_t event);

/*!
 * @typedef dispatch_source_finalizer_t
 *
 * @abstract
 * The prototype of a dispatch source finalizer Block.
 */
typedef void (^dispatch_source_finalizer_t)(dispatch_source_t source);

/*!
 * @function	dispatch_source_get_machport
 *
 * @abstract
 * Returns the Mach port associated with this dispatch source, or MACH_PORT_NULL
 * if not a Mach port source.
 *
 * @param	source
 * The result of passing NULL in this parameter is undefined.
 */
__OSX_AVAILABLE_STARTING(__MAC_10_6,__IPHONE_NA)
DISPATCH_PUBLIC_API DISPATCH_NONNULL_ALL DISPATCH_WARN_RESULT
mach_port_t
dispatch_source_get_machport(dispatch_source_t source);

/*!
 * @function	dispatch_source_get_descriptor
 *
 * @abstract
 * Returns the Unix descriptor associated with this dispatch source, or -1 if
 * not a Unix descriptor source.
 *
 * @param	source
 * The result of passing NULL in this parameter is undefined.
 */
__OSX_AVAILABLE_STARTING(__MAC_10_6,__IPHONE_NA)
DISPATCH_PUBLIC_API DISPATCH_NONNULL_ALL DISPATCH_WARN_RESULT
int
dispatch_source_get_descriptor(dispatch_source_t source);

/*!
 * @function dispatch_source_get_pid
 * 
 * @abstract
 * Returns the process ID associated with this dispatch source, or -1 if not a
 * process source.
 *
 * @param	source
 * The result of passing NULL in this parameter is undefined.
 */
__OSX_AVAILABLE_STARTING(__MAC_10_6,__IPHONE_NA)
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
 * Flags are interpreted differently based on the source type, and may be the
 * values found in:
 * - dispatch_source_timer_flags_t
 * - dispatch_source_proc_flags_t
 * - dispatch_source_vnode_flags_t
 * - dispatch_source_machport_flags_t
 * - sigset_t
 * 
 * @param	source
 * The result of passing NULL in this parameter is undefined.
 */
__OSX_AVAILABLE_STARTING(__MAC_10_6,__IPHONE_NA)
DISPATCH_PUBLIC_API DISPATCH_NONNULL_ALL DISPATCH_WARN_RESULT
uint64_t
dispatch_source_get_flags(dispatch_source_t source);

/*!
 * @function dispatch_source_get_context
 *
 * @abstract
 * Returns the application defined context of the source.
 *
 * @param	source
 * The result of passing NULL in this parameter is undefined.
 *
 * @result
 * The context pointer for this source.
 */
__OSX_AVAILABLE_STARTING(__MAC_10_6,__IPHONE_NA)
DISPATCH_PUBLIC_API DISPATCH_NONNULL_ALL DISPATCH_PURE
void *
dispatch_source_get_context(dispatch_source_t source);

/*!
 * @function dispatch_source_set_context
 *
 * @abstract
 * Associates an application defined context with the source.
 *
 * @param	source
 * The result of passing NULL in this parameter is undefined.
 *
 * @param	context
 * The previous context of the source; may be NULL.
 */
__OSX_AVAILABLE_STARTING(__MAC_10_6,__IPHONE_NA)
DISPATCH_PUBLIC_API DISPATCH_NONNULL1
void
dispatch_source_set_context(dispatch_source_t source, void * context);

/*!
 * @function	dispatch_source_cancel
 *
 * @abstract
 * Cancels the delivery of events from the dispatch source.
 *
 * @discussion
 * After cancellation, a single event will be delivered with an error value of
 * ECANCELED in the DISPATCH_ERROR_DOMAIN_POSIX.  No further events will be
 * delivered by this source.
 *
 * @param source
 * The result of passing NULL in this parameter is undefined.
 */
__OSX_AVAILABLE_STARTING(__MAC_10_6,__IPHONE_NA)
DISPATCH_PUBLIC_API DISPATCH_NONNULL_ALL
void
dispatch_source_cancel(dispatch_source_t source);

/*!
 * @function	dispatch_source_suspend
 *
 * @abstract
 * Suspends the submission of event handler Blocks to the target queue.
 *
 * @discussion
 * A suspended source will not submit any event handler Blocks to its target
 * queue.  Suspension of a source will occur after the currently executing
 * event handler Block (if any) finishes.
 *
 * Calls to dispatch_source_suspend() must be balanced with calls
 * to dispatch_source_resume().
 *
 * @param	source
 * The result of passing NULL in this parameter is undefined.
 */
__OSX_AVAILABLE_STARTING(__MAC_10_6,__IPHONE_NA)
DISPATCH_PUBLIC_API DISPATCH_NONNULL_ALL
void
dispatch_source_suspend(dispatch_source_t source);

/*!
 * @function	dispatch_source_resume
 *
 * @abstract
 * Resumes the submission of event handler Blocks to the target queue.
 *
 * @discussion
 * When the dispatch source is resumed, an event handler Block will be delivered
 * which summarizes the activity (if any) that occurred while the source was
 * suspended.  All parties suspending a dispatch source must resume it before
 * any activity will occur.
 *
 * @param	source
 * The result of passing NULL in this parameter is undefined.
 */
__OSX_AVAILABLE_STARTING(__MAC_10_6,__IPHONE_NA)
DISPATCH_PUBLIC_API DISPATCH_NONNULL_ALL
void
dispatch_source_resume(dispatch_source_t source);

/*!
 * @function	dispatch_source_retain
 *
 * @abstract
 * Increases the reference count of a dispatch source.
 *
 * @discussion
 * Calls to dispatch_source_retain() must be balanced with
 * calls to dispatch_source_release().
 *
 * @param queue
 * The source to retain.
 * The result of passing NULL in this parameter is undefined.
 */
__OSX_AVAILABLE_STARTING(__MAC_10_6,__IPHONE_NA)
DISPATCH_PUBLIC_API DISPATCH_NONNULL_ALL
void
dispatch_source_retain(dispatch_source_t ds);

/*!
 * @function	dispatch_source_release
 *
 * @abstract
 * Decreases the reference count of a dispatch source.
 *
 * @discussion
 * A dispatch source will be deallocated once all references
 * to it have been released (i.e. the reference count reaches
 * zero).
 *
 * @param queue
 * The source to release.
 * The result of passing NULL in this parameter is undefined.
 */
__OSX_AVAILABLE_STARTING(__MAC_10_6,__IPHONE_NA)
DISPATCH_PUBLIC_API DISPATCH_NONNULL_ALL
void
dispatch_source_release(dispatch_source_t source);

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
__OSX_AVAILABLE_STARTING(__MAC_10_6,__IPHONE_NA)
DISPATCH_PUBLIC_API DISPATCH_NONNULL_ALL DISPATCH_WARN_RESULT
dispatch_source_t
dispatch_event_get_source(dispatch_event_t event);

/*!
 * @enum dispatch_error_domain_t
 *
 * @abstract
 * Return values for dispatch_event_get_error().
 */
enum {
	DISPATCH_ERROR_DOMAIN_NO_ERROR = 0,
	DISPATCH_ERROR_DOMAIN_POSIX = 1,
	DISPATCH_ERROR_DOMAIN_MACH = 2,
};

/*!
 * @function dispatch_event_get_error
 *
 * @abstract
 * Returns the error associated with the event, or zero if no error occurred.
 *
 * @discussion
 * If the event describes an error condition due to failure to register (or re-
 * register) a dispatch source, this function will return a non-zero error
 * domain and a specific error number via an output parameter.
 *
 * For all dispatch sources, no further events will be delivered after an event
 * with a non-zero error number; the source is effectively canceled.
 *
 * If the source was canceled by an explicit call to dispatch_source_cancel(),
 * an error of ECANCELED in the DISPATCH_ERROR_DOMAIN_POSIX will be returned to
 * give the application notification of the cancellation.
 *
 * @param	event
 * The result of passing NULL in this parameter is undefined.
 *
 * @param	error
 * On output, the specific error value that occurred.  This parameter may be
 * NULL if the application is not interested in the specific error.
 *
 * @result
 * An error domain defined by the enumeration dispatch_error_domain_t is
 * returned, indicating how the error output parameter should be interpreted.
 * If no error is associated with this event, DISPATCH_ERROR_DOMAIN_NO_ERROR
 * (zero) will be returned.
 */
__OSX_AVAILABLE_STARTING(__MAC_10_6,__IPHONE_NA)
DISPATCH_PUBLIC_API DISPATCH_NONNULL1 DISPATCH_WARN_RESULT
long
dispatch_event_get_error(dispatch_event_t event, long* error);

/*!
 * @function dispatch_event_get_nanoseconds
 *
 * @abstract
 * For timer events returns the number of nanoseconds for the timer, or zero for
 * any other event type.
 *
 * @param   event
 * The result of passing NULL in this parameter is undefined.
 *
 * @result
 * The number of nanoseconds for a timer event, otherwise zero.
 */
__OSX_AVAILABLE_STARTING(__MAC_10_6,__IPHONE_NA)
DISPATCH_PUBLIC_API DISPATCH_NONNULL_ALL DISPATCH_WARN_RESULT
uint64_t
dispatch_event_get_nanoseconds(dispatch_event_t event);

/*!
 * @function dispatch_event_get_signals
 *
 * @abstract
 * Returns the sigset that triggered the event.
 *
 * @param   event
 * The result of passing NULL in this parameter is undefined.
 *
 * @result
 * The sigset that triggered the event, the sigset is empty for events from
 * non-signal sources.
 */
__OSX_AVAILABLE_STARTING(__MAC_10_6,__IPHONE_NA)
DISPATCH_PUBLIC_API DISPATCH_NONNULL_ALL DISPATCH_WARN_RESULT
sigset_t
dispatch_event_get_signals(dispatch_event_t event);

/*!
 * @function dispatch_event_get_flags
 *
 * @abstract
 * Returns flags describing the event.
 *
 * @discussion
 * Flags are interpreted differently based on the event type, and may be the
 * values defined in:
 * - dispatch_source_timer_flags_t
 * - dispatch_source_proc_flags_t
 * - dispatch_source_vnode_flags_t
 * - dispatch_source_machport_flags_t
 *
 * @param	event
 * The result of passing NULL in this parameter is undefined.
 *
 * @result
 * The flags describing the event.
 */
__OSX_AVAILABLE_STARTING(__MAC_10_6,__IPHONE_NA)
DISPATCH_PUBLIC_API DISPATCH_NONNULL_ALL DISPATCH_WARN_RESULT
uint64_t
dispatch_event_get_flags(dispatch_event_t event);

/*!
 * @function dispatch_event_get_bytes_available
 *
 * @abstract
 * Returns the estimated number of bytes available on a Unix descriptor.
 *
 * @discussion
 * For Unix descriptor read events, this value is the estimated number of bytes
 * waiting to be read from the Unix descriptor.
 *
 * For Unix descriptor write events, this value is the estimated number of bytes
 * that may be written to the Unix descriptor.
 *
 * For other event types, zero will be returned.
 *
 * @param	event
 * The result of passing NULL in this parameter is undefined.
 *
 * @result
 * The number of bytes available.
 */
__OSX_AVAILABLE_STARTING(__MAC_10_6,__IPHONE_NA)
DISPATCH_PUBLIC_API DISPATCH_NONNULL_ALL DISPATCH_WARN_RESULT
size_t
dispatch_event_get_bytes_available(dispatch_event_t event);

/*!
 * @function	dispatch_source_attr_create
 *
 * @abstract
 * Creates a new dispatch source attribute structure.  These attributes may be
 * provided at creation time to modify the default behavior of the source.
 *
 * @discussion
 * The values present in this structure are copied to newly created sources.
 * The same attribute structure may be provided to multiple calls to
 * dispatch_source_create() but only the values in the structure at the time the
 * call is made will be used.
 *
 * @result
 * The new dispatch source attribute structure, initialized to default values.
 */
__OSX_AVAILABLE_STARTING(__MAC_10_6,__IPHONE_NA)
DISPATCH_PUBLIC_API DISPATCH_MALLOC DISPATCH_WARN_RESULT
dispatch_source_attr_t
dispatch_source_attr_create(void);

/*!
 * @function	dispatch_source_attr_release
 *
 * @abstract
 * Releases a dispatch source attribute structure and frees all memory
 * associated with it.
 *
 * @discussion
 * This operation has no effect on any currently running sources.
 */
__OSX_AVAILABLE_STARTING(__MAC_10_6,__IPHONE_NA)
DISPATCH_PUBLIC_API DISPATCH_NONNULL_ALL
void
dispatch_source_attr_release(dispatch_source_attr_t attr);

/*!
 * @function	dispatch_source_attr_set_finalizer
 *
 * @abstract
 * Set the finalizer Block for a dispatch queue.
 *
 * @discussion
 * A dispatch source's finalizer Block will be submitted to the source's target
 * queue after all references to the source have been released.  The memory
 * used by the dispatch source will be deallocated once the finalizer Block
 * has finished.  This Block may be used by the application to release any
 * resources associated with the source, such as closing the underlying Unix
 * descriptor, destroying the underlying Mach port, etc.
 *
 * The system will perform a Block_copy() on the application's behalf,
 * and a Block_release() after the finalizer Block has finished.
 *
 * @result
 * Returns zero if the finalizer was successfully updated, non-zero otherwise.
 */
__OSX_AVAILABLE_STARTING(__MAC_10_6,__IPHONE_NA)
DISPATCH_PUBLIC_API DISPATCH_NONNULL1
long
dispatch_source_attr_set_finalizer(
	dispatch_source_attr_t attr,
	dispatch_source_finalizer_t finalizer);

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
 * @function	dispatch_source_timer_create
 *
 * @abstract
 * Periodically submits an event handler Block to the target dispatch queue.
 *
 * @discussion
 * A best effort attempt is made to invoke the event handler Block at the
 * specified time; however, actual invocation may occur at a later time.
 *
 * Event handler Blocks for a dispatch source need not be re-entrant safe as
 * the block will not be submitted until any previous invocation of the block
 * has finished.
 *
 * @param	flags
 * See dispatch_source_timer_flags_t for a list of supported flags.
 *
 * @param	nanoseconds
 * The nanosecond interval for the timer.  Interpretation of this value depends
 * on the flags specified.
 *
 * @param	leeway
 * A hint given to the system by the application for the amount of leeway, in
 * nanoseconds, that the system may defer the timer in order to align with other
 * system activity for improved system performance or power consumption.  (For
 * example, an application might perform a periodic task every 5 minutes, with
 * a leeway of up to 30 seconds.)  Note that some latency is to be expected for
 * all timers even when a leeway value of zero is specified.
 *
 * @param	attr
 * Future attribute and policy extensions.  This argument may be NULL.
 *
 * @param	queue
 * The target queue to which the event handler Block should be submitted.
 * The dispatch source will hold a reference to the target queue that is
 * released only after the source is cancelled and delivers its cancellation
 * event, or when the source is deallocated.
 *
 * @param	handler
 * An event handler Block to be submitted to the target queue when the timer
 * fires.
 *
 * The system will perform a Block_copy() on the application's behalf when the
 * source is created, and a Block_release() when the source is deallocated.
 *
 * @result
 * Returns the new source, or NULL if a new source could not be allocated.
 */
__OSX_AVAILABLE_STARTING(__MAC_10_6,__IPHONE_NA)
DISPATCH_PUBLIC_API DISPATCH_MALLOC DISPATCH_WARN_RESULT DISPATCH_NONNULL5 DISPATCH_NONNULL6
dispatch_source_t
dispatch_source_timer_create(
	uint64_t flags,
	uint64_t nanoseconds,
	uint64_t leeway,
	dispatch_source_attr_t attr,
	dispatch_queue_t q,
	dispatch_event_handler_t handler);

/*!
 * @function	dispatch_source_signal_create
 *
 * @abstract
 * Monitors the current process for Unix signals and submits an event handler
 * Block to the target dispatch queue when signals are received.
 *
 * @discussion
 * Unlike traditional Unix signal delivery, this method does not interrupt the
 * current thread of execution, and therefore the event handler Block is not
 * restricted in which interfaces it may use.
 *
 * Any signal generated by the kernel due to either an invalid instruction
 * stream or invalid data access is not supported by this interface.
 *
 * Event handler Blocks for a dispatch source need not be re-entrant safe as
 * the block will not be submitted until any previous invocation of the block
 * has finished.
 *
 * @param	signals
 * The set of Unix signals to monitor, represented as a bit mask.
 *
 * @param	attr
 * Future attribute and policy extensions.  This argument may be NULL.
 *
 * @param	queue
 * The target queue to which the event handler Block should be submitted.
 * The dispatch source will hold a reference to the target queue that is
 * released only after the source is cancelled and delivers its cancellation
 * event, or when the source is deallocated.
 *
 * @param	handler
 * An event handler Block to be submitted to the target queue when a Unix signal
 * is received.
 *
 * The system will perform a Block_copy() on the application's behalf when the
 * source is created, and a Block_release() when the source is deallocated.
 *
 * @result
 * Returns the new source, or NULL if a new source could not be allocated.
 */
__OSX_AVAILABLE_STARTING(__MAC_10_6,__IPHONE_NA)
DISPATCH_PUBLIC_API DISPATCH_MALLOC DISPATCH_WARN_RESULT
dispatch_source_t
dispatch_source_signal_create(
	sigset_t signals,
	dispatch_source_attr_t attr,
	dispatch_queue_t q,
	dispatch_event_handler_t handler);

/*!
 * @typedef	dispatch_mig_callback_t
 *
 * @abstract
 * The signature of a function that handles Mach message delivery and response.
 */
typedef boolean_t (*dispatch_mig_callback_t)(mach_msg_header_t *message, mach_msg_header_t *reply);

/*!
 * @function	dispatch_source_mig_create
 *
 * @abstract
 * Monitors a Mach port for messages and submits an event handler Block to the
 * target dispatch queue when messages are received.
 *
 * @discussion
 * This dispatch source is designed for use in combination with MIG
 * (Mach Interface Generator).
 *
 * The semantics of using the MIG dispatch source are identical
 * to the use of mach_msg_server(), specifically:
 *
 * 1) The system will not send the reply message if the "return code" of the
 * reply message is MIG_NO_REPLY.
 *
 * 2) If the return value of the callback is false OR the "return code" within
 * the reply message is both non-zero and not MIG_NO_REPLY, then the system will
 * deallocate the out-of-line data and out-of-line ports supplied in the
 * incoming message before sending the reply message. 
 *
 * The result of monitoring the same Mach port from multiple dispatch sources is
 * undefined.
 *
 * Event handler Blocks for a dispatch source need not be re-entrant safe as
 * the block will not be submitted until any previous invocation of the block
 * has finished.
 *
 * @param	mport
 * The Mach port (receive right) to monitor.
 *
 * @param	max_reply_size
 * The maximum size of a reply message used by this port (not including Mach
 * message trailers).
 *
 * @param	attr
 * Future attribute and policy extensions.  This argument may be NULL.
 *
 * @param	queue
 * The target queue to which the event handler Block should be submitted.
 * The dispatch source will hold a reference to the target queue that is
 * released only after the source is cancelled and delivers its cancellation
 * event, or when the source is deallocated.
 *
 * @param	mig_callback
 * A callback function to be called when a message is delivered to the Mach 
 * port.  This callback function is called from within a system-provided event
 * handler Block submitted to the target queue.
 *
 * @result
 * Returns the new source, or NULL if a new source could not be allocated.
 */
__OSX_AVAILABLE_STARTING(__MAC_10_6,__IPHONE_NA)
DISPATCH_PUBLIC_API DISPATCH_MALLOC DISPATCH_WARN_RESULT DISPATCH_NONNULL4 DISPATCH_NONNULL5
dispatch_source_t
dispatch_source_mig_create(
	mach_port_t mport, 
	size_t max_reply_size,
	dispatch_source_attr_t attr,
	dispatch_queue_t queue,
	dispatch_mig_callback_t mig_callback);

/*!
 * @function	dispatch_source_read_create
 *
 * @abstract
 * Monitors a Unix descriptor (i.e. file descriptor or socket) and submits an
 * event handler Block to the target dispatch queue when more data may be read
 * from the Unix descriptor.
 *
 * @discussion
 *
 * Event handler Blocks for a dispatch source need not be re-entrant safe as
 * the block will not be submitted until any previous invocation of the block
 * has finished.
 *
 * @param	descriptor
 * The Unix descriptor (i.e. file descriptor or socket) to monitor.
 *
 * @param	attr
 * Future attribute and policy extensions.  This argument may be NULL.
 *
 * @param	queue
 * The target queue to which the event handler Block should be submitted.
 * The dispatch source will hold a reference to the target queue that is
 * released only after the source is cancelled and delivers its cancellation
 * event, or when the source is deallocated.
 *
 * @param	handler
 * An event handler Block to be submitted to the target queue when more data
 * may be read from the Unix descriptor.
 *
 * The system will perform a Block_copy() on the application's behalf when the
 * source is created, and a Block_release() when the source is deallocated.
 *
 * @result
 * Returns the new source, or NULL if a new source could not be allocated.
 */
__OSX_AVAILABLE_STARTING(__MAC_10_6,__IPHONE_NA)
DISPATCH_PUBLIC_API DISPATCH_MALLOC DISPATCH_WARN_RESULT DISPATCH_NONNULL3 DISPATCH_NONNULL4
dispatch_source_t
dispatch_source_read_create(
	int descriptor,
	dispatch_source_attr_t attr,
	dispatch_queue_t q,
	dispatch_event_handler_t handler);

/*!
 * @function	dispatch_source_write_create
 *
 * @abstract
 * Monitors a Unix descriptor (i.e. file descriptor or socket) and submits an
 * event handler Block to the target dispatch queue when more data may be
 * written to the Unix descriptor.
 *
 * @discussion
 *
 * Event handler Blocks for a dispatch source need not be re-entrant safe as
 * the block will not be submitted until any previous invocation of the block
 * has finished.
 *
 * @param	descriptor
 * The Unix descriptor (i.e. file descriptor or socket) to monitor.
 *
 * @param	attr
 * Future attribute and policy extensions.  This argument may be NULL.
 *
 * @param	queue
 * The target queue to which the event handler Block should be submitted.
 * The dispatch source will hold a reference to the target queue that is
 * released only after the source is cancelled and delivers its cancellation
 * event, or when the source is deallocated.
 *
 * @param	handler
 * An event handler Block to be submitted to the target queue when more data
 * may be written to the Unix descriptor.
 *
 * The system will perform a Block_copy() on the application's behalf when the
 * source is created, and a Block_release() when the source is deallocated.
 *
 * @result
 * Returns the new source, or NULL if a new source could not be allocated.
 */
__OSX_AVAILABLE_STARTING(__MAC_10_6,__IPHONE_NA)
DISPATCH_PUBLIC_API DISPATCH_MALLOC DISPATCH_WARN_RESULT DISPATCH_NONNULL3 DISPATCH_NONNULL4
dispatch_source_t
dispatch_source_write_create(
	int descriptor, 
	dispatch_source_attr_t attr,
	dispatch_queue_t q,
	dispatch_event_handler_t handler);

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
 * @function	dispatch_source_vnode_create
 *
 * @abstract
 * Monitors a VFS node (filesystem object) and submits an event handler Block
 * to the target dispatch queue when the VFS node's state changes.
 *
 * @discussion
 * The VFS node dispatch source monitors a Unix descriptor reference to a VFS
 * node (filesystem object) for state changes, and submits an event handler
 * Block to the target dispatch queue when changes occur.
 *
 * The result of monitoring Unix descriptors not associated with VFS nodes
 * (i.e. sockets, pipes, and fifos) is undefined.
 *
 * Event handler Blocks for a dispatch source need not be re-entrant safe as
 * the block will not be submitted until any previous invocation of the block
 * has finished.
 *
 * @param	descriptor
 * The Unix descriptor (file descriptor) of the VFS node to monitor.
 *
 * @param	flags
 * See dispatch_source_vnode_flags_t for a list of events to monitor.
 *
 * @param	attr
 * Future attribute and policy extensions.  This argument may be NULL.
 *
 * @param	queue
 * The target queue to which the event handler Block should be submitted.
 * The dispatch source will hold a reference to the target queue that is
 * released only after the source is cancelled and delivers its cancellation
 * event, or when the source is deallocated.
 *
 * @param	handler
 * An event handler Block to be submitted to the target queue when the VFS
 * node's state changes.
 *
 * The system will perform a Block_copy() on the application's behalf when the
 * source is created, and a Block_release() when the source is deallocated.
 *
 * @result
 * Returns the new source, or NULL if a new source could not be allocated.
 */
__OSX_AVAILABLE_STARTING(__MAC_10_6,__IPHONE_NA)
DISPATCH_PUBLIC_API DISPATCH_MALLOC DISPATCH_WARN_RESULT DISPATCH_NONNULL4 DISPATCH_NONNULL5
dispatch_source_t
dispatch_source_vnode_create(
	int descriptor,
	uint64_t flags,
	dispatch_source_attr_t attr,
	dispatch_queue_t q,
	dispatch_event_handler_t handler);

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
 * @function	dispatch_source_proc_create
 *
 * @abstract
 * Monitors a Unix process and submits an event handler Block to the target
 * dispatch queue when the process's state changes.
 *
 * @discussion
 *
 * Event handler Blocks for a dispatch source need not be re-entrant safe as
 * the block will not be submitted until any previous invocation of the block
 * has finished.
 *
 * @param	pid
 * The Unix process ID to monitor.
 *
 * @param	flags
 * See dispatch_source_proc_flags_t for a list of process events to monitor.
 *
 * @param	attr
 * Future attribute and policy extensions.  This argument may be NULL.
 *
 * @param	queue
 * The target queue to which the event handler Block should be submitted.
 * The dispatch source will hold a reference to the target queue that is
 * released only after the source is cancelled and delivers its cancellation
 * event, or when the source is deallocated.
 *
 * @param	handler
 * An event handler Block to be submitted to the target queue when the process's
 * state changes.
 *
 * The system will perform a Block_copy() on the application's behalf when the
 * source is created, and a Block_release() when the source is deallocated.
 *
 * @result
 * Returns the new source, or NULL if a new source could not be allocated.
 */
__OSX_AVAILABLE_STARTING(__MAC_10_6,__IPHONE_NA)
DISPATCH_PUBLIC_API DISPATCH_MALLOC DISPATCH_WARN_RESULT DISPATCH_NONNULL4 DISPATCH_NONNULL5
dispatch_source_t
dispatch_source_proc_create(
	pid_t pid,
	uint64_t flags,
	dispatch_source_attr_t attr,
	dispatch_queue_t q,
	dispatch_event_handler_t handler);


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
 * @function	dispatch_source_machport_create
 *
 * @abstract
 * Monitors a Mach port and submits an event handler Block to the target
 * dispatch queue when the Mach port's state changes.
 *
 * @discussion
 *
 * Event handler Blocks for a dispatch source need not be re-entrant safe as
 * the block will not be submitted until any previous invocation of the block
 * has finished.
 *
 * @param	mport
 * The Mach port to monitor.
 *
 * @param	flags
 * See dispatch_machport_flags_t for a list of events to monitor.
 *
 * @param	attr
 * Future attribute and policy extensions.  This argument may be NULL.
 *
 * @param	queue
 * The target queue to which the event handler Block should be submitted.
 * The dispatch source will hold a reference to the target queue that is
 * released only after the source is cancelled and delivers its cancellation
 * event, or when the source is deallocated.
 *
 * @param	handler
 * An event handler Block to be submitted to the target queue when the mach
 * port's state changes.
 *
 * The system will perform a Block_copy() on the application's behalf when the
 * source is created, and a Block_release() when the source is deallocated.
 *
 * @result
 * Returns the new source, or NULL if a new source could not be allocated.
 */
__OSX_AVAILABLE_STARTING(__MAC_10_6,__IPHONE_NA)
DISPATCH_PUBLIC_API DISPATCH_MALLOC DISPATCH_WARN_RESULT 
dispatch_source_t
dispatch_source_machport_create(
	mach_port_t mport,
	uint64_t flags, 
	dispatch_source_attr_t attr,
	dispatch_queue_t q,
	dispatch_event_handler_t handler);

#endif
