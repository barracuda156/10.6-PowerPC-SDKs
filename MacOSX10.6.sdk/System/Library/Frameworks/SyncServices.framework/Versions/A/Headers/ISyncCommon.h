/*
 * SyncServices -- ISyncCommon.h
 * Copyright (c) 2004, Apple Computer, Inc.  All rights reserved.
 */

#ifndef H_ISYNCCOMMON
#define H_ISYNCCOMMON

#import <Foundation/Foundation.h>

// TODO - REMOVE THIS WHEN WE DONT WANT TO BUILD ON LEOPARD - Add this so we can use the 10.6 availability macros on an 10.5 system
#if (MAC_OS_X_VERSION_MIN_REQUIRED < 1060)
    #define AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER
@protocol NSKeyedUnarchiverDelegate
@end
@protocol NSMachPortDelegate
@end
@protocol NSPortDelegate
@end
@protocol NSApplicationDelegate
@end
@protocol NSWindowDelegate
@end
@protocol NSToolbarDelegate
@end
#endif

#if defined(__cplusplus)
    #define SYNCSERVICES_EXPORT extern "C"
#else
    #define SYNCSERVICES_EXPORT extern
#endif

#endif // H_ISYNCCOMMON
