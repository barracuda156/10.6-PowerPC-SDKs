/*
	AirPortAPI.h
	AirPort
	Copyright (c) 2002-2008, Apple Inc.
	All rights reserved.
 
 */

#ifndef _AIRPORTAPI_H_
#define _AIRPORTAPI_H_

#include "AirPortVar.h"
#include <Availability.h>

typedef struct _AirPort * AirPortRef;

/*!
	@enum AirPortErr
	@discussion There are two domains of AirPort error codes. Negative values correspond to the AirPortErr enumeration. Positive error values correspond to standard errno error codes defined in sys/errno.h.
	@constant kAP_NoErr
		Success.
	@constant kAP_ParamErr
		Parameter error.
	@constant kAP_NoMemErr
		Memory allocation failed.
	@constant kAP_UknownErr
		Unexpected error condition encountered for which no error code exists.
	@constant kAP_NotSupportedErr
		Operation not supported.
	@constant kAP_FormatErr
		Invalid protocol element field detected.
	@constant kAP_TimeoutErr
		Authentication/Association timed out.
	@constant kA11UnspecifiedFailureErr
		Access point did not specify a reason for authentication/association failure.
	@constant kAP_UnsupportedCapabilitiesErr
		Access point cannot support all requested capabilities.
	@constant kAP_ReassociationDeniedErr
		Reassociation was denied because the access point was unable to determine that an association exists.
	@constant kAP_AssociationDeniedErr
		Association was denied for an unspecified reason.
	@constant kAP_AuthAlgUnsupportedErr
		Specified authentication algorithm is not supported.
	@constant kAP_InvalidAuthSeqNumErr
		Authentication frame received with an authentication sequence number out of expected sequence.
	@constant kAP_ChallengeFailureErr
		Authentication was rejected because of a challenge failure.
	@constant kAP_AP_FullErr
		Access point is unable to handle another associated station.
	@constant kAP_UnsupportedRateSetErr
		Interface does not support all of the rates in the access point's basic rate set.
	@constant kAP_ShortSlotUnsupportedErr
		Association denied because short slot time option is not supported by requesting station.
	@constant kAP_DSSS_OFDM_UnsupportedErr
		Association denied because DSSS-OFDM is not supported by requesting station.
	@constant kAP_InvalidInfoElementErr
		Invalid information element included in association request.
	@constant kAP_InvalidGroupCipherErr
		Invalid group cipher requested.
	@constant kAP_InvalidPairwiseCipherErr
		Invalid pairwise cipher requested.
	@constant kAP_InvalidAKMP_Err
		Invalid authentication selector requested.
	@constant kAP_UnsupportedRSN_VersionErr
		Invalid WPA/WPA2 version specified.
	@constant kAP_InvalidRSN_CapabilitiesErr
		Invalid RSN capabilities specified in association request.
	@constant kAP_CipherSuiteRejectedErr
		Cipher suite rejected due to network security policy.
	@constant kAP_InvalidPMKErr
		PMK rejected by the access point.
	@constant kAP_SupplicantTimeoutErr
		WPA/WPA2 handshake timed out.
	@constant kAP_RefNotBoundErr
		No interface is associated with the AirPortRef.
	@constant kAP_IPC_Error
		Error communicating with a separate process.
	@constant kAP_OpNotPermitted
		Calling process does not have permission to perform this operation.
*/

enum AirPortErr
{
	kAP_NoErr						= 0,
	kAP_ParamErr					= -1,
	kAP_NoMemErr					= -2,
	kAP_UknownErr					= -3,
	kAP_NotSupportedErr				= -4,
	kAP_FormatErr					= -5,
	kAP_TimeoutErr					= -6,
	kAP_UnspecifiedFailureErr		= -7,
	kAP_UnsupportedCapabilitiesErr	= -8,
	kAP_ReassociationDeniedErr		= -9,
	kAP_AssociationDeniedErr		= -10,
	kAP_AuthAlgUnsupportedErr		= -11,
	kAP_InvalidAuthSeqNumErr		= -12,
	kAP_ChallengeFailureErr			= -13,
	kAP_AP_FullErr					= -14,
	kAP_UnsupportedRateSetErr		= -15,
	kAP_ShortSlotUnsupportedErr		= -16,
	kAP_DSSS_OFDM_UnsupportedErr	= -17,
	kAP_InvalidInfoElementErr		= -18,
	kAP_InvalidGroupCipherErr		= -19,
	kAP_InvalidPairwiseCipherErr	= -20,
	kAP_InvalidAKMP_Err				= -21,
	kAP_UnsupportedRSN_VersionErr	= -22,
	kAP_InvalidRSN_CapabilitiesErr	= -23,
	kAP_CipherSuiteRejectedErr		= -24,
	kAP_InvalidPMKErr				= -25,
	kAP_SupplicantTimeoutErr		= -26,
	kAP_RefNotBoundErr				= -27,
	kAP_IPC_Error					= -28,
	kAP_OpNotPermitted				= -29,
	kAP_Error						= -30,
};
typedef enum AirPortErr AirPortErr;

#pragma mark -
#pragma mark Opening, Binding and Closing an AirPortRef

/*! @group Opening and Closing an AirPortRef */

/*! @function AirPortCreateRef
	@abstract Allocates an AirPortRef.
	@discussion An AirPortRef must be allocated using AirPortCreateRef before it can be used. 
	@param ref Pointer through which newly allocated AirPortRef will be returned.
	@result Returns kAP_NoErr upon success or an appropriate error code. 
	*/ 

AirPortErr AirPortCreateRef( AirPortRef * ref ) __OSX_AVAILABLE_STARTING(__MAC_10_6,__IPHONE_NA);

/*! @function AirPortReleaseRef
	@abstract Releases an AirPortRef.
	@discussion AirPortRefs allocated by AirPortCreateRef must be released by calling AirPortReleaseRef. 
	@param ref AirPortRef to be freed.
	@result Returns kAP_NoErr upon success or an appropriate error code. 
	*/ 

AirPortErr AirPortReleaseRef( AirPortRef ref ) __OSX_AVAILABLE_STARTING(__MAC_10_6,__IPHONE_NA);

/*! @function AirPortCopyInterfaceList
	@abstract Retrieves an array of AirPort BSD interface names.
	@discussion An array containing the BSD interface names of all AirPort interfaces on the system is allocated and returned. 
	@param ref AirPortRef allocated by AirPortCreateRef.
	@param ifList Pointer through which the interface name list will be returned. Array must be released by the caller.
	@result Returns kAP_NoErr upon success or an appropriate error code. 
	*/ 

/*! @group AirPort Interfaces */

AirPortErr AirPortCopyInterfaceList( AirPortRef ref, CFArrayRef * ifList ) __OSX_AVAILABLE_STARTING(__MAC_10_6,__IPHONE_NA);

/*! @function AirPortBindToInterface
	@abstract Associates an AirPortRef with a specific interface.
	@discussion The AirPortRef will be "bound" to the specified interface name. All subsequent commands issued using the AirPortRef will be routed to that interface.
	@param ref AirPortRef allocated by AirPortCreateRef.
	@param ifName Name of interface to which interface should be bound.
	@result Returns kAP_NoErr upon success or an appropriate error code. 
	*/ 

AirPortErr AirPortBindToInterface( AirPortRef ref, CFStringRef ifName ) __OSX_AVAILABLE_STARTING(__MAC_10_6,__IPHONE_NA);

#pragma mark -
#pragma mark AirPort Interface Status

/*! @group AirPort Interface Status */

/*! @function AirPortCopyStatus
	@abstract Allocates and fills in an interface status dictionary.
	@discussion A status dictionary using keys defined in AirPortKeys.h will be allocated and returned.
	@param ref AirPortRef allocated by AirPortCreateRef and bound by AirPortBindToInterface.
	@param statusDictPtr Pointer through which status dictionary is returned. Dictionary must be released by the caller.
	@result Returns kAP_NoErr upon success or an appropriate error code. 
	*/
AirPortErr AirPortCopyStatus( AirPortRef ref, CFDictionaryRef * statusDictPtr ) __OSX_AVAILABLE_STARTING(__MAC_10_6,__IPHONE_NA);

/*! @function AirPortSetPower
	@abstract Powers AirPort interface on or off.
	@discussion Operation may fail if calling process does not have permission to change an AirPort card's power state.
	@param ref AirPortRef allocated by AirPortCreateRef and bound by AirPortBindToInterface.
	@param power If true, requesting card to be powered on, otherwise requesting card to be powered off.
	@result Returns kAP_NoErr upon success or an appropriate error code. 
	*/
AirPortErr AirPortSetPower( AirPortRef ref, Boolean power ) __OSX_AVAILABLE_STARTING(__MAC_10_6,__IPHONE_NA);

/*! @function AirPortGetPower
	@abstract Retrieves interface power state.
	@param ref AirPortRef allocated by AirPortCreateRef and bound by AirPortBindToInterface.
	@param power Pointer through which interface power state is returned. If set to true, AirPort card is powered on, otherwise AirPort card is powered off.
	@result Returns kAP_NoErr upon success or an appropriate error code. 
	*/
AirPortErr AirPortGetPower( AirPortRef ref, Boolean * power ) __OSX_AVAILABLE_STARTING(__MAC_10_6,__IPHONE_NA);

/*! @function AirPortSetChannel
	@abstract Tunes AirPort card to a specific channel.
	@discussion Operation will fail if interface is currently participating in a network.
	@param ref AirPortRef allocated by AirPortCreateRef and bound by AirPortBindToInterface.
	@param channel Channel dictionary containing keys and values defined in AirPortKeys.h. If no channel flags parameter is specified, then it will be assumed that the channel is 20 MHz wide.
	@result Returns kAP_NoErr upon success or an appropriate error code. 
	*/
AirPortErr AirPortSetChannel( AirPortRef ref, CFDictionaryRef channel ) __OSX_AVAILABLE_STARTING(__MAC_10_6,__IPHONE_NA);

#pragma mark -
#pragma mark Scanning for Avaliable Networks

/*! @group Scanning for Avaliable Networks */

/*! @function AirPortCreateScanResults
	@abstract Scans for networks.
	@discussion Scanning for networks can potentially move an AirPort card off of its primary channel for relatively long periods of time. Frequent scans can severly impact performance if done while participating in a network.
	@param ref AirPortRef allocated by AirPortCreateRef and bound by AirPortBindToInterface.
	@param scanArgs Scan argument dictionary containing keys and values defined in AirPortKeys.h. If not specified, then a default set of parameters will be used.
	@param scanResults Pointer through which list of network dictionaries will be returned. Array must be released by the caller.
	@result Returns kAP_NoErr upon success or an appropriate error code. 
	*/
AirPortErr AirPortCreateScanResults( AirPortRef ref, CFDictionaryRef scanArgs, CFArrayRef * scanResults ) __OSX_AVAILABLE_STARTING(__MAC_10_6,__IPHONE_NA); 

#pragma mark -
#pragma mark Assoiciation

/*! @group Assoiciation */

/*! @function AirPortAssociate
	@abstract Associate to a network.
	@discussion This method is used to initiate participation in a network. It can be used to "join" both infrastructure and already existing IBSS networks. Operation may fail is calling process does not have permission to join networks.
	@param ref AirPortRef allocated by AirPortCreateRef and bound by AirPortBindToInterface.
	@param networkRecord A scan result dictionary returned from AirPortCreateScanResults.
	@param argsDict A dictionary of arguments using keys and values from AirPortVar.h.
	@result Returns kAP_NoErr upon success or an appropriate error code. 
	*/
AirPortErr AirPortAssociate( AirPortRef ref, CFDictionaryRef networkRecord, CFDictionaryRef argsDict ) __OSX_AVAILABLE_STARTING(__MAC_10_6,__IPHONE_NA);

/*! @function AirPortDisassociate
	@abstract End participation in a network.
	@discussion This method is used to terminate participation in both infrastructure and IBSS networks. The operation will fail if the calling process does not have permission to disassociate from networks.
	@param ref AirPortRef allocated by AirPortCreateRef and bound by AirPortBindToInterface.
	@result Returns kAP_NoErr upon success or an appropriate error code. 
	*/
AirPortErr AirPortDisassociate( AirPortRef ref ) __OSX_AVAILABLE_STARTING(__MAC_10_6,__IPHONE_NA);

/*! @function AirPortCreateIBSS
	@abstract Creates an IBSS network.
	@discussion This method is used to create an IBSS network. The operation will fail if the calling process does not have permission to create IBSS networks.
	@param ref AirPortRef allocated by AirPortCreateRef and bound by AirPortBindToInterface.
	@param ibssParams Dictionary containing IBSS network keys specified in AirPortKeys.h.
	@result Returns kAP_NoErr upon success or an appropriate error code. 
	*/
AirPortErr AirPortCreateIBSS( AirPortRef ref, CFDictionaryRef ibssParams ) __OSX_AVAILABLE_STARTING(__MAC_10_6,__IPHONE_NA);

#pragma mark -
#pragma mark Event Monitoring

/*! @group Event Monitoring */

/*! @typedef AirPortEventCallback
	@discussion Callback through which AirPort interface events are delivered.
	@param err Error associated with event, or kAP_NoErr if there is no error to report.
	@param ref AirPortRef through which the event was delivered.
	@param event AirPortEvent code.
	@param eventData Data associated with this event.
	@param context pointer passed to AirPortEventMonitorStart
	*/

typedef void (*AirPortEventCallback) ( AirPortErr err, AirPortRef ref, UInt32 event, void * eventData, void * context ) __OSX_AVAILABLE_STARTING(__MAC_10_6,__IPHONE_NA);

/*! @function AirPortEventMonitorStart
	@abstract Starts monitoring interface AirPort events.
	@discussion This funciton is used to initiate interface event monitoring. Events, errors, and data are delivered through the specified callback.
	@param ref AirPortRef allocated by AirPortCreateRef and bound by AirPortBindToInterface.
	@param eventCallback Callback through which event data is delivered.
	@param context Context pointer passed to callback function.
	@param eventsList CFArray of 32 bit AirPortEvent codes.
	*/
AirPortErr AirPortEventMonitorStart( AirPortRef ref, AirPortEventCallback eventCallback, void * context, CFArrayRef eventsList ) __OSX_AVAILABLE_STARTING(__MAC_10_6,__IPHONE_NA);

/*! @function AirPortEventMonitorStop
	@abstract Stops monitoring interface AirPort events.
	@discussion Used to terminate interface event monitoring. Event callbacks will no longer be delivered.
	@param ref AirPortRef allocated by AirPortCreateRef and bound by AirPortBindToInterface.
	*/
AirPortErr AirPortEventMonitorStop( AirPortRef ref ) __OSX_AVAILABLE_STARTING(__MAC_10_6,__IPHONE_NA);

#pragma mark -
#pragma mark AirPort Preferences

/*! @group AirPort Preferences */

/*! @function AirPortCopyPreference
	@abstract copies the value for the indicated preference
	@discussion
	@param ref AirPortRef allocated by AirPortCreateRef and bound by AirPortBindToInterface.
	@param pref string key for the preference to get, see AirPortKeys for possible values
	@param value CFTypeRef value pointer, must be non-null, preference value is copied here 
	*/
AirPortErr AirPortCopyPreference( AirPortRef ref, CFStringRef pref, CFTypeRef * value ) __OSX_AVAILABLE_STARTING(__MAC_10_6,__IPHONE_NA);

/*! @function AirPortSetPreference
	@abstract sets the value for the indicated preference
	@discussion
	@param ref AirPortRef allocated by AirPortCreateRef and bound by AirPortBindToInterface.
	@param pref string key for the preference to be set, see AirPortKeys for possible values
	@param value CFTypeRef with the new value to be set
 */
AirPortErr AirPortSetPreference( AirPortRef ref, CFStringRef pref, CFTypeRef value ) __OSX_AVAILABLE_STARTING(__MAC_10_6,__IPHONE_NA);

#pragma mark -
#pragma mark Unit Conversion

AirPortErr AirPortConvertUnits( UInt32 fromValue, AirPortPowerUnit fromUnits, AirPortPowerUnit toUnits, UInt32 * toValue) __OSX_AVAILABLE_STARTING(__MAC_10_6,__IPHONE_NA);

#endif /* _AIRPORTAPI_H_ */