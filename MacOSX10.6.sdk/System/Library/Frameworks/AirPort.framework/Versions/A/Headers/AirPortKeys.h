/*
	AirPortKeys.h
	AirPort
	Copyright (c) 2002-2008, Apple Inc.
	All rights reserved.
 
 */

#ifndef _AIRPORTKEYS_H_
#define _AIRPORTKEYS_H_

#pragma mark -
#pragma mark Scan Request Parameters

/*! @group Scan Request Parameters */

/*!
	@const kAirPortScanParamKeySSID
	@discussion CFStringRef containing a UTF8 representation of the target SSID of a directed scan request.
*/

extern CFStringRef const kAirPortScanParamKeySSID;

/*!
	@const kAirPortScanParamKeyBSSID
	@discussion CFStringRef containing a UTF8 representation of the target BSSID of a directed scan request.
*/

extern CFStringRef const kAirPortScanParamKeyBSSID;

/*!
	@const kAirPortScanParamKeyMerge
	@discussion Boolean. Indicates whether or not all duplicate SSIDs should be included in the scan result list, or only the BSSID with the strongest signal strength. Defaults to true if not included in the scan argument dictionary.
*/

extern CFStringRef const kAirPortScanParamKeyMerge;

/*!
	@const kAirPortScanParamKeyNumScans
	@discussion 32 bit number. Indicates number of scan iterations to perform. The results of each scan are aggregated into a single result list. Multiple back to back scan requests can severely impact performance. Defaults to one scan iteration if not included in scan argument dictionary.
*/

extern CFStringRef const kAirPortScanParamKeyNumScans;

/*!
	@const kAirPortScanParamKeyType
	@discussion 32 bit number. See AirPortVar.h for AirPortScanTypes. Defaults to kAirPortScanTypeActive.
*/

extern CFStringRef const kAirPortScanParamKeyType;

/*!
	@const kAirPortScanParamKeyBSS_Type
	@discussion 32 bit number. If a specific BSS type is requested, then only networks of the requested type will be returned in the scan result list. See AirPortVar.h for AirPortNetworkMode definition. Defaults to kAirPortNetModeAny.
*/

extern CFStringRef const kAirPortScanParamKeyBSS_Type;

/*!
	@const kAirPortScanParamKeyPhyMode
	@discussion 32 bit number. Allows a network PHY type filter to be specified by passing in a vector of AirPortPhyTypes. If parameter is not included in argument dictionary, AirPortPhyTypeAuto will be used. See Apple80211Var.h for AirPortPhyType definition.
*/

extern CFStringRef const kAirPortScanParamKeyPhyMode;

/*!
	@const kAirPortScanParamKeyDwellTime
	@discussion 16 bit number. Specifies a fixed time in ms for the interface to spend on each channel listening for beacons and probe responses. If argument is not specified, the driver default will be used.
*/

extern CFStringRef const kAirPortScanParamKeyDwellTime;

/*!
	@const kAirPortScanParamKeyRestTime
	@discussion 32 bit number. Specifies a fixed time in ms for the interface to spend on its home channels between intervals of off channel activity during the scan request. If argument is not specified, the driver default will be used.
*/

extern CFStringRef const kAirPortScanParamKeyRestTime;

/*!
	@const kAirPortScanParamKeyChannels
	@discussion Array of dictionaries. Specifies a list of channels on which the interface should look for networks during the scan request. Each channel is specified as a channel dictionary. If argument is not included in the scan parameter dictionary, then the driver default channel list for the active country code will be used.
*/

extern CFStringRef const kAirPortScanParamKeyChannels;

#pragma mark -
#pragma mark IBSS Network Dictionary Keys

/*! @group IBSS Network Dictionary Keys */


#pragma mark -
#pragma mark Channel Dictionary Keys

/*! @group Channel Dictionary Keys */

/*!
	@const kAirPortChanParamKeyChannel
	@discussion 32 bit channel number.
*/

extern CFStringRef const kAirPortChanParamKeyChannel;

/*!
	@const kAirPortChanParamKeyFlags
	@discussion 32 bit vector of AirPortChannelFlags.
*/

extern CFStringRef const kAirPortChanParamKeyFlags;

#pragma mark -
#pragma mark Interface Status Keys

/*! @group Interface Status Keys */

/*!
	@const kAirPortInfoKeyPowerSave
	@discussion 32 bit number containing an AirPortPowerSaveMode value.
*/

extern CFStringRef const kAirPortInfoKeyPowerSave;

/*!
	@const kAirPortInfoKeyTxPower
	@discussion 32 bit number. Power value is reported in milliwatts.
*/

extern CFStringRef const kAirPortInfoKeyTxPower;

/*!
	@const kAirPortInfoKeyState
	@discussion 32 bit number containing an AirPortInterfaceState.
*/

extern CFStringRef const kAirPortInfoKeyState;

/*!
	@const kAirPortInfoKeyPhyMode
	@discussion Dictionary containing supported and active phy modes.
*/

extern CFStringRef const kAirPortInfoKeyPhyMode;

/*!
	@const kAirPortInfoKeyOpMode
	@discussion 32 bit number containing AirPortInterfaceOpModeFlags.
*/

extern CFStringRef const kAirPortInfoKeyOpMode;

/*!
	@const kAirPortInfoKeyNoise
	@discussion Dictionary containing per radio chain (if supported)
		noise measurements.
*/

extern CFStringRef const kAirPortInfoKeyNoise;

/*!
	@const kAirPortInfoKeyRate
	@discussion 32 bit number. Current data rate in Mbps.
*/

extern CFStringRef const kAirPortInfoKeyRate;

/*!
	@const kAirPortInfoKeyRSSI
	@discussion Dictionary containing per radio chain (if supported )
		RSSI measurements.
*/

extern CFStringRef const kAirPortInfoKeyRSSI;

/*!
	@const kAirPortInfoKeyChannel
	@discussion Dictionary containing information about interface's current channel.
*/

extern CFStringRef const kAirPortInfoKeyChannel;

/*!
	@const kAirPortInfoKeyAuthType
	@discussion Dictionary containing information about interface's current authentication configuration.
*/

extern CFStringRef const kAirPortInfoKeyAuthType;

/*!
	@const kAirPortInfoKeySSID_Bytes
	@discussion CFData containing the bytes of the SSID of the network in which the interface is currently participating.
*/

extern CFStringRef const kAirPortInfoKeySSID_Bytes;

/*!
	@const kAirPortInfoKeySSID_Str
	@discussion CFString containing a UTF-8 representation of the SSID of the network in which the interface is currently participating.
*/

extern CFStringRef const kAirPortInfoKeySSID_Str;

/*!
	@const kAirPortInfoKeyBSSID
	@discussion CFString containing the BSSID of the of the network in which the interface is currently participating.
*/

extern CFStringRef const kAirPortInfoKeyBSSID;

/*!
	@const kAirPortInfoKeyCaps
	@discussion CFData object containing an interface capabilities bit vector. See AirPortInterfaceCapability enum in Apple80211Var.h.
*/

extern CFStringRef const kAirPortInfoKeyCaps;


#pragma mark -
#pragma mark Noise and RSSI Dictionary Keys

/*! @group Noise and RSSI Dictionary Keys */

/*!
	@const kAirPortNoiseKeyPrimaryAggregate
	@discussion Aggregate noise measured across all radio chains on interface's primary channel. The algorithm for computing aggregate noise may vary across chipset vendor.
*/

extern CFStringRef const kAirPortNoiseKeyPrimaryAggregate;

/*!
	@const kAirPortNoiseKeyPrimaryList
	@discussion CFArray containing 32 bit noise measurements on primary channel for each radio chain. May not be supported by all chipsets.
*/

extern CFStringRef const kAirPortNoiseKeyPrimaryList;

/*!
	@const kAirPortNoiseKeySecondaryAggregate
	@discussion Aggregate noise measured across all radio chains on interface's secondary channel. Will not be present if the interface is not using a wide channel. The algorithm for computing aggregate noise may vary across chipset vendor.
*/

extern CFStringRef const kAirPortNoiseKeySecondaryAggregate;

/*!
	@const kAirPortNoiseKeySecondaryList
	@discussion CFArray containing 32 bit noise measurements on secondary channel for each radio chain. Will not be present if the interface is not using a wide channel. May not be supported by all chipsets.
*/

extern CFStringRef const kAirPortNoiseKeySecondaryList;

/*!
	@const kAirPortNoiseKeyUnit
	@discussion 32 bit number containing AirPortPowerUnit of noise measurements.
*/

extern CFStringRef const kAirPortNoiseKeyUnit;

/*!
	@const kAirPortRSSI_KeyPrimaryAggregate
	@discussion Aggregate RSSI measured across all radio chains on interface's primary channel. The algorithm for computing aggregate RSSI may vary across chipset vendor.
*/

extern CFStringRef const kAirPortRSSI_KeyPrimaryAggregate;

/*!
	@const kAirPortRSSI_KeyPrimaryList
	@discussion CFArray containing 32 bit RSSI measurements on primary channel for each radio chain. May not be supported by all chipsets.
*/

extern CFStringRef const kAirPortRSSI_KeyPrimaryList;

/*!
	@const kAirPortRSSI_KeySecondaryAggregate
	@discussion Aggregate RSSI measured across all radio chains on interface's secondary channel. Will not be present if the interface is not using a wide channel. The algorithm for computing aggregate RSSI may vary across chipset vendor.
*/

extern CFStringRef const kAirPortRSSI_KeySecondaryAggregate;

/*!
	@const kAirPortRSSI_KeySecondaryList
	@discussion CFArray containing 32 bit RSSI measurements on secondary channel for each radio chain. Will not be present if the interface is not using a wide channel. May not be supported by all chipsets.
*/

extern CFStringRef const kAirPortRSSI_KeySecondaryList;

/*!
	@const kAirPortRSSI_KeyUnit
	@discussion 32 bit number containing AirPortPowerUnit of RSSI measurements.
*/

extern CFStringRef const kAirPortRSSI_KeyUnit;

#pragma mark -
#pragma mark PHY Mode Dictionary Keys

/*! @group PHY Mode Dictionary Keys */

/*!
	@const kAirPortPhyModeKeySupported
	@discussion 32 bit number containing a vector of AirPortPhyTypeFlags corresponding to PHY modes supported by the interface.
*/

extern CFStringRef const kAirPortPhyModeKeySupported;

/*!
	@const kAirPortPhyModeKeyActive
	@discussion 32 bit number containing a AirPortPhyTypeFlag corresponding to the PHY mode currently in use by the interface.
*/

extern CFStringRef const kAirPortPhyModeKeyActive;

#pragma mark -
#pragma mark Authentication Type Dictionary Keys

/*! @group Authentication Type Dictionary Keys */

/*!
	@const kAirPortAuthTypeKey80211
	@discussion 32 bit number containing the AirPort80211AuthType for which the interface is currently configured.
*/

extern CFStringRef const kAirPortAuthTypeKey80211;

/*!
	@const kAirPortAuthTypeKeyPort
	@discussion 32 bit number containing a vector of AirPortPortAuthTypeFlags for which the interface is currently configured.
*/

extern CFStringRef const kAirPortAuthTypeKeyPort;

#pragma mark -
#pragma mark Association Argument Dictionary Keys

/*! @group Association Argument Dictionary Keys */

/*!
	@const kAirPortAssocKeyPassPhrase
	@discussion CFString containing network pass phrase or key. If not present, then it is assumed that the network either does not require a key, or that the key will be obtained via an 802.1x authentication.
*/

extern CFStringRef const kAirPortAssocKeyPassPhrase;

/*!
	@const kAirPortAssocKeyRemember
	@discussion CFBoolean. Indicates whether or not network should be remembered in the user's preferences. If not present, defaults to false.
*/

extern CFStringRef const kAirPortAssocKeyRemember;

/*!
	@const kAirPortAssocKey8021XProfile
	@discussion CFDictionaryRef. The 802.1x profile used to join the network.
 */

extern CFStringRef const kAirPortAssocKey8021XProfile;

#pragma mark -
#pragma mark Association 802.1x Profile Keys

/*! @group Association 802.1x Profile Keys */

/*!
 @const kAirPortAssocKey8021XUserName
 @discussion CFStringRef. The 802.1x profile user name used to join the network.
 */

extern CFStringRef const kAirPortAssocKey8021XUserName;

/*!
 @const kAirPortAssocKey8021XPassword
 @discussion CFStringRef. The 802.1x profile password used to join the network.
 */

extern CFStringRef const kAirPortAssocKey8021XPassword;

/*!
 @const kAirPortAssocKey8021XUserPasswordKeychainItemID
 @discussion CFStringRef. The 802.1x profile password keychain id used to join the network.
 */

extern CFStringRef const kAirPortAssocKey8021XUserPasswordKeychainItemID;

/*!
 @const kAirPortAssocKey8021XOneTimePassword
 @discussion CFBooleanRef. The 802.1x one time password preference, defaults to false.
 */

extern CFStringRef const kAirPortAssocKey8021XOneTimePassword;

/*!
 @const kAirPortAssocKey8021XAcceptEAPTypes
 @discussion CFArrayRef of CFNumberRefs. The 802.1x EAP types supported for this connection.
 */

extern CFStringRef const kAirPortAssocKey8021XAcceptEAPTypes;


#pragma mark -
#pragma mark IBSS Creation Parameter Dictionary Keys

/*! @group IBSS Creation Parameter Dictionary Keys */

/*!
	@const kAirPortIBSSKeySSID
	@discussion UTF8 encoded CFString containing the SSID of the network to be created.
*/

extern CFStringRef const kAirPortIBSSKeySSID;

/*!
	@const kAirPortIBSSKeyChannel
	@discussion 32 bit number containing channel number on which IBSS network should be created.
*/

extern CFStringRef const kAirPortIBSSKeyChannel;

/*!
	@const kAirPortIBSSKeyCipherKey
	@discussion UTF8 encoded string containing network cipher key. At this time only 40 and 104 bit WEP modes are supported. Cipher mode is inferred from the length of the string. A cipher key that is 5 characters or 10 hex characters corresponds to a 40 bit WEP key. A cipher key that is 13 characters or 26 hex characters corresponds to a 104 bit WEP key. If this key is not present, then no cipher key will be used on the network.
*/

extern CFStringRef const kAirPortIBSSKeyCipherKey;

#pragma mark -
#pragma mark Scan Result Dictionary Keys

/*! @group Scan Result Dictionary Keys */

/*!
	@const kAirPortScanResultKeySSID
	@discussion CFData containing SSID bytes.
*/

extern CFStringRef const kAirPortScanResultKeySSID;

/*!
	@const kAirPortScanResultKeySSID_Str
	@discussion UTF8 string interpretation of SSID.
*/

extern CFStringRef const kAirPortScanResultKeySSID_Str;

/*!
	@const kAirPortScanResultKeyBSSID
	@discussion String interpretation of BSSID.
*/

extern CFStringRef const kAirPortScanResultKeyBSSID;

/*!
	@const kAirPortScanResultKeyRSSI
	@discussion 16 bit signed number.
*/

extern CFStringRef const kAirPortScanResultKeyRSSI;

/*!
	@const kAirPortScanResultKeyNoise
	@discussion 16 bit signed number.
*/

extern CFStringRef const kAirPortScanResultKeyNoise;

/*!
	@const kAirPortScanResultKeyChannel
	@discussion 32 bit number.
*/

extern CFStringRef const kAirPortScanResultKeyChannel;

/*!
	@const kAirPortScanResultKeyChannelFlags
	@discussion 32 bit number. See AirPortVar.h.
*/

extern CFStringRef const kAirPortScanResultKeyChannelFlags;

/*!
	@const kAirPortScanResultKeyBeaconInt
	@discussion 16 bit number.
*/

extern CFStringRef const kAirPortScanResultKeyBeaconInt;

/*!
	@const kAirPortScanResultKeyAP_Mode
	@discussion 16 bit number. See AirPortVar.h.
*/

extern CFStringRef const kAirPortScanResultKeyAP_Mode;

/*!
	@const kAirPortScanResultKeyRateSet
	@discussion Array of 32 bit numbers.
*/

extern CFStringRef const kAirPortScanResultKeyRateSet;

/*!
	@const kAirPortScanResultKeyIE_List
	@discussion CFData of IE data included in beacon or probe response.
*/

extern CFStringRef const kAirPortScanResultKeyIE_List;

/*!
	@const kAirPortScanResultKeyWEP
	@discussion Boolean.
*/

extern CFStringRef const kAirPortScanResultKeyWEP;

/*!
	@const kAirPortScanResultKeySecurityType
	@discussion CFStringRef with a human readable security type
*/
extern CFStringRef const kAirPortScanResultKeySecurityType;

/*!
	@const kAirPortScanResultKeyHT
	@discussion Boolean. True if HT IEs present, false otherwise.
*/

extern CFStringRef const kAirPortScanResultKeyHT;

/*!
	@const kAirPortScanResultKeyAge
	@discussion 32 bit number. Age of scan result in ms.
*/

extern CFStringRef const kAirPortScanResultKeyAge;

#pragma mark -
#pragma mark Information Element Dictionary Keys

/*! @group Information Element Dictionary Keys */

// WPA Information Element

/*!
	@const kAirPortScanResultKeyWPA_IE
	@discussion CFDictionary
*/

extern CFStringRef const kAirPortScanResultKeyWPA_IE;

/*!
	@const kAirPortIEKeyWPAVersion
	@discussion 16 bit integer
*/

extern CFStringRef const kAirPortIEKeyWPAVersion;

/*!
	@const kAirPortIEKeyWPA_MCipher
	@discussion 32 bit integer
*/

extern CFStringRef const kAirPortIEKeyWPA_MCipher;

/*!
	@const kAirPortIEKeyWPA_UCiphers
	@discussion Array of 32 bit integers
*/

extern CFStringRef const kAirPortIEKeyWPA_UCiphers;

/*!
	@const kAirPortIEKeyWPA_AuthSels
	@discussion Array of 32 bit integers
*/

extern CFStringRef const kAirPortIEKeyWPA_AuthSels;

// RSN (WPA2) Information Element

/*!
	@const kAirPortScanResultRSN_IE
	@discussion CFDictionary
*/

extern CFStringRef const kAirPortScanResultKeyRSN_IE;

/*!
	@const kAirPortIEKeyRSNVersion
	@discussion 16 bit integer
*/

extern CFStringRef const kAirPortIEKeyRSNVersion;

/*!
	@const kAirPortIEKeyRSN_MCipher
	@discussion 32 bit integer
*/

extern CFStringRef const kAirPortIEKeyRSN_MCipher;

/*!
	@const kAirPortIEKeyRSN_UCiphers
	@discussion Array of 32 bit integers
*/

extern CFStringRef const kAirPortIEKeyRSN_UCiphers;

/*!
	@const kAirPortIEKeyRSN_AuthSels
	@discussion Array of 32 bit integers
*/

extern CFStringRef const kAirPortIEKeyRSN_AuthSels;

// 802.11d

/*!
	@const kAirPortScanResultKey80211dIE
	@discussion CFDictionary
*/

extern CFStringRef const kAirPortScanResultKey80211dIE;

/*!
	@const kAirPortIEKey80211dCountryCode
	@discussion CFString
*/

extern CFStringRef const kAirPortIEKey80211dCountryCode;

/*!
	@const kAirPortIEKey80211dChannelInfo
	@discussion Array of channel information dictionaries.
*/

extern CFStringRef const kAirPortIEKey80211dChannelInfo;

// 802.11d channel information dictionary keys

/*!
	@const kAirPortIEKey80211dFirstChannel
	@discussion 32 bit number.
*/

extern CFStringRef const kAirPortIEKey80211dFirstChannel;

/*!
	@const kAirPortIEKey80211dNumChannels
	@discussion 32 bit number.
*/

extern CFStringRef const kAirPortIEKey80211dNumChannels;

/*!
	@const kAirPortIEKey80211dMaxPower
	@discussion 32 bit number.
*/

extern CFStringRef const kAirPortIEKey80211dMaxPower;

#pragma mark -
#pragma mark AirPort Preferences Keys

/*!
 @group AirPort Prefs Dictionary Keys
 @discussion For use with AirPortCopyPreference(...) and AirPortSetPreference(...)
 */

/*!
 @const kAirPortPrefJoinMode
 @discussion CFStringRef
 */

extern CFStringRef const kAirPortPrefJoinMode;

/*!
 @const kAirPortPrefJoinModeFallbacks
 @discussion CFArrayRef
 */

extern CFStringRef const kAirPortPrefJoinModeFallbacks;

/*!
 @const kAirPortPrefPreferredNetworks
 @discussion CFArrayRef - read-only
 */

extern CFStringRef const kAirPortPrefPreferredNetworks;

/*!
 @const kAirPortPrefDisconnectOnLogout
 @discussion CFBooleanRef
 */

extern CFStringRef const kAirPortPrefDisconnectOnLogout;


#endif /* _AIRPORTKEYS_H_ */
