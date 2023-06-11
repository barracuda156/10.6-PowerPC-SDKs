/*
 NSMenu.h
 Application Kit
 Copyright (c) 1996-2007, Apple Inc.
 All rights reserved.
 */

#import <Foundation/NSObject.h>
#import <Foundation/NSGeometry.h>
#import <AppKit/AppKitDefines.h>
#import <AppKit/NSMenuItem.h>

@class NSEvent, NSView, NSFont;
@class NSMenu;
@class NSMutableArray, NSArray;

@interface NSMenu : NSObject <NSCopying, NSCoding>
{
    /*All instance variables are private*/
    @private
    NSMenu *_supermenu;
    NSString *_title;
    id _itemArray;
    id _extra;
    struct __mFlags {
        unsigned int noAutoenable:1;
        unsigned int menuChangedMessagesDisabled:1;
        unsigned int needsMenuChangedMessage:1;
        unsigned int suppressAutoenable:1;
        unsigned int disabled:1;
        unsigned int ownedByPopUp:1;
	unsigned int delegateNeedsUpdate:1;
	unsigned int delegateUpdateItem:1;
	unsigned int delegateHasKeyEquiv:1;
	unsigned int delegateHasAltKeyEquiv:1;
	unsigned int excludeMarkColumn:1;
	unsigned int isContextualMenu:1;
        unsigned int forbidCMPlugins:1;
        unsigned int allowsDifferentSelection:1;
        unsigned int RESERVED:18;
    } _mFlags;
    NSString *_name;
}

+ (void)setMenuZone:(NSZone *)aZone;
+ (NSZone *)menuZone;

+ (void)popUpContextMenu:(NSMenu*)menu withEvent:(NSEvent*)event forView:(NSView*)view;
#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_3
+ (void)popUpContextMenu:(NSMenu*)menu withEvent:(NSEvent*)event forView:(NSView*)view withFont:(NSFont*)font;
#endif

/* Pops up the receiver. The top left corner of the given item (which must be present in the receiver) is positioned at the given location in the given view, interpreted in the view's own coordinate system.  If item is nil, the menu is positioned such that the top left of the menu content frame is at the given location.  If view is nil, the location is interpreted in the screen coordinate system. This allows you to pop up a menu disconnected from any window.  The method returns YES if menu tracking ended because an item was selected, and NO if menu tracking was cancelled for any reason.
*/
- (BOOL)popUpMenuPositioningItem:(NSMenuItem *)item atLocation:(NSPoint)location inView:(NSView *)view AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_2
+ (void)setMenuBarVisible:(BOOL)visible;
+ (BOOL)menuBarVisible;
#endif

- (id)initWithTitle:(NSString *)aTitle;

- (void)setTitle:(NSString *)aString;
- (NSString *)title;

- (void)setSupermenu:(NSMenu *)supermenu;
- (NSMenu *)supermenu;
    // Never call the set method directly it is there only for subclassers.

- (void)insertItem:(NSMenuItem *)newItem atIndex:(NSInteger)index;
- (void)addItem:(NSMenuItem *)newItem;
- (NSMenuItem *)insertItemWithTitle:(NSString *)aString action:(SEL)aSelector keyEquivalent:(NSString *)charCode atIndex:(NSInteger)index;
- (NSMenuItem *)addItemWithTitle:(NSString *)aString action:(SEL)aSelector keyEquivalent:(NSString *)charCode;
- (void)removeItemAtIndex:(NSInteger)index;
- (void)removeItem:(NSMenuItem *)item;
- (void)setSubmenu:(NSMenu *)aMenu forItem:(NSMenuItem *)anItem;

/* Removes all items.  This does not post NSMenuDidRemoveItemNotification, for efficiency.
*/
- (void)removeAllItems AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

- (NSArray *)itemArray;
- (NSInteger)numberOfItems;

- (NSInteger)indexOfItem:(NSMenuItem *)index;
- (NSInteger)indexOfItemWithTitle:(NSString *)aTitle;
- (NSInteger)indexOfItemWithTag:(NSInteger)aTag;
- (NSInteger)indexOfItemWithRepresentedObject:(id)object;
- (NSInteger)indexOfItemWithSubmenu:(NSMenu *)submenu;
- (NSInteger)indexOfItemWithTarget:(id)target andAction:(SEL)actionSelector;

- (NSMenuItem *)itemAtIndex:(NSInteger)index;
- (NSMenuItem *)itemWithTitle:(NSString *)aTitle;
- (NSMenuItem *)itemWithTag:(NSInteger)tag;

- (void)setAutoenablesItems:(BOOL)flag;
- (BOOL)autoenablesItems;

- (BOOL)performKeyEquivalent:(NSEvent *)theEvent;
- (void)update;

- (void)setMenuChangedMessagesEnabled:(BOOL)flag;
- (BOOL)menuChangedMessagesEnabled;

- (void)itemChanged:(NSMenuItem *)item;

- (void)helpRequested:(NSEvent *)eventPtr;

- (void)setMenuRepresentation:(id)menuRep;
- (id)menuRepresentation;

- (void)setContextMenuRepresentation:(id)menuRep;
- (id)contextMenuRepresentation;

- (void)setTearOffMenuRepresentation:(id)menuRep;
- (id)tearOffMenuRepresentation;

- (BOOL)isTornOff;

    // These methods are platform specific.  They really make little sense on Windows.  Their use is discouraged.
- (NSMenu *)attachedMenu;
- (BOOL)isAttached;
- (void)sizeToFit;
- (NSPoint)locationForSubmenu:(NSMenu *)aSubmenu;

- (void)performActionForItemAtIndex:(NSInteger)index;

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_3
- (void)setDelegate:(id)anObject;
- (id)delegate;
#endif

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4
- (CGFloat)menuBarHeight;
#endif

/* Dismisses the menu and ends all menu tracking */
- (void)cancelTracking AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

/* Dismisses the menu immediately, without any fade or other effect, and ends all menu tracking */
- (void)cancelTrackingWithoutAnimation AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

/* Returns the highlighted item in the menu, or nil if no item in the menu is highlighted */
- (NSMenuItem *)highlightedItem AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

/* Set the minimum width of the menu, in screen coordinates. The menu will prefer to not draw smaller than its minimum width, but may draw larger if it needs more space. The default value is 0.
*/
- (CGFloat)minimumWidth AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;
- (void)setMinimumWidth:(CGFloat)width AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

/* Returns the size of the menu, in screen coordinates.  The menu may draw at a smaller size when shown, depending on its positioning and display configuration.
*/
- (NSSize)size AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

/* Sets the font for the menu.  This also affects the font of all submenus that do not have their own font.
*/
- (NSFont *)font AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;
- (void)setFont:(NSFont *)font AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

/* Determines whether contextual menu plugins may be appended to the menu, if used as a context menu. The default is YES.
*/
- (BOOL)allowsContextMenuPlugIns AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;
- (void)setAllowsContextMenuPlugIns:(BOOL)allows AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

- (void)setShowsStateColumn:(BOOL)showsState AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
- (BOOL)showsStateColumn AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

@end

@interface NSMenu(NSSubmenuAction)
- (void)submenuAction:(id)sender;
@end

@interface NSObject(NSMenuValidation)
- (BOOL)validateMenuItem:(NSMenuItem *)menuItem;
@end

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_3
@interface NSObject(NSMenuDelegate)
- (void)menuNeedsUpdate:(NSMenu*)menu;
- (NSInteger)numberOfItemsInMenu:(NSMenu*)menu;
- (BOOL)menu:(NSMenu*)menu updateItem:(NSMenuItem*)item atIndex:(NSInteger)index shouldCancel:(BOOL)shouldCancel;
    // implement either the first one or the next two to populate the menu
- (BOOL)menuHasKeyEquivalent:(NSMenu*)menu forEvent:(NSEvent*)event target:(id*)target action:(SEL*)action;
    // bypasses populating the menu for checking for key equivalents. set target and action on return

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5
/* indicates that the menu is being opened (displayed) or closed (hidden).  Do not modify the structure of the menu or the menu items from within these callbacks. */
- (void)menuWillOpen:(NSMenu *)menu;
- (void)menuDidClose:(NSMenu *)menu;

/* Indicates that menu is about to highlight item.  Only one item per menu can be highlighted at a time.  If item is nil, it means all items in the menu are about to be unhighlighted. */
- (void)menu:(NSMenu *)menu willHighlightItem:(NSMenuItem *)item;

#endif

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_6
/* Given a menu that is about to be opened on the given screen, return a rect, in screen coordinates, within which the menu will be positioned.  If you return NSZeroRect, or if the delegate does not implement this method, the menu will be confined to the bounds appropriate for the given screen.  The returned rect may not be honored in all cases, such as if it would force the menu to be too small.
*/
- (NSRect)confinementRectForMenu:(NSMenu *)menu onScreen:(NSScreen *)screen;
#endif

@end
#endif

APPKIT_EXTERN NSString *NSMenuWillSendActionNotification;
APPKIT_EXTERN NSString *NSMenuDidSendActionNotification;

APPKIT_EXTERN NSString *NSMenuDidAddItemNotification;
APPKIT_EXTERN NSString *NSMenuDidRemoveItemNotification;
APPKIT_EXTERN NSString *NSMenuDidChangeItemNotification;
// All three of these have a user info key NSMenuItemIndex with a NSNumber value.

APPKIT_EXTERN NSString *NSMenuDidBeginTrackingNotification  AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
APPKIT_EXTERN NSString *NSMenuDidEndTrackingNotification    AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
