/*
 *  ServiceManagement.h
 *  Copyright (c) 2008 Apple Inc.  All rights reserved.
 */

#ifndef __SERVICE_MANAGEMENT_H__
#define __SERVICE_MANAGEMENT_H__

#include <ServiceManagement/SMErrors.h>
#include <CoreFoundation/CoreFoundation.h>
#include <Security/Authorization.h>
#include <launch.h>

#define kSMRightAddPrivilegedJob "com.apple.ServiceManagement.privileged.addjob"

extern const CFStringRef kSMDomainRootLaunchd;
extern const CFStringRef kSMDomainUserLaunchd;

// Info.plist Keys
#define SM_INFOKEY_PRIVILEGEDEXECUTABLES		"SMPrivilegedExecutables"
#define SM_INFOKEY_AUTHORIZEDCLIENTS			"SMAuthorizedClients"
#define SM_TOOLKEY_PATH							"SMExecutablePath"
#define SM_TOOLKEY_REQUIREMENT					"SMCodeRequirement"

#pragma mark Examining Jobs
/*!
 * @function SMJobCopyDictionary
 * @abstract Copy the job description dictionary for the given job label.
 * @discussion SMJobCopyDictionary returns a copy of the job description
 * dictionary for the given job label, or NULL if no job with the given
 * label was found or an error occurred.
 * @param domain The job's domain (e.g. kSMDomainRootLaunchd).
 * @param jobLabel The label identifier for the job to copy.
 * @param outError An output reference to a CFErrorRef describing the specific
 * error encountered while copying the job description dictionary, or NULL
 * if no error occurred.
 * It is the responsibility of the application to release the error reference.
 * This argument may be NULL.
 * @result A new dictionary describing the job, or NULL if an error occurred.
 * Must be released by the caller.
 */
CFDictionaryRef SMJobCopyDictionary(CFStringRef domain, CFStringRef jobLabel);

/*!
 * @function SMJobCopyAllDictionaries
 * @abstract Copy the job description dictionaries for all jobs in the
 * given domain.
 * @discussion SMJobCopyAllDictionaries returns an array of the job
 * description dictionaries for all jobs in the given domain, or NULL
 * if an error occurred.
 * @param domain The job's domain (e.g. kSMDomainRootLaunchd).
 * @param outError An output reference to a CFErrorRef describing the specific
 * error encountered while copying the job description dictionaries, or NULL
 * if no error occurred.  It is the responsibility of the application to
 * release the error reference.  This argument may be NULL.
 * @result A new array containing all job dictionaries, or NULL if an error
 * occurred.  Must be released by the caller.
 */
CFArrayRef SMCopyAllJobDictionaries(CFStringRef domain);

#pragma mark Adding Jobs Securely
/*!
 * @function SMJobSubmitWithExecutableURL
 * @abstract Submits the executable for the given label as a launchd job.
 * @discussion SMJobSubmitWithExecutableURL submits the executable for the given
 * label as a launchd job.  This function obviates the need for a
 * setuid helper invoked via AuthorizationExecuteWithPrivileges() in order
 * to install a launchd plist.
 *
 * If the job is already installed, success is returned.
 *
 * In order to use this function the following requirements must be met:
 *
 * 1.	The calling application and target executable tool must both be signed.
 * 
 * 2.	The calling application's Info.plist must include a
 *		"SMPrivilegedExecutables" dictionary of strings. Each string is a textual
 *		representation of a code signing requirement used to determine whether
 *		the application owns the privileged tool once installed (i.e. in order
 *		for subsequent versions to update the installed version).
 * 
 *		Each key of SMPrivilegedExecutables is a reverse-DNS label for the helper
 *		tool (must be globally unique).
 *
 * 3.	The helper tool must have an embedded Info.plist containing an "SMAuthorizedClients"
 *		array of strings. Each string is a textual representation of a code signing
 *		requirement describing a client which is allowed to add and remove the tool.
 *
 * 4.	The helper tool must have an embedded launchd plist. The only required key in this
 *		plist is the Label key. When the launchd plist is extracted and written to disk, 
 *		the key for ProgramArguments will be set to an array of 1 element pointing to a 
 *		standard location. You cannot specify your own program arguments, so do not rely
 *		on custom command line arguments being passed to your tool. Pass any parameters via IPC.
 *
 * 5.	The helper tool must reside in the Contents/Library/LaunchServices directory inside the
 *		application bundle, and its name must be its launchd job label. So if your launchd job
 *		label is "com.apple.Mail.helper", this must be the name of the tool in your application
 *		bundle.
 * 
 * @param domain The job's domain. Only kSMDomainRootLaunchd is supported.
 * @param executableLabel the label of the privileged executable to install.
 * This label must be one of the keys found in the SMPrivilegedExecutables
 * dictionary in the application's Info.plist.
 * @param auth An authorization reference containing the
 * kSMRightAddPrivilegedJob if the tool is to be added to the
 * kSMDomainRootLaunchd domain.
 * @param outError An output reference to a CFErrorRef describing the specific
 * error encountered while submitting the executable tool, or NULL if
 * successful.  It is the responsibility of the application to release the
 * error reference.  This argument may be NULL.
 * @result True if the job was successfully submitted, otherwise false.
 */
Boolean SMJobBless(CFStringRef domain, CFStringRef executableLabel, AuthorizationRef auth, CFErrorRef *outError);

#endif /* __SERVICE_MANAGEMENT_H__ */
