/*
 *  SMErrors.h
 *  launchdadd
 *
 *  Created by Damien Sorresso on 5/19/08.
 *  Copyright 2008 Apple Inc. All rights reserved.
 *
 */

#ifndef __SMERRORS_H__
#define __SMERRORS_H__

#include <CoreFoundation/CoreFoundation.h>

// Error domains.
extern const CFStringRef kSMErrorDomainIPC;
extern const CFStringRef kSMErrorDomainFramework;
extern const CFStringRef kSMErrorDomainLaunchd;

/*!
 * @const kSMErrorInternalFailure An internal failure has occurred.
 * @const kSMErrorInvalidSignature The Application's code signature
 *		does not meet the requirements to perform the operation.
 * @const kSMErrorAuthorizationFailure The request required authorization
 *		(i.e. adding a job to the kSMDomainRootLaunchd) but the AuthorizationRef
 *		did not contain the required right.
 * @const kSMErrorToolNotValid The specified path does not exist or the tool at
 *		the specified path is not valid.
 * @const kSMErrorJobNotFound No job with the given label was found.
 */

enum {
	kSMErrorInternalFailure			= 2,
	kSMErrorInvalidSignature,
	kSMErrorAuthorizationFailure,
	kSMErrorToolNotValid,
	kSMErrorJobNotFound
};

CFErrorRef SMErrorCreate(CFAllocatorRef allocator, CFStringRef domain, CFIndex code);

#endif /* __SMERRORS_H__ */
