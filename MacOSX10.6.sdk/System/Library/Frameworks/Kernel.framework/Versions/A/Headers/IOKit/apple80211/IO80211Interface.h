/*
 * Copyright (c) 2005 Apple Computer, Inc. All rights reserved.
 *
 * @APPLE_LICENSE_HEADER_START@
 * 
 * The contents of this file constitute Original Code as defined in and
 * are subject to the Apple Public Source License Version 1.1 (the
 * "License").  You may not use this file except in compliance with the
 * License.  Please obtain a copy of the License at
 * http://www.apple.com/publicsource and read it before using this file.
 * 
 * This Original Code and all software distributed under the License are
 * distributed on an "AS IS" basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE OR NON-INFRINGEMENT.  Please see the
 * License for the specific language governing rights and limitations
 * under the License.
 * 
 * @APPLE_LICENSE_HEADER_END@
 */

#ifndef _IO80211INTERFACE_H
#define _IO80211INTERFACE_H

/*
 * Kernel
 */
#if defined(KERNEL) && defined(__cplusplus)

#include <libkern/version.h>

#if VERSION_MAJOR > 8
	#define _MODERN_BPF
#endif

#include <IOKit/network/IOEthernetInterface.h>
#include <net/if_var.h>
#include <sys/queue.h>

/*! @enum IO80211LinkState.
    @abstract Link states of IO80211Interfaces.
	@constant kIO80211NetworkLinkUndefined Starting link state when an interface is created.
	@constant kIO80211NetworkLinkDown Interface not capable of transmitting packets.
	@constant kIO80211NetworkLinkUp Interface capable of transmitting packets.
	*/
enum IO80211LinkState
{
	kIO80211NetworkLinkUndefined,
	kIO80211NetworkLinkDown,
	kIO80211NetworkLinkUp,
};
typedef enum IO80211LinkState IO80211LinkState;

/*!	@defined kIO80211InterfaceClass
	@abstract The name of the IO80211Interface class. 
	*/
#define kIO80211InterfaceClass     "IO80211Interface"

class RSNSupplicant;
class IOTimerEventSource;
class IOGatedOutputQueue;
class IO80211Controller;
class IO80211ScanManager;

struct rsn_pmksa_node;

/*!	@class IO80211Interface
	@abstract The 802.11 interface object. 
	@discussion An 802.11 controller driver, that is a subclass of IOEthernetController, will instantiate an object of this class when the driver calls the attachInterface() method.
				This interface object will then send an Ethernet interface to DLIL, and manage the connection between the controller driver and the upper networking layers.
				Drivers will seldom need to subclass IO80211Interface. 
	*/
class IO80211Interface : public IOEthernetInterface
{
	OSDeclareDefaultStructors( IO80211Interface );
	
public:
	
	/*!	@function init
		@abstract Initializes an IO80211Interface instance.
		@discussion Instance variables are initialized, and a reference to the controller is retained. The interface queries the controller
					to determine if WME, short GI in 20 Mhz, and short GI in 40 MHz are supported. Output queue(s) for the interface are
					allocated
		@param controller An IO80211Controller object that will service the interface object being initialized.
		@result Returns true on success, false otherwise. 
		*/
	virtual bool init( IONetworkController * controller );
	
	/*! @function free
		@abstract Frees the IO80211Interface instance.
		@discussion All memory allocated by the IO80211Interface class is freed, followed by a call to super::free().
		*/
	virtual void free();
	
	/*! @function attachToDataLinkLayer
		@abstract Attaches the network interface to the data link layer.
		@discussion After the interface's ifnet has been allocated and attached, the IO80211Interface code will create a character
					device for passing 802.11 events from this interface to userland, add the Apple wireless stats protocol multicast
					address to the interface's multicast list, add static properties for the interface to the IORegistry, and setup code
					for handling scan requests made to the interface.
		@result Returns kIOReturnSuccess on success.
		*/
	virtual IOReturn	attachToDataLinkLayer(IOOptionBits	options,
											  void			*parameter);
											
	/*! @function detachFromDataLinkLayer
		@abstract Detaches the network interface from the data link layer.
		@discussion Releases memory allocated by attachToDataLinkLayer.
		*/
	virtual void		detachFromDataLinkLayer(IOOptionBits options,
												void		*parameter);
												
	/*! @function inputEvent
		@abstract Sends an event to the data link layer.
		@discussion This method can be used by the network controller to
					send an event to the data link layer.
		@param type A constant describing the event type.
		@param data Data associated with the event.
		@result Returns true if the event was delivered, false if the event type
				specified is invalid, or if the event delivery was unsuccesful. 
		*/
	virtual bool inputEvent(UInt32 type, void * data);
										  
	/*! @function setPoweredOnByUser
		@abstract Used to remember if this interface is powered on across sleep/wake.
		@discussion This method should only be called by the IO80211Controller. Subclass drivers should not use it.
		@param poweredOn true if the interface has been powered on, false otherwise.
		*/
	virtual void setPoweredOnByUser( bool poweredOn );

	/*! @function poweredOnByUser
		@abstract Indicates whether or not the interface should be powered on after a wake from sleep event.
		@discussion This method should only be called by the IO80211Family. Subclass drivers should not use it.
		@result true if the interface should be powered on, false otherwise.
		*/
	bool poweredOnByUser();
	
	/*! @function setEnabledBySystem
		@abstract Used to remember whether this interface has been enabled.
		@discussion This method should only be called by the IO80211Family. Subclass drivers should not use it.
		@param systemEnabled true if interface has been enabled by the system, false otherwise.
		*/
	virtual void setEnabledBySystem( bool systemEnabled );

	/*! @function enabledBySystem
		@abstract Indicates whether or not the interface has been enabled by the system.
		@result true if the interface has been enabled, false otherwise.
		*/
	bool enabledBySystem();

	/*! @function postMessage
		@abstract Used by subclass drivers to indicate when an 802.11 event has occured on the interface.
		@param msg The event, as defined in apple80211_var.h, that has occurred.
		@param data An optional data buffer to be included with the event.
		@param dataLen The length of the data buffer included with the event.
		*/
	void postMessage( UInt32 msg, void * data = NULL, size_t dataLen = 0 );
	
	/*! @function setAuthTimeout
		@abstract Used to set an authentication timeout limit when associating to WPA/WPA2 networks.
		@discussion This method should only be used by the IO80211Family.
		@param timeout The clock time (in seconds) in the future when authentication will be considered timed out.
		*/
	void setAuthTimeout( unsigned int timeout );
	
	/*! @function authTimeout
		@abstract Used to determine when WPA/WPA2 authentication has timed out on the interface.
		@result Returns the clock time (in seconds) when authentication will be considered timed out.
		*/
	unsigned int authTimeout();
	
	/*! @function setLinkState
		@abstract Used by subclass drivers to indicate when an interface is capable or no longer capable of sending packets.
		@param linkState kIO80211NetworkLinkUp if the interface is capable of sending and receiving packets, kIO80211NetworkLinkDown
			   if it is not.
		@result true if link state has been successfully updated to the requested value, false otherwise.
		*/
	virtual bool setLinkState( IO80211LinkState linkState );
	
	/*! @function linkState
		@abstract Used to determine an interface's current link state.
		@result Returns kIO80211NetworkLinkUndefined if the interface's link state is not know, otherwise kIO80211NetworkLinkUp or
				kIO80211NetworkLinkDown.
		*/
	IO80211LinkState linkState();
	
	/*! @function initSupplicant
		@abstract Allocates and initializes a supplicant instance for the interface.
		@discussion When an association request is issued to a WPA network, and IO80211Controller::useAppleRSNSupplicant() has indicated
					that this interface will use the Apple RSN supplicant, a supplicant instance is allocated and initialized with the WPA
					IE used in the association request. This method should be called only by the IO80211Family.
		@result true if successful, false otherwise.
		*/
	bool initSupplicant( UInt8 * ie );
	
	/*! @function terminateSupplicant
		@abstract Stops and frees the interface's supplicant instance.
		@discussion This method should only be called by the IO80211Family.
		*/
	void terminateSupplicant();
	
	/*! @function resetSupplicant
		@abstract Resets supplicant state such that it is ready to start a handshake using the same parameters with which it was configured.
		@discussion This method should only be called by the IO80211Family.
		*/
	void resetSupplicant();
	
	/*! @function setPMK
		@abstract Used to pass a PMK to the interface's RSN supplicant.
		@discussion This method should only be called by the IO80211Family.
		@result true if successful, false otherwise. 
		*/
	bool setPMK( UInt8 * pmk );
	
	/*! @function supplicantExchangeComplete
		@abstract Used to determine when a PTK and GTK has been received by the interface's supplicant from the authenticator.
		@result true if both a PTK and GTK have been received, false otherwise.
		*/
	bool supplicantExchangeComplete();
	
	/*! @function supplicantInitialized
		@abstract Used to determine if a supplicant has been allocated by the interface.
		@discussion true if a supplicant has been allocated, false otherwise.
		*/
	bool supplicantInitialized();
	
	/*! @function outputEAPOLFrame
		@abstract Used by the Apple RSN supplicant to output EAPOL frames.
		@discussion This method will feed packets generated by the Apple RSN supplicant to BPF, and then pass them to IO80211Controller::outputPacket().
		@param m The EAPOL packet being sent.
		@result The value returned by IO80211Controller::outputPacket().
		*/
	UInt32 outputEAPOLFrame( mbuf_t m );
	
	/*! @function cachePMKSA
		@abstract Used by the Apple RSN supplicant to cache PMK security associations.
		@discussion The interface's PMK cache will be cleared of stale entries before the new PMKSA is cached. This method should only
					be called by the IO80211Family.
		@param pmk The pairwise master key.
		@param pmkLen The length of the pairwise master key.
		@param aa The authenticator's ethernet address.
		@param pmkID The PMK ID generated for this association by the Apple supplicant.
		*/
	void cachePMKSA( UInt8 * pmk, size_t pmkLen, struct ether_addr * aa, UInt8 * pmkID );
	
	/*! @function cachePMKSA
		@abstract Used to generate and cache PMK IDs if a userland supplicant is doing RSN pre-authentication.
		@discussion The interface's PMK cache will be cleared of stale entries before the new PMKSA is cached. This method should only
					be called by the IO80211Family.
		@param pmk The pairwise master key.
		@param pmkLen The length of the pairwise master key.
		@param aa The authenticator's ethernet address.
		*/
	SInt32 cachePMKSA( UInt8 * pmk, size_t pmkLen, struct ether_addr * authenticatorEA );
	
	/*! @function pmksaLookup
		@abstract Searches for a cached PMK security association.
		@discussion The interface's PMK cache will be cleared of stale entries before the search is performed. A search may be performed
					using just an authenticator ethernet address or just a PMK ID.
		@param authenticatorEA The ethernet address of the authenticator (may be NULL).
		@param The PMK ID received in PTK 1/4 from the authenticator (may be NULL).
		@result A pointer to a PMKSA information structure if the PMKID is cached for the specified authenticator, or NULL otherwise.
		*/
	struct rsn_pmksa_node * pmksaLookup( struct ether_addr * authenticatorEA, UInt8 * pmkID );
	
	/*! @function shouldRoam
		@abstract Inspects scan result structure to determine if WPA parameters are compatible with current Apple supplicant configuration.
		@discussion The shouldRoam method provides the IO80211Family an opportunity to reject an AP that is a candidate for a roam attempt.
					At this time, the method only inspects the scan record when in WPA/WPA2 mode and the Apple supplicant is in use. If operating
					in WEP or no security mode, or when the subclass driver is using an internal WPA supplicant, the family leaves the selection of
					APs for roam attempts up to the subclass driver.
		@param asr The scan record of an access point the subclass driver is considering as a candidate for a roam attempt.
		@result If operating in WEP or no security mode, or WPA/WPA2 mode but not using the Apple supplicant, true. If operating in WPA/WPA2 mode and
				using the Apple RSN supplicant, true if the scan record of the candidate AP is compatible with the supplicant's current configuration,
				false otherwise.
		*/
	bool shouldRoam( struct apple80211_scan_result * asr );
	
	/*! @function willRoam
		@abstract Gives the Apple supplicant an opportunity to reset itself and update IE configuration in the event of a roam.
		@discussion willRoam is used to reset the Apple supplicant back to a state where it is expecting to receive PTK 1/4. If using
					WPA2 enterprise, and a PMKSA is cached for the target AP, the WPA2 IE to be sent by the subclass driver in the association request
					is updated using APPLE80211_IOC_RSN_IE.
		@param bssid The BSSID of the AP which has been selected by the subclass driver for a roam attempt.
		*/
	void willRoam( struct ether_addr * bssid );
	
	/*! @function inputPacket
		@abstract Submits a single packet received from the network to the data link layer.
		@discussion The packet will be inspected to determine if it is possibly an Apple wireless stats or WPA/WPA2 EAPOL frame.
					If so, it will be passed to the appropriate handler before being sent up the stack. See also IONetworkInterface.h.
		@param m The mbuf containing the received packet.
		@param length Specify the size of the received packet in the mbuf.
			   The mbuf length fields are updated with this value. If zero,
			   then the mbuf length fields are not updated.
		@param options Options defined by inputPacket() that the caller
			   can use to specify this method call.
		@param param A parameter provided by the caller. Not used by
			   IONetworkInterface.
		@result Returns the number of packets that were submitted to the data link layer,
				or 0 if the packet was queued. 
		*/
	virtual UInt32 inputPacket(mbuf_t m,
                               UInt32        length  = 0,
                               IOOptionBits  options = 0,
                               void *        param   = 0);
	
	/*! @function outputPacket
		@abstract Output action for all output queues created by the IO80211Interface.
		@discussion If WME_QUEUES is not defined and WME is supported by the interface, then packets will be tagged with the appropriate access category
					before being passed to IO80211Controller::outputPacket().
		@param m An mbuf chain containing the output packet to be sent on the network.
		@param param A parameter provided by the caller.
		@result Returns the value returned by IO80211Controller::outputPacket().
		*/						   
	virtual UInt32	outputPacket( mbuf_t m, void * param );
	
	/*! @function getBSDName
		@abstract Retrieves a pointer to a string that is the concatenation of the interface name and unit.
		@result The name of the interface as it appears in programs like ifconfig.
		*/
	const char * getBSDName();
	
	/*! @function getStatusDevName
		@abstract Retrieves a pointer to a string that contains the name of the 802.11 event status device associated with the interface. This device
				  is located in /dev.
		@result The name of the character device associated with the interface.
		*/
	char * getStatusDevName();
	
	/*! @function setCountermeasuresTimer
		@abstract Used by the Apple RSN supplicant to store a reference to a timer created when the interface enters TKIP countermeasures mode.
		@discussion When two MIC errors are reported by the subclass driver in less than 60 seconds, the interface enters TKIP countermeasures mode
					for one minute. The countermeasures timer is used to exit TKIP countermeasures mode after this one minute time period has expired.
					The timer is stored by the interface class because the RSN supplicant may be terminted before the TKIP countermeasures period has
					expired. This method should only be used by the IO80211Family. 
		@param timer Timer object created by the Apple RSN supplicant for the purposes of exiting TKIP countermeasures mode after one minute.
		*/
	void setCountermeasuresTimer( IOTimerEventSource * timer );
	
	/*! @function stopCountermeasures
		@abstract Timer action method for exiting TKIP countermeasures mode.
		@discussion When the TKIP countermeasures timer expires, this method is called to inform the subclass driver and Apple RSN supplicant that
					TKIP countermeasures are no longer in effect.
		@param owner Not used.
		@param sender Not used.
		*/
	static void stopCountermeasures( OSObject *owner, IOTimerEventSource *sender );
	
	/*! @function updateChannelProperty
		@abstract Updates interface's channel, extension channel, and channel band properties in the IO registry.
		@discussion This method should only be used by the IO80211Family.
		*/
	void updateChannelProperty();
	
	/*! @function updateSSIDProperty
		@abstract Updates interface's SSID property in the IO registry.
		@discussion This method should only be used by the IO80211Family.
		*/
	void updateSSIDProperty();
	
	/*! @function updateStaticProperties
		@abstract Places the interface's hardware and driver versions, locale, and default country code in the IO registry.
		@discussion This method is only called once and should only be used by the IO80211Family. 
		*/
	void updateStaticProperties();
	
	/*! @function updateCountryCodeProperty
		@abstract If a country code is active, the country code property is updated in the IO registry. If a country code is not
				  active, the property is removed from the IO registry.
		@discussion This method should only be called by the IO80211Family.
		*/
	void updateCountryCodeProperty( bool shouldLog );
	
	/*! @function configureAntennae
		@abstract Performs platform specific antenna configuration.
		@discussion This method is used by the IO80211Family to configure the antennae of wireless cards on older systems where platform
					specific antenna information is included in the IO registery. This method should only be used by the IO80211Family.
		*/
	void configureAntennae();
	
	/*! @function setDebugFlags
		@abstract Configures IO80211Family debug logging.
		@discussion This method configures a vector of apple80211_debug_flags (as defined in apple80211_var.h). This vector is used
					by the IO80211Family on a per-interface basis to determine what information should be logged.
		@param debugFlags A vector of apple80211_debug_flags.
		*/
	void setDebugFlags( UInt32 debugFlags );
	
	/*! @function debugFlags
		@abstract Retrieves interface's IO80211Family specific debug flags.
		@result A vector of apple80211_debug_flags (as defined in apple80211_var.h).
		*/
	UInt32 debugFlags();
	
	/*! @function getOutputQueue
		@abstract Retrieves interface's best effort output queue.
		@result If WME_QUEUES is defined, the interface's best effort output queue will be returned. If WME_QUEUES is not defined,
				the interface's only output queue will be returned.
		*/
	IOGatedOutputQueue * getOutputQueue();
	
	/*! @function bpfAttach
		@abstract Allows subclass drivers to attach to BPF with more than one data link type.
		@discussion If a subclass driver supports data link types other than EN10MB, it may register support for these DLTs with BPF
					by calling this method.
		*/
	errno_t	bpfAttach( UInt32 dlt, UInt32 headerLen );
	
	/*! @function monitorModeInputPacket
		@abstract Passes monitor mode frames to BPF.
		@discussion This method is used by subclass drivers to pass monitor mode frames to BPF after an 802.11 specific data link type
					has been enabled through IO80211Controller::monitorModeSetEnabled().
		@result Returns 0 if successful, otherwise an appropriate errno value.
		*/
	errno_t	monitorModeInputPacket( mbuf_t m, UInt32 dlt, void * header, size_t header_len );

	/*! @function get80211OutputQueue
		@abstract Retrieves output queue used by IO80211Family to queue raw 802.11 frames.
		@discussion This method should only be used by the IO80211Family. The 802.11 frame output queue is created when a driver attaches
					to BPF with DLT_IEEE802_11. Frames queued to this output queue will eventually be passed to the subclass driver using
					IO80211Controller::outputRaw80211Packet().
		@result Output queue used specifically for fully formed 802.11 frames passed down through BPF.
		*/
	IOGatedOutputQueue * get80211OutputQueue();

	/*! @function output80211Packet
		@abstract IOOutputAction for 802.11 frame queue.
		@discussion This method should only be used by the IO80211Family.
		@param m Mbuf chain received from BPF.
		@param param Unused.
		*/
	virtual UInt32 output80211Packet( mbuf_t m, void * param );
	
#ifdef WME_QUEUES
	
	/* When WME_QUEUES is defined, the IO80211Interface class will create one IOOutputQueue for each WME access category. Subclass drivers
	   may control the output queue for each access category individually. For example, if your driver is getting overloaded with best effort
	   packets, it may stop the interface's best effort queue while still allowing frames from the voice and video queues through. 
	*/

	/*! @function getWMEBestEffortQueue
		@abstract Accessor for interface's best effort access category output queue.
		@result Returns output queue for packets mapped to WME best effort category by IO80211Family.
		*/
	IOGatedOutputQueue * getWMEBestEffortQueue() { return _outputQueue; }
	
	/*! @function getWMEBackgroundQueue
		@abstract Accessor for interface's background access category output queue.
		@result Returns output queue for packets mapped to WME background category by IO80211Family.
		*/
	IOGatedOutputQueue * getWMEBackgroundQueue() { return _queueBackground; }
	
	/*! @function getWMEVoiceQueue
		@abstract Accessor for interface's voice access category output queue.
		@result Returns output queue for packets mapped to WME voice category by IO80211Family.
		*/
	IOGatedOutputQueue * getWMEVoiceQueue()	{ return _queueVoice; }
	
	/*! @function getWMEVideoQueue
		@abstract Accessor for interface's video access category output queue.
		@result Returns output queue for packets mapped to WME video category by IO80211Family.
		*/
	IOGatedOutputQueue * getWMEVideoQueue() { return _queueVideo; }
	
	/*! @function wmeSupported
		@abstract Indicates whether or not WME is supported by the interface.
		@discussion The _wmeSupported flag is set when the interface is initialized if the APPLE80211_CAP_WME flag is included in the
					capabilities list returned by an APPLE80211_IOC_CARD_CAPABILITIES query.
		@result true if WME is supported by the interface, false otherwise.
		*/
	bool wmeSupported() { return _wmeSupported; }
	
	/*! @function queueWMEPacket
		@abstract Interface output handler.
		@discussion When multiple output queues are managed by the interface, this method is responsible for receiving a packet from DLIL,
					determining packet access category, and then sending the frame to the appropriate output queue. Access category is
					determined by examing the IP TOS/traffic class field, and using criteria defined by the WiFi WMM Test Plan v1.3.1 to
					categorize the packet. Non-IP packets default to the best effort queue.
	    @param m A packet mbuf.
		@param param A parameter for the output request.
		@result Always returns 0.
		*/
	UInt32 queueWMEPacket( mbuf_t m, void * param );
	
	/*! @function getWMEOutputHandler
		@abstract Accessor for interface's output handler.
		@result Pointer to the interface's output handler function.
		*/
	IOOutputAction getWMEOutputHandler() { return (IOOutputAction)&IO80211Interface::queueWMEPacket; }
	
	/*! @function startOutputQueues
		@abstract Starts all of the interface's output queues.
		@discussion The best effort, background, voice, and video output queues are configured with a capacity of 256 and started.
		*/
	void startOutputQueues();
	
	/*! @function stopOutputQueues
		@abstract Stops all of the interface's output queues.
		@discussion The best effort, background, voice, and video output queues are stopped, flushed, and configured with a capacity
					of 0.
		*/
	void stopOutputQueues();

#endif /* WME_QUEUES */

	/*! @function shortGISupported40MHz
		@abstract Indicates whether or not short guard interval is supported when utilizing 40 MHz channels.
		@discussion Support is determined by querying the capabilities list of the interface for APPLE80211_CAP_SHORT_GI_40MHZ
					when the interface is initialized.
		@result Returns true if short guard interval is supported on 40 MHz channels, false otherwise.
		*/
	bool shortGISupported40MHz() { return _shortGISupported40MHz; }
	
	/*! @function shortGISupported20MHz
		@abstract Indicates whether or not short guard interval is supported when utilizing 20 MHz channels.
		@discussion Support is determined by querying the capabilities list of the interface for APPLE80211_CAP_SHORT_GI_20MHZ
					when the interface is initialized.
		@result Returns true if short guard interval is supported on 20 MHz channels, false otherwise.
		*/
	bool shortGISupported20MHz() { return _shortGISupported20MHz; }
	
	/*! @function getScanManager
		@abstract Retrieves per interface scan manager object.
		@discussion Each IO80211Interface allocates an IO80211ScanManager object for coalescing scan requests and managing
					scan caches. This object maybe accessed through this method.
		@result The interface's IO80211ScanManager object.
		*/
	IO80211ScanManager * getScanManager() { return _scanManager; }
	
	/*! @function setWoWEnabled
		@abstract Enables or disables wake on wireless for the interface.
		@discussion If wake on wireless is enabled for the interface, the subclass driver will be put into WoW mode the next
					time the system goes to sleep while the interface is participating in a network. This method should only be
					used by the IO80211Family.
		@param enabled If true, WoW is enabled for the interface. If false, WoW is disabled.
		*/
	void setWoWEnabled( bool enabled ) { _wowEnabled = enabled; }
	
	/*! @function wowEnabled
		@abstract Indicates whether or not wake on wireless is enabled for the interface.
		@discussion This method should only be used by the IO80211Family.
		@result If wake on wireless is enabled, true, otherwise false.
		*/
	bool wowEnabled() { return _wowEnabled; }
	
	/*! @function setBPFCallbackPending
		@abstract Sets flag to avoid deadlocks with BPF.
		@discussion The BPF callback pending flag must be set in order to avoid deadlocks with BPF. If BPF is making a call into
					the driver, the driver cannot make a call into BPF at the same time.
		@param pending If true, a BPF callback is running through the command gate. If false, the BPF callback has exited the command
					   gate.
		*/
	void setBPFCallbackPending( bool pending ) { _bpfCallbackPending = pending; }
		
	// Used internally by IO80211Family
	static IOReturn monitorCallbackGated( OSObject *owner, void * arg0, void * arg1, void *arg2, void *arg3 );
	
protected:
	
	/*!	@function performCommand
		@abstract Handles an ioctl command sent to the Ethernet interface.
		@discussion This method handles socket ioctl commands sent to the Ethernet interface from DLIL. Commands recognized and processed by this method are SIOCSIFADDR, SIOCSIFFLAGS, SIOCADDMULTI, and SIOCDELMULTI. Other commands are passed to the superclass.
		@param controller The controller object.
		@param cmd The ioctl command code.
		@param arg0 Command argument 0. Generally a pointer to an ifnet structure associated with the interface.
		@param arg1 Command argument 1.
		@result Returns a BSD return value defined in bsd/sys/errno.h. 
		*/
	virtual SInt32		performCommand(IONetworkController	*controller,
									   UInt32				cmd,
									   void					*arg0,
									   void					*arg1);
	
	// Used internally by IO80211Family
	static IOReturn	performCountryCodeOpGated( OSObject * owner, void * inInterface, void * inParams, void *arg2, void *arg3 );
	static int performGatedCommand( void * target, void * ctr, void * cmd, void * ifp, void * req );
	static IOReturn powerChangeHandler( void * target, void * refCon, UInt32 messageType,
										IOService * service, void * messageArgument, vm_size_t argSize );
	
private:
	
	/*! @function inputAWSPacket
		@abstract Entry point for Apple wireless stats processing.
		@discussion Ethernet packets with an 'ether_type' field less than or equal to 1514 are passed to this method for processing. If the
					packet is a valid Apple wireless stats frame, it is processed. If the packet is not an Apple wireless stats frame, it is
					ignored.
		@param m Packet passed up from subclass driver.
		*/
	void inputAWSPacket( mbuf_t m );
	
	/*! @function awsRespond
		@abstract Builds reponse to Apple wireless stats query and places it on the output queue.
		@discussion This method queries the subclass driver for any information requested by the wireless stats packet, builds a response,
					and sends it to the interface's best effort queue.
		@param m The packet passed to inputAWSPacket.
		@param requestList A pointer to the start of the AWS request list.
		@param numRequests The number of requests in the requestList.
		@param packetID The ID found in the AWS header of the packet passed to inputAWSPacket.
		*/
	void awsRespond( mbuf_t m, struct AWSRequest * requestList, size_t numRequests, UInt16 packetID );
	
	/*! @function purgePMKSACache
		@abstract Removes PMKSA structures from PMKSA list that have expired.
		@discussion This method is called whenever a PMKSA is cached or a look up is requested.
		*/
	void purgePMKSACache();
	
	/*! @function freePMKSACache
		@abstract Frees all entries in the PMKSA cache list.
		*/
	void freePMKSACache();
	
	/*! @function createStatusDevice
		@abstract Creates a status device for 802.11 events that are posted to this interface.
		@discussion A character device is created for each interface in /dev that is responsible for passing 802.11 specific events to
					userland applications. Each device has a unique name created by appending a number to the end of the name string passed
					to this method.
		@param name The name prefix of the character device that will be created in /dev. The name is retrieved from the subclass driver using
					APPLE80211_IOC_STATUS_DEV_NAME.
		@result kIOReturnSuccess or an error code.
		*/
	IOReturn createStatusDevice( char * name );
	
	int			_minor;
	u_int32_t	_devUnit;
	char *		_statusDevName;
	size_t		_statusDevNameLen;
	
	bool		_poweredOnByUser;
	bool		_enabledBySystem;	// IFF_UP flag set?
	
	unsigned int	_authTimeout;
	
	IO80211LinkState _linkState;
	bool			 _pendingLinkEvent;
	
	RSNSupplicant * _rsnSupplicant;
	
	ifmultiaddr_t	_awsAddr;
	
	IOTimerEventSource * _countermeasuresTimer;
	
	char _bsdName[IFNAMSIZ];
	
	LIST_HEAD( , rsn_pmksa_node ) _pmksaCacheHead;
	
	IONotifier * _powerChangeNotifier;
	
	UInt32	_debugFlags;
	
	IOGatedOutputQueue * _outputQueue;
	
	IOGatedOutputQueue * _80211outputQueue;
	
	IO80211Controller * _controller;
	
	void * _llAddr;
	UInt8 _ifiType;
	
	bool _wmeSupported;
	bool _shortGISupported40MHz;
	bool _shortGISupported20MHz;
	
#ifdef WME_QUEUES
	IOGatedOutputQueue * _queueBackground;
	IOGatedOutputQueue * _queueVoice;
	IOGatedOutputQueue * _queueVideo;
#endif /* WME_QUEUES */

	IO80211ScanManager * _scanManager;
	
	bool _wowEnabled;
	
	bool _bpfCallbackPending;
		
	struct ExpansionData {};
	struct ExpansionData * _reserved;
	
public:

	// Virtual function padding
	
	OSMetaClassDeclareReservedUnused( IO80211Interface,  0);
	OSMetaClassDeclareReservedUnused( IO80211Interface,  1);
	OSMetaClassDeclareReservedUnused( IO80211Interface,  2);
	OSMetaClassDeclareReservedUnused( IO80211Interface,  3);
	OSMetaClassDeclareReservedUnused( IO80211Interface,  4);
	OSMetaClassDeclareReservedUnused( IO80211Interface,  5);
	OSMetaClassDeclareReservedUnused( IO80211Interface,  6);
	OSMetaClassDeclareReservedUnused( IO80211Interface,  7);
	OSMetaClassDeclareReservedUnused( IO80211Interface,  8);
	OSMetaClassDeclareReservedUnused( IO80211Interface,  9);
	OSMetaClassDeclareReservedUnused( IO80211Interface, 10);
	OSMetaClassDeclareReservedUnused( IO80211Interface, 11);
	OSMetaClassDeclareReservedUnused( IO80211Interface, 12);
	OSMetaClassDeclareReservedUnused( IO80211Interface, 13);
	OSMetaClassDeclareReservedUnused( IO80211Interface, 14);
	OSMetaClassDeclareReservedUnused( IO80211Interface, 15);
};

#endif /* defined(KERNEL) && defined(__cplusplus) */

#endif /* ! _IO80211INTERFACE_H */

