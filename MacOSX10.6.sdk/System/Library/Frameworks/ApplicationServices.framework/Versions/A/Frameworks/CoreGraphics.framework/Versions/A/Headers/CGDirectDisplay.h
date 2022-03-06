/* CoreGraphics - CGDirectDisplay.h
 * Copyright (c) 2000-2008 Apple Inc.
 * All rights reserved. */

#ifndef CGDIRECTDISPLAY_H_
#define CGDIRECTDISPLAY_H_

#include <CoreGraphics/CGContext.h>
#include <CoreGraphics/CGError.h>
#include <CoreGraphics/CGGeometry.h>
#include <mach/boolean.h>

typedef uint32_t CGDirectDisplayID;
typedef uint32_t CGOpenGLDisplayMask;
typedef double CGRefreshRate;

typedef struct _CGDirectPaletteRef *CGDirectPaletteRef;

#define kCGNullDirectDisplay ((CGDirectDisplayID)0)
#define kCGDirectMainDisplay CGMainDisplayID()

/* Return the display ID of the current main display. */

CG_EXTERN CGDirectDisplayID CGMainDisplayID(void)
  CG_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_NA);

/* Mechanisms used to find screen IDs.

   The following functions take an array length (`maxDisplays') and array of
   pointers to CGDirectDisplayIDs (`displays'). The array is filled in with
   the displays meeting the specified criteria; no more than `maxDisplays'.
   will be stored in `displays'. The number of displays meeting the criteria
   is returned in `matchingDisplayCount'.

   If the `displays' array is NULL, only the number of displays meeting the
   specified criteria is returned in `matchingDisplayCount'. */

CG_EXTERN CGError CGGetDisplaysWithPoint(CGPoint point, uint32_t maxDisplays,
  CGDirectDisplayID *displays, uint32_t *matchingDisplayCount)
  CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);

CG_EXTERN CGError CGGetDisplaysWithRect(CGRect rect, uint32_t maxDisplays,
  CGDirectDisplayID *displays, uint32_t *matchingDisplayCount)
  CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);

CG_EXTERN CGError CGGetDisplaysWithOpenGLDisplayMask(CGOpenGLDisplayMask mask,
  uint32_t maxDisplays, CGDirectDisplayID *displays,
  uint32_t *matchingDisplayCount)
  CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);
                            
/* Return a list of active displays.

   If `activeDisplays' is NULL, then `maxDisplays' is ignored, and
   `displayCount' is set to the number of displays. Otherwise, the list of
   active displays is stored in `activeDisplays'; no more than `maxDisplays'
   will be stored in `activeDisplays'.

   The first display returned in the list is the main display (the one with
   the menu bar). When mirroring, this will be the largest drawable display
   in the mirror set, or, if all displays are the same size, the one with
   the deepest pixel depth. */

CG_EXTERN CGError CGGetActiveDisplayList(uint32_t maxDisplays,
  CGDirectDisplayID *activeDisplays, uint32_t *displayCount)
  CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);

/* Return a list of online displays.

   If `onlineDisplays' is NULL, then `maxDisplays' is ignored, and
   `displayCount' is set to the number of displays. Otherwise, the list of
   online displays is stored in `onlineDisplays'; no more than `maxDisplays'
   will be stored in `onlineDisplays'.

   With hardware mirroring, a display may be online but not necessarily
   active or drawable. Programs which manipulate display settings such as
   the palette or gamma tables need access to all displays in use, including
   hardware mirrors which are not drawable. */

CG_EXTERN CGError CGGetOnlineDisplayList(uint32_t maxDisplays,
  CGDirectDisplayID *onlineDisplays, uint32_t *displayCount)
  CG_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_NA);

/* Return the OpenGL display mask for `display', or 0 is `display' is an
   invalid display. */

CG_EXTERN CGOpenGLDisplayMask CGDisplayIDToOpenGLDisplayMask(
  CGDirectDisplayID display) CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);

/* Return the display for the OpenGL display mask `mask', or
   `kCGNullDirectDisplay' if the bits set dont't match a display. A mask
   with multiple bits set returns an arbitrary match. */

CG_EXTERN CGDirectDisplayID CGOpenGLDisplayMaskToDisplayID(
  CGOpenGLDisplayMask mask) CG_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_NA);

/* Return the screen size and screen origin of `display' in global
   coordinates, or `CGRectZero' if `display' is invalid. */

CG_EXTERN CGRect CGDisplayBounds(CGDirectDisplayID display)
  CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);

/* Return the width in pixels of `display'. */

CG_EXTERN size_t CGDisplayPixelsWide(CGDirectDisplayID display)
  CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);

/* Return the height in pixels of `display'. */

CG_EXTERN size_t CGDisplayPixelsHigh(CGDirectDisplayID display)
  CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);

/* Display mode selection.

   Display modes are represented as CFDictionaries. All dictionaries and
   arrays returned via these mechanisms are owned by the CoreGraphics
   framework and should not be released. The dictionaries are valid for
   the lifetime of a process.

   Values associated with the following keys are CFNumbers; for best
   results, use `kCFNumberLongType' when fetching values, with one
   exception: `kCGDisplayRefreshRate' is stored as a double value, so to get
   the fractional refresh rate use `kCFNumberDoubleType'. */

/* Keys used in mode dictionaries. */

#define kCGDisplayWidth				CFSTR("Width")
#define kCGDisplayHeight			CFSTR("Height")
#define kCGDisplayMode				CFSTR("Mode")
#define kCGDisplayBitsPerPixel			CFSTR("BitsPerPixel")
#define kCGDisplayBitsPerSample			CFSTR("BitsPerSample")
#define kCGDisplaySamplesPerPixel		CFSTR("SamplesPerPixel")
#define kCGDisplayRefreshRate			CFSTR("RefreshRate")
#define kCGDisplayModeUsableForDesktopGUI	CFSTR("UsableForDesktopGUI")
#define kCGDisplayIOFlags			CFSTR("IOFlags")
#define kCGDisplayBytesPerRow			CFSTR("kCGDisplayBytesPerRow")
#define kCGIODisplayModeID			CFSTR("IODisplayModeID")

/* Keys describing optional properties of display modes.

   The key will only be present if the property applies and will have a
   value of `kCFBooleanTrue'. Keys not relevant to a particular display mode
   will not appear in the mode dictionary. */

/* Set if a display mode doesn't need a confirmation dialog to be set. */

#define kCGDisplayModeIsSafeForHardware					\
  CFSTR("kCGDisplayModeIsSafeForHardware")

/* Interesting bits of the IOKit display mode flags. */

#define kCGDisplayModeIsInterlaced					\
  CFSTR("kCGDisplayModeIsInterlaced") 
#define kCGDisplayModeIsStretched					\
  CFSTR("kCGDisplayModeIsStretched")
#define kCGDisplayModeIsTelevisionOutput				\
  CFSTR("kCGDisplayModeIsTelevisionOutput")

/* Return a CFArray of CFDictionaries describing all display modes for
   `display', or NULL if `display' is invalid. */

CG_EXTERN CFArrayRef CGDisplayAvailableModes(CGDirectDisplayID display)
  CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);

/* Return the display mode for `display' with the specified depth and
   dimensions equal to or greater than those specified. If there is no such
   display mode, return the display mode with the next larger depth and with
   dimensions equal to or greater than those specified. If there is again no
   such display mode, return the current mode. If `display' is invalid,
   return NULL.

   If `exactMatch' is non-NULL, then it is set to 'true' if an exact match
   in width, height, and depth is found, `false' otherwise. */

CG_EXTERN CFDictionaryRef CGDisplayBestModeForParameters(CGDirectDisplayID
  display, size_t bitsPerPixel, size_t width, size_t height,
  boolean_t *exactMatch) CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);

/* Return the display mode for `display' with the specified depth and
   dimensions equal to or greater than those specified, and a refresh rate
   equal to or near the specified rate. If there is again no such display
   mode, return the current mode. If `display' is invalid, return NULL.

   If `exactMatch' is non-NULL, then it is set to 'true' if an exact match
   in width, height, depth, and refresh rate is found, `false' otherwise. */

CG_EXTERN CFDictionaryRef CGDisplayBestModeForParametersAndRefreshRate(
  CGDirectDisplayID display, size_t bitsPerPixel, size_t width, size_t height,
  CGRefreshRate refreshRate, boolean_t *exactMatch)
  CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);

/* Return the display mode with the specified property for `display' with
   the specified depth and dimensions equal to or greater than those
   specified, and a refresh rate equal to or near the specified rate. If
   there is again no such display mode, return the current mode. If
   `display' is invalid, return NULL.

   If `exactMatch' is non-NULL, then it is set to 'true' if an exact match
   in width, height, depth, and refresh rate is found, `false' otherwise.

   The property should be one one of `kCGDisplayModeIsSafeForHardware',
   `kCGDisplayModeIsInterlaced', `kCGDisplayModeIsStretched', or
   `kCGDisplayModeIsTelevisionOutput'. */

CG_EXTERN CFDictionaryRef
  CGDisplayBestModeForParametersAndRefreshRateWithProperty(CGDirectDisplayID
    display, size_t bitsPerPixel, size_t width, size_t height,
    CGRefreshRate refreshRate, CFStringRef property, boolean_t *exactMatch)
    CG_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_NA);

/* Return a CFDictionary describing the current display mode for `display',
   or NULL if `display' is invalid. */

CG_EXTERN CFDictionaryRef CGDisplayCurrentMode(CGDirectDisplayID display)
  CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);

/* Switch the display mode of `display' to `mode'.

   The selected display mode persists for the life of the program, and
   automatically reverts to the permanent setting when the program
   terminates. The mode dictionary passed in must be a dictionary vended by
   other CGDirectDisplay APIs such as `CGDisplayBestModeForParameters' or
   `CGDisplayAvailableModes'.

   When changing display modes of displays in a mirroring set, other
   displays in the mirroring set will be set to a display mode capable of
   mirroring the bounds of the largest display being explicitly set.

   Note that after switching, display parameters and addresses may change. */

CG_EXTERN CGError CGDisplaySwitchToMode(CGDirectDisplayID display,
  CFDictionaryRef mode) CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);

/* Return the bits/pixel of the current mode of `display'. */

CG_EXTERN size_t CGDisplayBitsPerPixel(CGDirectDisplayID display)
  CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);

/* Return the bits/sample of the current mode of `display'. */

CG_EXTERN size_t CGDisplayBitsPerSample(CGDirectDisplayID display)
  CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);

/* Return the sample/pixel of the current mode of `display'. */

CG_EXTERN size_t CGDisplaySamplesPerPixel(CGDirectDisplayID display)
  CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);

/* Return the bytes/row of the current mode of `display'. */

CG_EXTERN size_t CGDisplayBytesPerRow(CGDirectDisplayID display)
  CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);

/* Set the gamma function for `display' by specifying the coefficients of
   the gamma transfer function.

   Gamma values must be greater than 0. Minimum values must be in the
   interval [0, 1). Maximum values must be in the interval (0, 1]. Out of
   range values or maximum values greater than or equal to minimum values
   return `kCGErrorRangeCheck'.

   Values are computed by sampling a function for a range of indexes from 0
   to 1:
     value = Min + ((Max - Min) * pow(index, Gamma))
   The resulting values are converted to a machine-specific format and
   loaded into display hardware. */

typedef float CGGammaValue;
                                              
CG_EXTERN CGError CGSetDisplayTransferByFormula(CGDirectDisplayID display,
  CGGammaValue redMin, CGGammaValue redMax, CGGammaValue redGamma,
  CGGammaValue greenMin, CGGammaValue greenMax, CGGammaValue greenGamma,
  CGGammaValue blueMin, CGGammaValue blueMax, CGGammaValue blueGamma)
  CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);

/* Return the coefficients of the gamma transfer function for `display'. */

CG_EXTERN CGError CGGetDisplayTransferByFormula(CGDirectDisplayID display,
  CGGammaValue *redMin, CGGammaValue *redMax, CGGammaValue *redGamma,
  CGGammaValue *greenMin, CGGammaValue *greenMax, CGGammaValue *greenGamma,
  CGGammaValue *blueMin, CGGammaValue *blueMax, CGGammaValue *blueGamma)
  CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);

/* Return the capacity, or number of entries, in the gamma table for
   `display', or 0 if 'display' is invalid. */

CG_EXTERN uint32_t CGDisplayGammaTableCapacity(CGDirectDisplayID display)
  CG_AVAILABLE_STARTING(__MAC_10_3, __IPHONE_NA);

/* Set the gamma function for `display' by specifying the values in the RGB
   gamma tables.

   Values within each table should be in the interval [0, 1] The same table
   may be passed in for red, green, and blue channels. The number of entries
   in the tables is specified by `tableSize'. The tables are interpolated as
   needed to generate the number of samples needed by the display hardware. */

CG_EXTERN CGError CGSetDisplayTransferByTable(CGDirectDisplayID display,
  uint32_t tableSize, const CGGammaValue *redTable,
  const CGGammaValue *greenTable, const CGGammaValue *blueTable)
  CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);

/* Return the RGB gamma table values for `display'.

   The number of entries in each array is specified by `capacity'; no more
   than `capacity' entries will be written to each table. The number of
   entries written is stored in `sampleCount'. */

CG_EXTERN CGError CGGetDisplayTransferByTable(CGDirectDisplayID display,
  uint32_t capacity, CGGammaValue *redTable, CGGammaValue *greenTable,
  CGGammaValue *blueTable, uint32_t *sampleCount)
  CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);

/* Set the gamma function for `display' by specifying the values in the RGB
   gamma tables as bytes.

   Values within each table should be in the interval [0, 255] The same
   table may be passed in for red, green, and blue channels. The number of
   entries in the tables is specified by `tableSize'. The tables are
   interpolated as needed to generate the number of samples needed by the
   display hardware. */

CG_EXTERN CGError CGSetDisplayTransferByByteTable(CGDirectDisplayID display,
  uint32_t tableSize, const uint8_t *redTable, const uint8_t *greenTable,
  const uint8_t *blueTable) CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);

/* Restore the gamma tables of all system displays to the values in the
   user's ColorSync display profile. */

CG_EXTERN void CGDisplayRestoreColorSyncSettings(void)
  CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);

/* Options used with `CGDisplayCaptureWithOptions' and
   `CGCaptureAllDisplaysWithOptions'. */

enum {
  kCGCaptureNoOptions = 0,	/* Default behavior. */
  kCGCaptureNoFill = (1 << 0)	/* Disables fill with black on capture. */
};
typedef uint32_t CGCaptureOptions;

/* Return true if `display' is captured; false otherwise. */

CG_EXTERN boolean_t CGDisplayIsCaptured(CGDirectDisplayID display)
  CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);

/* Capture `display' for exclusive use by an application. */

CG_EXTERN CGError CGDisplayCapture(CGDirectDisplayID display)
  CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);

/* Capture `display' for exclusive use by an application, using the options
   specified by `options'. */

CG_EXTERN CGError CGDisplayCaptureWithOptions(CGDirectDisplayID display,
  CGCaptureOptions options) CG_AVAILABLE_STARTING(__MAC_10_3, __IPHONE_NA);

/* Release the captured display `display'. */

CG_EXTERN CGError CGDisplayRelease(CGDirectDisplayID display)
  CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);

/* Capture all displays. This operation provides an immersive environment
   for an appplication, and prevents other applications from trying to
   adjust to display changes. */

CG_EXTERN CGError CGCaptureAllDisplays(void)
  CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);

/* Capture all displays, using the options specified by `options'. This
   operation provides an immersive environment for an appplication, and
   prevents other applications from trying to adjust to display changes. */

CG_EXTERN CGError CGCaptureAllDisplaysWithOptions(CGCaptureOptions options)
  CG_AVAILABLE_STARTING(__MAC_10_3, __IPHONE_NA);

/* Release all captured displays and restore the display modes to the user's
   preferences. May be used in conjunction with `CGDisplayCapture' or
   `CGCaptureAllDisplays'. */

CG_EXTERN CGError CGReleaseAllDisplays(void)
  CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);

/* Returns window ID of the shield window for the captured display `display',
   or NULL if the display is not not shielded. */

CG_EXTERN uint32_t CGShieldingWindowID(CGDirectDisplayID display)
  CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);

/* Returns the window level of the shield window for the captured display
   `display'. */

CG_EXTERN int32_t CGShieldingWindowLevel(void)
  CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);

/* Return an image containing the contents of the display identified by `displayID'. */

CGImageRef CGDisplayCreateImage(CGDirectDisplayID displayID)
    CG_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_NA);

/* Return an image containing the contents of the rectangle `rect',
specified in display space, of the display identified by `displayID'.
The actual rectangle used is the rectangle returned from
`CGRectIntegral(rect)'. */

CGImageRef CGDisplayCreateImageForRect(CGDirectDisplayID display, CGRect rect)
    CG_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_NA);

/* Returns base address of `display', or NULL for  invalid display. If the
   display has not been captured, the returned address may refer to
   read-only memory. */

CG_EXTERN void *CGDisplayBaseAddress(CGDirectDisplayID display)
  CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);

/* Return the address in the frame buffer of `display' that corresponds to
   `(x,y)' in global coordinates, or NULL if `display' is invalid or the
   coordinates are out-of-bounds. The point `(0,0)' represents the
   upper-left corner of the main display. If the display has not been
   captured, the returned address may refer to read-only memory. */

CG_EXTERN void *CGDisplayAddressForPosition(CGDirectDisplayID display,
  int32_t x, int32_t y) CG_AVAILABLE_STARTING(__MAC_10_1, __IPHONE_NA);

/* Hide the mouse cursor and increment the hide cursor count. The `display'
   parameter is ignored. */

CG_EXTERN CGError CGDisplayHideCursor(CGDirectDisplayID display)
  CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);

/* Decrement the hide cursor count; show the cursor if the hide cursor count
   is zero. The `display' parameter is ignored. */

CG_EXTERN CGError CGDisplayShowCursor(CGDirectDisplayID display)
  CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);

/* Move the mouse cursor to the specified point relative to the origin (the
   upper-left corner) of `display'. No events are generated as a result of
   the move. Points that lie outside the desktop are clipped to the
   desktop. */

CG_EXTERN CGError CGDisplayMoveCursorToPoint(CGDirectDisplayID display,
  CGPoint point) CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);

/* Return the mouse position change since with the last mouse move event
   received by the application. */

CG_EXTERN void CGGetLastMouseDelta(int32_t *deltaX, int32_t *deltaY)
  CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);

/* Return true if the current display mode of `display' supports palettes,
   false otherwise. */

CG_EXTERN boolean_t CGDisplayCanSetPalette(CGDirectDisplayID display)
  CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);

/* Set the palette for `display' to `palette'. */

CG_EXTERN CGError CGDisplaySetPalette(CGDirectDisplayID display,
  CGDirectPaletteRef palette) CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);

/* Wait until the beam position moves outside the region specified by
   `upperScanLine' and `lowerScanLine' of `display'. If `upperScanLine' is
   greater than `lowerScanLine' or if `upperScanLine' and `lowerScanLine'
   encompass the entire display height, return an error.

   Some display systems may not use conventional video vertical and
   horizontal sweep. These displays report a `kCGDisplayRefreshRate' of 0 in
   the dictionary returned by `CGDisplayCurrentMode'. On such displays, this
   function returns at once. Also, some display device drivers may not
   implement support for this mechanism. On such displays, this function
   returns at once. */

CG_EXTERN CGError CGDisplayWaitForBeamPositionOutsideLines(CGDirectDisplayID
  display, uint32_t upperScanLine, uint32_t lowerScanLine)
  CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);

/* Return the current beam position of `display', or 0 if `display' is
   invalid, if `display' does not implement conventional video vertical and
   horizontal sweep, or if the display device driver does not implement this
   functionality. */

CG_EXTERN uint32_t CGDisplayBeamPosition(CGDirectDisplayID display)
  CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);

/* Return a CGContext suitable for drawing to the captured display
   `display', or NULL if `display' has not been captured. The context is
   owned by the device and should not be released by the caller.

   The context remains valid while the display is captured and while the
   display configuration is unchanged. Releasing the captured display or
   reconfiguring the display invalidates the drawing context.

   The determine when the display configuration is changing, use
   `CGRegisterDisplayRegisterReconfigurationCallback'. */

CG_EXTERN CGContextRef CGDisplayGetDrawingContext(CGDirectDisplayID display)
  CG_AVAILABLE_STARTING(__MAC_10_3, __IPHONE_NA);

/* These types are obsolete; don't use them. */

typedef uint32_t CGDisplayCount;
typedef CGError CGDisplayErr;
typedef uint32_t CGBeamPosition CG_OBSOLETE;
typedef uint8_t CGByteValue CG_OBSOLETE;
typedef int32_t	CGDisplayCoord CG_OBSOLETE;
typedef int32_t CGMouseDelta CG_OBSOLETE;
typedef uint32_t CGTableCount CG_OBSOLETE;
#define CGDisplayNoErr kCGErrorSuccess

#define __CGDIRECT_DISPLAY_H__ 1

#endif /* CGDIRECTDISPLAY_H_ */
