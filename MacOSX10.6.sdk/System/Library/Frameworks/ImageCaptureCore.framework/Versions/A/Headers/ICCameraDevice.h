//------------------------------------------------------------------------------------------------------------------------------
//
//  ICCameraDevice.h
//  ImageCaptureCore
//
//  Copyright (c) 2008 Apple Inc., all rights reserved.
//
//  Best viewed with the following settings: Tab width 4, Indent width 2, Wrap lines, Indent wrapped lines by 3, Page guide 128.
//
//------------------------------------------------------------------------------------------------------------------------------
/*!
	@header ICCameraDevice
    ICCameraDevice is a concrete subclass of ICDevice class. ICDeviceBrowser creates instances of this class.
*/

#import <ImageCaptureCore/ICDevice.h>
#import <ImageCaptureCore/ICCameraItem.h>

//------------------------------------------------------------------------------------------------------------------------------
// Constants used to describe capabilities of a camera

/*!
    @const      ICCameraDeviceCanTakePicture
    @abstract   ICCameraDeviceCanTakePicture
    @discussion Indicates that the camera can capture shoot a picture while it is connected.
*/
extern NSString *const ICCameraDeviceCanTakePicture;

/*!
    @const      ICCameraDeviceCanDeleteOneFile
    @abstract   ICCameraDeviceCanDeleteOneFile
    @discussion Indicates that the camera can delete a file at a time while it is connected.
*/
extern NSString *const ICCameraDeviceCanDeleteOneFile;

/*!
    @const      ICCameraDeviceCanDeleteAllFiles
    @abstract   ICCameraDeviceCanDeleteAllFiles
    @discussion Indicates that the camera can delete all files in a single operation while it is connected. 
*/
extern NSString *const ICCameraDeviceCanDeleteAllFiles;

/*!
    @const      ICCameraDeviceCanSyncClock
    @abstract   ICCameraDeviceCanSyncClock
    @discussion Indicates that the camera can synchronize its date and time with that of the host computer.
*/
extern NSString *const ICCameraDeviceCanSyncClock;

/*!
    @const      ICCameraDeviceCanReceiveFile
    @abstract   ICCameraDeviceCanReceiveFile
    @discussion Indicates that the host can upload files to the camera.
*/
extern NSString *const ICCameraDeviceCanReceiveFile;

/*!
    @const      ICCameraDeviceCanEject
    @abstract   ICCameraDeviceCanEject
    @discussion Indicates that the device is mounted as an ejectable mass-storage volume.
*/
extern NSString *const ICCameraDeviceCanEject;

//------------------------------------------------------------------------------------------------------------------------------
// Allowed keys in the options dictionary used when downloading a file from the camera

/*!
    @const      ICDownloadsDirectoryURL
    @abstract   ICDownloadsDirectoryURL
    @discussion The value for this key should be an NSURL object referencing a writable directory. The downloaded files will be saved in that directory.
*/
extern NSString *const ICDownloadsDirectoryURL;

/*!
    @const      ICSaveAsFilename
    @abstract   ICSaveAsFilename
    @discussion The value for this key should be an NSString object holding the name to be used for the downloaded file.
*/
extern NSString *const ICSaveAsFilename;

/*!
    @const      ICSavedFilename
    @abstract   ICSavedFilename
    @discussion The value for this key will be an NSString object holding the actual name of the saved file. The options dictionary returned in didDownloadFile:error:options:contextInfo: will have this key. 
*/
extern NSString *const ICSavedFilename;

/*!
    @const      ICOverwrite
    @abstract   ICOverwrite
    @discussion The value for this key should be an NSNumber object representing a boolean value. If this value is YES, the downloaded file will overwrite an existing file with the same name and extension.
*/
extern NSString *const ICOverwrite;

/*!
    @const      ICEXIFOrientation
    @abstract   ICEXIFOrientation
    @discussion The value for this key should be a NSNumber object whose integer value ranges from 1 to 8. The meaning of this values is defined by the EXIF specification. Here is what the letter F would look like if it were tagged correctly and displayed by a program that ignores the orientation tag (thus showing the stored image):

               1             2             3             4

            8888888       8888888            88       88
            88                 88            88       88
            8888             8888          8888       8888
            88                 88            88       88
            88                 88       8888888       8888888

               5             6             7             8

            8888888888    88                    88    8888888888
            88  88        88  88            88  88        88  88
            88            8888888888    8888888888            88

*/
extern NSString *const ICEXIFOrientation;

//--------------------------------------------------------------------------------------------------------- Forward Declarations

@class ICCameraDevice;

//------------------------------------------------------------------------------------------------------- ICCameraDeviceDelegate
/*! 
  @protocol ICCameraDeviceDelegate  <ICDeviceDelegate>
  @abstract A delegate of ICCameraDevice must conform to ICCameraDeviceDelegate protocol.
  @discussion The ICCameraDeviceDelegate protocol inherits from the ICDeviceDelegate protocol.
*/

@protocol ICCameraDeviceDelegate  <ICDeviceDelegate>

@optional

/*! 
  @method cameraDevice:didAddItem:
  @abstract This message is sent when an object is added to the device.
  @discussion The object may be an instance of ICCameraFolder or ICCameraFile class.
*/
- (void)cameraDevice:(ICCameraDevice*)camera didAddItem:(ICCameraItem*)item;

/*! 
  @method cameraDevice:didRemoveItem:
  @abstract This message is sent when an object is removed from the device.
  @discussion The object may be an instance of ICCameraFolder or ICCameraFile class.
*/
- (void)cameraDevice:(ICCameraDevice*)camera didRemoveItem:(ICCameraItem*)item;

/*! 
  @method cameraDeviceDidChangeCapability:
  @abstract This message is sent when the capability of a device changes.
  @discussion This usually happens when the device module takes control or yields control of the device.
*/
- (void)cameraDeviceDidChangeCapability:(ICCameraDevice*)camera;

/*! 
  @method cameraDevice:didReceiveThumbnailForItem:
  @abstract This message is sent when the thumbnail requested for an item on a device is available.
*/
- (void)cameraDevice:(ICCameraDevice*)camera didReceiveThumbnailForItem:(ICCameraItem*)item;

/*! 
  @method cameraDevice:didReceiveMetadataForItem:
  @abstract This message is sent when the metadata requested for an item on a device is available.
*/
- (void)cameraDevice:(ICCameraDevice*)camera didReceiveMetadataForItem:(ICCameraItem*)item;

@end

//--------------------------------------------------------------------------------------------------------------- ICCameraDevice
/*!
	@class ICCameraDevice
    @abstract ICCameraDevice is a concrete subclass of ICDevice class. ICDeviceBrowser creates instances of this class.
*/

@interface ICCameraDevice : ICDevice
{
@private
    id _cameraProperties;
}

/*!
    @property batteryLevelAvailable
    @abstract Indicates if the device has reported battery charge level￼.

*/
@property(readonly)   BOOL          batteryLevelAvailable;

/*!
    @property batteryLevel
    @abstract ￼Indicates the battery charge level. Its value ranges from 0 to 100.

*/
@property(readonly)   NSUInteger    batteryLevel;

/*!
    @property contentCatalogPercentCompleted
    @abstract ￼Indicates the percentage of content cataloging completed on the device. Its value ranges from 0 to 100.

*/
@property(readonly)   NSUInteger    contentCatalogPercentCompleted;

/*!
    @property contents
    @abstract ￼Contents of the camera. The structure of the elements in this array will reflect the folder structure of the storage reported by the camera. Each item in this array will correspond to a storage on the camera.

*/
@property(readonly)   NSArray*      contents;

/*!
    @property mediaFiles
    @abstract ￼The property mediaFiles represents all image, movie and audio files on the camera. These files are returned as a single array without regard to the folder hierarchy used to store these files on the camera.

*/
@property(readonly)   NSArray*      mediaFiles;


/*! 
  @method filesOfType:
  @abstract This method returns an array of files on the camera of type fileType. 
  @discussion The fileType string is one of the following Uniform Type Identifier strings: kUTTypeImage, kUTTypeMovie, kUTTypeAudio, or kUTTypeData.
*/
- (NSArray*)filesOfType:(NSString*)fileUTType;

/*! 
  @method requestSyncClock
  @abstract Synchronize camera's clock with the computer's clock.
*/
- (void)requestSyncClock;

/*! 
  @method requestTakePicture
  @abstract Capture a new image using the camera.
*/
- (void)requestTakePicture;

/*! 
  @method requestDeleteFiles
  @abstract Deletes files.
*/
- (void)requestDeleteFiles:(NSArray*)files;

/*! 
  @method requestEject
  @abstract Eject the media if permitted by the device.
*/
- (void)requestEject;

/*! 
  @method requestDownloadFile:options:downloadDelegate:didDownloadSelector:contextInfo:
  @abstract Download a file from the camera. Please refer to the top of this header for information about the options.
  @discussion The downloadDelegate passed must not be nil. When this request is completed, the didDownloadSelector of the downloadDelegate object is called. The content of error returned should be examined to determine if the request completed successfully. The didDownloadSelector should have the same signature as: - (void)didDownloadFile:(ICCameraFile*)file error:(NSError*)error options:(NSDictionary*)options contextInfo:(void*)contextInfo.
*/
- (void)requestDownloadFile:(ICCameraFile*)file options:(NSDictionary*)options downloadDelegate:(id)downloadDelegate didDownloadSelector:(SEL)selector contextInfo:(void*)contextInfo;

/*! 
  @method requestUploadFile:options:uploadDelegate:didUploadSelector:contextInfo:
  @abstract Upload a file at fileURL to the camera. The options dictionary is not used in this version.
  @discussion The uploadDelegate passed must not be nil. When this request is completed, the didUploadSelector of the uploadDelegate object is called. The content of error returned should be examined to determine if the request completed successfully. The didUploadSelector should have the same signature as: - (void)didUploadFile:(NSURL*)fileURL error:(NSError*)error contextInfo:(void*)contextInfo.
*/
- (void)requestUploadFile:(NSURL*)fileURL options:(NSDictionary*)options uploadDelegate:(id)uploadDelegate didUploadSelector:(SEL)selector contextInfo:(void*)contextInfo;

/*! 
  @method requestReadDataFromFile:atOffset:length:delegate:didReadDataSelector:contextInfo:
  @abstract This method asynchronously reads data of a specified length from a specified offset.
  @discussion The readDelegate passed must not be nil. When this request is completed, the didReadDataSelector of the readDelegate object is called. The content of error returned should be examined to determine if the request completed successfully. The didReadDataSelector should have the same signature as: - (void)didReadData:(NSData*)data fromFile:(ICCameraFile*)file error:(NSError*)error contextInfo:(void*)contextInfo.
*/
- (void)requestReadDataFromFile:(ICCameraFile*)file atOffset:(off_t)offset length:(off_t)length readDelegate:(id)readDelegate didReadDataSelector:(SEL)selector contextInfo:(void*)contextInfo;

/*! 
  @method requestReadDataFromOffset:length:delegate:didReadDataSelector:contextInfo:
  @abstract This method asynchronously sends a message to the device.
  @discussion Image Capture enables client applications that know about the communication protocol used by the device to send messages to the device. The message and the payload are passed between the cient application and the device without as-is.
*/
- (void)requestSendMessage:(NSUInteger)messageType payload:(NSMutableData**)payload messageDelegate:(id)delegate didSendMessageSelector:(SEL)selector contextInfo:(void*)contextInfo;

@end

//------------------------------------------------------------------------------------------------------------------------------

