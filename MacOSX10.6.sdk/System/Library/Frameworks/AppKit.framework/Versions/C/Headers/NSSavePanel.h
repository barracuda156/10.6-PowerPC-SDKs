/*
	NSSavePanel.h
	Application Kit
	Copyright (c) 1994-2007, Apple Inc.
	All rights reserved.
*/

#import <AppKit/NSNibDeclarations.h>
#import <AppKit/NSPanel.h>

@class NSBox, NSMutableArray, NSNavView, NSTextField, NSTextView, NSView, NSURL;

enum {
    NSFileHandlingPanelCancelButton	= NSCancelButton,
    NSFileHandlingPanelOKButton		= NSOKButton,
};		

typedef struct __SPFlags {
    unsigned int saveMode:1;
    unsigned int isExpanded:1;
    unsigned int allowsOtherFileTypes:1;
    unsigned int canCreateDirectories:1;
    unsigned int canSelectedHiddenExtension:1;
    unsigned int inConfigureForDirectory:1;
    unsigned int delegate_shouldShowFilename:1;
    unsigned int delegate_compareFilename:1;
    unsigned int reserved:24;
} _SPFlags;

@class NSSavePanelAuxiliary;

@interface NSSavePanel : NSPanel {
    NSNavView *_navView;
    NSView *_accessoryView;
    NSArray *_allowedFileTypes;
    NSString *_validatedPosixName;
    NSString *_hiddenExtension;
        
    IBOutlet NSTextField  *_messageTextField;
    IBOutlet NSView       *_savePane;
    IBOutlet NSBox        *_saveNavSeparatorBox;
    IBOutlet NSView         *_savePaneTopPartsContainer;
    IBOutlet NSTextField      *_nameField;
    IBOutlet NSTextField      *_nameFieldLabel;
    IBOutlet NSButton         *_expansionButton;
    IBOutlet NSView         *_directoryPopUpContainer;
    IBOutlet id             _directoryPopUp;
    IBOutlet NSTextField       *_directoryPopUpLabel;
    IBOutlet NSBox        *_navViewContainer;
    IBOutlet NSBox        *_accessoryViewContainer;
    IBOutlet NSView       *_bottomControlsContainer;
    IBOutlet NSButton       *_hideExtensionButton;
    IBOutlet NSButton       *_newFolderButton;
    IBOutlet NSButton       *_cancelButton;
    IBOutlet NSButton       *_okButton;
    
    IBOutlet id _filepathInputController;
    IBOutlet id _newFolderController;

    _SPFlags	_spFlags;
    
    NSSavePanelAuxiliary *_spAuxiliaryStorage;
    
    char _reserved[5];

    void *_private;
}

+ (NSSavePanel *)savePanel;

- (NSURL *)URL;

- (NSString *)filename;

- (NSString *)directory;
- (void)setDirectory:(NSString *)path;

/* A file specified in the save panel is saved with the designated filename and this file type as an extension. This method is equivalent to calling allowedFileTypes and returning the first element of the list of allowed types, or nil if there are none.  It is preferred to use 'allowedFileTypes' over this method.
 */
- (NSString *)requiredFileType;
- (void)setRequiredFileType:(NSString *)type;

/* An array NSStrings specifying the file types the user can save the file as. The fil type can be a common file extension, or a UTI. A nil value indicates that any file type can be used. If the array is not nil and the array contains no items, an exception will be raised. If the user specifies a type not in the array, and 'allowsOtherFileTypes' is YES, they will be presented with another dialog when prompted to save. The default value is 'nil'.
 */
- (NSArray *)allowedFileTypes AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
- (void)setAllowedFileTypes:(NSArray *)types AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

/* Returns a BOOL value that indicates whether the receiver allows the user to save files with an extension that's not in the list of 'allowedFileTypes'.
 */
- (BOOL)allowsOtherFileTypes AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
- (void)setAllowsOtherFileTypes:(BOOL)flag AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

- (NSView *)accessoryView;
- (void)setAccessoryView:(NSView *)view;

- (id)delegate AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
- (void)setDelegate:(id)delegate;

- (BOOL)isExpanded;

- (BOOL)canCreateDirectories AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
- (void)setCanCreateDirectories:(BOOL)flag AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

- (BOOL)canSelectHiddenExtension AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
- (void)setCanSelectHiddenExtension:(BOOL)flag;
- (BOOL)isExtensionHidden;
- (void)setExtensionHidden:(BOOL)flag;

- (BOOL)treatsFilePackagesAsDirectories;
- (void)setTreatsFilePackagesAsDirectories:(BOOL)flag;

- (NSString *)prompt;
- (void)setPrompt:(NSString *)prompt;

- (NSString *)title;
- (void)setTitle:(NSString *)title;

- (NSString *)nameFieldLabel AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
- (void)setNameFieldLabel:(NSString *)label AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

- (NSString *)message AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
- (void)setMessage:(NSString *)message AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

- (void)validateVisibleColumns;

@end


@interface NSSavePanel(NSSavePanelRuntime)

- (IBAction)ok:(id)sender;
- (IBAction)cancel:(id)sender;

/* didEndSelector should have the signature:
    - (void)savePanelDidEnd:(NSSavePanel *)sheet returnCode:(NSInteger)returnCode contextInfo:(void *)contextInfo;
   The value passed as returnCode will be either NSCancelButton or NSOKButton.
*/
- (void)beginSheetForDirectory:(NSString *)path file:(NSString *)name modalForWindow:(NSWindow *)docWindow modalDelegate:(id)delegate didEndSelector:(SEL)didEndSelector contextInfo:(void *)contextInfo;

- (NSInteger)runModalForDirectory:(NSString *)path file:(NSString *)name;

- (NSInteger)runModal;

@end


@interface NSObject(NSSavePanelDelegate)

/* Despite the name, this method controls whether or not a filename should appear enabled. Delegate implementations should be fast to avoid stalling the UI.
 */
- (BOOL)panel:(id)sender shouldShowFilename:(NSString *)filename;

/* Optional - Filename validation. For the NSSavePanel: the delegate has a chance to validate the proposed filename before the window closes. For the NSOpenPanel: The delegate will get a chance to validate each selected filename before the window closes, and it will get called once for each selected filename. Returning YES will allow the filename to be accepted, and the window to be closed. Returning NO will not allow it to be accepted. 
 */
- (BOOL)panel:(id)sender isValidFilename:(NSString *)filename;

/* Optional - Filename customization for the NSSavePanel. Allows the deleagte to customize the filename entered by the user, before the extension is appended, and before the user is potentially asked to replace a file.
 */
- (NSString *)panel:(id)sender userEnteredFilename:(NSString *)filename confirmed:(BOOL)okFlag;

/* Optional - Sent when the user clicks the disclosure triangle to expand or collapse the file browser while in NSOpenPanel.
 */
- (void)panel:(id)sender willExpand:(BOOL)expanding;

/* Optional - Sent when the user has changed the selected directory.
 */
- (void)panel:(id)sender directoryDidChange:(NSString *)path AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

/* Optional - Sent when the user has changed the selection.
 */
- (void)panelSelectionDidChange:(id)sender AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

- (NSComparisonResult)panel:(id)sender compareFilename:(NSString *)name1 with:(NSString *)name2 caseSensitive:(BOOL)caseSensitive;

@end

@interface NSSavePanel(NSDeprecated)

/* A method that was deprecated in Mac OS 10.3.  -[NSSavePanel selectText:] does nothing.
 */
- (IBAction)selectText:(id)sender DEPRECATED_IN_MAC_OS_X_VERSION_10_3_AND_LATER;

@end
