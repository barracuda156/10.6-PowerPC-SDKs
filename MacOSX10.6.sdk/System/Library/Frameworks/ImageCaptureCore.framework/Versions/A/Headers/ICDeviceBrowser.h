//------------------------------------------------------------------------------------------------------------------------------
//
//  ICDeviceBrowser.h
//  ImageCaptureCore
//
//  Copyright (c) 2008 Apple, Inc., all rights reserved.
//
//  Best viewed with the following settings: Tab width 4, Indent width 2, Wrap lines, Indent wrapped lines by 3, Page guide 128.
//
//------------------------------------------------------------------------------------------------------------------------------
/*!
	@header ICDeviceBrowser
    @discussion The ICDeviceBrowser object is used to find devices such as digital cameras and scanners that are supported by Image Capture. These device may be directly attached to the USB or FireWire bus on the host computer, shared by other computers, or available over a TCP/IP network. This object communicates with an Image Capture agent process asynchronously to accomplish this. There is only one instance of this class per process.
*/

@class ICDeviceBrowser;
@class ICDevice;

//------------------------------------------------------------------------------------------------------------------------------
// Constants used to identify the type of a device.
/*!
    @const      ICDeviceTypeCamera
    @abstract   ICDeviceTypeCamera
    @discussion Indicates that the device is a camera.
*/
extern NSString *const ICDeviceTypeCamera;

/*!
    @const      ICDeviceTypeScanner
    @abstract   ICDeviceTypeScanner
    @discussion Indicates that the device is a scanner.
*/
extern NSString *const ICDeviceTypeScanner;

//------------------------------------------------------------------------------------------------------ ICDeviceBrowserDelegate
/*! 
  @protocol ICDeviceBrowserDelegate <NSObject>
  @abstract A delegate of ICDeviceBrowser must conform to ICDeviceBrowserDelegate protocol. 
*/
@protocol ICDeviceBrowserDelegate <NSObject>

@required

/*! 
  @method deviceBrowser:didAddDevice:moreComing:
  @abstract This message is sent to the delegate to inform that a device has been added.
  @discussion If several devices are found during the initial search, then this message is sent once for each device with the value of 'moreComing' set to YES in each message except the last one. 
*/
- (void)deviceBrowser:(ICDeviceBrowser*)browser didAddDevice:(ICDevice*)device moreComing:(BOOL)moreComing;

/*! 
  @method deviceBrowser:didRemoveDevice:moreGoing:
  @abstract This message is sent to the delegate to inform that a device has been removed.
  @discussion If several devices are removed at the same time, then this message is sent once for each device with the value of 'moreGoing' set to YES in each message except the last one. 
*/
- (void)deviceBrowser:(ICDeviceBrowser*)browser didRemoveDevice:(ICDevice*)device moreGoing:(BOOL)moreGoing;

@optional

/*! 
  @method deviceBrowser:deviceDidChangeName:
  @abstract This message is sent if the name of a device changes.
  @discussion This happens if the device module overrides the default name of the device reported by the device's transport layer, or if the name of the filesystem volume mounted by the device is changed by the user.
*/
- (void)deviceBrowser:(ICDeviceBrowser*)browser deviceDidChangeName:(ICDevice*)device;

/*! 
  @method deviceBrowser:deviceDidChangeSharingState:
  @abstract This message is sent when the sharing state of a device has changes.
  @discusson Any Image Capture client application can choose to share the device over the network using the sharing or webSharing facility in Image Capture.
*/
- (void)deviceBrowser:(ICDeviceBrowser*)browser deviceDidChangeSharingState:(ICDevice*)device;

/*! 
  @method deviceBrowser:requestsSelectDevice:
  @abstract This message is sent when an event that occurred on the device that may be of interest to the client application.
  @discussion In Mac OS X 10.6, this message is sent when a button is pressed on a device and the current application is the target for that button press. In the case of the button-press event, if a session is open on the device, this message will not be sent to the browser delegate, instead the message 'device:didReceiveButtonPress:' is sent to the device delegate.
*/
- (void)deviceBrowser:(ICDeviceBrowser*)browser requestsSelectDevice:(ICDevice*)device;

@end

//-------------------------------------------------------------------------------------------------------------- ICDeviceBrowser
/*! 
  @class ICDeviceBrowser
  @abstract The ICDeviceBrowser object is used to find devices such as digital cameras and scanners that are supported by Image Capture. These device may be directly attached to the USB or FireWire bus on the host computer, shared by other computers, or available over a TCP/IP network. This object communicates with an Image Capture agent process asynchronously to accomplish this. There is only one instance of this class per process.
*/
@interface ICDeviceBrowser : NSObject
{
@private
    id _privateData;
}

/*! 
  @property delegate
  @abstract The delegate. It must conform to ICDeviceBrowserDelegate protocol. The messages this delegate can expect to receive are described by ICDeviceBrowserDelegate protocol.
*/
@property(assign)     id <ICDeviceBrowserDelegate>  delegate;

/*! 
  @property browsing
  @abstract Indicates whether the device browser is browsing for devices.
*/
@property(readonly)   BOOL                          browsing;

/*! 
  @property devices
  @abstract All devices found by the browser. This property will change as devices appear and disappear.
*/
@property(readonly)   NSArray*                      devices;

/*! 
  @method sharedDeviceBrowser
  @abstract This is the designated initializer.
*/
- (id)init;

/*! 
  @method start:
  @abstract This message tells the receiver to start looking for devices supported by Image Capture.
  @discussion Make sure that the receiver's delegate is set prior to sending this message; otherwise this message will be ignored. The messages the delegate can expect to receive are described by ICDeviceBrowserDelegate protocol.
*/
- (void)start;

/*! 
  @method startBrowsingForCameras:
  @abstract This message tells the receiver to start looking for cameras supported by Image Capture.
  @discussion Make sure that the receiver's delegate is set prior to sending this message; otherwise this message will be ignored. The messages the delegate can expect to receive are described by ICDeviceBrowserDelegate protocol.
*/
- (void)startBrowsingForCameras;

/*! 
  @method startBrowsingForScanners:
  @abstract This message tells the receiver to start looking for scanners supported by Image Capture.
  @discussion Make sure that the receiver's delegate is set prior to sending this message; otherwise this message will be ignored. The messages the delegate can expect to receive are described by ICDeviceBrowserDelegate protocol.
*/
- (void)startBrowsingForScanners;

/*! 
  @method stop:
  @abstract This method tells the receiver to stop looking for devices supported by Image Capture.
  @discussion This will free all device instances that are not in use.
*/
- (void)stop;

@end

//------------------------------------------------------------------------------------------------------------------------------
