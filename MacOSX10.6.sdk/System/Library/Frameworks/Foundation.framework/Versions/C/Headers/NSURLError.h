/*	
    NSURLError.h
    Copyright (C) 2003-2008, Apple Inc. All rights reserved.    
    
    Public header file.
*/

// Note: To use the APIs described in these headers, you must perform
// a runtime check for Foundation-462.1 or later.
#import <AvailabilityMacros.h>
#if MAC_OS_X_VERSION_10_2 <= MAC_OS_X_VERSION_MAX_ALLOWED

// Retrieve kCFURLError* values used in the NSURLError* assignments
#if DEPLOYMENT_TARGET_EMBEDDED || DEPLOYMENT_TARGET_WINDOWS
#import <CFNetwork/CFNetwork.h>
#else
#import <CoreServices/CoreServices.h>
#endif

@class NSString;

/*
    @discussion Constants used by NSError to differentiate between "domains" of error codes, 
    serving as a discriminator for error codes that originate from different subsystems or sources.
    @constant WebFoundationErrorDomain Indicates a WebFoundation error.
*/
extern NSString * const NSURLErrorDomain;

/*!
    @const NSErrorFailingURLStringKey
    @abstract The NSError userInfo dictionary key used to store and retrieve 
    the URL which caused a load to fail.
*/
extern NSString * const NSErrorFailingURLStringKey;


/*!
    @enum NSURL-related Error Codes
    @abstract Constants used by NSError to indicate errors in the WebFoundation domain
    @discussion Documentation on each constant forthcoming.
*/
enum
{
    NSURLErrorUnknown = 			-1,
    NSURLErrorCancelled = 			kCFURLErrorCancelled,
    NSURLErrorBadURL = 				kCFURLErrorBadURL,
    NSURLErrorTimedOut = 			kCFURLErrorTimedOut,
    NSURLErrorUnsupportedURL = 			kCFURLErrorUnsupportedURL,
    NSURLErrorCannotFindHost = 			kCFURLErrorCannotFindHost,
    NSURLErrorCannotConnectToHost = 		kCFURLErrorCannotConnectToHost,
    NSURLErrorNetworkConnectionLost = 		kCFURLErrorNetworkConnectionLost,
    NSURLErrorDNSLookupFailed = 		kCFURLErrorDNSLookupFailed,
    NSURLErrorHTTPTooManyRedirects = 		kCFURLErrorHTTPTooManyRedirects,
    NSURLErrorResourceUnavailable = 		kCFURLErrorResourceUnavailable,
    NSURLErrorNotConnectedToInternet = 		kCFURLErrorNotConnectedToInternet,
    NSURLErrorRedirectToNonExistentLocation = 	kCFURLErrorRedirectToNonExistentLocation,
    NSURLErrorBadServerResponse = 		kCFURLErrorBadServerResponse,
    NSURLErrorUserCancelledAuthentication = 	kCFURLErrorUserCancelledAuthentication,
    NSURLErrorUserAuthenticationRequired = 	kCFURLErrorUserAuthenticationRequired,
    NSURLErrorZeroByteResource = 		kCFURLErrorZeroByteResource,
    NSURLErrorCannotDecodeRawData =             kCFURLErrorCannotDecodeRawData,
    NSURLErrorCannotDecodeContentData =         kCFURLErrorCannotDecodeContentData,
    NSURLErrorCannotParseResponse =             kCFURLErrorCannotParseResponse,
    NSURLErrorFileDoesNotExist = 		kCFURLErrorFileDoesNotExist,
    NSURLErrorFileIsDirectory = 		kCFURLErrorFileIsDirectory,
    NSURLErrorNoPermissionsToReadFile = 	kCFURLErrorNoPermissionsToReadFile,
#if MAC_OS_X_VERSION_10_5 <= MAC_OS_X_VERSION_MAX_ALLOWED
    NSURLErrorDataLengthExceedsMaximum =	kCFURLErrorDataLengthExceedsMaximum,
#endif
    
    // SSL errors
    NSURLErrorSecureConnectionFailed = 		kCFURLErrorSecureConnectionFailed,
    NSURLErrorServerCertificateHasBadDate = 	kCFURLErrorServerCertificateHasBadDate,
    NSURLErrorServerCertificateUntrusted = 	kCFURLErrorServerCertificateUntrusted,
    NSURLErrorServerCertificateHasUnknownRoot = kCFURLErrorServerCertificateHasUnknownRoot,
    NSURLErrorServerCertificateNotYetValid = 	kCFURLErrorServerCertificateNotYetValid,
    NSURLErrorClientCertificateRejected = 	kCFURLErrorClientCertificateRejected,
    NSURLErrorCannotLoadFromNetwork = 		kCFURLErrorCannotLoadFromNetwork,
    
    // Download and file I/O errors
    NSURLErrorCannotCreateFile = 		kCFURLErrorCannotCreateFile,
    NSURLErrorCannotOpenFile = 			kCFURLErrorCannotOpenFile,
    NSURLErrorCannotCloseFile = 		kCFURLErrorCannotCloseFile,
    NSURLErrorCannotWriteToFile = 		kCFURLErrorCannotWriteToFile,
    NSURLErrorCannotRemoveFile = 		kCFURLErrorCannotRemoveFile,
    NSURLErrorCannotMoveFile = 			kCFURLErrorCannotMoveFile,
    NSURLErrorDownloadDecodingFailedMidStream = kCFURLErrorDownloadDecodingFailedMidStream,
    NSURLErrorDownloadDecodingFailedToComplete =kCFURLErrorDownloadDecodingFailedToComplete,
};

#endif
