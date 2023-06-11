/*
	AirPortVar.h
	AirPort
	Copyright (c) 2002-2008, Apple Inc.
	All rights reserved.
 
 */

#ifndef _AIRPORTVAR_H_
#define _AIRPORTVAR_H_


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
	@constant AirPortPhyTypeFlagAuto
		PHY type is automatically selected. If passed as an argument to a scan request, networks of all PHY types supported by the interface are returned in the scan result list.
	@constant AirPortPhyTypeFlag_11A
		IEEE 802.11a.
	@constant AirPortPhyTypeFlag_11B
		IEEE 802.11b.
	@constant AirPortPhyTypeFlag_11G
		IEEE 802.11g.
	@constant AirPortPhyTypeFlag_11N
		IEEE 802.11n.
*/

enum AirPortPhyTypeFlags
{
	AirPortPhyTypeFlagAuto = 0x01,
	AirPortPhyTypeFlag_11A = 0x02,
	AirPortPhyTypeFlag_11B = 0x04,
	AirPortPhyTypeFlag_11G = 0x08,
	AirPortPhyTypeFlag_11N = 0x10
};
typedef enum AirPortPhyTypeFlags AirPortPhyTypeFlags;

/*!
	@enum AirPortPowerSaveMode
	@discussion Defines power savings modes.
	@constant AirPortPowerSaveModeDisabled
		Power save mode is disabled.
	@constant AirPortPowerSaveMode80211
		IEEE 802.11 power save mode.
	@constant AirPortPowerSaveModeVendor
		Vendor specific power save mode.
	@constant AirPortPowerSaveModeMaxThroughput
		Vendor power save mode offering best throughput, possibly at the expense of more power.
	@constant AirPortPowerSaveModeMaxPowerSave
		Vendor power save mode offering best power savings, possibly at the expense of less throughput.
*/

enum AirPortPowerSaveMode
{
	AirPortPowerSaveModeDisabled		= 0,
	AirPortPowerSaveMode80211			= 1,
	AirPortPowerSaveModeVendor			= 2,
	AirPortPowerSaveModeMaxThroughput	= 7,
	AirPortPowerSaveModeMaxPowerSave	= 8,
};
typedef enum AirPortPowerSaveMode AirPortPowerSaveMode;

/*!
	@enum AirPortInterfaceState
	@discussion Specifies AirPort interface states.
	@constant AirPortInterfaceStateInactive
		Interface is not participating in a network.
	@constant AirPortInterfaceStateScanning
		Interface is scanning.
	@constant AirPortInterfaceStateAuthenticating
		Interface is performing 802.11 authentication.
	@constant AirPortInterfaceStateAssociating
		Interface is performing 802.11 association.
	@constant AirPortInterfaceStateRunning
		Interface is participating in a network.
*/

enum AirPortInterfaceState
{
	AirPortInterfaceStateInactive		= 0,
	AirPortInterfaceStateScanning		= 1,
	AirPortInterfaceStateAuthenticating = 2,
	AirPortInterfaceStateAssociating	= 3,
	AirPortInterfaceStateRunning		= 4,
};
typedef enum AirPortInterfaceState AirPortInterfaceState;

/*!
	@enum AirPortInterfaceOpModeFlags
	@discussion Interface operational mode flags.
	@constant AirPortInterfaceOpModeFlagStation
		Interface is participating in an infrastructure network as a non-AP station.
	@constant AirPortInterfaceOpModeFlagIBSS
		Interface is participating in an IBSS network.
	@constant AirPortInterfaceOpModeFlagHostAP
		Interface is participating in an infrastructure network as an access point.
	@constant AirPortInterfaceOpModeFlagMonitor
		Interface is in 802.11 monitor mode.
*/

enum AirPortInterfaceOpModeFlags
{
	AirPortInterfaceOpModeFlagStation = 0x01,
	AirPortInterfaceOpModeFlagIBSS	  = 0x02,
	AirPortInterfaceOpModeFlagHostAP  = 0x08,
	AirPortInterfaceOpModeFlagMonitor = 0x10,
};
typedef enum AirPortInterfaceOpModeFlags AirPortInterfaceOpModeFlags;

/*!
	@enum AirPort80211AuthType
	@discussion 802.11 authentication algorithms.
	@constant AirPort80211AuthTypeOpen
		Open system authentication.
	@constant AirPort80211AuthTypeShared
		Shared key authentication.
	@constant AirPort80211AuthTypeCisco
		Cisco network authentication (auth type 0x80).
*/

enum AirPort80211AuthType
{
	AirPort80211AuthTypeOpen	= 1,
	AirPort80211AuthTypeShared	= 2,
	AirPort80211AuthTypeCisco	= 3,
};
typedef enum AirPort80211AuthType AirPort80211AuthType;

/*!
	@enum AirPortPortAuthTypeFlags
	@discussion AirPort network port authentication types.
	@constant AirPortPortAuthTypeWPA
		WPA enterprise.
	@constant AirPortPortAuthTypeWPA_PSK
		WPA preshared key.
	@constant AirPortPortAuthTypeWPA2
		WPA2 enterprise.
	@constant AirPortPortAuthTypeWPA2_PSK
		WPA2 preshared key.
	@constant AirPortPortAuthTypeLEAP
		Cisco LEAP authentication.
	@constant AirPortPortAuthType8021X
		802.1x authentication.
*/

enum AirPortPortAuthTypeFlags
{
	AirPortPortAuthTypeWPA		= 0x01,
	AirPortPortAuthTypeWPA_PSK	= 0x02,
	AirPortPortAuthTypeWPA2		= 0x04,
	AirPortPortAuthTypeWPA2_PSK = 0x08,
	AirPortPortAuthTypeLEAP		= 0x10,
	AirPortPortAuthType8021X	= 0x20,
};
typedef enum AirPortPortAuthTypeFlags AirPortPortAuthTypeFlags;

/*!
	@enum AirPortPowerUnit
	@discussion Units for measuring power.
	@constant AirPortPowerUnitDBM
		Power ratio in decibals of measured power referenced to one watt.
	@constant AirPortPowerUnitMW
		Milliwatts.
	@constant AirPortPowerUnitPercentage
		Percentage of total power.
*/

enum AirPortPowerUnit
{
	AirPortPowerUnitDBM			= 0,
	AirPortPowerUnitMW			= 1,
	AirPortPowerUnitPercentage	= 2,
};
typedef enum AirPortPowerUnit AirPortPowerUnit;

/*!
	@enum AirPortInterfaceCapability
	@discussion Specifies interface capabilities.
	@constant AirPortInterfaceCapWEP
		WEP supported.
	@constant AirPortInterfaceCapTKIP
		TKIP supported.
	@constant AirPortInterfaceCapAES_CCM
		AES supported.
	@constant AirPortInterfaceCapIBSS
		IBSS mode supported.
	@constant AirPortInterfaceCapPwrManagement
		Power save modes are supported.
	@constant AirPortInterfaceCapHostAP
		Host AP mode is supported.
	@constant AirPortInterfaceCapMonitorMode
		Monitor mode is supported.
	@constant AirPortInterfaceCapWPA
		WPA is supported.
	@constant AirPortInterfaceCapWPA2
		WPA2 is supported.
	@constant AirPortCapWME
		WME is supported.
	@constant AirPortCapShortGI40Mhz
		Short guard interval is supported on wide channels.
	@constant AirPortCapShortGI20Mhz
		Short guard interval is supported on 20 Mhz channels.
	@constant AirPortCapTSN
		Transitional security networks are supported (WEP group cipher with TKIP or AES unicast cipher).
*/

enum AirPortInterfaceCapability
{
	AirPortInterfaceCapWEP			 = 0,
	AirPortInterfaceCapTKIP			 = 1,
	AirPortInterfaceCapAES_CCM		 = 3,
	AirPortInterfaceCapIBSS			 = 5,
	AirPortInterfaceCapPwrManagement = 6,
	AirPortInterfaceCapHostAP		 = 7,
	AirPortInterfaceCapMonitorMode	 = 11,
	AirPortInterfaceCapWPA			 = 13,
	AirPortInterfaceCapWPA2			 = 14,
	AirPortCapWME					 = 17,
	AirPortCapShortGI40Mhz			 = 18,
	AirPortCapShortGI20Mhz			 = 19,
	AirPortCapTSN					 = 21,
};
typedef enum AirPortInterfaceCapability AirPortInterfaceCapability;

#define AIRPORT_INTERFACE_CAP_SUPPORTED( buf, cap ) isset( buf, cap )

/*!
	@enum AirPortWPA_CipherType
	@discussion IEEE 802.11i cipher type constants.
	@constant AirPortWPA_CipherTypeNone
		No cipher.
	@constant AirPortWPA_CipherTypeWEP40
		40 bit WEP.
	@constant AirPortWPA_CipherTypeTKIP
		TKIP.
	@constant AirPortWPA_CipherTypeAES
		AES-CCMP.
	@constant AirPortWPA_CipherTypeWEP104
		104 bit WEP.
*/

enum AirPortWPA_CipherType
{
	AirPortWPA_CipherTypeNone	= 0x0,
	AirPortWPA_CipherTypeWEP40	= 0x1,
	AirPortWPA_CipherTypeTKIP	= 0x2,
	AirPortWPA_CipherTypeAES	= 0x4,
	AirPortWPA_CipherTypeWEP104 = 0x5,
};
typedef enum AirPortWPA_CipherType AirPortWPA_CipherType;

/*!
	@enum AirPortWPA_AuthSelType
	@discussion IEEE 802.11i authentication selector type constants.
	@constant AirPortWPA_AuthSelTypeNone
		None.
	@constant AirPortWPA_AuthSelTypeUnspec
		WPA Enterprise.
	@constant AirPortWPA_AuthSelTypePSK
		Pre-shared key.
*/

enum AirPortWPA_AuthSelType
{
	AirPortWPA_AuthSelTypeNone	 = 0,
	AirPortWPA_AuthSelTypeUnspec = 1,
	AirPortWPA_AuthSelTypePSK	 = 2,
};
typedef enum AirPortWPA_AuthSelType AirPortWPA_AuthSelType;

#pragma mark -
#pragma mark AirPortEvent

/*!
	@enum AirPortEvent
	@discussion AirPort interface event type constants.
	@constant AirPortEventPowerChanged
		Posted when AirPort card power state changes. No event data.
	@constant AirPortEventBSSID_Changed
		Posted by interface when roaming between access points using the same SSID. No event data.
	@constant AirPortEventLinkChanged
		Posted by interface when the link goes up or down. No event data.
	@constant AirPortEventModeChanged
		Posted by interface when host AP or IBSS mode is enabled or disabled. No event data.
*/

enum AirPortEvent
{
	AirPortEventPowerChanged		= 1,
	AirPortEventBSSID_Changed		= 3,
	AirPortEventLinkChanged			= 4,
	AirPortEventModeChanged			= 8,
};
typedef enum AirPortEvent AirPortEvent;

#endif /* _AIRPORTVAR_H_ */