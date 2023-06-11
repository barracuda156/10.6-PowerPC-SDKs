/*
	NSWorkspace.h
	Application Kit
	Copyright (c) 1994-2007, Apple Inc.
	All rights reserved.
*/

#import <Foundation/NSObject.h>
#import <Foundation/NSGeometry.h>
#import <Foundation/NSAppleEventDescriptor.h>
#import <AppKit/AppKitDefines.h>

@class NSArray, NSError, NSImage, NSView, NSNotificationCenter, NSURL, NSScreen;

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_3
typedef NSUInteger NSWorkspaceLaunchOptions;
enum {
     NSWorkspaceLaunchAndPrint = 0x00000002,
     NSWorkspaceLaunchInhibitingBackgroundOnly = 0x00000080,
     NSWorkspaceLaunchWithoutAddingToRecents = 0x00000100,
     NSWorkspaceLaunchWithoutActivation = 0x00000200,
     NSWorkspaceLaunchAsync = 0x00010000,
     NSWorkspaceLaunchAllowingClassicStartup = 0x00020000,
     NSWorkspaceLaunchPreferringClassic = 0x00040000,
     NSWorkspaceLaunchNewInstance = 0x00080000,
     NSWorkspaceLaunchAndHide = 0x00100000,
     NSWorkspaceLaunchAndHideOthers = 0x00200000,
     // NSWorkspaceLaunchAndDisplayFailures
     NSWorkspaceLaunchDefault = NSWorkspaceLaunchAsync | 
NSWorkspaceLaunchAllowingClassicStartup
};
#endif

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4
typedef NSUInteger NSWorkspaceIconCreationOptions;
enum {
    NSExcludeQuickDrawElementsIconCreationOption    = 1 << 1,
    NSExclude10_4ElementsIconCreationOption	    = 1 << 2
};
#endif

@interface NSWorkspace : NSObject {
  /*All instance variables are private*/
  @private
    NSNotificationCenter *notificationCenter;
#if ! __LP64__
    int deviceStatusCount;
    int applicationStatusCount;
#endif
    id _reservedWorkspace1;
}

/* Get the shared instance of NSWorkspace.  This method will create an instance of NSWorkspace if it has not been created yet.  You should not attempt to instantiate instances of NSWorkspace yourself, and you should not attempt to subclass NSWorkspace. */
+ (NSWorkspace *)sharedWorkspace;

/* Returns the NSNotificationCenter for this NSWorkspace.  All notifications in this header file must be registered on this notifcation center.  If you register on other notification centers, you will not receive the notifications. */
- (NSNotificationCenter *)notificationCenter;

/* Open a file at some path.  If you use the variant without the withApplication: parameter, or if you pass nil for this parameter, the default application is used.  The appName parameter may be a full path to an application, or just the application's name, with or without the .app extension.  If you pass YES for andDeactivate:, or call a variant without this parameter, the calling app is deactivated before the new app is launched, so that the new app may come to the foreground unless the user switches to another application in the interim.  Passing YES for andDeactivate: is generally recommended.
 */
- (BOOL)openFile:(NSString *)fullPath;
- (BOOL)openFile:(NSString *)fullPath withApplication:(NSString *)appName;
- (BOOL)openFile:(NSString *)fullPath withApplication:(NSString *)appName andDeactivate:(BOOL)flag;

/* Open a file with an animation.  This currently does the same thing as openFile: and its use is discouraged. */
- (BOOL)openFile:(NSString *)fullPath fromImage:(NSImage *)anImage at:(NSPoint)point inView:(NSView *)aView;

/* Open a URL, using the default handler for the URL's scheme. */
- (BOOL)openURL:(NSURL *)url;

/* Launches an application.  The appName may be a full path to the app, or the name alone, with or without the .app extension. */
- (BOOL)launchApplication:(NSString *)appName;

/* This currently does the same thing as launchApplication:.  Its use is discouraged. */
- (BOOL)launchApplication:(NSString *)appName showIcon:(BOOL)showIcon autolaunch:(BOOL)autolaunch;

/* Get the full path for a given application name, which may or may not have the .app extension.  This indicuates the application that will be opened by methods such as launchApplication:.  If the application could not be found, returns nil. */
- (NSString *)fullPathForApplication:(NSString *)appName;

/* Activate the Finder and open a window selecting the file at the given path.  If fullPath is nil, this will instead open the directory specified by rootFullPath, and not select any file. */
- (BOOL)selectFile:(NSString *)fullPath inFileViewerRootedAtPath:(NSString *)rootFullPath;

/* Displays a Spotlight search results window in Finder for the specified query string. Finder becomes the active application, if possible. The user can further refine the search via the Finder UI. Returns YES if the communication with Finder was successful.
 */
- (BOOL)showSearchResultsForQueryString:(NSString *)queryString AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

/* noteFileSystemChanged: informs listeners of a filesystem change, using the FNNotifyByPath() API.  As the FNNotify API has been supplanted by the FSEvents API, the use of this method is discouraged. */
- (void)noteFileSystemChanged:(NSString *)path;

/* Get, by reference, the name of the app used to open a file at the given path, and the type of the file.  The type of the file will either be a filename extension or an HFS type encoded with NSFileTypeForHFSTypeCode(). Both strings are returned autoreleased.  The method returns YES if successful, NO if not. */
- (BOOL)getInfoForFile:(NSString *)fullPath application:(NSString **)appName type:(NSString **)type;

/* Indicates whether a given directory is a package.  Returns YES if the file is a package, NO if not, or if the file does not exist or the operation otherwise failed.  A file may be a package because its filename extension indicates so (for example, .framework) or because it has the package bit set. */
- (BOOL)isFilePackageAtPath:(NSString *)fullPath;

/* Returns the icon for a file at a given path, or a generic icon if the operation fails. */
- (NSImage *)iconForFile:(NSString *)fullPath;

/* Returns the icon for a group of files at the given paths. */
- (NSImage *)iconForFiles:(NSArray *)fullPaths;

/* Get the icon for a given file type.  The file type may be a filename extension, or a HFS code encoded via NSFileTypeForHFSTypeCode, or a Universal Type Identifier (UTI).   Returns a default icon if the operation fails.  */
- (NSImage *)iconForFileType:(NSString *)fileType;

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4

/* If image is not nil, this sets a custom icon for the file at the given path.  If image is nil, this removes any custom icon at the given path.  Returns YES if successful, NO if not. */
- (BOOL)setIcon:(NSImage *)image forFile:(NSString *)fullPath options:(NSWorkspaceIconCreationOptions)options;
#endif

/* Get the array of file labels as NSStrings.  The file label index for a particular file is available as a property on the URL.  You may listen for NSWorkspaceDidChangeFileLabelsNotification to be notified when these change. */
- (NSArray *)fileLabels;

/* Get the corresponding array of file label colors.  This array has the same number of elements as fileLabels, and the color at a given index corresponds to the label at the same index . You may listen for NSWorkspaceDidChangeFileLabelsNotification to be notified when these change. */
- (NSArray *)fileLabelColors;

/* Gets information about the filesystem.  fullPath is the path to any file or directory on the filesystem, including the filesystem's mount point.  The returned values have the following significance:
   - isRemovable: whether the filesytem is backed by removable media, such as a CD or floppy disk.
   - isWritable: whether the filesystem can be written to
   - isUnmountable: whether the filesystem can be unmounted.
   - description: typically the type of the volume or the name of the filesystem
   - the file system type, for example, 'hfs'
*/
- (BOOL)getFileSystemInfoForPath:(NSString *)fullPath isRemovable:(BOOL *)removableFlag isWritable:(BOOL *)writableFlag isUnmountable:(BOOL *)unmountableFlag description:(NSString **)description type:(NSString **)fileSystemType;

/* Performs the given file operation, blocking until complete.  source should be the directory containing the file(s).  For operations that require a destination, such as Move and Copy, destination should be the destination directory; otherwise it should be nil.  files is an array of file names that are in the source directory.
 A value is returned by reference in the tag parameter, either 0 for success, or -1 for failure.  tag may be NULL.
 */
- (BOOL)performFileOperation:(NSString *)operation source:(NSString *)source destination:(NSString *)destination files:(NSArray *)files tag:(NSInteger *)tag;

/* Attempt to eject the volume mounted at the given path.  Returns YES if successful, NO if not, for example, if the volume is not ejectable. */
- (BOOL)unmountAndEjectDeviceAtPath:(NSString *)path;

/* extendPowerOffBy: is currently not implemented.  Do not use it. */
- (NSInteger)extendPowerOffBy:(NSInteger)requested;

/* Attempt to hide all other applications. */
- (void)hideOtherApplications;

/* Get the mount paths of all local volumes, that is, volumes that are backed by a physical device and are not a network mount. */
- (NSArray *)mountedLocalVolumePaths;

/* Get the mount paths of all volumes backed by removable media, such as DVDs. */
- (NSArray *)mountedRemovableMedia;

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_3
/* Get the path for the application with the given identifier.  This uses various heuristics in case multiple apps have the same bundle ID. */
- (NSString *)absolutePathForAppBundleWithIdentifier:(NSString *)bundleIdentifier; 

/* The following methods launch an app with the given bundle identifier.  The descriptor describes the first AppleEvent to be sent to the process.  The launchIdentifier is currently of no significance.
If the application is already running, and NSWorkspaceLaunchNewInstance is not specified in the options, then the descriptor is delivered to the currently running app, and YES is returned.
 */
- (BOOL)launchAppWithBundleIdentifier:(NSString *)bundleIdentifier options:(NSWorkspaceLaunchOptions)options additionalEventParamDescriptor:(NSAppleEventDescriptor *)descriptor launchIdentifier:(NSNumber **)identifier;
- (BOOL)openURLs:(NSArray *)urls withAppBundleIdentifier:(NSString *)bundleIdentifier options:(NSWorkspaceLaunchOptions)options additionalEventParamDescriptor:(NSAppleEventDescriptor *)descriptor launchIdentifiers:(NSArray **)identifiers;
#endif

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_2

/* The following methods return information about an application as a dictionary containing as many of the following keys as are available:
        NSApplicationPath (the full path to the application, as a string)
        NSApplicationName (the application's name, as a string)
        NSApplicationBundleIdentifier (the application's bundle identifier, as a string)
        NSApplicationProcessIdentifier (the application's process id, as an NSNumber)
        NSApplicationProcessSerialNumberHigh (the high long of the PSN, as an NSNumber)
        NSApplicationProcessSerialNumberLow (the low long of the PSN, as an NSNumber)
   The same information will now be provided in the userInfo of the NSWorkspace notifications for application launch and termination.
*/

/* Gets an array of NSDictionaries with the above keys.  In addition, the NSWorkspaceApplicationKey is provided, and vends an instance of NSRunningApplication. The -[NSWorkspace runningApplications] method, declared in NSRunningApplication.h, provides more information. */
- (NSArray *)launchedApplications;

/* Get an NSDictionary representing the currently frontmost app, with the above keys.  The NSWorkspaceApplicationKey is also provided. */
- (NSDictionary *)activeApplication;

#endif

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5

/* Given an absolute file path, return the uniform type identifier (UTI) of the file, if one can be determined. Otherwise, return nil after setting *outError to an NSError that encapsulates the reason why the file's type could not be determined. If the file at the end of the path is a symbolic link the type of the symbolic link will be returned.

You can invoke this method to get the UTI of an existing file.
*/
- (NSString *)typeOfFile:(NSString *)absoluteFilePath error:(NSError **)outError;

/* Given a UTI, return a string that describes the document type and is fit to present to the user, or nil for failure.

You can invoke this method to get the name of a type that must be shown to the user, in an alert about your application's inability to handle the type, for instance.
*/
- (NSString *)localizedDescriptionForType:(NSString *)typeName;

/* Given a UTI, return the best file name extension to use when creating a file of that type, or nil for failure.

You can invoke this method when your application has only the base name of a file that's being written and it has to append a file name extension so that the file's type can be reliably identified later on.
*/
- (NSString *)preferredFilenameExtensionForType:(NSString *)typeName;

/* Given a file name extension and a UTI, return YES if the file name extension is a valid tag for the identified type, NO otherwise.

You can invoke this method when your application needs to check if a file name extension can be used to reliably identify the type later on. For example, NSSavePanel uses this method to validate any extension that the user types in the panel's file name field.  
*/
- (BOOL)filenameExtension:(NSString *)filenameExtension isValidForType:(NSString *)typeName;

/* Given two UTIs, return YES if the first "conforms to" to the second in the uniform type identifier hierarchy, NO otherwise. This method will always return YES if the two strings are equal, so you can also use it with other kinds of type name, including those declared in CFBundleTypeName Info.plist entries in apps that don't take advantage of the support for UTIs that was added to Cocoa in Mac OS 10.5.

You can invoke this method when your application must determine whether it can handle a file of a known type, returned by -typeOfFile:error: for instance.
    
Use this method instead of merely comparing UTIs for equality.
*/
- (BOOL)type:(NSString *)firstTypeName conformsToType:(NSString *)secondTypeName;

#endif

@end


/* Desktop images */
@interface NSWorkspace (NSDesktopImages)

/* Sets the desktop image for the given screen to the image at the given URL.  The URL must be a file URL and may not be nil.  The options dictionary may contain any of the NSWorkspaceDesktopImage keys, which control how the image is scaled on the screen.  This returns YES if the image was successfully set; otherwise, NO is returned and an error is returned by reference.
 */
- (BOOL)setDesktopImageURL:(NSURL *)url forScreen:(NSScreen *)screen options:(NSDictionary *)options error:(NSError **)error AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

/* Returns the URL for the desktop image for the given screen.
 */
- (NSURL *)desktopImageURLForScreen:(NSScreen *)screen AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

/* Returns the options dictionary for the desktop image for the given screen.
 */
- (NSDictionary *)desktopImageOptionsForScreen:(NSScreen *)screen AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

@end

/* The following keys may be specified or returned in the options dictionary for setDesktopImageURL:forScreen:options:error: and desktopImageURLForScreen:options:. */

/* The value is an NSNumber containing an NSImageScaling.  If this is not specified, NSImageScaleProportionallyUpOrDown is used.  Note: NSImageScaleProportionallyDown is not currently supported.
 */
APPKIT_EXTERN NSString * const NSWorkspaceDesktopImageScalingKey AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

/* The value is an NSNumber containing a BOOL, which affects the interpretation of Proportional scaling types.  A NO value will make the image fully visible, but there may be empty space on the sides or top and bottom.  A YES value will cause the image to fill the entire screen, but the image may be clipped.  If this is not specified, NO is assumed.  Non-proportional scaling types ignore this value.
 */
APPKIT_EXTERN NSString * const NSWorkspaceDesktopImageAllowClippingKey AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

/* The value is an NSColor, which is used to fill any empty space around the image.  If not specified, a default value is used.  Currently, only colors that use or can be converted to use NSCalibratedRGBColorSpace are supported, and any alpha value is ignored.
 */
APPKIT_EXTERN NSString * const NSWorkspaceDesktopImageFillColorKey AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;


/* Application notifications */

/* In Mac OS X 10.6 and later, all application notifications have the following key in their userInfo:.  Its value is an instance of NSRunningApplication, representing the affected app.
 */
APPKIT_EXTERN NSString * const NSWorkspaceApplicationKey AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

APPKIT_EXTERN NSString * const NSWorkspaceWillLaunchApplicationNotification;	//	see above
APPKIT_EXTERN NSString * const NSWorkspaceDidLaunchApplicationNotification;	//	see above
APPKIT_EXTERN NSString * const NSWorkspaceDidTerminateApplicationNotification;	//	see above
APPKIT_EXTERN NSString * const NSWorkspaceDidHideApplicationNotification AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;
APPKIT_EXTERN NSString * const NSWorkspaceDidUnhideApplicationNotification AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;
APPKIT_EXTERN NSString * const NSWorkspaceDidActivateApplicationNotification AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;
APPKIT_EXTERN NSString * const NSWorkspaceDidDeactivateApplicationNotification AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;


/* Volume notifications */

/* In Mac OS X 10.6 and later, the following keys are available in the userInfo of NSWorkspaceDidMountNotification, NSWorkspaceWillUnmountNotification, NSWorkspaceDidUnmountNotification, and NSWorkspaceDidRenameVolumeNotification.
*/
APPKIT_EXTERN NSString * const NSWorkspaceVolumeLocalizedNameKey AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER; //NSString containing the user-visible name of the volume
APPKIT_EXTERN NSString * const NSWorkspaceVolumeURLKey AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;  //NSURL containing the mount path of the volume

/* The following additional keys are provided in the userInfo of NSWorkspaceDidRenameVolumeNotification.
 */
APPKIT_EXTERN NSString * const NSWorkspaceVolumeOldLocalizedNameKey AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER; //NSString containing the old user-visible name of the volume
APPKIT_EXTERN NSString * const NSWorkspaceVolumeOldURLKey AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;  //NSURL containing the old mount path of the volume

APPKIT_EXTERN NSString * const NSWorkspaceDidMountNotification;		//	@"NSDevicePath"
APPKIT_EXTERN NSString * const NSWorkspaceDidUnmountNotification;		//	@"NSDevicePath"
APPKIT_EXTERN NSString * const NSWorkspaceWillUnmountNotification;		//	@"NSDevicePath"

/* NSWorkspaceDidRenameVolumeNotification is posted when a volume changes its name and/or mount path.  These typically change simultaneously, in which case only one notification is posted.
 */
APPKIT_EXTERN NSString * const NSWorkspaceDidRenameVolumeNotification AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;


/* Power notifications */
APPKIT_EXTERN NSString * const NSWorkspaceWillPowerOffNotification;

APPKIT_EXTERN NSString * const NSWorkspaceWillSleepNotification	AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
APPKIT_EXTERN NSString * const NSWorkspaceDidWakeNotification	AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

APPKIT_EXTERN NSString * const NSWorkspaceScreensDidSleepNotification	AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;
APPKIT_EXTERN NSString * const NSWorkspaceScreensDidWakeNotification	AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

/* Session notifications */
APPKIT_EXTERN NSString * const NSWorkspaceSessionDidBecomeActiveNotification	AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
APPKIT_EXTERN NSString * const NSWorkspaceSessionDidResignActiveNotification	AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;


/* Miscellaneous notifications */

APPKIT_EXTERN NSString * const NSWorkspaceDidPerformFileOperationNotification;	//	@"NSOperationNumber"

/* NSWorkspaceDidChangeFileLabelsNotification is posted when the user changes a file label color name or the color itself.  The notification object is always NSWorkspace, and there is no user info.
 */
APPKIT_EXTERN NSString * const NSWorkspaceDidChangeFileLabelsNotification AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;


/* Possible values for operation in performFileOperation:... 
*/
APPKIT_EXTERN NSString * const NSWorkspaceMoveOperation;
APPKIT_EXTERN NSString * const NSWorkspaceCopyOperation;
APPKIT_EXTERN NSString * const NSWorkspaceLinkOperation;
APPKIT_EXTERN NSString * const NSWorkspaceCompressOperation;
APPKIT_EXTERN NSString * const NSWorkspaceDecompressOperation;
APPKIT_EXTERN NSString * const NSWorkspaceEncryptOperation;
APPKIT_EXTERN NSString * const NSWorkspaceDecryptOperation;
APPKIT_EXTERN NSString * const NSWorkspaceDestroyOperation;
APPKIT_EXTERN NSString * const NSWorkspaceRecycleOperation;
APPKIT_EXTERN NSString * const NSWorkspaceDuplicateOperation;


/* Everything remaining in this header is deprecated and should not be used. */

@interface NSWorkspace (NSDeprecated)
- (BOOL)openTempFile:(NSString *)fullPath AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_6;
- (void)findApplications AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_6;
- (void)noteUserDefaultsChanged AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_6;
- (void)slideImage:(NSImage *)image from:(NSPoint)fromPoint to:(NSPoint)toPoint AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_6;
- (void)checkForRemovableMedia AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_6;
- (void)noteFileSystemChanged AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_6;
- (BOOL)fileSystemChanged AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_6;
- (BOOL)userDefaultsChanged AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_6;
- (NSArray *)mountNewRemovableMedia AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_6;
@end

APPKIT_EXTERN NSString *NSPlainFileType AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_6;
APPKIT_EXTERN NSString *NSDirectoryFileType AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_6;
APPKIT_EXTERN NSString *NSApplicationFileType AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_6;
APPKIT_EXTERN NSString *NSFilesystemFileType AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_6;
APPKIT_EXTERN NSString *NSShellCommandFileType AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_6;
