/*
    NSUserInterfaceItemSearching.h
    Application Kit
    Copyright (c) 2008, Apple Inc.
    All rights reserved.
*/

#import <Foundation/NSArray.h>
#import <Foundation/NSGeometry.h>
#import <Foundation/NSString.h>
#import <AppKit/NSApplication.h>

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_6

@protocol NSUserInterfaceItemSearching

@required

/* Return a list of items for the search string.  The framework does not care what these items are. They are just used to identify particular search results in other protocol methods.  May be called from a thread other than the main UI thread. partialResults is an in/out parameter that controls returning results in multiple chunks.  On the first call of a new search it is set to NO.  This is used to indicate the start of a new search.  Leave it set to NO if there are no more search results available.  Set it to YES if you want to be called again for more search results.  If you do this be sure to check the flag on entry as Spotlight may choose to ask for additional results or not.
*/
- (NSArray *)itemsForSearchString:(NSString *)searchString withPartialResults:(BOOL *)partialResults;

/* return an array of strings (localized for display in the menu) that will be combined with separators to form the menu item title
 */
- (NSArray *)localizedTitlesForItem:(id)item;

@optional

/* return a string to describe the category of the item returned.  This allows developers to customize the name of their help topics in the Help menu. 
 * If not implemented or returns nil, then Spotlight for Help will place the results in "Help Topics"
 */
- (NSString *)localizedCategoryForItem:(id)item;

/* Called when the user selects a search result in Help menu. For example, the default implementation brings up Help Viewer for a Help item. 
 */
- (void)performActionForItem:(id)item;

/* Called by Spotlight for Help when the user highlights a Help menu item. Implement to preview result when user is selecting on the menu
 */
- (void)showItem:(id)item;

/* Called when Spotlight for Help needs to hide a previously selected item. 
 */
- (void)hideItem:(id)item;

/* return a custom icon to display in the menu for this item
 */
- (NSImage *)iconForItem:(id)item;

@end


@interface NSApplication (NSUserInterfaceItemSearching)

/* Register an an object that conforms to NSUserInterfaceItemSearching with the application.  You can register as many as you like.  If you register the same instance more than once the subsequent registrations are ignored
 */
- (void)registerUserInterfaceItemSearchHandler:(id<NSUserInterfaceItemSearching>)handler;

/* Unregister an object that conforms to NSUserInterfaceItemSearching with the application.  If you unregister the same instance more than once the subsequent registrations are ignored. Also, unregistering an instance that was never registered is a NOP.
 */
- (void)unregisterUserInterfaceItemSearchHandler:(id<NSUserInterfaceItemSearching>)handler;

/* returns YES if searchString matches the supplied range of stringToBeSearched according to Spotlight for Help default matching rules  
 * if found range is non null then the matching range is returned in it 
 */
- (BOOL)searchString:(NSString *)searchString inUserInterfaceItemString:(NSString *)stringToSearch searchRange:(NSRange)searchRange foundRange:(NSRange *)foundRange;

/* Returns yes if Spotlight for Help will search HelpViewer topics in addition to possible custom search handlers
 */
- (BOOL)isDefaultHelpBookSearchEnabled;

/* Set to NO to disable the built in Help Viewer Topic search.  Otherwise Spotlight for Help will combine custom search results with HelpViewer topics
 */
- (void)setDefaultHelpBookSearchEnabled:(BOOL)value;

@end

#endif
