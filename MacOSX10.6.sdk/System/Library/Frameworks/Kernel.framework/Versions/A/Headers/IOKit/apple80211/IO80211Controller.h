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

#ifndef _IO80211CONTROLLER_H
#define _IO80211CONTROLLER_H

/*
 * Kernel
 */
#if defined(KERNEL) && defined(__cplusplus)

#include <libkern/version.h>

#if VERSION_MAJOR > 8
	#define _MODERN_BPF
#endif

#include <IOKit/network/IOEthernetController.h>

#include <sys/param.h>
#include <net/bpf.h>

#include "apple80211_ioctl.h"

// always compile with legacy compatibility for now. This will go away soon.
#ifndef IO80211_LEGACY_COMPAT
#define IO80211_LEGACY_COMPAT
#endif 

#ifdef IO80211_LEGACY_COMPAT
#ifndef __STRUCT_WEPNETWORK__
#define __STRUCT_WEPNETWORK__
// Have to redifine this here because can't include AirPortComm.h; this header file is used by all the vendors
typedef struct WepNetwork
{
//	UInt32	keyLen;					// zero keyLen ==> encryption off
	UInt16	bssType;				// selects Infra/IBSS
	UInt16	keyLen;					// zero keyLen ==> encryption off
	UInt8	key[16];				// WEP key (5 or 13 bytes)
	UInt16	authentication;			// open system, or shared key
	char	ssid[34];               // Network name.
	UInt8	rsnKey[32];				// RSN keys are bigger
} WepNetwork;
typedef WepNetwork *WepNetworkPtr;
#endif
#endif

#define AUTH_TIMEOUT			15	// seconds

/*! @enum LinkSpeed.
    @abstract The raw link speeds, in bits per second, of the various 802.11 protocol variations.
    @discussion These values may be passed directly as the speed parameter to IONetworkMedium::medium().
	@constant LINK_SPEED_80211A 54 Mbps
    @constant LINK_SPEED_80211B 11 Mbps.
    @constant LINK_SPEED_80211G 54 Mbps.
	@constant LINK_SPEED_80211N 300 Mbps.
	*/
enum {
	LINK_SPEED_80211A	= 54000000ul,		// 54 Mbps
	LINK_SPEED_80211B	= 11000000ul,		// 11 Mbps
	LINK_SPEED_80211G	= 54000000ul,		// 54 Mbps
	LINK_SPEED_80211N	= 300000000ul,		// 300 Mbps (MCS index 15, 400ns GI, 40 MHz channel)
};

/*! @enum IO80211CountryCodeOp.
    @abstract Country code related operations that may be requested by the IO80211Family.
    @discussion These operation constants may be passed to subclass implementations of performCountryCodeOperation().
	@constant kIO80211CountryCodeReset Reset country code to world wide default, and start searching for a beacon containing an 802.11d IE.
	*/
enum IO80211CountryCodeOp
{
	kIO80211CountryCodeReset,
};
typedef enum IO80211CountryCodeOp IO80211CountryCodeOp;

/*! @enum IO80211FeatureCode.
    @abstract Driver features that may be requested by an external source.
    @discussion The 802.11 family may requests these features be enabled by passing them to enableFeature().
	@constant kIO80211Feature80211n 802.11n.
	*/
enum IO80211FeatureCode
{
	kIO80211Feature80211n = 1,
};
typedef enum IO80211FeatureCode IO80211FeatureCode;

#define IO80211_LOG( _interface, _level, _msg, ... )	do{ if( _interface && ( _interface->debugFlags() & _level ) ) IOLog( _msg, ##__VA_ARGS__ ); }while(0)

class IO80211Interface;
class IO80211Scanner;
class IO80211WorkLoop;

/*! @class IO80211Controller
    @abstract Abstract superclass for 80211 controllers. 
    @discussion 802.11 controller drivers should subclass IO80211Controller, and implement or override the hardware specific methods to create an 802.11 driver.
				An interface object (an IO80211Interface instance) must be instantiated by the driver, through attachInterface(), to connect the controller driver to the data link layer. 
	*/
class IO80211Controller : public IOEthernetController
{
    OSDeclareAbstractStructors( IO80211Controller )

	#ifdef IO80211_LEGACY_COMPAT
	private:
		struct apple80211_assoc_data	_lastAssocData;
		bool							_interferenceRobustness;
		IO80211Scanner					*_scanner;
		WepNetwork						_lastLegacyAssocInfo;

	public:
		IOReturn newUserClient( task_t owningTask, void * securityID, UInt32 type, 
						OSDictionary * properties, IOUserClient ** handler );
		IOReturn queueCommand( UInt8 commandCode, void *arguments, void *returnValue );
		static IOReturn execCommand( OSObject * obj, void *field0, void *field1, void *field2, void *field3 );
		
		SInt32 getLastAssocData( struct apple80211_assoc_data * ad);
		SInt32 setLastAssocData( struct apple80211_assoc_data * ad);

		IOReturn getLastLegacyAssocInfo(WepNetworkPtr netPtr );
		IOReturn setLastLegacyAssocInfo(WepNetworkPtr netPtr );
		
		bool getInterferenceRobustness()			{ return _interferenceRobustness; }
		void setInterferenceRobustness(bool flag)	{ _interferenceRobustness = flag; }
		
		IO80211Scanner *getScanner()				{ return _scanner; }
		void setScanner(IO80211Scanner *scanner)	{ _scanner = scanner; }
	#endif

public:
	
	/*! @function start
		@abstract Starts network controller.
		@discussion Initializes sleep/wake callback and retains a pointer to the driver's provider. 
		@param provider The provider class against which the driver matched.
		@result Returns true on success, false otherwise. 
		*/ 
	virtual bool start( IOService * provider );

	/*! @function stop
		@abstract Stops the network controller.
		@discussion Memory that has been allocated by start and during network controller initialization is released.
		@param provider The provider class against which the driver matched.
		*/ 
	virtual void stop( IOService * provider );

	/*! @function init
		@abstract Initializes the IO80211Controller object.
		@discussion Instance variables are initialized, then super::init() is called.
		@param properties A dictionary object containing a property table associated with this instance.
		@result Returns true on success, false otherwise. 
		*/  
	virtual bool init( OSDictionary * properties );
	
	/*! @function free
		@abstract Frees the IO80211Controller object.
		@discussion All remaining allocated memory is released, then super::free() is called.
		*/ 
	virtual void free();

	/*! @function createWorkLoop
		@abstract Method called by IONetworkController prior to the initial
				  getWorkLoop() call.
		@discussion Before IONetworkController calls getWorkLoop() in its
					start() method, it will call createWorkLoop() to make sure that a
					subclass that wants to create a workloop, will do so before its
					first use. IO80211Controller::createWorkLoop() will create an IO80211WorkLoop.
		@result Returns true to indicate success, false otherwise. Returning false
				will fail IONetworkController::start(). 
		*/
	virtual bool createWorkLoop();

	/*! @function getWorkLoop
		@abstract Returns the IO80211WorkLoop created by createWorkLoop().
		@result A pointer to an IO80211WorkLoop object. 
		*/ 
	virtual IOWorkLoop * getWorkLoop() const;
	
	/*! @function getProvider
		@abstract Returns the provider object passed to start.
		@result A pointer to the provider object passed to start. 
		*/
	IOService * getProvider();

	/*! @function enable
		@abstract Requests an interface to be "enabled" by the network controller after the IFF_UP flag has been set in its ifnet structure.
		@discussion The enable method is responsible for getting the controller ready to service commands and send and receive data. The interface's output queue is started with a default capacity
					of 256. APPLE80211_POWERSAVE_MODE_VENDOR is unconditionally enabled for every interface (<rdar://problem/5669676>). If an interface was powered on the last time it was disabled,
					it is powered on.
		@param aNetif The object representing the interface that has been "enabled".
		@result Returns kIOReturnSuccess or an error code. 
		*/ 
	virtual IOReturn enable( IONetworkInterface * aNetif );

	/*! @function disable
		@abstract Requests an interface to be "disabled" by the network controller after the IFF_UP flag has been cleared from its ifnet structure.
		@discussion The disable method stops the inteface's output queue(s) and sets their capacity to 0. If wake on wireless is enabled, APPLE80211_POWERSAVE_MODE_WOW will be set, otherwise the inteface
					will be powered off.
		@param aNetif The object representing the interface that has been "disabled".
		@result Returns kIOReturnSuccess or an error code. 
		*/ 
	virtual IOReturn disable( IONetworkInterface * aNetif );

	/*! @function getHardwareAddress
		@abstract Gets the hardware address of the first 802.11 interface attached to the controller.
		@discussion This method should really take a pointer an IONetworkInterface class, but since it does not the driver should return the hardware address of only the first inteface that is attached to
					the controller. Any subsequent interface's will have to be attached using attachInterfaceWithMacAddress().
		@param addr The buffer where the interface's hardware address should be written.
		@result Returns kIOReturnSuccess on success, or an error otherwise. 
		*/
	virtual IOReturn getHardwareAddress( IOEthernetAddress * addr );
	
	/*! @function getOutputQueue
		@abstract Returns an output queue associated with the network controller.
		@discussion This method should really have an additional IONetworkInterface parameter, but even then an interface can have multiple output queues. For that reason one of the IO80211Interface
					getOutputQueue methods should be used to retrieve the exact output queue desired. This method will return the best effort queue of the first interface attached to the controller.
		@result Returns A pointer to the best effort output queue of the first interface attached to the controller. 
		*/ 
	virtual IOOutputQueue * getOutputQueue() const;

	/*! @function configureInterface
		@abstract Configures a newly created network interface object.
		@discussion This method configures an interface object that was created by
					createInterface(). Subclasses can override this method to customize
					and examine the interface object that will be attached to the
					controller as a client.
		@param interface The interface object to be configured.
		@result Returns true if the operation was successful, false otherwise
				(this will cause attachInterface() to fail and return 0). 
		*/
	virtual bool configureInterface( IONetworkInterface * netIf );
	
	/*! @function inputMonitorPacket
		@abstract Sends a monitor mode packet to bpf.
		@discussion This is a convenience method for controllers with only one interface. It will pass a monitor mode frame up through the first interface attached to the controller. An optional header
					may be specified, which will be prepended by bpf before the frame is passed to any awaiting processes.
		@param m An mbuf containing an 802.11 frame.
		@param dlt The data link type of the monitor mode frame
		@param header An optional pointer to a header buffer to be prepended to the frame by bpf. May be NULL.
		@param header_len The length of the optional header.
		*/
	virtual void inputMonitorPacket( mbuf_t m, UInt32 dlt, void * header, size_t header_len );
	
	/*! @function outputRaw80211Packet
		@abstract Sends a fully formed 802.11 frame to the controller for output.
		@discussion This method should be implemented by drivers capable of taking an 802.11 frame created at a higher level and putting it directly onto the air.
		@param interface The inteface through which the frame was output.
		@param m A fully formed 802.11 frame.
		@result Returns 0 if frame is successfully queued, otherwise an errno value should be returned.
		*/ 
	virtual int	outputRaw80211Packet( IO80211Interface * interface, mbuf_t m )	{ return ENXIO; }
	
	/*! @function monitorModeSetEnabled
		@abstract Requests the controller to start/stop passing monitor mode frames up with the specified data link type.
		@discussion This method will be called when an application requests one of the data link types registered by IO80211Interface::bpfAttach() to be enabled or disabled.
					If enabled is set to true and monitor mode is not already enabled, your controller should enable monitor mode and start passing frames to
					IO80211Interface::monitorModeInputPacket(). If enabled is set to false, and no other monitor mode data link types are enabled, monitor mode should be disabled.
		@param interface The interface through which the request to enable/disable the specified data link type was sent.
		@param enabled True if requesting the specified data link type to be enabled, false if requesting it to be disabled.
		@param dlt Data link type
		@result Returns 0 if successful, otherwise an appropriate errno value. 
		*/ 
	
	virtual SInt32	monitorModeSetEnabled( IO80211Interface * interface, bool enabled, UInt32 dlt ) {return ENXIO; }
	
	/*! @function getNetworkInterface
		@result Returns a pointer to the first interface object attached to the controller. 
		*/ 

	virtual IO80211Interface * getNetworkInterface();
	
	/*! @function apple80211_ioctl
		@abstract Entry point in the controller for all SIOCGA80211 and SIOCSA80211 requests.
		@discussion ioctl requests are passed to apple80211_ioctl_get or apple80211_ioctl_set for processing.
		@param interface The interface through which the request was received.
		@param ifn The ifnet structure of the interface through which the request was received.
		@param cmd SIOCGA80211 or SIOCSA80211.
		@param data A pointer to an apple80211req structure.
		@result Returns 0 if successful, otherwise an appropriate errno value. 
		*/ 
	virtual	SInt32 apple80211_ioctl( IO80211Interface * interface, ifnet_t ifn, u_int32_t	cmd, void * data );
	
	/*! @function apple80211Request
		@abstract Implemented by subclasses to handle apple80211 ioctl request callbacks from the IO80211Family.
		@param req SIOCGA80211 or SIOCSA80211.
		@param type The APPLE80211_IOC request as defined in apple80211_ioctl.h.
		@param intf The object representing the interface through which the ioctl request was received.
		@param data A pointer to the data structure corresponding to the ioctl type. These structures are defined in apple80211_ioctl.h
		@result Returns 0 if successful, otherwise an appropriate errno value. 
		*/ 
	#define IOCTL_GET( type, intf, data ) apple80211Request( SIOCGA80211, APPLE80211_IOC_##type, intf, (void *)data )
	#define IOCTL_SET( type, intf, data ) apple80211Request( SIOCSA80211, APPLE80211_IOC_##type, intf, (void *)data )
	virtual SInt32 apple80211Request( UInt32 req, int type, IO80211Interface * intf, void * data ) = 0;
	
	/*! @function stopDMA
		@abstract Called by the IO80211Controller when all DMA activity must stop.
		@discussion This method will be called as the system shuts down or restarts.
		@result Returns 0 if successful, otherwise an appropriate errno value. 
		*/
	virtual SInt32	stopDMA() { return EOPNOTSUPP; }
	
	/*! @function hardwareOutputQueueDepth
		@abstract Returns the number of packets queued by subclass driver and hardware for output.
		@discussion When WPA reauthentication occurs, there is a race between sending PTK 4/4 and installing the new cipher key received in PTK 3/4. The Apple RSN supplicant
					will send PTK 4/4 to the driver, then poll this method until it returns zero or a timeout occurs. When all packets have been transmitted, the pairwise cipher
					key received in PTK 3/4 will be installed.
		@param interface The object representing the interface whose output queue depth is being queried.
		@result The number of packets queued by the subclass driver and hardware for output. 
		*/
	virtual UInt32	hardwareOutputQueueDepth( IO80211Interface * interface ) { return 0; }
	
	/*! @function performCountryCodeOperation
		@abstract Used by the IO80211Family to request a country code operation be performed.
		@discussion At present, this method is only used for reseting the country code when an interface has been powered off, and then powered back on.
		@param interface The object representing the interface whose country code will be affected.
		@param op The IO80211CountryCodeOp the driver should perform on the specified interface.
		@result Returns 0 if successful, otherwise an appropriate errno value. 
		*/
	virtual SInt32	performCountryCodeOperation( IO80211Interface * interface, IO80211CountryCodeOp op )	{ return EOPNOTSUPP; }
	
	/*! @function useAppleRSNSupplicant
		@abstract Used by the IO80211Family to determine if the built-in Apple RSN supplicant should be used.
		@discussion Most drivers should use the Apple supplicant. However, in some special cases it may not be practical. If, for instance, the majority of the driver firmware runs on a 
					dongle-like device that includes its own supplicant, it may be simpler handle supplicant related tasks directly in the firmware.
		@param interface The object representing the interface whose supplicant status is being queried.
		@result Returns true if the Apple supplicant should be used, otherwise false.
		*/
	virtual bool	useAppleRSNSupplicant( IO80211Interface * interface ) { return true; }
	
	/*! @function dataLinkLayerAttachComplete
		@abstract This callback is made to the controller class when an ifnet structure has been allocated and attached.
		@discussion If subclass drivers need to do any processing at this time, they may override this method, but must make sure to call super.
		@param interface The object representing the interface whose ifnet structure has been allocated and attached.
		*/
	
	virtual void	dataLinkLayerAttachComplete( IO80211Interface * interface );
	
	/*! @function enableFeature
		@abstract Used by the IO80211Family to request a feature be enabled.
		@discussion enableFeature may be used to dynamically enable driver features and capabilities.
		@param feature The feature to be enabled.
		@param refcon Currently not used.
		@result Returns 0 if successful, otherwise an appropriate errno value.
		*/
	virtual SInt32 enableFeature( IO80211FeatureCode feature, void * refcon ) { return EOPNOTSUPP; }
	
	/*! @function getASSOCIATE_RESULT
		@abstract Examines driver state and attempts to formulate an accurate description of the current state of an association request.
		@discussion Method checks if the interface has been deauthenticated, the current association status value, the state of the Apple supplicant
					(if in use), and aggregates the information into a single apple80211_associate_result value as defined in apple80211_var.h.
		@param interface The interface whose status is being queried.
		@param ard apple80211_associate_result code is returned through this parameter.
		@result Returns 0 if successful, otherwise an appropriate errno value.
		*/
	SInt32 getASSOCIATE_RESULT( IO80211Interface * interface, 
								struct apple80211_assoc_result_data * ard );

	/*! @function setSleeping
		@abstract Sets/clears flag as the system goes to/wakes from sleep.
		@param sleeping true if the system is going to sleep, false if the system is waking.
		*/
	void setSleeping( bool sleeping ) { _sleeping = sleeping; }
	
	/*! @function radioCountForInterface
		@abstract Determines number of RF chains supported by the interface.
		@discussion Interface radio information is queried using APPLE80211_IOC_RADIO_INFO. If the query fails, chain count defaults to 1.
		@param interface The interface whose RF chain count is being queried.
		@result The number of RF chains supported by the interface.
		*/
	UInt32 radioCountForInterface( IO80211Interface * interface );
	
	// Methods used internally by the IO80211Family
	void join4NetBoot( IO80211Interface * interface, void * nvram );
	static IOReturn powerChangeGated( OSObject * owner, void * arg0, void * arg1, void * arg2, void * arg3 );

protected:
	
	/*!	@function createInterface
		@abstract Allocates and initializes a new IO80211Interface object.
		@discussion This method is called by attachInterface() to perform
					allocation and initialization of a new interface object. A subclass of
					IONetworkController must implement this method and return a matching
					interface object.
		@result Returns a newly allocated and initialized IO80211Interface object. 
		*/
	virtual IONetworkInterface * createInterface();

	/*! @function inputPacket
		@abstract A convenience methods for drivers that have only one network inteface.
		@discussion Passes the packet to the inputPacket method of the first network interface attached to the controller.
		@param m The packet being sent up from the driver.
		*/

	virtual void inputPacket( mbuf_t m );

	/*! @function apple80211_ioctl_get
		@abstract Handler for SIOCGA80211 requests.
		@discussion apple80211_ioctl_get handles copying data into and out of the kernel, and calling into the subclass driver through apple80211Request to query data necessary
					for servicing the request.
		@param interface The interface through which the request was received.
		@param ifn The ifnet structure of the interface through which the request was received.
		@param data A pointer to an apple80211req structure.
		@result Returns 0 if successful, otherwise an appropriate errno value. 
		*/
	virtual SInt32 apple80211_ioctl_get( IO80211Interface * interface, ifnet_t ifn, void * data );

	/*! @function apple80211_ioctl_set
		@abstract Handler for SIOCSA80211 requests.
		@discussion apple80211_ioctl_set handles copying data into and out of the kernel, and calling into the subclass driver through apple80211Request to pass data necessary
					for servicing the request.
		@param interface The interface through which the request was received.
		@param ifn The ifnet structure of the interface through which the request was received.
		@param data A pointer to an apple80211req structure.
		@result Returns 0 if successful, otherwise an appropriate errno value. 
		*/
	virtual SInt32	apple80211_ioctl_set( IO80211Interface	* interface, ifnet_t ifn, void * data );
	
	// See IONetworkController.h
	virtual bool attachInterface(IONetworkInterface ** interface,
                                 bool                  doRegister = true);
	
	/*!	@function attachInterfaceWithMacAddress
		@abstract Handles attaching a second, third, fourth, etc. IO80211Interface to an IO80211Controller.
		@discussion The standard attachInterface method is not capable of attaching more than one interface to the same controller class without help. This methods works around the
					shortcomings of attachInterface by interfacing directly with the IONetworkStack.
		@param macAddr The MAC address of the interface being attached.
		@param macLen The length of the MAC address data.
		@param interface If successful, a new IO80211Interface object will be allocated and returned through this pointer.
		@param doRegister This parameter should always be set to true. It will make a synchronous registerService call on the new interface, and force registeration with the IONetworkStack.
		@param timeout A time value, in ms, that specifies how long to wait for other interfaces being registered asynchronously to complete the registration process. If the time limit is
			   exceeded, the method will fail.
		@result Returns true if successful, otherwise false. 
		*/
	virtual bool attachInterfaceWithMacAddress( void * macAddr, 
												UInt32 macLen, 
												IONetworkInterface ** interface, 
												bool doRegister = true,
												UInt32 timeout = 5000 /*ms*/ );
	
	// Used internally by IO80211Controller
	static IOReturn	powerChangeHandler( void * target, void * refCon, UInt32 messageType,
										IOService * service, void * messageArgument, vm_size_t argSize );
	bool readNetBootParams( void * nvram, apple80211_assoc_data &data );

private:

	bool forceInterfaceRegistration( IO80211Interface * interface );
	
	IO80211WorkLoop				*_myWorkLoop;
	IONetworkInterface			*_netIF;

	// Intel power management handler
	IONotifier	*	_powerDownNotifier;
	
	IOService	*	_provider;
	
	bool _ifAttachPending;
	
	bool _sleeping;
	
	struct ExpansionData 
	{
		bool		netBooting;
		IONotifier *interfaceNotifier;
	};
	struct ExpansionData * _reserved;

		// Virtual function padding
	OSMetaClassDeclareReservedUnused( IO80211Controller,  0);
	OSMetaClassDeclareReservedUnused( IO80211Controller,  1);
    OSMetaClassDeclareReservedUnused( IO80211Controller,  2);
    OSMetaClassDeclareReservedUnused( IO80211Controller,  3);
    OSMetaClassDeclareReservedUnused( IO80211Controller,  4);
    OSMetaClassDeclareReservedUnused( IO80211Controller,  5);
    OSMetaClassDeclareReservedUnused( IO80211Controller,  6);
    OSMetaClassDeclareReservedUnused( IO80211Controller,  7);
    OSMetaClassDeclareReservedUnused( IO80211Controller,  8);
    OSMetaClassDeclareReservedUnused( IO80211Controller,  9);
    OSMetaClassDeclareReservedUnused( IO80211Controller, 10);
    OSMetaClassDeclareReservedUnused( IO80211Controller, 11);
    OSMetaClassDeclareReservedUnused( IO80211Controller, 12);
    OSMetaClassDeclareReservedUnused( IO80211Controller, 13);
    OSMetaClassDeclareReservedUnused( IO80211Controller, 14);
    OSMetaClassDeclareReservedUnused( IO80211Controller, 15);
};
	
#endif /* defined(KERNEL) && defined(__cplusplus) */
	
#endif /* !_IO80211CONTROLLER_H */
	