//
//  IKCameraDeviceView.h
//  ImageKit
//
//  Copyright 2008 Apple Inc.. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import <ImageCaptureCore/ImageCaptureCore.h>

@class IKCameraDeviceView;



/*! 
 @protocol IKCameraDeviceView
 @abstract A delegate of IKCameraDeviceView must conform to IKCameraDeviceViewDelegate protocol.
 */
@protocol IKCameraDeviceViewDelegate
@optional

/*! 
 @method cameraDeviceViewSelectionDidChange:
 @abstract This message is sent when the user selection did change.
 */
- (void)cameraDeviceViewSelectionDidChange: (IKCameraDeviceView *)cameraDeviceView;

/*! 
 @method cameraDeviceView:didDownloadFile:location:fileData:error:
 @abstract This message is sent for each file that gets downloaded.
 @discussion Based on the IKCameraDeviceViewDisplayMode the downloaded file will be saved on disk using the 'url', or returned in memory as NSData
 */
- (void)cameraDeviceView: (IKCameraDeviceView *)cameraDeviceView
         didDownloadFile: (ICCameraFile*)file
                location: (NSURL *)url
                fileData: (NSData *)data
                   error: (NSError*)error;

/*! 
 @method cameraDeviceView:didEncounterError:
 @abstract This message is sent every time the camera device reports an error.
 */
- (void)cameraDeviceView: (IKCameraDeviceView *)cameraDeviceView
       didEncounterError: (NSError*)error;
@end




enum
{
    IKCameraDeviceViewDisplayModeTable = 0,
    IKCameraDeviceViewDisplayModeIcon
    
};
typedef NSInteger IKCameraDeviceViewDisplayMode;

enum
{
    IKCameraDeviceViewTransferModeFileBased = 0,
    IKCameraDeviceViewTransferModeMemoryBased
    
};
typedef NSInteger IKCameraDeviceViewTransferMode;




/*! 
 @class IKCameraDeviceView
 @abstract IKCameraDeviceView displays content of a Image Capture supported camera.
 */
@interface IKCameraDeviceView : NSView
{
@private
    id _privateData;
}

// delegate of the IKCameraDeviceView
@property (assign)      id<IKCameraDeviceViewDelegate>  delegate;

// the camera device 
@property (assign)      ICCameraDevice *                cameraDevice;

// current display mode 
@property               IKCameraDeviceViewDisplayMode   mode;

// support table view display mode 
@property               BOOL                            hasDisplayModeTable;

// support icon view display mode 
@property               BOOL                            hasDisplayModeIcon;

// label for the 'Download All' control - allows for example renaming to 'Import All'
@property (copy)        NSString *                      downloadAllControlLabel;

// label for the 'Download Selected' control
@property (copy)        NSString *                      downloadSelectedControlLabel;

// in icon mode: size of the image thumbnails
@property               NSUInteger                      iconSize;

// transfer mode either file based - or - in memory
@property               IKCameraDeviceViewTransferMode  transferMode;

// show a downloads directory control
@property               BOOL                            displaysDownloadsDirectoryControl;

// downloads directory
@property (retain)      NSURL *                         downloadsDirectory;

// show a postprocessing application control
@property               BOOL                            displaysPostProcessApplicationControl;

// postprocessing application
@property (retain)      NSURL *                         postProcessApplication;

// indicates if the user selected items can be rotated left or right
@property (readonly)    BOOL                            canRotateSelectedItemsLeft;
@property (readonly)    BOOL                            canRotateSelectedItemsRight;

// indicates if the user selected items can be deleted
@property (readonly)    BOOL                            canDeleteSelectedItems;

// indicates if the user selected items can be downloaded
@property (readonly)    BOOL                            canDownloadSelectedItems;


// current user selection
- (NSIndexSet *)selectedIndexes;

// setting current user selection
- (void)selectIndexes: (NSIndexSet *)indexes
 byExtendingSelection: (BOOL)extend;

// rotate selected items left/right
- (void)rotateLeft: (id)sender; 
- (void)rotateRight: (id)sender;

// delete selected items
- (void)deleteSelectedItems: (id)sender;

// download selected items
- (void)downloadSelectedItems: (id)sender;

// download all items
- (void)downloadAllItems: (id)sender;
@end

