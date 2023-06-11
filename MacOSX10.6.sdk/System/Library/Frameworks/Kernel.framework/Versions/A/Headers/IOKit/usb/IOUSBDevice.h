/*
 * Copyright (c) 1998-2007 Apple Inc. All rights reserved.
 *
 * @APPLE_LICENSE_HEADER_START@
 * 
 * The contents of this file constitute Original Code as defined in and
 * are subject to the Apple Public Source License Version 1.2 (the
 * "License").  You may not use this file except in compliance with the
 * License.  Please obtain a copy of the License at
 * http://www.apple.com/publicsource and read it before using this file.
 * 
 * This Original Code and all software distributed under the License are
 * distributed on an "AS IS" basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.  
 * Please see the License for the specific language governing rights and 
 * limitations under the License.
 * 
 * @APPLE_LICENSE_HEADER_END@
 */

#ifndef __OPEN_SOURCE__
/*
 *
 *	$Log: IOUSBDevice.h,v $
 *	Revision 1.57.84.2  2008/04/22 22:38:01  nano
 *	Bring in changes from Foxhound-320.2.9
 *	
 *	Revision 1.60  2008/04/18 22:03:28  nano
 *	Bring in fix for rdar://5874560
 *	
 *	Revision 1.59.4.1  2008/04/18 21:55:55  nano
 *	<rdar://problem/5874560> Need API to know how much extra power has been allocated
 *	
 *	Revision 1.59  2008/04/17 16:56:57  nano
 *	Bring in branches for rdar://5867990 & rdar://5768343
 *	
 *	Revision 1.58.4.1  2008/04/16 20:26:13  nano
 *	<rdar://problem/5867990> Add API to allocate sleep current, as well as making sure that we return any extra power if our client dies or our device is terminated without returning it
 *	
 *	Revision 1.58  2008/04/14 16:08:38  nano
 *	Add new APIs for high power and for GetDeviceInformation.
 *	
 *	Revision 1.57.126.2  2008/04/13 05:25:40  nano
 *	Call into PolicyMaker for the GetPortInformation
 *	
 *	Revision 1.57.126.1  2008/04/11 22:25:44  nano
 *	Initial work on new user-client APIs and new IOUSBDevice APIs to return port state information and manage extra power requests, as well as groundwork for calling the policy maker directly from the IOUSBDevice
 *	
 *	Revision 1.57  2007/08/07 20:30:36  rhoads
 *	rolled in a few branches to TOT
 *	
 *	Revision 1.56.92.1  2007/08/07 03:43:34  nano
 *	Bring in more changes for M89 suppport -- like actually use the dang power if the properties are available
 *	
 *	Revision 1.56  2007/03/06 12:23:41  rhoads
 *	roll in 5024412, 5035829, and 5039670
 *	
 *	Revision 1.55.30.1  2007/02/27 16:08:33  rhoads
 *	some fine tuning of our IOService overrides, including not overriding willTerminate and didTerminate (5024412)
 *	
 *	Revision 1.55  2007/01/19 17:58:48  rhoads
 *	roll in branches for a leopard build
 *	
 *	Revision 1.54.30.1  2007/01/17 16:37:02  rhoads
 *	remove the IOUSBDevice::attach method which is not really useful
 *	
 *	Revision 1.54  2006/10/06 04:42:01  rhoads
 *	roll in branches 4727961, 4758404, 4759810, 4760274, and 4762769
 *	
 *	Revision 1.53.4.1  2006/10/04 16:03:57  rhoads
 *	better IOUSBHubDevice design
 *	
 */
#endif

#ifndef _IOKIT_IOUSBDEVICE_H
#define _IOKIT_IOUSBDEVICE_H

#include <IOKit/usb/IOUSBNub.h>
#include <IOKit/usb/IOUSBPipe.h>
#include <IOKit/IOBufferMemoryDescriptor.h>
#include <IOKit/IOWorkLoop.h>
#include <IOKit/IOCommandGate.h>

#include <kern/thread_call.h>

// The following are definitions for errata properties needed for different devices.  This
// should be but in the dictionary of the IOUSBDevice in question.  This can be achieved
// by using the AppleUSBMergeNub class and having an IOProviderMergeProperties dictionary
// with the required properties.

// This property allows a device to specify a configuration value of 0 in its configuration
// descriptor.  This does not follow the spec, but we will allow it in order to get the device 
// to work.  The property should be a Boolean
//
#define kAllowConfigValueOfZero		"kAllowZeroConfigValue"
#define kAllowNumConfigsOfZero		"kAllowZeroNumConfigs"


class IOUSBController;
class IOUSBControllerV2;
class IOUSBInterface;
class IOUSBHubPolicyMaker;
/*!
    @class IOUSBDevice
    @abstract The IOService object representing a device on the USB bus.
    @discussion This class provides functionality to configure a device and to create
	IOUSBInterface objects to represent the interfaces of the device.
*/

class IOUSBDevice : public IOUSBNub
{
    friend class IOUSBController;
    friend class IOUSBControllerV2;
    friend class IOUSBInterface;
    friend class IOUSBPipe;
   
    OSDeclareDefaultStructors(IOUSBDevice)

protected:

    USBDeviceAddress				_address;
    IOUSBController *	     		_controller;
    IOUSBPipe *						_pipeZero;
    IOUSBDeviceDescriptor			_descriptor;
    UInt32							_busPowerAvailable;
    UInt8							_speed;
    IOUSBEndpointDescriptor			_endpointZero; 				// Fake ep for control pipe
    void *							_port;					// Obsolete, do not use
    IOBufferMemoryDescriptor**		_configList;
    IOUSBInterface**				_interfaceList;
    UInt8							_currentConfigValue;
    UInt8							_numInterfaces;
    
    struct ExpansionData 
    {
        UInt32					_portNumber;
        thread_call_t			_doPortResetThread;
        IOUSBDevice *			_usbPlaneParent;
        bool					_portResetThreadActive;
        bool					_allowConfigValueOfZero;
        thread_call_t			_doPortSuspendThread;
        bool					_portSuspendThreadActive;
        thread_call_t			_doPortReEnumerateThread;
        bool					_resetInProgress;
        bool					_portHasBeenReset;
        IORecursiveLock*		_getConfigLock;
        bool					_doneWaiting;                   // Obsolete
        bool					_notifiedWhileBooting;          // Obsolete
        IOWorkLoop *			_workLoop;
        IOTimerEventSource *	_notifierHandlerTimer;
        UInt32					_notificationType;
        bool					_suspendInProgress;
        bool					_portHasBeenSuspendedOrResumed;
        bool					_addExtraResetTime;
		bool					_suspendCommand;
		IOCommandGate *			_commandGate;
		OSSet *					_openInterfaces;
		bool					_resetCommand;
		IOReturn				_resetError;
		IOReturn				_suspendError;
        thread_call_t			_doMessageClientsThread;
		IOUSBHubPolicyMaker *	_hubPolicyMaker;
		UInt32					_sleepPowerAllocated;				// how much sleep power we already gave to our client
		UInt32					_wakePowerAllocated;				// how much extra power during wake did we already give our client
		UInt32					_devicePortInfo;
    };	
    ExpansionData * _expansionData;

    const IOUSBConfigurationDescriptor *FindConfig(UInt8 configValue, UInt8 *configIndex=0);

    virtual IOUSBInterface * GetInterface(const IOUSBInterfaceDescriptor *interface);

public:
    virtual IOReturn SetFeature(UInt8 feature);

protected:    
    virtual IOReturn GetConfigDescriptor(UInt8 configIndex, void *data, UInt32 len);

    virtual IOReturn GetDeviceDescriptor(IOUSBDeviceDescriptor *desc, UInt32 size);

    virtual bool init(USBDeviceAddress deviceAddress, UInt32 powerAvaiable, UInt8 speed, UInt8 maxPacketSize );

    virtual bool matchPropertyTable(OSDictionary * table, SInt32 *score);
    
public:
    // IOService methods
    virtual bool		init( void );
    virtual bool		start( IOService *provider );	
	virtual bool		handleIsOpen(const IOService *forClient) const;
	virtual bool		handleOpen(IOService *forClient, IOOptionBits options, void *arg);
	virtual void		handleClose(IOService *forClient, IOOptionBits options);
    virtual IOReturn 	message( UInt32 type, IOService * provider,  void * argument = 0 );
    virtual bool		terminate( IOOptionBits options = 0 );
    virtual bool		requestTerminate( IOService * provider, IOOptionBits options );
    virtual void		stop( IOService *provider );
    virtual bool		finalize(IOOptionBits options);
	virtual void		free( void );	

	// IOUSBDevice methods
    virtual void SetProperties();
    
    static IOUSBDevice *NewDevice(void);
    
    virtual void SetPort(void *port);			// Obsolete, do NOT use

    /*!
	@function FindNextInterfaceDescriptor
	return a pointer to the next interface descriptor within the given full configuration descriptor satisfying the requirements specified, or NULL if there aren't any.
        @param configDescIn the configuration descriptor within which to search. obtained from GetFullConfigurationDescriptor(configIndex). use NULL to specify the current configuration's descriptor.
        @param intfDesc interface descriptor from which to start the search. NULL for the first interface descriptor in the given configuration descriptor
        @param request IOUSBFindInterfaceRequest specifying the desired interface. Not changed.
        @param descOut pointer to placeholder for the returned descriptor ptr
	@result returns kIOReturnBadArgument if configDesc is not correct, or if configDesc is NULL and the device is not configured, or if intfDesc is not in configDesc. Otherwise returns kIOReturnSuccess or kIOUSBInterfaceNotFound.
    */
    virtual IOReturn FindNextInterfaceDescriptor(const IOUSBConfigurationDescriptor *configDescIn, 
                                                 const IOUSBInterfaceDescriptor *intfDesc,
                                                 const IOUSBFindInterfaceRequest *request,
                                                 IOUSBInterfaceDescriptor **descOut);
    /*!
	@function FindNextInterface
	return an pointer to an IOUSBInterface object satisfying the requirements specified in request, or NULL if there aren't any. the device
        must be configured for there to be any interfaces.
        @param current interface to start searching from, NULL to start at the beginning of the device's interface list for the current configuration.
	@param request specifies what properties an interface must have to match.
	@result Pointer to a matching IOUSBInterface, or NULL if none match. Note: The IOUSBInterface is NOT retained for the caller. If the caller wishes to continue to use the returned object, it should call retain() on that object.
    */
    virtual IOUSBInterface *FindNextInterface(IOUSBInterface *current,
                                              IOUSBFindInterfaceRequest *request);

    /*!
        @function CreateInterfaceIterator 
        return an OSIterator to iterate through interfaces satisfying the requirements specified in request.                        
        @param request specifies what properties an interface must have to match.
        @result Pointer to an OSIterator.
    */
    virtual OSIterator *CreateInterfaceIterator(IOUSBFindInterfaceRequest *request);

    // Get pointer to full config info (cached in device, don't free returned pointer)
    /*!
	@function GetFullConfigurationDescriptor
	return a pointer to all the descriptors for the requested configuration.
        @param configIndex The configuration index (not the configuration value)
	@result Pointer to the descriptors, which are cached in the IOUSBDevice object.
    */
    virtual const IOUSBConfigurationDescriptor *GetFullConfigurationDescriptor(UInt8 configIndex);

    /*!
	@function GetConfigurationDescriptor
        Copy the specified amount of data for a configuration into the suppled buffer.
        @param configValue The configuration value
	@param data Buffer to copy data into
	@param len number of bytes to copy
    */
    virtual IOReturn GetConfigurationDescriptor(UInt8 configValue, void *data, UInt32 len);

    /*!
	@function ResetDevice
	Reset the device, returning it to the addressed, unconfigured state.
	This is useful if a device has got badly confused. Note that the AppleUSBComposite driver will automatically
        reconfigure the device if it is a composite device.
    */
    virtual IOReturn ResetDevice();

    /*!
	@function SetConfiguration
	Do a USB SetConfiguration call to the device. The caller must have the device open() in order to 
	actually cause a configuration change. If the device is currently configured, all IOUSBInterface objects
	associated with the device are freed. After the new configuration has been set, all of its IOUSBInterface objects are
	instantiated automatically.
	@param forClient The client requesting the configuration change
	@param configValue The desired configuration value.
	@param startInterfaceMatching A boolean specifying whether IOKit should begin the process of finding
	matching drivers for the new IOUSBInterface objects.
    */
    virtual IOReturn SetConfiguration(IOService *forClient, UInt8 configValue, bool startInterfaceMatching=true);
    
    // Access to addressing and cached info
    /*!
        @function GetAddress
        returns the bus address of the device
    */
    virtual USBDeviceAddress GetAddress(void);
    
    /*!
        @function GetSpeed
        returns the speed of the device
    */
    virtual UInt8 GetSpeed(void);
    /*!
        @function GetBus
        returns a pointer to the IOUSBController object for the device
    */
    virtual IOUSBController *GetBus(void);
    /*!
        @function GetBusPowerAvailable
        returns the power available to the device, in units of 2mA
    */
    virtual UInt32 GetBusPowerAvailable( void );
    /*!
        @function GetMaxPacketSize
        returns the maximum packet size for endpoint zero (only 8, 16, 32, 64 are valid)
    */
    virtual UInt8 GetMaxPacketSize(void);
    /*!
        @function GetVendorID
        returns the Vendor ID of the device
    */
    virtual UInt16 GetVendorID(void);
    /*!
        @function GetProductID
        returns the Product ID of the device
    */
    virtual UInt16 GetProductID(void);
    /*!
        @function GetDeviceRelease
        returns the DeviceRelease information
    */
    virtual UInt16 GetDeviceRelease(void);
    /*!
        @function GetNumConfigs
        returns the number of configs in the device config descriptor
    */
    virtual UInt8 GetNumConfigurations(void);
    /*!
        @function GetManufacturerStringIndex
        returns the index of string descriptor describing manufacturer
    */
    virtual UInt8 GetManufacturerStringIndex(void );
    /*!
        @function GetProductStringIndex
        returns the index of string descriptor describing product
    */
    virtual UInt8 GetProductStringIndex(void );
    /*!
        @function GetSerialNumberStringIndex
        returns the index of string descriptor describing the device's serial number
    */
    virtual UInt8 GetSerialNumberStringIndex(void );
    /*!
        @function GetPipeZero
        returns a pointer to the device's default control pipe
    */
    virtual IOUSBPipe * GetPipeZero(void);

	// Deprecated but needed for binary compatibility
    virtual IOUSBPipe*	MakePipe(const IOUSBEndpointDescriptor *ep);
    
    // this method is deprecated. use the other DeviceRequest methods
    virtual IOReturn DeviceRequest(IOUSBDevRequest	*request,
                                IOUSBCompletion	*completion = 0);

    // Same but with a memory descriptor
    virtual IOReturn DeviceRequest(IOUSBDevRequestDesc	*request,
                                   IOUSBCompletion	*completion = 0);

    /*!
	@function GetConfiguration
	Gets the current configuration from the IOUSBDevice object.  Note that this call will send a control
        request on the bus to get the current configuration from the physical device.
	@param configNum Pointer to place to store configuration value.
    */
    virtual IOReturn GetConfiguration(UInt8 *configNumber);

    /*!
        @function GetDeviceStatus
        Gets the device's status.  Note that this sends a control request to the physical device.
        @param status Pointer to place to store the status.
    */
    virtual IOReturn GetDeviceStatus(USBStatus *status);

    /*! 
	@function GetStringDescriptor
	Get a string descriptor as ASCII, in the specified language (default is US English)
	@param index Index of the string descriptor to get.
	@param buf Pointer to place to store ASCII string
	@param maxLen Size of buffer pointed to by buf
        @param lang Language to get string in (default is US English)
    */
    virtual IOReturn GetStringDescriptor(UInt8 index, char *buf, int maxLen, UInt16 lang=0x409);
    
    /*! 
	@function GetChildLocationID
	Get the locationID (UInt32) given the port number and the parent's location
	@param parentLocationID locationID for the hub to which this device is attached.
	@param port Port number of the hub where this device is attached
    */
    virtual UInt32 GetChildLocationID(UInt32 parentLocationID, int port);

    virtual const IOUSBDescriptorHeader* FindNextDescriptor(const void *cur, UInt8 descType);

    virtual void 	DisplayNotEnoughPowerNotice();
    
    // this is a non-virtual function so that we don't have to take up a binary compatibility slot.
    UInt16	GetbcdUSB(void);
    UInt8	GetProtocol(void);
	void	SetBusPowerAvailable(UInt32 newPower);

    OSMetaClassDeclareReservedUsed(IOUSBDevice,  0);
    /*!
	@function DeviceRequest
        @abstract execute a control request to the default control pipe (pipe zero)
        @param request The parameter block to send to the device
        @param noDataTimeout Specifies an amount of time (in ms) after which the command will be aborted
        if no data has been transferred on the bus.
        @param completionTimeout Specifies an amount of time (in ms) after which the command will be aborted if the entire command has
        not been completed.
	@param completion Function to call when request completes. If omitted then
        DeviceRequest() executes synchronously, blocking until the request is complete.
    */
    virtual IOReturn DeviceRequest(IOUSBDevRequest	*request,
				UInt32 noDataTimeout,
				UInt32 completionTimeout,
                                IOUSBCompletion	*completion = 0);

    // Same but with a memory descriptor
    OSMetaClassDeclareReservedUsed(IOUSBDevice,  1);
    virtual IOReturn DeviceRequest(IOUSBDevRequestDesc	*request,
				    UInt32 noDataTimeout,
				    UInt32 completionTimeout,
				    IOUSBCompletion	*completion = 0);

    OSMetaClassDeclareReservedUsed(IOUSBDevice,  2);
    /*!
	@function SuspendDevice
        @abstract Instruct the hub to which this device is attached to suspend or resume the port to which the device is attached.
        Note that if there are any outstanding transactions on any pipes in the device, those transactions will get returned with a 
        kIOReturnNotResponding error.
        @param suspend Boolean value. true = suspend, false = resume.
    */
    virtual IOReturn SuspendDevice( bool suspend);
    
    OSMetaClassDeclareReservedUsed(IOUSBDevice,  3);
    /*!
	@function ReEnumerateDevice
        @abstract Instruct the hub to which this device is attached to reset the port to which this device is attached. This causes the
        IOUSBDevice object and any child objects (IOUSBInterface objects or driver objects) to be terminated, and the device to be
        completely reenumerated, as if it had been detached and reattached.
        @param options Reserved for future use.
    */
    virtual IOReturn ReEnumerateDevice( UInt32 options );
    
    OSMetaClassDeclareReservedUsed(IOUSBDevice,  4);
    /*!
        @function DisplayUserNotification
        @abstract  Will use the KUNCUserNotification mechanism to display a notification to the user.
        @param notificationType Which notification to display.
     */
    virtual void	DisplayUserNotification(UInt32 notificationType);
    
    OSMetaClassDeclareReservedUsed(IOUSBDevice,  5);
	/*!
        @function MakePipe
	 @abstract build a pipe on a given endpoint
	 @param ep A description of the endpoint
	 @param interface The IOUSBInterface object requesting the pipe
	 returns the desired IOUSBPipe object
	 */
    virtual IOUSBPipe*	MakePipe(const IOUSBEndpointDescriptor *ep, IOUSBInterface *interface);
    
	
    OSMetaClassDeclareReservedUsed(IOUSBDevice,  6);
	/*!
	 @function SetHubPolicyMaker
	 @abstract Used by the hub driver to give the nub a pointer to its HubPolicyMaker object
	 @param hubPolicyMaker	The object representing the Hub driver
	 */
    virtual void	SetPolicyMaker(IOUSBHubPolicyMaker *hubPolicyMaker);
    
    OSMetaClassDeclareReservedUsed(IOUSBDevice,  7);
	/*!
	 @function SetHubPolicyMaker
	 @abstract Used by the hub driver to give the nub a pointer to its HubPolicyMaker object
	 @param hubPolicyMaker	The object representing the Hub driver
	 */
    virtual IOUSBHubPolicyMaker*	GetPolicyMaker();
    
    OSMetaClassDeclareReservedUsed(IOUSBDevice,  8);
    /*!
	 @function 	GetDeviceInformation
	 @abstract 	Returns status information about the USB device, such as whether the device is captive or whether it is in the suspended state.
	 @param requestedPower 	The desired amount of power that the client wishes to reserve
	 @result 		Actual power that was reserved
	 
		*/
	virtual IOReturn	GetDeviceInformation(UInt32 *info);
    
    OSMetaClassDeclareReservedUsed(IOUSBDevice,  9);
    /*!
	 @function				RequestExtraPower
	 @abstract				Clients can use this API to reserve extra power for use by this device while the machine is asleep or while it is awake.  Units are milliAmps (mA).
	 @param type			Indicates whether the power is to be used during wake or sleep (One of kUSBPowerDuringSleep or kUSBPowerDuringWake)
	 @param requestedPower 	Amount of power desired, in mA
	 @result				Amount of power actually reserved, in mA.  It can be less than the requested or zero.
	 
	 */
	virtual UInt32	RequestExtraPower(UInt32 type, UInt32 requestedPower);
    
    OSMetaClassDeclareReservedUsed(IOUSBDevice,  10);
    /*!
	 @function				ReturnExtraPower
	 @abstract				Clients can use this API to tell the system that they will not use power that was previously reserved by using the RequestExtraPower API.
	 @param type			Indicates whether the power is to be used during wake or sleep (One of kUSBPowerDuringSleep or kUSBPowerDuringWake)
	 @param returnedPower 	Amount of power that is no longer needed, in mA
	 @result				If the returnedPower was not previously allocated, an error will be returned.  This will include the case for power that was requested for sleep but was returned for wake.
	 
	 */
	virtual IOReturn		ReturnExtraPower(UInt32 type, UInt32 returnedPower);
    
    OSMetaClassDeclareReservedUsed(IOUSBDevice,  11);
    /*!
	 @function				GetExtraPowerAllocated
	 @abstract				Clients can use this API to ask how much extra power has already been reserved by this device.  Units are milliAmps (mA).
	 @param type			Indicates whether the allocated power was to be used during wake or sleep (One of kUSBPowerDuringSleep or kUSBPowerDuringWake)
	 @result				Amount of power allocated, in mA.  .
	 
	 */
	virtual UInt32	GetExtraPowerAllocated(UInt32 type);
    
    OSMetaClassDeclareReservedUnused(IOUSBDevice,  12);
    OSMetaClassDeclareReservedUnused(IOUSBDevice,  13);
    OSMetaClassDeclareReservedUnused(IOUSBDevice,  14);
    OSMetaClassDeclareReservedUnused(IOUSBDevice,  15);
    OSMetaClassDeclareReservedUnused(IOUSBDevice,  16);
    OSMetaClassDeclareReservedUnused(IOUSBDevice,  17);
    OSMetaClassDeclareReservedUnused(IOUSBDevice,  18);
    OSMetaClassDeclareReservedUnused(IOUSBDevice,  19);
    
private:

    static void 	ProcessPortResetEntry(OSObject *target);
    void 		ProcessPortReset(void);

    void 		TerminateInterfaces(void);

    static void 	ProcessPortSuspendEntry(OSObject *target, thread_call_param_t suspend);
    void 		ProcessPortSuspend( bool suspend);
   
    static void 	ProcessPortReEnumerateEntry(OSObject *target, thread_call_param_t options);
    void 		ProcessPortReEnumerate(UInt32 options);
	
    static void 	DoMessageClientsEntry(OSObject *target, thread_call_param_t messageStruct);
    void 		DoMessageClients( void * messageStructPtr);
	
    static void 	DisplayUserNotificationForDeviceEntry (OSObject *owner, IOTimerEventSource *sender);
    void		DisplayUserNotificationForDevice( );
    
    UInt32              SimpleUnicodeToUTF8(UInt16 uChar, UInt8 utf8Bytes[4]);
    void                SwapUniWords (UInt16  **unicodeString, UInt32 uniSize);

};

#endif /* _IOKIT_IOUSBDEVICE_H */
