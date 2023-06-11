//
//  IKScannerView.h
//  ImageKit
//
//  Copyright 2008 Apple Inc.. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import <ImageCaptureCore/ImageCaptureCore.h>

@class IKScannerDeviceView;


/*! 
 @protocol IKScannerDeviceViewDelegate
 @abstract A delegate of IKScannerDeviceView must conform to IKScannerDeviceViewDelegate protocol.
 */
@protocol IKScannerDeviceViewDelegate
@optional
/*! 
 @method scannerDeviceView:didScanToURL:fileData:error:
 @abstract This message is sent for each image that gets scanned.
 @discussion Based on the IKScannerDeviceViewTransferMode the downloaded file will be saved on disk using the 'url', or returned in memory as NSData
 */
- (void)scannerDeviceView: (IKScannerDeviceView *)scannerDeviceView
             didScanToURL: (NSURL *)url
                 fileData: (NSData *)data
                    error: (NSError*)error;

/*! 
 @method scannerDeviceView:didEncounterError:
 @abstract This message is sent every time the scanner device reports an error.
 */
- (void)scannerDeviceView: (IKScannerDeviceView *)scannerDeviceView
        didEncounterError: (NSError*)error;
@end




enum 
{
    IKScannerDeviceViewTransferModeFileBased = 0,
    IKScannerDeviceViewTransferModeMemoryBased
    
};
typedef NSInteger IKScannerDeviceViewTransferMode;



enum 
{
        IKScannerDeviceViewDisplayModeSimple,
        IKScannerDeviceViewDisplayModeAdvanced
};
typedef NSInteger IKScannerDeviceViewDisplayMode;




/*! 
 @class IKScannerDeviceView
 @abstract IKScannerDeviceView displays a UI to work with Image Capture supported scanners.
 */
@interface IKScannerDeviceView : NSView 
{
@private
    id _privateData;
}

// delegate of the IKScannerDeviceView
@property (assign)      id<IKScannerDeviceViewDelegate> delegate;

// the scanner device 
@property (assign)      ICScannerDevice *               scannerDevice;

// current display mode 
@property               IKScannerDeviceViewDisplayMode  mode;

// support a simple scanning UI 
@property               BOOL                            hasDisplayModeSimple;

// support advanced scanning UI 
@property               BOOL                            hasDisplayModeAdvanced;
    
// transfer mode either file based - or - in memory
@property               IKScannerDeviceViewTransferMode transferMode;

// label for the 'Scan' control
@property (copy)        NSString *                      scanControlLabel;

// label for the 'Overview' control
@property (copy)        NSString *                      overviewControlLabel;

// show a downloads directory control
@property               BOOL                            displaysDownloadsDirectoryControl;

// downloads directory
@property (retain)      NSURL *                         downloadsDirectory;

// document name
@property (copy)        NSString *                      documentName;

// show a postprocessing application control
@property               BOOL                            displaysPostProcessApplicationControl;

// postprocessing application
@property (retain)      NSURL *                         postProcessApplication;

@end
