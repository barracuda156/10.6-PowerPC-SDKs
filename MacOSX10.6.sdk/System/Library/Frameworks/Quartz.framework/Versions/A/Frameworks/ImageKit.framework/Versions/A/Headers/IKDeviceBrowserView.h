//
//  IKDeviceBrowserView.h
//  ImageKit
//
//  Copyright 2008 Apple Inc.. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import <ImageCaptureCore/ImageCaptureCore.h>

@class IKDeviceBrowserView;


/*! 
 @protocol IKDeviceBrowserViewDelegate
 @abstract A delegate of IKDeviceBrowserView must conform to IKDeviceBrowserViewDelegate protocol.
 */

@protocol IKDeviceBrowserViewDelegate
@required
/*! 
 @method deviceBrowserView:selectionDidChange:
 @abstract This message is sent when the user selection did change.
 @discussion The device may be a ICCameraDevice or a ICScannerDevice.
 */
- (void)deviceBrowserView: (IKDeviceBrowserView*)deviceBrowserView
       selectionDidChange: (ICDevice*)device;

@optional
/*! 
 @method deviceBrowserView:didEncounterError:
 @abstract This message is sent every time the device browser reports an error.
 */
- (void)deviceBrowserView: (IKDeviceBrowserView*)deviceBrowserView
        didEncounterError: (NSError*)error;

@end




enum 
{
    IKDeviceBrowserViewDisplayModeTable,
    IKDeviceBrowserViewDisplayModeOutline,
    IKDeviceBrowserViewDisplayModeIcon
};
typedef NSInteger IKDeviceBrowserViewDisplayMode;




/*! 
 @class IKDeviceBrowserView
 @abstract IKDeviceBrowserView displays Image Capture cameras and scanners.
 */
@interface IKDeviceBrowserView : NSView
{
@private
    id _privateData;
}

// delegate of the IKDeviceBrowserView
@property (assign)  id<IKDeviceBrowserViewDelegate>  delegate;

// for device filtering - indicates that the IKDeviceBrowserView should include local cameras
@property           BOOL                             displaysLocalCameras;

// for device filtering - indicates that the IKDeviceBrowserView should include network/shared cameras
@property           BOOL                             displaysNetworkCameras;

// for device filtering - indicates that the IKDeviceBrowserView should include local scanners
@property           BOOL                             displaysLocalScanners;

// for device filtering - indicates that the IKDeviceBrowserView should include network/shared scanners
@property           BOOL                             displaysNetworkScanners;

// one of the supported display modes (table, outline, or icon mode)
@property           IKDeviceBrowserViewDisplayMode   mode;

// user selected device (ICCameraDevice or ICScannerDevice)
@property (readonly)ICDevice *                       selectedDevice;
@end
