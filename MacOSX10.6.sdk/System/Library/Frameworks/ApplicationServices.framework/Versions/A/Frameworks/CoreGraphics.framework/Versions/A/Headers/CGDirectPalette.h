/* CoreGraphics - CGDirectPalette.h
 * Copyright (c) 2000-2008 Apple Inc.
 * All rights reserved. */

#ifndef __CGDIRECT_PALETTE_H__
#define __CGDIRECT_PALETTE_H__ 1

#include <CoreGraphics/CGDirectDisplay.h>

typedef float CGPaletteBlendFraction; /* A value between 0.0 and 1.0 */

/* Convenient device color representation
 *
 * Values should be in the range from 0.0 to 1.0, where 0.0 is black, and
 * 1.0 is full on for each channel.
 */

struct _CGDeviceColor
{
    float red;
    float green;
    float blue;
};
typedef struct _CGDeviceColor CGDeviceColor;

struct _CGDeviceByteColor
{
    CGByteValue red;
    CGByteValue green;
    CGByteValue blue;
};
typedef struct _CGDeviceByteColor CGDeviceByteColor;

/*
 * Create a new palette object representing the default 8 bit color palette.
 * Release the palette using CGPaletteRelease().
 */

CG_EXTERN CGDirectPaletteRef CGPaletteCreateDefaultColorPalette(void)
    CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);

/*
 * Create a copy of the display's current palette, if any.
 * Returns NULL if the current display mode does not support a palette.
 * Release the palette using CGPaletteRelease().
 */
CG_EXTERN CGDirectPaletteRef CGPaletteCreateWithDisplay(CGDirectDisplayID display) CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);

/*
 * Create a new palette with a capacity as specified.  Entries are initialized from
 * the default color palette.  Release the palette using CGPaletteRelease().
 */
CG_EXTERN CGDirectPaletteRef CGPaletteCreateWithCapacity( CGTableCount capacity ) CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);

/*
 * Create a new palette with a capacity and contents as specified.
 * Release the palette using CGPaletteRelease().
 */
CG_EXTERN CGDirectPaletteRef CGPaletteCreateWithSamples(CGDeviceColor * sampleTable, CGTableCount sampleCount) CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);

/*
 * Convenience function:
 * Create a new palette with a capacity and contents as specified.
 * Release the palette using CGPaletteRelease().
 */
CG_EXTERN CGDirectPaletteRef CGPaletteCreateWithByteSamples(CGDeviceByteColor * sampleTable, CGTableCount sampleCount) CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);

/*
 * Release a palette
 */
CG_EXTERN void CGPaletteRelease( CGDirectPaletteRef palette ) CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);

/*
 * Get the color value at the specified index
 */
CG_EXTERN CGDeviceColor CGPaletteGetColorAtIndex(CGDirectPaletteRef palette, CGTableCount index) CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);

/*
 * Get the index for the specified color value
 * The index returned is for a palette color with the
 * lowest RMS error to the specified color.
 */
CG_EXTERN CGTableCount CGPaletteGetIndexForColor(CGDirectPaletteRef palette, CGDeviceColor color) CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);

/*
 * Get the number of samples in the palette
 */
CG_EXTERN CGTableCount CGPaletteGetNumberOfSamples(CGDirectPaletteRef palette) CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);


/*
 * Set the color value at the specified index
 */
CG_EXTERN void CGPaletteSetColorAtIndex(CGDirectPaletteRef palette, CGDeviceColor color, CGTableCount index) CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);

/*
 * Copy a palette
 */
CG_EXTERN CGDirectPaletteRef CGPaletteCreateCopy(CGDirectPaletteRef palette) CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);

/*
 * Compare two palettes
 */
CG_EXTERN Boolean CGPaletteIsEqualToPalette(CGDirectPaletteRef palette1, CGDirectPaletteRef palette2) CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);

/*
 * Create a new palette blended with a fraction of a device color.
 * Free the resulting palette with CGPaletteRelease()
 */
CG_EXTERN CGDirectPaletteRef CGPaletteCreateFromPaletteBlendedWithColor(
                                          CGDirectPaletteRef palette,
                                          CGPaletteBlendFraction fraction,
                                          CGDeviceColor color) CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);

#endif /* __CGDIRECT_PALETTE_H__ */
