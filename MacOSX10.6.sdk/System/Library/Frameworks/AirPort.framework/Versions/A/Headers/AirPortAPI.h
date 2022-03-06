/*
	AirPortAPI.h
	AirPort
	Copyright (c) 2002-2008, Apple Inc.
	All rights reserved.
 
 */

#ifndef _AIRPORTAPI_H_
#define _AIRPORTAPI_H_

#include "AirPortVar.h"

#pragma mark -
#pragma mark Allocating and deallocating an AirPortRef

/*! @group Allocating and deallocating an AirPortRef */

/*! @function AirPortCreateRefWithInterfaceName
	@abstract Allocates an AirPortRef.
	@discussion An AirPortRef is used to communicate with a specific wireless interface. 
	@param ifName The name of an interface included in the list returned from AirPortCopyInterfaceList(). If
				  NULL, the first AirPort interface on the system will be used.
	@param ref Pointer through which the newly allocated AirPortRef will be returned. The AirPortRef must be
			   freed by calling AirPortReleaseRef().
	@result Returns kAP_NoErr upon success or an appropriate error code. 
	*/ 

AirPortErr AirPortCreateRefWithInterfaceName( CFStringRef ifName, AirPortRef * ref ) __OSX_AVAILABLE_STARTING(__MAC_10_6,__IPHONE_NA);

/*! @function AirPortReleaseRef
	@abstract Releases an AirPortRef.
	@discussion AirPortRefs allocated by AirPortCreateRefWithInterfaceName must be released by calling AirPortReleaseRef. 
	@param ref AirPortRef to be freed.
	@result Returns kAP_NoErr upon success or an appropriate error code. 
	*/ 

AirPortErr AirPortReleaseRef( AirPortRef ref ) __OSX_AVAILABLE_STARTING(__MAC_10_6,__IPHONE_NA);

/*! @group AirPort Interfaces */

/*! @function AirPortCopyInterfaceList
	@abstract Retrieves an array of AirPort BSD interface names.
	@discussion An array containing the BSD interface names of all AirPort interfaces on the system is allocated and returned. 
	@param ifList Pointer through which the interface name list will be returned. Array must be released by the caller.
	@result Returns kAP_NoErr upon success or an appropriate error code. 
	*/ 

AirPortErr AirPortCopyInterfaceList( CFArrayRef * ifList ) __OSX_AVAILABLE_STARTING(__MAC_10_6,__IPHONE_NA);

/*! @function AirPortRefCopyInterfaceName
	@abstract Retrieves the BSD interface name associated with the specified AirPortRef.
	@param ref AirPortRef allocated by AirPortCreateRefWithInterfaceName.
	@param ifName Pointer through which the interface name will be returned. The caller is responsible for releasing
				  the CFStringRef.
	@result Returns kAP_NoErr upon success or an appropriate error code. 
	*/
AirPortErr AirPortRefCopyInterfaceName( AirPortRef ref, CFStringRef * ifName ) __OSX_AVAILABLE_STARTING(__MAC_10_6,__IPHONE_NA);

#pragma mark -
#pragma mark AirPort Interface Status

/*! @group AirPort Interface Status */

/*! @function AirPortCopyStaticConnectionParameters
	@abstract Allocates and fills in a dictionary of connection parameters that remain static while participating in a network.
	@discussion A dictionary using keys and values defined in AirPortKeys.h will be allocated and returned. These parameters need to be queried only
				once during the life of a connection.
	@param ref AirPortRef allocated by AirPortCreateRefWithInterfaceName.
	@param staticParamDict Pointer through which static parameter dictionary is returned. Dictionary must be released by the caller.
	@result Returns kAP_NoErr upon success or an appropriate error code. 
	*/
AirPortErr AirPortCopyStaticConnectionParameters( AirPortRef ref, CFDictionaryRef * staticParamDict ) __OSX_AVAILABLE_STARTING(__MAC_10_6,__IPHONE_NA);

/*! @function AirPortCopyDynamicConnectionParameters
	@abstract Allocates and fills in a dictionary of connection parameters that may change while participating in a network.
	@discussion A dictionary using keys and values defined in AirPortKeys.h will be allocated and returned.
	@param ref AirPortRef allocated by AirPortCreateRefWithInterfaceName.
	@param dynamicParamDict Pointer through which dynamic parameter dictionary is returned. Dictionary must be released by the caller.
	@result Returns kAP_NoErr upon success or an appropriate error code. 
	*/
AirPortErr AirPortCopyDynamicConnectionParameters( AirPortRef ref, CFDictionaryRef * dynamicParamDict ) __OSX_AVAILABLE_STARTING(__MAC_10_6,__IPHONE_NA);

/*! @function AirPortSetPower
	@abstract Powers AirPort interface on or off.
	@discussion Operation may fail if calling process does not have permission to change an AirPort card's power state.
	@param ref AirPortRef allocated by AirPortCreateRefWithInterfaceName.
	@param power If true, requesting card to be powered on, otherwise requesting card to be powered off.
	@result Returns kAP_NoErr upon success or an appropriate error code. 
	*/
AirPortErr AirPortSetPower( AirPortRef ref, Boolean power ) __OSX_AVAILABLE_STARTING(__MAC_10_6,__IPHONE_NA);

/*! @function AirPortGetPower
	@abstract Retrieves interface power state.
	@param ref AirPortRef allocated by AirPortCreateRefWithInterfaceName.
	@param power Pointer through which interface power state is returned. If set to true, AirPort card is powered on, otherwise AirPort card is powered off.
	@result Returns kAP_NoErr upon success or an appropriate error code. 
	*/
AirPortErr AirPortGetPower( AirPortRef ref, Boolean * power ) __OSX_AVAILABLE_STARTING(__MAC_10_6,__IPHONE_NA);

/*! @function AirPortCopyRegulatoryInfo
	@abstract Retrieves information about the interface's active regulatory region.
	@discussion An interface's regulatory region is dynamic and may change when a new 802.11d
				country code information element is detected during a scan operation.
	@param ref AirPortRef allocated by AirPortCreateRefWithInterfaceName.
	@param regInfo Upon success, a dictionary containing country code and supported channel
				   information is allocated and returned through this parameter. Supported
				   channels dictionary keys are defined in AirPortKeys.h.
	@result Returns kAP_NoErr upon success or an appropriate error code. 
	*/
AirPortErr AirPortCopyRegulatoryInfo( AirPortRef ref, CFDictionaryRef * regInfo ) __OSX_AVAILABLE_STARTING(__MAC_10_6,__IPHONE_NA);

/*! @function AirPortSetChannel
	@abstract Tunes AirPort card to a specific channel.
	@discussion Operation will fail if interface is currently participating in a network.
	@param ref AirPortRef allocated by AirPortCreateRefWithInterfaceName.
	@param channelDict Channel dictionary containing keys and values defined in AirPortKeys.h. If no channel flags parameter is specified, then it will be assumed that the channel is 20 MHz wide.
	@result Returns kAP_NoErr upon success or an appropriate error code. 
	*/
AirPortErr AirPortSetChannel( AirPortRef ref, CFDictionaryRef channelDict ) __OSX_AVAILABLE_STARTING(__MAC_10_6,__IPHONE_NA);

/*! @function AirPortCopyChannel
	@abstract Retrieves channel to which the AirPort card is currently tuned.
	@param ref AirPortRef allocated by AirPortCreateRefWithInterfaceName.
	@param channelDict Parameter through which information about the channel to which the AirPort card is tuned is returned. Channel dictionary keys and values are defined in AirPortKeys.h. The
					   caller is responsible for releasing the dictionary.
	@result Returns kAP_NoErr upon success or an appropriate error code. 
	*/
AirPortErr AirPortCopyChannel( AirPortRef ref, CFDictionaryRef * channelDict ) __OSX_AVAILABLE_STARTING(__MAC_10_6,__IPHONE_NA);

/*! @function AirPortCopyCapabilities
	@abstract Retrieves a dictionary describing AirPort card capabilities.
	@param ref AirPortRef allocated by AirPortCreateRefWithInterfaceName.
	@param capDict Parameter through which dictionary describing AirPort card capabilities is returned. Capability dictionary keys and values are defined in AirPortKeys.h. If a capability
				   key is missing from the dictionary, it indicates to the caller that the capability is not supported. The caller is responsible for releasing the dictionary.
	@result Returns kAP_NoErr upon success or an appropriate error code. 
	*/
AirPortErr AirPortCopyCapabilities( AirPortRef ref, CFDictionaryRef * capDict ) __OSX_AVAILABLE_STARTING(__MAC_10_6,__IPHONE_NA);

#pragma mark -
#pragma mark Scanning for Avaliable Networks

/*! @group Scanning for Avaliable Networks */

/*! @function AirPortCreateScanResults
	@abstract Scans for networks.
	@discussion Scanning for networks can potentially move an AirPort card off of its primary channel for relatively long periods of time. Frequent scans can severly impact performance if done while participating in a network.
	@param ref AirPortRef allocated by AirPortCreateRefWithInterfaceName.
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
	@param ref AirPortRef allocated by AirPortCreateRefWithInterfaceName.
	@param networkRecord A scan result dictionary returned from AirPortCreateScanResults.
	@param argsDict A dictionary of arguments using keys and values from AirPortVar.h.
	@result Returns kAP_NoErr upon success or an appropriate error code. 
	*/
AirPortErr AirPortAssociate( AirPortRef ref, CFDictionaryRef networkRecord, CFDictionaryRef argsDict ) __OSX_AVAILABLE_STARTING(__MAC_10_6,__IPHONE_NA);

/*! @function AirPortDisassociate
	@abstract End participation in a network.
	@discussion This method is used to terminate participation in both infrastructure and IBSS networks. The operation will fail if the calling process does not have permission to disassociate from networks.
	@param ref AirPortRef allocated by AirPortCreateRefWithInterfaceName.
	@result Returns kAP_NoErr upon success or an appropriate error code. 
	*/
AirPortErr AirPortDisassociate( AirPortRef ref ) __OSX_AVAILABLE_STARTING(__MAC_10_6,__IPHONE_NA);

/*! @function AirPortCreateIBSS
	@abstract Creates an IBSS network.
	@discussion This method is used to create an IBSS network. The operation will fail if the calling process does not have permission to create IBSS networks.
	@param ref AirPortRef allocated by AirPortCreateRefWithInterfaceName.
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

typedef void (*AirPortEventCallback) ( AirPortErr err, AirPortRef ref, UInt32 event, void * eventData, UInt32 eventDataLen, void * context );

/*! @function AirPortEventMonitorStart
	@abstract Starts monitoring interface AirPort events.
	@discussion This funciton is used to initiate interface event monitoring. Events, errors, and data are delivered through the specified callback.
	@param ref AirPortRef allocated by AirPortCreateRefWithInterfaceName.
	@param eventCallback Callback through which event data is delivered.
	@param context Context pointer passed to callback function.
	@param eventsList CFArray of 32 bit AirPortEvent codes.
	@param runLoop The run loop with which to schedule event callbacks.
	*/

AirPortErr AirPortEventMonitorStart( AirPortRef ref, AirPortEventCallback eventCallback, void * context, CFArrayRef eventsList, CFRunLoopRef runLoop ) __OSX_AVAILABLE_STARTING(__MAC_10_6,__IPHONE_NA);

/*! @function AirPortEventMonitorStop
	@abstract Stops monitoring interface AirPort events.
	@discussion Used to terminate interface event monitoring. Event callbacks will no longer be delivered.
	@param ref AirPortRef allocated by AirPortCreateRefWithInterfaceName.
	*/
AirPortErr AirPortEventMonitorStop( AirPortRef ref ) __OSX_AVAILABLE_STARTING(__MAC_10_6,__IPHONE_NA);

#pragma mark -
#pragma mark AirPort Preferences

/*! @group AirPort Preferences */

/*! @function AirPortCopyPreference
	@abstract copies the value for the indicated preference
	@discussion
	@param ref AirPortRef allocated by AirPortCreateRefWithInterfaceName.
	@param pref string key for the preference to get, see AirPortKeys for possible values
	@param value CFTypeRef value pointer, must be non-null, preference value is copied here 
	*/
AirPortErr AirPortCopyPreference( AirPortRef ref, CFStringRef pref, CFTypeRef * value ) __OSX_AVAILABLE_STARTING(__MAC_10_6,__IPHONE_NA);

/*! @function AirPortSetPreference
	@abstract sets the value for the indicated preference
	@discussion
	@param ref AirPortRef allocated by AirPortCreateRefWithInterfaceName.
	@param pref string key for the preference to be set, see AirPortKeys for possible values
	@param value CFTypeRef with the new value to be set
 */
AirPortErr AirPortSetPreference( AirPortRef ref, CFStringRef pref, CFTypeRef value ) __OSX_AVAILABLE_STARTING(__MAC_10_6,__IPHONE_NA);

#pragma mark -
#pragma mark Unit Conversion

AirPortErr AirPortConvertUnits( UInt32 fromValue, AirPortPowerUnit fromUnits, AirPortPowerUnit toUnits, UInt32 * toValue) __OSX_AVAILABLE_STARTING(__MAC_10_6,__IPHONE_NA);

#endif /* _AIRPORTAPI_H_ */