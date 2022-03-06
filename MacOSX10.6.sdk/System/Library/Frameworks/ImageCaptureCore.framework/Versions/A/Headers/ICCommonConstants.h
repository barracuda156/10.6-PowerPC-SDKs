//------------------------------------------------------------------------------------------------------------------------------
//
//  ICCommonConstants.h
//  ImageCaptureCore
//
//  Copyright (c) 2008 Apple, Inc., all rights reserved.
//
//  Best viewed with the following settings: Tab width 4, Indent width 2, Wrap lines, Indent wrapped lines by 3, Page guide 128.
//
//------------------------------------------------------------------------------------------------------------------------------

/*!
  @enum ICEXIFOrientationType
  @abstract Type representing EXIF Orientation tag value
  @discussion The meaning of this value is defined by the EXIF specification. Here is what the letter F would look like if it were tagged correctly and displayed by a program that ignores the orientation tag (thus showing the stored image):

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

enum
{
    ICEXIFOrientation1  = 1,    // Normal
    ICEXIFOrientation2  = 2,    // Flipped horizontally
    ICEXIFOrientation3  = 3,    // Rotated 180°
    ICEXIFOrientation4  = 4,    // Flipped vertically
    ICEXIFOrientation5  = 5,    // Rotated 90° CCW and flipped vertically
    ICEXIFOrientation6  = 6,    // Rotated 90° CW
    ICEXIFOrientation7  = 7,    // Rotated 90° CW and flipped vertically
    ICEXIFOrientation8  = 8,    // Rotated 90° CCW
};
typedef NSUInteger ICEXIFOrientationType;

//------------------------------------------------------------------------------------------------------------------------------
