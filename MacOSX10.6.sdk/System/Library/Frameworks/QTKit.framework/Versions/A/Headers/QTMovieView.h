/*
	File:		QTMovieView.h

	Copyright:	(c)2004-2008 by Apple Inc., all rights reserved.

	
	Revision: 1.33.30.1.2.4.4.2 Thursday, March 6, 2008 6:23:13 PM PT dunderwo
	[5763950] QTMovieView and QTMovieControllerView now share common implementation files between 32-bit and 64-bit. Common 32-bit specific functionality has been factored into separate shared classes to be used natively in 32-bt and by the server in 64-bit. The common coordinate translation logic is now completely generic and should work under rotation, HiDPI, and other previously unsupported scenarios. Mouse tracking in the controller view should no longer block the UI in 64-bit. QTMovieView undo should now be supported in 64-bit. QTKitServer no longer creates a proxy view and window for QTMovieView, instead using much lighter weight server-specific classes.
	
	Revision: 1.33.30.1.2.4.4.1	Wednesday, January 16, 2008 7:38:15 PM PT dunderwo
	[5691936] Added initial implementation of new QTMovieView and CGContext renderer. <cad>
	
	Revision 1.35  2008/01/18 02:18:27  ibarberi
	=== QT74GM => TopOfTree Merge ===

*/

#ifndef QTMOVIEVIEW_H
#define QTMOVIEVIEW_H

#import <Cocoa/Cocoa.h>
#import <QTKit/QTKitDefines.h>

@class QTMovie;
@class QTMovieControllerView;
@class QTMovieViewInternal;

QTKIT_EXTERN NSString * const QTMovieViewMovieBinding						AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
QTKIT_EXTERN NSString * const QTMovieViewControllerVisibleBinding			AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
QTKIT_EXTERN NSString * const QTMovieViewPreservesAspectRatioBinding		AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
QTKIT_EXTERN NSString * const QTMovieViewFillColorBinding					AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

#if __LP64__
@interface QTMovieView : NSView <NSCoding, NSUserInterfaceValidations>
#else
@interface QTMovieView : NSView <NSCoding, NSUserInterfaceValidations, NSTextInput>
#endif
{
@private
    QTMovie                 *_movie;
    
    NSColor                 *_fillColor;
    BOOL                    _controllerVisible;
	BOOL                    _preservesAspectRatio;
    
#if !__LP64__
    NSView                  *_rendererView;
    QTMovieControllerView   *_movieControllerView;
#endif    
    NSUInteger              _viewFlags;
    QTMovieViewInternal     *_internal;
	long					_reserved3;
	id						_delegate;
#if __LP64__
	int32_t					_proxy;
	int32_t					_delegateProxy;
    BOOL					_useVisualContext;
    NSView                  *_rendererView;
	QTMovieControllerView   *_movieControllerView;
#endif
}

- (QTMovie *)movie;
- (void)setMovie:(QTMovie *)movie;

- (BOOL)preservesAspectRatio;
- (void)setPreservesAspectRatio:(BOOL)preservesAspectRatio;
- (NSColor *)fillColor;
- (void)setFillColor:(NSColor *)fillColor;

- (BOOL)isControllerVisible;
- (void)setControllerVisible:(BOOL)controllerVisible;
- (void)setShowsResizeIndicator:(BOOL)show;
#if QTKIT_VERSION_MAX_ALLOWED >= QTKIT_VERSION_7_2
- (BOOL)isBackButtonVisible;
- (void)setBackButtonVisible:(BOOL)state;
- (BOOL)isCustomButtonVisible;
- (void)setCustomButtonVisible:(BOOL)state;
- (BOOL)isHotSpotButtonVisible;
- (void)setHotSpotButtonVisible:(BOOL)state;
- (BOOL)areStepButtonsVisible;
- (void)setStepButtonsVisible:(BOOL)state;
- (BOOL)isTranslateButtonVisible;
- (void)setTranslateButtonVisible:(BOOL)state;
- (BOOL)isVolumeButtonVisible;
- (void)setVolumeButtonVisible:(BOOL)state;
- (BOOL)areZoomButtonsVisible;
- (void)setZoomButtonsVisible:(BOOL)state;
#endif /* QTKIT_VERSION_MAX_ALLOWED >= QTKIT_VERSION_7_2 */ 

- (NSRect)movieBounds;
- (NSRect)movieControllerBounds;
- (float)controllerBarHeight;

- (IBAction)play:(id)sender;
- (IBAction)pause:(id)sender;
- (IBAction)gotoBeginning:(id)sender;
- (IBAction)gotoEnd:(id)sender;
- (IBAction)gotoNextSelectionPoint:(id)sender;
- (IBAction)gotoPreviousSelectionPoint:(id)sender;
- (IBAction)gotoPosterFrame:(id)sender;
- (IBAction)stepForward:(id)sender;
- (IBAction)stepBackward:(id)sender;

- (BOOL)isEditable;
- (void)setEditable:(BOOL)editable;

- (IBAction)cut:(id)sender;
- (IBAction)copy:(id)sender;
- (IBAction)paste:(id)sender;
- (IBAction)selectAll:(id)sender;
- (IBAction)selectNone:(id)sender;
- (IBAction)delete:(id)sender;
- (IBAction)add:(id)sender;
- (IBAction)addScaled:(id)sender;
- (IBAction)replace:(id)sender;
- (IBAction)trim:(id)sender;

#if QTKIT_VERSION_MAX_ALLOWED >= QTKIT_VERSION_7_2
- (id)delegate;
- (void)setDelegate:(id)delegate;
#endif /* QTKIT_VERSION_MAX_ALLOWED >= QTKIT_VERSION_7_2 */ 

@end

@interface NSObject (QTMovieView_Delegate)

#if (QTKIT_VERSION_MAX_ALLOWED >= QTKIT_VERSION_7_2) && (MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4)
- (CIImage *)view:(QTMovieView *)view willDisplayImage:(CIImage *)image;
#endif /* (QTKIT_VERSION_MAX_ALLOWED >= QTKIT_VERSION_7_2) && (MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4) */

#if (QTKIT_VERSION_MAX_ALLOWED >= QTKIT_VERSION_7_5_7) && (MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_6)
/*!
 @method		menuForEventDelegate:
 @param			An NSEvent object that specifies an event.
 @abstract		Returns an NSMenu object that is the contextual menu for the specified event.
 @discussion	This delegate method can be used instead of subclassing QTMovieView in cases that
				an application cannot hard link against the QTKit framework.
 */

- (NSMenu *)menuForEventDelegate:(NSEvent *)event;
#endif

@end

#endif	// QTMOVIEVIEW_H
