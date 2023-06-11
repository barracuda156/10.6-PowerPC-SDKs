//------------------------------------------------------------------------------------------------------------------------------
//
//  ICDevice.h
//  ImageCaptureCore
//
//  Copyright (c) 2008 Apple, Inc., all rights reserved.
//
//  Best viewed with the following settings: Tab width 4, Indent width 2, Wrap lines, Indent wrapped lines by 3, Page guide 128.
//
//------------------------------------------------------------------------------------------------------------------------------
/*!
	@header ICDevice
    ICDevice is an abstract class that represents a device supported by Image Capture. ImageCaptureCore defines two concrete subclasses of ICDevice, ICCameraDevice and ICScannerDevice. ICDeviceBrowser creates instances of these two subclasses to represent cameras and scanners it finds.
*/

@class  ICDevice;

//------------------------------------------------------------------------------------------------------------------------------
// Constants used to identify the transport type used by a device.
/*!
    @const      ICTransportTypeUSB
    @abstract   ICTransportTypeUSB
    @discussion Indicates that the device uses USB transport.
*/
extern NSString *const ICTransportTypeUSB;

/*!
    @const      ICTransportTypeFireWire
    @abstract   ICTransportTypeFireWire
    @discussion Indicates that the device uses FireWire transport.
*/
extern NSString *const ICTransportTypeFireWire;

/*!
    @const      ICTransportTypeBluetooth
    @abstract   ICTransportTypeBluetooth
    @discussion Indicates that the device uses Bluetooth transport.
*/
extern NSString *const ICTransportTypeBluetooth;

/*!
    @const      ICTransportTypeTCPIP
    @abstract   ICTransportTypeTCPIP
    @discussion Indicates that the device uses TCP/IP transport. These devices are discovered using Bonjour.
*/
extern NSString *const ICTransportTypeTCPIP;

/*!
    @const      ICTransportTypeMassStorage
    @abstract   ICTransportTypeMassStorage
    @discussion Indicates that the device use mounts as a mass-storage volume.
*/
extern NSString *const ICTransportTypeMassStorage;

//------------------------------------------------------------------------------------------------------------------------------
// Constants used for device status notifications.
/*!
    @const      ICStatusNotificationKey
    @abstract   ICStatusNotificationKey
    @discussion Key for a non-localized notification string.
*/
extern NSString *const ICStatusNotificationKey;

/*!
    @const      ICLocalizedStatusNotificationKey
    @abstract   ICLocalizedStatusNotificationKey
    @discussion Key for a localized notification string.
*/
extern NSString *const ICLocalizedStatusNotificationKey;

//------------------------------------------------------------------------------------------------------------- ICDeviceDelegate
/*! 
  @protocol ICDeviceDelegate <NSObject>
  @abstract A delegate of ICDevice must conform to ICDeviceDelegate protocol.
*/

@protocol ICDeviceDelegate <NSObject>

@required

/*! 
  @method didRemoveDevice:
  @abstract This message is sent to the delegate to inform that a device has been removed.
*/
- (void)didRemoveDevice:(ICDevice*)device;

@optional

/*! 
  @method device:didOpenSessionWithError:
  @abstract This message is sent when a session is opened on a device.
  @discussion This message completes the process initiated by the message "requestOpenSession" sent to the device object.
*/
- (void)device:(ICDevice*)device didOpenSessionWithError:(NSError*)error;

/*! 
  @method deviceDidBecomeReady:
  @abstract This message is sent when the device is ready.
  @discusson A camera device is ready, when its contents are enumerated. A scanner device is ready when its functional units are found and the default functional unit is selected for use.
*/
- (void)deviceDidBecomeReady:(ICDevice*)device;

/*! 
  @method device:didCloseSessionWithError:
  @abstract This message is sent when a session is closed on a device.
  @discussion This message completes the process initiated by the message "requestCloseSession" sent to the device object. This message is also sent if the device module in control of the device ceases to control the device.
*/
- (void)device:(ICDevice*)device didCloseSessionWithError:(NSError*)error;

/*! 
  @method deviceDidChangeName:
  @abstract This message is sent if the name of a device changes.
  @discussion This happens if the device module overrides the default name of the device reported by the device's transport layer, or if the name of the filesystem volume mounted by the device is changed by the user.
*/
- (void)deviceDidChangeName:(ICDevice*)device;

/*! 
  @method deviceDidChangeSharingState:
  @abstract This message is sent when the sharing state of a device has changes.
  @discusson Any Image Capture client application can choose to share the device over the network using the sharing or webSharing facility in Image Capture.
*/
- (void)deviceDidChangeSharingState:(ICDevice*)device;

/*! 
  @method device:didReceiveNotification:
  @abstract This message is sent when a camera or scanner has an unsolicited notification.
*/
- (void)device:(ICDevice*)device didReceiveNotification:(NSDictionary*)notification;

/*! 
  @method scannerDevice:didEncounterError:
  @abstract This message is sent when a camera or scanner device encounters an error.
*/
- (void)device:(ICDevice*)device didEncounterError:(NSError*)error;

@end

//--------------------------------------------------------------------------------------------------------------------- ICDevice
/*! 
  @class ICDevice
  @abstract ICDevice is an abstract class that represents a device supported by Image Capture facility. ImageCaptureCore defines two concrete subclasses of ICDevice, ICCameraDevice and ICScannerDevice. ICDeviceBrowser creates instances of these two subclasses to represent cameras and scanners it finds.
*/

@interface ICDevice : NSObject
{
@private
    id _deviceProperties;
}

/*! 
  @property delegate
  @abstract The delegate to receive messages once a session is opened on the device. It must conform to ICDeviceDelegate protocol. In addition it should respond to selectors defined in ICCameraDeviceDelegate or ICScannerDeviceDelegate protocols in order to effectively interact with the device object. The messages this delegate can expect to receive are described by these protocols.
*/
@property(assign)                       id <ICDeviceDelegate> delegate;

/*!
    @property type
    @abstract ￼The type of the device is either ICDeviceTypeCamera or ICDeviceTypeScanner.

*/
@property(readonly)                     NSString*             type;

/*!
    @property name
    @abstract ￼Name of the device as reported by the device module or by the device transport when a device module is not in control of this device. This name may change if the device module overrides the default name of the device reported by the device's transport, or if the name of the filesystem volume mounted by the device is changed by the user.

*/
@property(readonly)                     NSString*             name;

/*!
    @property icon
    @abstract ￼Icon image for the device.

*/
@property(readonly)                     CGImageRef            icon;

/*!
    @property capabilities
    @abstract ￼The capabilities of the device as reported by the device module. Currently only cameras have capabilities. These are defined above in ICCameraDevice.h.

*/
@property(readonly)                     NSArray*              capabilities;

/*!
    @property modulePath
    @abstract ￼Filesystem path of the device module that is associated with this device.

*/
@property(readonly)                     NSString*             modulePath;

/*!
    @property moduleVersion
    @abstract ￼The bundle version of the device module associated with this device. This may change if an existing device module associated with this device is updated or a new device module for this device is installed.

*/
@property(readonly)                     NSString*             moduleVersion;

/*!
    @property moduleExecutableArchitecture
    @abstract ￼Executable Architecture of the device module in control of this device. This is equal to a value as defined in NSBundle.h or CFBundle.h.

*/
@property(readonly)                     int                   moduleExecutableArchitecture; 

/*!
    @property remote
    @abstract ￼Indicates whether the device is a remote device published by Image Capture device sharing facility.

*/
@property(readonly, getter=isRemote)    BOOL                  remote;

/*!
    @property shared
    @abstract ￼Indicates whether the device is shared using the Image Capture device sharing facility. This value will change when sharing of this device is enabled or disabled.

*/
@property(readonly, getter=isShared)    BOOL                  shared;

/*!
    @property webShared
    @abstract ￼Indicates whether the device is shared over the web using the Image Capture device sharing facility. This value will change when web-sharing of this device is enabled or disabled.

*/
@property(readonly, getter=isWebShared) BOOL                  webShared;

/*!
    @property hasConfigurableWiFiInterface
    @abstract ￼Indicates whether the device can be configured for use on a WiFi network.

*/
@property(readonly)                     BOOL                  hasConfigurableWiFiInterface;

/*!
    @property transportType
    @abstract ￼The transport type used by the device. The possible values are: ICTransportTypeUSB, ICTransportTypeFireWire, ICTransportTypeBluetooth, ICTransportTypeTCPIP, or ICTransportTypeMassStorage.

*/
@property(readonly)                     NSString*             transportType;

/*!
    @property hasOpenSession
    @abstract ￼Indicates whether the device has an open session.

*/
@property(readonly)                     BOOL                  hasOpenSession;

/*! 
  @method requestOpenSession:
  @abstract This message requests to open a session on the device.
  @discussion Make sure the receiver's delegate is set prior to sending this message; otherwise this message will be ignored. This request is completed when the delegate receives a "device:didOpenSessionWithError:" message. No more messages will be sent to the delegate if this request fails.
*/
- (void)requestOpenSession;

/*! 
  @method requestCloseSession
  @abstract This message requests to close a previously opened session on this device.
  @discussion This request is completed when the delegate receives a "device:didCloseSessionWithError:" message. This will be the last message sent to the delegate.
*/
- (void)requestCloseSession;

/*! 
  @method requestYield
  @abstract This message requests the device module in control of this device to yield control.
  @discussion This message should be used only if the client is planning on communiting with the device directly. The device module may not yield control of the device if it has an open session.
*/
- (void)requestYield;

@end

//------------------------------------------------------------------------------------------------------------------------------
