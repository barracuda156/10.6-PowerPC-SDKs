/*
	AirPortVar.h
	AirPort
	Copyright (c) 2002-2008, Apple Inc.
	All rights reserved.
 
 */

#ifndef _AIRPORTVAR_H_
#define _AIRPORTVAR_H_

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
	@constant kAP_HT_FeaturesNotSupported
		Association was denied because the requesting station does not support HT features.
	@constant kAP_PCO_TransitionTimeNotSupported
		Association was denied because the requesting station does not support the PCO transition time required by the AP.
	@constant kAP_RefNotBoundErr
		No interface is associated with the AirPortRef.
	@constant kAP_IPC_Error
		Error communicating with a separate process.
	@constant kAP_OpNotPermitted
		Calling process does not have permission to perform this operation.
	@constant kAP_Error
		Generic error, no specific error code exists to describe the error condition.
 */

enum AirPortErr
{
	kAP_NoErr							=  0,
	kAP_ParamErr						= -3900,
	kAP_NoMemErr						= -3901,
	kAP_UknownErr						= -3902,
	kAP_NotSupportedErr					= -3903,
	kAP_FormatErr						= -3904,
	kAP_TimeoutErr						= -3905,
	kAP_UnspecifiedFailureErr			= -3906,
	kAP_UnsupportedCapabilitiesErr		= -3907,
	kAP_ReassociationDeniedErr			= -3908,
	kAP_AssociationDeniedErr			= -3909,
	kAP_AuthAlgUnsupportedErr			= -3910,
	kAP_InvalidAuthSeqNumErr			= -3911,
	kAP_ChallengeFailureErr				= -3912,
	kAP_AP_FullErr						= -3913,
	kAP_UnsupportedRateSetErr			= -3914,
	kAP_ShortSlotUnsupportedErr			= -3915,
	kAP_DSSS_OFDM_UnsupportedErr		= -3916,
	kAP_InvalidInfoElementErr			= -3917,
	kAP_InvalidGroupCipherErr			= -3918,
	kAP_InvalidPairwiseCipherErr		= -3919,
	kAP_InvalidAKMP_Err					= -3920,
	kAP_UnsupportedRSN_VersionErr		= -3921,
	kAP_InvalidRSN_CapabilitiesErr		= -3922,
	kAP_CipherSuiteRejectedErr			= -3923,
	kAP_InvalidPMKErr					= -3924,
	kAP_SupplicantTimeoutErr			= -3925,
	kAP_HT_FeaturesNotSupported			= -3926,
	kAP_PCO_TransitionTimeNotSupported  = -3927,
	kAP_RefNotBoundErr					= -3928,
	kAP_IPC_Error						= -3929,
	kAP_OpNotPermitted					= -3930,
	kAP_Error							= -3931,
};
typedef enum AirPortErr AirPortErr;

/*!
	@enum AirPortChannelFlags
	@discussion Flags that specify channel properties
		not discernable from the channel number alone.
	@constant kAirPortChanFlag20Mhz
		Channel is 20 Mhz wide.
	@constant kAirPortChanFlag40Mhz
		Channel is 40 Mhz wide.
	@constant kAirPortChanFlag2Ghz
		Channel is in the 2.4 Ghz frequency band.
	@constant kAirPortChanFlag5Ghz
		Channel is in the 5 Ghz frequency band.
	@constant kAirPortChanFlagSecondaryAbove
		If present with the kAirPortChanFlag40Mhz flag, indicates that the secondary channel is at a higher frequency than the primary channel. If this flag is absent when the kAirPortChannelFlag40Mhz flag is present, then the secondary channel is at a lower frequency than the primary channel.
*/

enum AirPortChannelFlags
{
	kAirPortChanFlagNone			= 0x000,
	kAirPortChanFlag20Mhz			= 0x002,
	kAirPortChanFlag40Mhz			= 0x004,
	kAirPortChanFlag2Ghz			= 0x008,
	kAirPortChanFlag5Ghz			= 0x010,
	kAirPortChanFlagSecondaryAbove	= 0x200,
};
typedef enum AirPortChannelFlags AirPortChannelFlags;

/*!
	@enum AirPortNetworkMode
	@discussion Describes network operation modes.
	@constant kAirPortNetModeIBSS
		Network is operating as an independent basic service set (IBSS).
	@constant kAirPortNetModeInfrastructure
		Network is operating in infrastructure mode.
	@constant kAirPortNetModeAny
		Network is operating in any supported mode.
*/

enum AirPortNetworkMode
{
	kAirPortNetModeIBSS				= 1,
	kAirPortNetModeInfrastructure	= 2,
	kAirPortNetModeAny				= 3,
};
typedef enum AirPortNetworkMode AirPortNetworkMode;

/*!
	@enum AirPortScanType
	@discussion Defines types of scans that may be requested from an AirPort interface.
	@constant kAirPortScanTypeActive
		On each channel where transmitting is allowed according to the interface's current country code configuration, interface will send probe requests and listen for probe responses.
	@constant kAirPortScanTypePassive
		Interface will listen for beacons silently on each channel regardless of country code configuration.
*/

enum AirPortScanType
{
	kAirPortScanTypeActive = 1,
	kAirPortScanTypePassive = 2,
};
typedef enum AirPortScanType AirPortScanType;

/*!
	@enum AirPortPhyTypeFlags
	@discussion Defines supported AirPort physical layers.
	@constant kAirPortPhyTypeFlagAuto
		PHY type is automatically selected. If passed as an argument to a scan request, networks of all PHY types supported by the interface are returned in the scan result list.
	@constant kAirPortPhyTypeFlag_11A
		IEEE 802.11a.
	@constant kAirPortPhyTypeFlag_11B
		IEEE 802.11b.
	@constant kAirPortPhyTypeFlag_11G
		IEEE 802.11g.
	@constant kAirPortPhyTypeFlag_11N
		IEEE 802.11n.
*/

enum AirPortPhyTypeFlags
{
	kAirPortPhyTypeFlagAuto = 0x01,
	kAirPortPhyTypeFlag_11A = 0x02,
	kAirPortPhyTypeFlag_11B = 0x04,
	kAirPortPhyTypeFlag_11G = 0x08,
	kAirPortPhyTypeFlag_11N = 0x10
};
typedef enum AirPortPhyTypeFlags AirPortPhyTypeFlags;

/*!
	@enum AirPortPowerSaveMode
	@discussion Defines power savings modes.
	@constant kAirPortPowerSaveModeDisabled
		Power save mode is disabled.
	@constant kAirPortPowerSaveMode80211
		IEEE 802.11 power save mode.
	@constant kAirPortPowerSaveModeVendor
		Vendor specific power save mode.
	@constant kAirPortPowerSaveModeMaxThroughput
		Vendor power save mode offering best throughput, possibly at the expense of more power.
	@constant kAirPortPowerSaveModeMaxPowerSave
		Vendor power save mode offering best power savings, possibly at the expense of less throughput.
*/

enum AirPortPowerSaveMode
{
	kAirPortPowerSaveModeDisabled		= 0,
	kAirPortPowerSaveMode80211			= 1,
	kAirPortPowerSaveModeVendor			= 2,
	kAirPortPowerSaveModeMaxThroughput	= 7,
	kAirPortPowerSaveModeMaxPowerSave	= 8,
};
typedef enum AirPortPowerSaveMode AirPortPowerSaveMode;

/*!
	@enum AirPortInterfaceState
	@discussion Specifies AirPort interface states.
	@constant kAirPortInterfaceStateInactive
		Interface is not participating in a network.
	@constant kAirPortInterfaceStateScanning
		Interface is scanning.
	@constant kAirPortInterfaceStateAuthenticating
		Interface is performing 802.11 authentication.
	@constant kAirPortInterfaceStateAssociating
		Interface is performing 802.11 association.
	@constant kAirPortInterfaceStateRunning
		Interface is participating in a network.
*/

enum AirPortInterfaceState
{
	kAirPortInterfaceStateInactive		 = 0,
	kAirPortInterfaceStateScanning		 = 1,
	kAirPortInterfaceStateAuthenticating = 2,
	kAirPortInterfaceStateAssociating	 = 3,
	kAirPortInterfaceStateRunning		 = 4,
};
typedef enum AirPortInterfaceState AirPortInterfaceState;

/*!
	@enum AirPortInterfaceOpModeFlags
	@discussion Interface operational mode flags.
	@constant kAirPortInterfaceOpModeFlagStation
		Interface is participating in an infrastructure network as a non-AP station.
	@constant kAirPortInterfaceOpModeFlagIBSS
		Interface is participating in an IBSS network.
	@constant kAirPortInterfaceOpModeFlagHostAP
		Interface is participating in an infrastructure network as an access point.
	@constant kAirPortInterfaceOpModeFlagMonitor
		Interface is in 802.11 monitor mode.
*/

enum AirPortInterfaceOpModeFlags
{
	kAirPortInterfaceOpModeFlagStation = 0x01,
	kAirPortInterfaceOpModeFlagIBSS	   = 0x02,
	kAirPortInterfaceOpModeFlagHostAP  = 0x08,
	kAirPortInterfaceOpModeFlagMonitor = 0x10,
};
typedef enum AirPortInterfaceOpModeFlags AirPortInterfaceOpModeFlags;

/*!
	@enum AirPort80211AuthType
	@discussion 802.11 authentication algorithms.
	@constant kAirPort80211AuthTypeOpen
		Open system authentication.
	@constant kAirPort80211AuthTypeShared
		Shared key authentication.
	@constant kAirPort80211AuthTypeCisco
		Cisco network authentication (auth type 0x80).
*/

enum AirPort80211AuthType
{
	kAirPort80211AuthTypeOpen	= 1,
	kAirPort80211AuthTypeShared	= 2,
	kAirPort80211AuthTypeCisco	= 3,
};
typedef enum AirPort80211AuthType AirPort80211AuthType;

/*!
	@enum AirPortPortAuthTypeFlags
	@discussion AirPort network port authentication types.
	@constant kAirPortPortAuthTypeWPA
		WPA enterprise.
	@constant kAirPortPortAuthTypeWPA_PSK
		WPA preshared key.
	@constant kAirPortPortAuthTypeWPA2
		WPA2 enterprise.
	@constant kAirPortPortAuthTypeWPA2_PSK
		WPA2 preshared key.
	@constant kAirPortPortAuthTypeLEAP
		Cisco LEAP authentication.
	@constant kAirPortPortAuthType8021X
		802.1x authentication.
*/

enum AirPortPortAuthTypeFlags
{
	kAirPortPortAuthTypeWPA		 = 0x01,
	kAirPortPortAuthTypeWPA_PSK	 = 0x02,
	kAirPortPortAuthTypeWPA2	 = 0x04,
	kAirPortPortAuthTypeWPA2_PSK = 0x08,
	kAirPortPortAuthTypeLEAP	 = 0x10,
	kAirPortPortAuthType8021X	 = 0x20,
};
typedef enum AirPortPortAuthTypeFlags AirPortPortAuthTypeFlags;

/*!
	@enum AirPortPowerUnit
	@discussion Units for measuring power.
	@constant kAirPortPowerUnitDBM
		Power ratio in decibals of measured power referenced to one watt.
	@constant kAirPortPowerUnitMW
		Milliwatts.
	@constant kAirPortPowerUnitPercentage
		Percentage of total power.
*/

enum AirPortPowerUnit
{
	kAirPortPowerUnitDBM		= 0,
	kAirPortPowerUnitMW			= 1,
	kAirPortPowerUnitPercentage	= 2,
};
typedef enum AirPortPowerUnit AirPortPowerUnit;

/*!
	@enum AirPortWPA_CipherType
	@discussion IEEE 802.11i cipher type constants.
	@constant kAirPortWPA_CipherTypeNone
		No cipher.
	@constant kAirPortWPA_CipherTypeWEP40
		40 bit WEP.
	@constant kAirPortWPA_CipherTypeTKIP
		TKIP.
	@constant kAirPortWPA_CipherTypeAES
		AES-CCMP.
	@constant kAirPortWPA_CipherTypeWEP104
		104 bit WEP.
*/

enum AirPortWPA_CipherType
{
	kAirPortWPA_CipherTypeNone	 = 0x0,
	kAirPortWPA_CipherTypeWEP40	 = 0x1,
	kAirPortWPA_CipherTypeTKIP	 = 0x2,
	kkAirPortWPA_CipherTypeAES	 = 0x4,
	kAirPortWPA_CipherTypeWEP104 = 0x5,
};
typedef enum AirPortWPA_CipherType AirPortWPA_CipherType;

/*!
	@enum AirPortWPA_AuthSelType
	@discussion IEEE 802.11i authentication selector type constants.
	@constant kAirPortWPA_AuthSelTypeNone
		None.
	@constant kAirPortWPA_AuthSelTypeUnspec
		WPA Enterprise.
	@constant kAirPortWPA_AuthSelTypePSK
		Pre-shared key.
*/

enum AirPortWPA_AuthSelType
{
	kAirPortWPA_AuthSelTypeNone	  = 0,
	kAirPortWPA_AuthSelTypeUnspec = 1,
	kAirPortWPA_AuthSelTypePSK	  = 2,
};
typedef enum AirPortWPA_AuthSelType AirPortWPA_AuthSelType;

#pragma mark -
#pragma mark AirPortEvent

/*!
	@enum AirPortEvent
	@discussion AirPort interface event type constants.
	@constant kAirPortEventPowerChanged
		Posted when AirPort card power state changes. No event data.
	@constant kAirPortEventBSSID_Changed
		Posted by interface when roaming between access points using the same SSID. No event data.
	@constant kAirPortEventLinkChanged
		Posted by interface when the link goes up or down. No event data.
	@constant kAirPortEventModeChanged
		Posted by interface when host AP or IBSS mode is enabled or disabled. No event data.
	@constant kAirPortEventCountryCodeChanged
		A new 802.11d country code information element has been
		received and the interface's active regulatory region
		has changed.
*/

enum AirPortEvent
{
	kAirPortEventPowerChanged		= 1,
	kAirPortEventBSSID_Changed		= 3,
	kAirPortEventLinkChanged		= 4,
	kAirPortEventModeChanged		= 8,
	kAirPortEventCountryCodeChanged	= 11,
};
typedef enum AirPortEvent AirPortEvent;

#endif /* _AIRPORTVAR_H_ */