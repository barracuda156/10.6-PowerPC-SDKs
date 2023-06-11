/*	CFURLAccess.h
	Copyright (c) 1998-2007, Apple Inc. All rights reserved.
*/

#if !defined(__COREFOUNDATION_CFURLACCESS__)
#define __COREFOUNDATION_CFURLACCESS__ 1

#include <CoreFoundation/CFBase.h>
#include <CoreFoundation/CFArray.h>
#include <CoreFoundation/CFData.h>
#include <CoreFoundation/CFDictionary.h>
#include <CoreFoundation/CFError.h>
#include <CoreFoundation/CFString.h>
#include <CoreFoundation/CFURL.h>

CF_EXTERN_C_BEGIN



/* The following APIs provide efficient access to resource properties. Properties 
are identified by keys, and values are represented as Core Foundation objects. The 
type of each value is fixed for each property, e.g. the modification date is a CFDateRef, 
the file size is a CFNumberRef.

Values are fetched on-demand, synchronously, from the resource's backing store. They
are cached and reused when fetched again through the same URL instance, until the 
client clears the value. The client has complete control over the cache lifetime.

Some resource property values can be changed, given sufficient access permission to the resource. 
When a resource property value is set, the change is written to backing store synchronously.
*/

/* Assigns the requested resource property value to the typeRefValuePtr output */
/* argument. Returns true if the output value was set. Note that NULL is a valid output value. */
/* The value is fetched synchronously from the resource backing store only if a value is not */
/* already cached. The type of the output value type varies by property (see property key */
/* definitions). Returns false if an error occurs. Optional output error: the error is set to */
/* a valid CFErrorRef when the function returns false. A valid output error must be */
/* released by the caller. */
CF_EXPORT
Boolean CFURLCopyResourcePropertyForKey(CFURLRef url, CFStringRef key, void *propertyValueTypeRefPtr, CFErrorRef *error) AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;


/* Returns any number of resource property values as a dictionary of keyed values. */
/* The requested values are specified as an array of keys to appear in */
/* the result dictionary. Values are fetched synchronously from the resource backing store unless */
/* already cached. The type of each value type varies (see key definitions, below). */
/* Returns an empty dictionary if no values are found. Returns NULL when an error occurs. */
/* Optional output error: the error is set to a valid CFErrorRef when the */
/* function returns NULL. A valid output error must be released by the caller. */
CF_EXPORT
CFDictionaryRef CFURLCopyResourcePropertiesForKeys(CFURLRef url, CFArrayRef keys, CFErrorRef *error) AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;


/* Changes a resource property value. Synchronously writes the value to the resource backing */
/* store. The input value type must be a valid CFTypeRef, of the type required for the specified */
/* key (see key definitions). Returns true upon success, false when an error occurs. */
/* Optional output error: the error is set to a valid CFErrorRef when the function */
/* returns false. A valid output error must be released by the caller. */
/* Note that some values are read-only. Attempting to set a read-only property */
/* results in an error. */
CF_EXPORT
Boolean CFURLSetResourcePropertyForKey(CFURLRef url, CFStringRef key, CFTypeRef propertValue, CFErrorRef *error) AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;


/* Changes any number of resource property values, specified as a dictionary of keyed values. */
/* Synchronously writes values to the resource backing store. The input dictionary's value types must conform */
/* to the type required for its key (see key definitions). Returns true when all values are set successfully, */
/* and false if an error occurs. Optional output error: the error is set to a valid CFErrorRef when the function returns */
/* false. A valid output error must be released by the caller. When an error occurs after some properties have been */
/* successfully changed, the user dictionary in the error contains an array of keys that */
/* were not set. Note that some values are read-only. Attempting to set a read-only value */
/* results in an error. */
CF_EXPORT
Boolean CFURLSetResourcePropertiesForKeys(CFURLRef url, CFDictionaryRef keyedPropertyValues, CFErrorRef *error) AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;


/* Discards a cached property value for a specific key */
CF_EXPORT
void CFURLClearResourcePropertyCacheForKey(CFURLRef url, CFStringRef key) AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;


/* Discards all cached property values */
CF_EXPORT
void CFURLClearResourcePropertyCache(CFURLRef url) AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;


/* Sets a temporary property value. Temporary properties exist only in memory and are never */
/* written to resource backing store. Once set, a temporary property value can be fetched */
/* with CFURLCopyResourcePropertyForKey and CFURLCopyResourcePropertiesForKeys. Temporary property */
/* values are for client use. Values must be valid Core Foundation types, and will be retained. */
/* To remove a temporary property value, use CFURLClearResourcePropertyCacheForKey. */
CF_EXPORT
void CFURLSetTemporaryResourcePropertyForKey(CFURLRef url, CFStringRef key, CFTypeRef propertyValue) AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;


/* Synchronously checks if the resource's backing store is reachable and the resource exists, */
/* returning true if so. The optional output error can be used to determine the type of reachability */
/* failure (e.g., file not found, network error, etc.). The error is set to a valid CFErrorRef if */
/* and only if the function returns false. A valid output error must be released by */
/* the caller. Checking for resource existence and reachability is appropriate when making decisions */
/* that do not require other immediate operations on the resource. An example would be */
/* periodic maintenance of UI state that depends on the existence of a particular document. */
/* When performing an operation such as opening a file, it is more efficient to */
/* simply try the operation and handle failures than to check first for reachability. */
CF_EXPORT
Boolean CFURLResourceIsReachable(CFURLRef url, CFErrorRef *error) AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;


/* Properties of File System Resources */

CF_EXPORT 
const CFStringRef kCFURLNameKey AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;
    /* The resource name provided by the file system (value type CFString) */

CF_EXPORT
const CFStringRef kCFURLLocalizedNameKey AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;
    /* Localized or extension-hidden name as displayed to users (Read-only, value type CFString) */

CF_EXPORT
const CFStringRef kCFURLIsRegularFileKey AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;
    /* True for regular files (Read-only, value type CFBoolean) */

CF_EXPORT
const CFStringRef kCFURLIsDirectoryKey AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;
    /* True for directories (Read-only, CFBoolean) */

CF_EXPORT
const CFStringRef kCFURLIsSymbolicLinkKey AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;
    /* True for symlinks (Read-only, value type CFBoolean) */

CF_EXPORT
const CFStringRef kCFURLIsVolumeKey AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;
    /* True for the root directory of a volume (Read-only, value type CFBoolean) */

CF_EXPORT
const CFStringRef kCFURLIsPackageKey AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;
    /* True for packaged directories (value type CFBoolean) */

CF_EXPORT
const CFStringRef kCFURLIsSystemImmutableKey AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;
    /* True for system-immutable resources (value type CFBoolean) */

CF_EXPORT
const CFStringRef kCFURLIsUserImmutableKey AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;
    /* True for user-immutable resources (value type CFBoolean) */

CF_EXPORT
const CFStringRef kCFURLIsHiddenKey AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;
    /* True for resources normally hidden from users (value type CFBoolean) */

CF_EXPORT
const CFStringRef kCFURLHasHiddenExtensionKey AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;
    /* True for resources whose filename extension is hiden (value type CFBoolean) */

CF_EXPORT
const CFStringRef kCFURLCreationDateKey AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;
    /* Value type CFDate */

CF_EXPORT
const CFStringRef kCFURLContentAccessDateKey AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;
    /* Value type CFDate */

CF_EXPORT
const CFStringRef kCFURLContentModificationDateKey AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;
    /* Value type CFDate */

CF_EXPORT
const CFStringRef kCFURLAttributeModificationDateKey AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;
    /* Value type CFDate */

CF_EXPORT
const CFStringRef kCFURLLinkCountKey AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;
    /* Number of hard links to the resource (Read-only, CFNumber) */

CF_EXPORT
const CFStringRef kCFURLParentDirectoryURLKey AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;
    /* URL of the parent directory, if any (Read-only, value type CFURL) */

CF_EXPORT
const CFStringRef kCFURLVolumeURLKey AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;
    /* URL of the volume on which the resource is stored (Read-only, value type CFURL) */

CF_EXPORT
const CFStringRef kCFURLTypeIdentifierKey AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;
    /* Uniform type identifier for the resource (Read-only, value type CFString) */

CF_EXPORT
const CFStringRef kCFURLLocalizedTypeDescriptionKey AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;
    /* User-visible type or "kind" descriptiopn (Read-only, value type CFString) */

CF_EXPORT
const CFStringRef kCFURLLabelNumberKey AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;
    /* The label number assigned to the resource (value type CFNumber) */

CF_EXPORT
const CFStringRef kCFURLLabelColorKey AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;
    /* The color of the assigned label (Read-only, value type CGColorRef, must link with Application Services) */

CF_EXPORT
const CFStringRef kCFURLLocalizedLabelKey AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;
    /* The user-visible label text (Read-only, value type CFString) */

CF_EXPORT
const CFStringRef kCFURLEffectiveIconKey AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;
    /* The icon normally displayed for the resource (Read-only, value type CGImageRef, must link with Application Services) */

CF_EXPORT
const CFStringRef kCFURLCustomIconKey AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;
    /* The custom icon assigned to the resource, if any (value type CGImageRef, must link with Application Services) */


/* File Properties */

CF_EXPORT
const CFStringRef kCFURLFileSizeKey AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;
    /* Total file size, in bytes (Read-only, value type CFNumber) */

CF_EXPORT
const CFStringRef kCFURLFileAllocatedSizeKey AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;
    /* Total size of blocks allocated (Read-only, value type CFNumber) */


/* Volume Properties */

/* For convenience, volume properties may be requested from any resource on a volume. */

CF_EXPORT
const CFStringRef kCFURLVolumeLocalizedFormatDescriptionKey AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;
    /* The user-visible volume format (Read-only, value type CFString) */

CF_EXPORT
const CFStringRef kCFURLVolumeTotalCapacityKey AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;
    /* Total volume capacity in bytes (Read-only, value type CFNumber) */

CF_EXPORT
const CFStringRef kCFURLVolumeAvailableCapacityKey AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;
    /* Total free space, in bytes (Read-only, value type CFNumber) */

CF_EXPORT
const CFStringRef kCFURLVolumeResourceCountKey AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;
    /* Total number of resources on the volume (Read-only, value type CFNumber) */

CF_EXPORT
const CFStringRef kCFURLVolumeSupportsPersistentIDsKey AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;
    /* Read-only, value type CFBoolean */

CF_EXPORT
const CFStringRef kCFURLVolumeSupportsSymbolicLinksKey AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;
    /* Read-only, value type CFBoolean */

CF_EXPORT
const CFStringRef kCFURLVolumeSupportsHardLinksKey AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;
    /* Read-only, value type CFBoolean */

CF_EXPORT
const CFStringRef kCFURLVolumeSupportsJournalingKey AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;
    /* Read-only, value type CFBoolean */

CF_EXPORT
const CFStringRef kCFURLVolumeIsJournalingKey AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;
    /* Read-only, value type CFBoolean */

CF_EXPORT
const CFStringRef kCFURLVolumeSupportsSparseFilesKey AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;
    /* Read-only, value type CFBoolean */

CF_EXPORT
const CFStringRef kCFURLVolumeSupportsZeroRunsKey AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;
    /* Read-only, value type CFBoolean */

CF_EXPORT
const CFStringRef kCFURLVolumeSupportsCaseSensitiveNamesKey AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;
    /* Read-only, value type CFBoolean */

CF_EXPORT
const CFStringRef kCFURLVolumeSupportsCasePreservedNamesKey AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;
    /* Read-only, value type CFBoolean */



/* Attempts to read the data and properties for the given URL.  If
only interested in one of the resourceData and properties, pass NULL
for the other.  If properties is non-NULL and desiredProperties is
NULL, then all properties are fetched.  Returns success or failure;
note that as much work as possible is done even if false is returned.
So for instance if one property is not available, the others are
fetched anyway. errorCode is set to 0 on success, and some other
value on failure.  If non-NULL, it is the caller 's responsibility
to release resourceData and properties.

    Apple reserves for its use all negative error code values; these
values represent errors common to any scheme.  Scheme-specific error
codes should be positive, non-zero, and should be used only if one of
the predefined Apple error codes does not apply.  Error codes should
be publicized and documented with the scheme-specific properties.

NOTE: When asking for the resource data, this call will allocate the entire
resource in memory. This can be very expensive, depending on the size of the
resource (file). Please use CFStream or other techniques if you are downloading
large files.

*/
CF_EXPORT
Boolean CFURLCreateDataAndPropertiesFromResource(CFAllocatorRef alloc, CFURLRef url, CFDataRef *resourceData, CFDictionaryRef *properties, CFArrayRef desiredProperties, SInt32 *errorCode) AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/* Attempts to write the given data and properties to the given URL.
If dataToWrite is NULL, only properties are written out (use
CFURLDestroyResource() to delete a resource).  Properties not present
in propertiesToWrite are left unchanged, hence if propertiesToWrite
is NULL or empty, the URL's properties are not changed at all.
Returns success or failure; errorCode is set as for
CFURLCreateDataAndPropertiesFromResource(), above.
*/
CF_EXPORT
Boolean CFURLWriteDataAndPropertiesToResource(CFURLRef url, CFDataRef dataToWrite, CFDictionaryRef propertiesToWrite, SInt32 *errorCode) AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/* Destroys the resource indicated by url. */
/* Returns success or failure; errorCode set as above. */
CF_EXPORT
Boolean CFURLDestroyResource(CFURLRef url, SInt32 *errorCode) AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/* Convenience method which calls through to CFURLCreateDataAndPropertiesFromResource(). */
/* Returns NULL on error and sets errorCode accordingly. */
CF_EXPORT
CFTypeRef CFURLCreatePropertyFromResource(CFAllocatorRef alloc, CFURLRef url, CFStringRef property, SInt32 *errorCode) AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* Common error codes (returned only by the older APIs that predate CFError) */
enum {
    kCFURLUnknownError = -10,
    kCFURLUnknownSchemeError = -11,
    kCFURLResourceNotFoundError = -12,
    kCFURLResourceAccessViolationError = -13,
    kCFURLRemoteHostUnavailableError = -14,
    kCFURLImproperArgumentsError = -15,
    kCFURLUnknownPropertyKeyError = -16,
    kCFURLPropertyKeyUnavailableError = -17,
    kCFURLTimeoutError = -18
};
typedef CFIndex CFURLError;

/* Older property keys */

CF_EXPORT
const CFStringRef kCFURLFileExists AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;
CF_EXPORT
const CFStringRef kCFURLFileDirectoryContents AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;
CF_EXPORT
const CFStringRef kCFURLFileLength AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;
CF_EXPORT 
const CFStringRef kCFURLFileLastModificationTime AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;
CF_EXPORT
const CFStringRef kCFURLFilePOSIXMode AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;
CF_EXPORT
const CFStringRef kCFURLFileOwnerID AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;
CF_EXPORT
const CFStringRef kCFURLHTTPStatusCode AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;
CF_EXPORT
const CFStringRef kCFURLHTTPStatusLine AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/* The value of kCFURLFileExists is a CFBoolean */
/* The value of kCFURLFileDirectoryContents is a CFArray containing CFURLs.  An empty array means the directory exists, but is empty */
/* The value of kCFURLFileLength is a CFNumber giving the file's length in bytes */
/* The value of kCFURLFileLastModificationTime is a CFDate */
/* The value of kCFURLFilePOSIXMode is a CFNumber as given in stat.h */
/* The value of kCFURLFileOwnerID is a CFNumber representing the owner's uid */

/* Properties for the http: scheme.  Except for the common error codes, above, errorCode will be set to the HTTP response status code upon failure.  Any HTTP header name can also be used as a property */
/* The value of kCFURLHTTPStatusCode is a CFNumber */
/* The value of kCFURLHTTPStatusLine is a CFString */

CF_EXTERN_C_END

#endif /* ! __COREFOUNDATION_CFURLACCESS__ */

