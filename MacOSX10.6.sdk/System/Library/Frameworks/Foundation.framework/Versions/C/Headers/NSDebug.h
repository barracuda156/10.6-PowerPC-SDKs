/*	NSDebug.h
	Copyright (c) 1994-2007, Apple Inc. All rights reserved.
*/

/**************************************************************************
WARNING: Unsupported API.

This module contains material that is only partially supported -- if
at all.  Do not depend on the existance of any of these symbols in your
code in future releases of this software.  Certainly, do not depend on
the symbols in this header in production code.  The format of any data
produced by the functions in this header may also change at any time.

However, it should be noted that the features (but not necessarily the
exact implementation) in this file have been found to be generally useful,
and in some cases invaluable, and are not likely to go away anytime soon.
**************************************************************************/

#import <Foundation/NSObject.h>
#import <Foundation/NSAutoreleasePool.h>
#import <Foundation/NSDate.h>
#import <Foundation/NSPort.h>

/* The environment component of this API

The boolean- and integer-valued variables declared in this header,
plus some values set by methods, read starting values from the
process's environment at process startup.  This is mostly a benefit
if you need to initialize these variables to some non-default value
before your program's main() routine gets control, but it also
allows you to change the value without modifying your program's
source. (Variables can be set and methods called around specific
areas within a program, too, of course.)

The initialization from the environment happens very early, but may
not have happened yet at the time of a +load method statically linked
into an application (as opposed to one in a dynamically loaded module). 
But as noted in the "Foundation Release Notes", +load methods that are
statically linked into an application are tricky to use and are not
recommended.

Here is a table of the variables/values initialized from the environment
at startup.  Some of these just set variables, others call methods to
set the values.

NAME OF ENV. VARIABLE		       DEFAULT	SET TO...
NSDebugEnabled				  NO	"YES"
NSZombieEnabled				  NO	"YES"
NSDeallocateZombies			  NO	"YES"
NSHangOnUncaughtException		  NO	"YES"

NSEnableAutoreleasePool			 YES	"NO"
NSAutoreleaseFreedObjectCheckEnabled	  NO	"YES"
NSAutoreleaseHighWaterMark		  0	non-negative integer
NSAutoreleaseHighWaterResolution	  0	non-negative integer

*/

/****************	General		****************/

FOUNDATION_EXPORT BOOL NSDebugEnabled;
	// General-purpose global boolean. Applications and frameworks
	// may choose to do some extra checking, or use different
	// algorithms, or log informational messages, or whatever, if
	// this variable is true (ex: if (NSDebugEnabled) { ... }).

FOUNDATION_EXPORT BOOL NSZombieEnabled;
	// Enable object zombies. When an object is deallocated, its isa
	// pointer is modified to be that of a "zombie" class (whether or
	// not the storage is then freed can be controlled by the
	// NSDeallocateZombies variable). Messages sent to the zombie
	// object cause logged messages and can be broken on in a debugger.
	// The default is NO.

FOUNDATION_EXPORT BOOL NSDeallocateZombies;
	// Determines whether the storage of objects that have been
	// "zombified" is then freed or not. The default value (NO)
	// is most suitable for debugging messages sent to zombie
	// objects. And since the memory is never freed, storage
	// allocated to an object will never be reused, either (which
	// is sometimes useful otherwise).

FOUNDATION_EXPORT BOOL NSHangOnUncaughtException;
	// If set to YES, causes the process to hang after logging the
	// "*** Uncaught exception:" message. A backtrace can be gotten
	// from the process with the 'sample' utility, or the process can
	// be attached to with a debugger. The default is NO.

FOUNDATION_EXPORT BOOL NSIsFreedObject(id anObject);
	// Returns YES if the value passed as the parameter is a pointer
	// to a freed object. Note that memory allocation packages will
	// eventually reuse freed memory blocks to satisfy a request.
	// NSZombieEnabled and NSDeallocateZombies can be used to prevent
	// reuse of allocated objects.

/****************	Stack processing	****************/

FOUNDATION_EXPORT void *NSFrameAddress(NSUInteger frame);
FOUNDATION_EXPORT void *NSReturnAddress(NSUInteger frame);
	// Returns the value of the frame pointer or return address,
	// respectively, of the specified frame. Frames are numbered
	// sequentially, with the "current" frame being zero, the
	// previous frame being 1, etc. The current frame is the
	// frame in which either of these functions is called. For
	// example, NSReturnAddress(0) returns an address near where
	// this function was called, NSReturnAddress(1) returns the
	// address to which control will return when current frame
	// exits, etc. If the requested frame does not exist, then
	// NULL is returned. The behavior of these functions is
	// undefined in the presence of code which has been compiled
	// without frame pointers.

FOUNDATION_EXPORT NSUInteger NSCountFrames(void);
	// Returns the number of call frames on the stack. The behavior
	// of this functions is undefined in the presence of code which
	// has been compiled without frame pointers.

/****************	Autorelease pool debugging	****************/

// Functions used as interesting breakpoints in a debugger
// void __NSAutoreleaseNoPool(void *object);
	// Called to log the "Object X of class Y autoreleased with no
	// pool in place - just leaking" message.

// void __NSAutoreleaseFreedObject(void *freedObject);
	// Called when a previously freed object would be released
	// by an autorelease pool.

@interface NSAutoreleasePool (NSAutoreleasePoolDebugging)

+ (void)showPools;
	// Displays to stderr the state of the current thread's
	// autorelease pool stack.

+ (void)enableFreedObjectCheck:(BOOL)enable DEPRECATED_IN_MAC_OS_X_VERSION_10_6_AND_LATER;
	// This behavior is now always on.

+ (void)enableRelease:(BOOL)enable DEPRECATED_IN_MAC_OS_X_VERSION_10_6_AND_LATER;
+ (void)resetTotalAutoreleasedObjects DEPRECATED_IN_MAC_OS_X_VERSION_10_6_AND_LATER;
+ (NSUInteger)totalAutoreleasedObjects DEPRECATED_IN_MAC_OS_X_VERSION_10_6_AND_LATER;
+ (NSUInteger)autoreleasedObjectCount DEPRECATED_IN_MAC_OS_X_VERSION_10_6_AND_LATER;
+ (NSUInteger)topAutoreleasePoolCount DEPRECATED_IN_MAC_OS_X_VERSION_10_6_AND_LATER;
+ (NSUInteger)poolCountHighWaterMark DEPRECATED_IN_MAC_OS_X_VERSION_10_6_AND_LATER;
+ (void)setPoolCountHighWaterMark:(NSUInteger)count DEPRECATED_IN_MAC_OS_X_VERSION_10_6_AND_LATER;
+ (NSUInteger)poolCountHighWaterResolution DEPRECATED_IN_MAC_OS_X_VERSION_10_6_AND_LATER;
+ (void)setPoolCountHighWaterResolution:(NSUInteger)res DEPRECATED_IN_MAC_OS_X_VERSION_10_6_AND_LATER;
	// There is no longer any way to do what these used to do.

/* DTrace static probes for autorelease pool performance analysis and debugging
    provider Cocoa_Autorelease {
       probe pool_push(unsigned long value);		// arg is a token representing pool
       probe pool_pop_start(unsigned long value);	// arg is a token representing pool
       probe pool_pop_end(unsigned long value);		// arg is a token representing pool
       probe autorelease(unsigned long value);		// arg is object pointer
       probe error_no_pool(unsigned long value);	// arg is object pointer
       probe error_freed_object(unsigned long value);	// arg is object pointer
    };
*/

@end

/****************	Allocation statistics	****************/

// The statistics-keeping facilities generate output on various types of
// events. Currently, output logs can be generated for use of the zone
// allocation functions (NSZoneMalloc(), etc.), and allocation and
// deallocation of objects (and other types of lifetime-related events).

// This boolean is obsolete and unused
FOUNDATION_EXPORT BOOL NSKeepAllocationStatistics;

// Object allocation event types
#define NSObjectAutoreleasedEvent		3
#define NSObjectExtraRefIncrementedEvent	4
#define NSObjectExtraRefDecrementedEvent	5
#define NSObjectInternalRefIncrementedEvent	6
#define NSObjectInternalRefDecrementedEvent	7


FOUNDATION_EXPORT void NSRecordAllocationEvent(int eventType, id object);
	// Notes an object or zone allocation event and various other
	// statistics, such as the time and current thread.
	// The behavior is undefined (and likely catastrophic) if
	// the correct arguments for 'eventType' are not provided.
	//
	// The parameter prototypes for each event type are shown below.
	//   NSRecordAllocationEvent(NSObjectAutoreleasedEvent, curObj)
	//   NSRecordAllocationEvent(NSObjectExtraRefIncrementedEvent, curObj)
	//   NSRecordAllocationEvent(NSObjectExtraRefDecrementedEvent, curObj)
	//   NSRecordAllocationEvent(NSObjectInternalRefIncrementedEvent, curObj)
	//   NSRecordAllocationEvent(NSObjectInternalRefDecrementedEvent, curObj)
	//
	// Only the Foundation should have reason to use many of these.
	// The only common use of this function should be with these two events:
	//	NSObjectInternalRefIncrementedEvent
	//	NSObjectInternalRefDecrementedEvent
	// when a class overrides -retain and -release to do its own
	// reference counting.

