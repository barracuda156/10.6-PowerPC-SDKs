/*
 * ImageIO - CGImageProperties.h
 * Copyright (c) 2004 Apple Computer, Inc. All rights reserved.
 *
 */

#ifndef __CGIMAGEPROPERTIES__
#define __CGIMAGEPROPERTIES__

#include <CoreFoundation/CoreFoundation.h>
#include <CoreGraphics/CGBase.h>


/* Properties that, if returned by CGImageSourceCopyProperties or 
 * CGImageSourceCopyPropertiesAtIndex, contain a dictionary of file-format 
 * or metadata-format specific key-values. */

CG_EXTERN const CFStringRef kCGImagePropertyTIFFDictionary  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
CG_EXTERN const CFStringRef kCGImagePropertyGIFDictionary  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
CG_EXTERN const CFStringRef kCGImagePropertyJFIFDictionary  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
CG_EXTERN const CFStringRef kCGImagePropertyExifDictionary  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
CG_EXTERN const CFStringRef kCGImagePropertyPNGDictionary  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
CG_EXTERN const CFStringRef kCGImagePropertyIPTCDictionary  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
CG_EXTERN const CFStringRef kCGImagePropertyGPSDictionary  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
CG_EXTERN const CFStringRef kCGImagePropertyRawDictionary  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
CG_EXTERN const CFStringRef kCGImagePropertyCIFFDictionary  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
CG_EXTERN const CFStringRef kCGImagePropertyMakerCanonDictionary;
CG_EXTERN const CFStringRef kCGImagePropertyMakerNikonDictionary;
CG_EXTERN const CFStringRef kCGImagePropertyMakerMinoltaDictionary  AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
CG_EXTERN const CFStringRef kCGImagePropertyMakerFujiDictionary  AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
CG_EXTERN const CFStringRef kCGImagePropertyMakerOlympusDictionary  AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
CG_EXTERN const CFStringRef kCGImagePropertyMakerPentaxDictionary  AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
CG_EXTERN const CFStringRef kCGImageProperty8BIMDictionary  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
CG_EXTERN const CFStringRef kCGImagePropertyDNGDictionary;
CG_EXTERN const CFStringRef kCGImagePropertyExifAuxDictionary  AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;


/** Properties which may be returned by "CGImageSourceCopyProperties".  The
 ** values apply to the container in general but not necessarily to any
 ** individual image that it contains. **/

/* The size of the image file in bytes, if known. If present, the value of
 * this key is a CFNumberRef. */

CG_EXTERN const CFStringRef kCGImagePropertyFileSize  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/** Properties which may be returned by "CGImageSourceCopyPropertiesAtIndex".
 ** The values apply to a single image of an image source file. **/

/* The number of pixels in the x- and y-dimensions. The value of these keys 
 * is a CFNumberRef. */

CG_EXTERN const CFStringRef kCGImagePropertyPixelHeight  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
CG_EXTERN const CFStringRef kCGImagePropertyPixelWidth  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/* The DPI in the x- and y-dimensions, if known. If present, the value of
 * these keys is a CFNumberRef. */

CG_EXTERN const CFStringRef kCGImagePropertyDPIHeight  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
CG_EXTERN const CFStringRef kCGImagePropertyDPIWidth  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/* The number of bits in each color sample of each pixel. The value of this 
 * key is a CFNumberRef. */

CG_EXTERN const CFStringRef kCGImagePropertyDepth  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/* The intended display orientation of the image. If present, the value 
 * of this key is a CFNumberRef with the same value as defined by the 
 * TIFF and Exif specifications.  That is:
 *   1  =  0th row is at the top, and 0th column is on the left.  
 *   2  =  0th row is at the top, and 0th column is on the right.  
 *   3  =  0th row is at the bottom, and 0th column is on the right.  
 *   4  =  0th row is at the bottom, and 0th column is on the left.  
 *   5  =  0th row is on the left, and 0th column is the top.  
 *   6  =  0th row is on the right, and 0th column is the top.  
 *   7  =  0th row is on the right, and 0th column is the bottom.  
 *   8  =  0th row is on the left, and 0th column is the bottom.  
 * If not present, a value of 1 is assumed. */ 
 
CG_EXTERN const CFStringRef kCGImagePropertyOrientation  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/* The value of this key is kCFBooleanTrue if the image contains floating- 
 * point pixel samples */ 
 
CG_EXTERN const CFStringRef kCGImagePropertyIsFloat  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/* The value of this key is kCFBooleanTrue if the image contains indexed 
 * (a.k.a. paletted) pixel samples */ 
 
CG_EXTERN const CFStringRef kCGImagePropertyIsIndexed  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/* The value of this key is kCFBooleanTrue if the image contains an alpha 
 * (a.k.a. coverage) channel */ 
 
CG_EXTERN const CFStringRef kCGImagePropertyHasAlpha  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/* The color model of the image such as "RGB", "CMYK", "Gray", or "Lab".
 * The value of this key is CFStringRef. */ 

CG_EXTERN const CFStringRef kCGImagePropertyColorModel  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/* The name of the optional ICC profile embedded in the image, if known.  
 * If present, the value of this key is a CFStringRef. */

CG_EXTERN const CFStringRef kCGImagePropertyProfileName  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Possible values for kCGImagePropertyColorModel property */

CG_EXTERN const CFStringRef kCGImagePropertyColorModelRGB  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
CG_EXTERN const CFStringRef kCGImagePropertyColorModelGray  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
CG_EXTERN const CFStringRef kCGImagePropertyColorModelCMYK  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
CG_EXTERN const CFStringRef kCGImagePropertyColorModelLab  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Possible keys for kCGImagePropertyTIFFDictionary */

CG_EXTERN const CFStringRef kCGImagePropertyTIFFCompression  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
CG_EXTERN const CFStringRef kCGImagePropertyTIFFPhotometricInterpretation  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
CG_EXTERN const CFStringRef kCGImagePropertyTIFFDocumentName  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
CG_EXTERN const CFStringRef kCGImagePropertyTIFFImageDescription  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
CG_EXTERN const CFStringRef kCGImagePropertyTIFFMake  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
CG_EXTERN const CFStringRef kCGImagePropertyTIFFModel  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
CG_EXTERN const CFStringRef kCGImagePropertyTIFFOrientation  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
CG_EXTERN const CFStringRef kCGImagePropertyTIFFXResolution  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
CG_EXTERN const CFStringRef kCGImagePropertyTIFFYResolution  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
CG_EXTERN const CFStringRef kCGImagePropertyTIFFResolutionUnit  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
CG_EXTERN const CFStringRef kCGImagePropertyTIFFSoftware  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
CG_EXTERN const CFStringRef kCGImagePropertyTIFFTransferFunction  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
CG_EXTERN const CFStringRef kCGImagePropertyTIFFDateTime  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
CG_EXTERN const CFStringRef kCGImagePropertyTIFFArtist  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
CG_EXTERN const CFStringRef kCGImagePropertyTIFFHostComputer  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
CG_EXTERN const CFStringRef kCGImagePropertyTIFFCopyright  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
CG_EXTERN const CFStringRef kCGImagePropertyTIFFWhitePoint  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
CG_EXTERN const CFStringRef kCGImagePropertyTIFFPrimaryChromaticities  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/* Possible keys for kCGImagePropertyJFIFDictionary */

CG_EXTERN const CFStringRef kCGImagePropertyJFIFVersion  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
CG_EXTERN const CFStringRef kCGImagePropertyJFIFXDensity  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
CG_EXTERN const CFStringRef kCGImagePropertyJFIFYDensity  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
CG_EXTERN const CFStringRef kCGImagePropertyJFIFDensityUnit  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
CG_EXTERN const CFStringRef kCGImagePropertyJFIFIsProgressive  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Possible keys for kCGImagePropertyExifDictionary */

CG_EXTERN const CFStringRef kCGImagePropertyExifExposureTime  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
CG_EXTERN const CFStringRef kCGImagePropertyExifFNumber  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
CG_EXTERN const CFStringRef kCGImagePropertyExifExposureProgram  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
CG_EXTERN const CFStringRef kCGImagePropertyExifSpectralSensitivity  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
CG_EXTERN const CFStringRef kCGImagePropertyExifISOSpeedRatings  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
CG_EXTERN const CFStringRef kCGImagePropertyExifOECF  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
CG_EXTERN const CFStringRef kCGImagePropertyExifVersion  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
CG_EXTERN const CFStringRef kCGImagePropertyExifDateTimeOriginal  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
CG_EXTERN const CFStringRef kCGImagePropertyExifDateTimeDigitized  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
CG_EXTERN const CFStringRef kCGImagePropertyExifComponentsConfiguration  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
CG_EXTERN const CFStringRef kCGImagePropertyExifCompressedBitsPerPixel  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
CG_EXTERN const CFStringRef kCGImagePropertyExifShutterSpeedValue  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
CG_EXTERN const CFStringRef kCGImagePropertyExifApertureValue  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
CG_EXTERN const CFStringRef kCGImagePropertyExifBrightnessValue  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
CG_EXTERN const CFStringRef kCGImagePropertyExifExposureBiasValue  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
CG_EXTERN const CFStringRef kCGImagePropertyExifMaxApertureValue  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
CG_EXTERN const CFStringRef kCGImagePropertyExifSubjectDistance  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
CG_EXTERN const CFStringRef kCGImagePropertyExifMeteringMode  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
CG_EXTERN const CFStringRef kCGImagePropertyExifLightSource  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
CG_EXTERN const CFStringRef kCGImagePropertyExifFlash  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
CG_EXTERN const CFStringRef kCGImagePropertyExifFocalLength  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
CG_EXTERN const CFStringRef kCGImagePropertyExifSubjectArea  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
CG_EXTERN const CFStringRef kCGImagePropertyExifMakerNote  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
CG_EXTERN const CFStringRef kCGImagePropertyExifUserComment  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
CG_EXTERN const CFStringRef kCGImagePropertyExifSubsecTime  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
CG_EXTERN const CFStringRef kCGImagePropertyExifSubsecTimeOrginal  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
CG_EXTERN const CFStringRef kCGImagePropertyExifSubsecTimeDigitized  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
CG_EXTERN const CFStringRef kCGImagePropertyExifFlashPixVersion  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
CG_EXTERN const CFStringRef kCGImagePropertyExifColorSpace  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
CG_EXTERN const CFStringRef kCGImagePropertyExifPixelXDimension  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
CG_EXTERN const CFStringRef kCGImagePropertyExifPixelYDimension  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
CG_EXTERN const CFStringRef kCGImagePropertyExifRelatedSoundFile  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
CG_EXTERN const CFStringRef kCGImagePropertyExifFlashEnergy  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
CG_EXTERN const CFStringRef kCGImagePropertyExifSpatialFrequencyResponse  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
CG_EXTERN const CFStringRef kCGImagePropertyExifFocalPlaneXResolution  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
CG_EXTERN const CFStringRef kCGImagePropertyExifFocalPlaneYResolution  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
CG_EXTERN const CFStringRef kCGImagePropertyExifFocalPlaneResolutionUnit  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
CG_EXTERN const CFStringRef kCGImagePropertyExifSubjectLocation  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
CG_EXTERN const CFStringRef kCGImagePropertyExifExposureIndex  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
CG_EXTERN const CFStringRef kCGImagePropertyExifSensingMethod  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
CG_EXTERN const CFStringRef kCGImagePropertyExifFileSource  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
CG_EXTERN const CFStringRef kCGImagePropertyExifSceneType  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
CG_EXTERN const CFStringRef kCGImagePropertyExifCFAPattern  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
CG_EXTERN const CFStringRef kCGImagePropertyExifCustomRendered  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
CG_EXTERN const CFStringRef kCGImagePropertyExifExposureMode  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
CG_EXTERN const CFStringRef kCGImagePropertyExifWhiteBalance  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
CG_EXTERN const CFStringRef kCGImagePropertyExifDigitalZoomRatio  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
CG_EXTERN const CFStringRef kCGImagePropertyExifFocalLenIn35mmFilm  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
CG_EXTERN const CFStringRef kCGImagePropertyExifSceneCaptureType  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
CG_EXTERN const CFStringRef kCGImagePropertyExifGainControl  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
CG_EXTERN const CFStringRef kCGImagePropertyExifContrast  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
CG_EXTERN const CFStringRef kCGImagePropertyExifSaturation  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
CG_EXTERN const CFStringRef kCGImagePropertyExifSharpness  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
CG_EXTERN const CFStringRef kCGImagePropertyExifDeviceSettingDescription  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
CG_EXTERN const CFStringRef kCGImagePropertyExifSubjectDistRange  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
CG_EXTERN const CFStringRef kCGImagePropertyExifImageUniqueID  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
CG_EXTERN const CFStringRef kCGImagePropertyExifGamma  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/* Possible keys for kCGImagePropertyExifAuxDictionary */
CG_EXTERN const CFStringRef kCGImagePropertyExifAuxLensInfo	AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
CG_EXTERN const CFStringRef kCGImagePropertyExifAuxLensModel  AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
CG_EXTERN const CFStringRef kCGImagePropertyExifAuxSerialNumber	AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
CG_EXTERN const CFStringRef kCGImagePropertyExifAuxLensID	AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
CG_EXTERN const CFStringRef kCGImagePropertyExifAuxLensSerialNumber	AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
CG_EXTERN const CFStringRef kCGImagePropertyExifAuxImageNumber	AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
CG_EXTERN const CFStringRef kCGImagePropertyExifAuxFlashCompensation	AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
CG_EXTERN const CFStringRef kCGImagePropertyExifAuxOwnerName	AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
CG_EXTERN const CFStringRef kCGImagePropertyExifAuxFirmware	AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

/* Possible keys for kCGImagePropertyGIFDictionary */

CG_EXTERN const CFStringRef kCGImagePropertyGIFLoopCount  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
CG_EXTERN const CFStringRef kCGImagePropertyGIFDelayTime  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
CG_EXTERN const CFStringRef kCGImagePropertyGIFImageColorMap  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
CG_EXTERN const CFStringRef kCGImagePropertyGIFHasGlobalColorMap  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/* Possible keys for kCGImagePropertyPNGDictionary */

CG_EXTERN const CFStringRef kCGImagePropertyPNGGamma  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
CG_EXTERN const CFStringRef kCGImagePropertyPNGInterlaceType  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
CG_EXTERN const CFStringRef kCGImagePropertyPNGXPixelsPerMeter  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
CG_EXTERN const CFStringRef kCGImagePropertyPNGYPixelsPerMeter  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
CG_EXTERN const CFStringRef kCGImagePropertyPNGsRGBIntent  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
CG_EXTERN const CFStringRef kCGImagePropertyPNGChromaticities  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/* Possible keys for kCGImagePropertyGPSDictionary */

CG_EXTERN const CFStringRef kCGImagePropertyGPSVersion  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
CG_EXTERN const CFStringRef kCGImagePropertyGPSLatitudeRef  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
CG_EXTERN const CFStringRef kCGImagePropertyGPSLatitude  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
CG_EXTERN const CFStringRef kCGImagePropertyGPSLongitudeRef  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
CG_EXTERN const CFStringRef kCGImagePropertyGPSLongitude  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
CG_EXTERN const CFStringRef kCGImagePropertyGPSAltitudeRef  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
CG_EXTERN const CFStringRef kCGImagePropertyGPSAltitude  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
CG_EXTERN const CFStringRef kCGImagePropertyGPSTimeStamp  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
CG_EXTERN const CFStringRef kCGImagePropertyGPSSatellites  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
CG_EXTERN const CFStringRef kCGImagePropertyGPSStatus  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
CG_EXTERN const CFStringRef kCGImagePropertyGPSMeasureMode  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
CG_EXTERN const CFStringRef kCGImagePropertyGPSDOP  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
CG_EXTERN const CFStringRef kCGImagePropertyGPSSpeedRef  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
CG_EXTERN const CFStringRef kCGImagePropertyGPSSpeed  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
CG_EXTERN const CFStringRef kCGImagePropertyGPSTrackRef  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
CG_EXTERN const CFStringRef kCGImagePropertyGPSTrack  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
CG_EXTERN const CFStringRef kCGImagePropertyGPSImgDirectionRef  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
CG_EXTERN const CFStringRef kCGImagePropertyGPSImgDirection  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
CG_EXTERN const CFStringRef kCGImagePropertyGPSMapDatum  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
CG_EXTERN const CFStringRef kCGImagePropertyGPSDestLatitudeRef  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
CG_EXTERN const CFStringRef kCGImagePropertyGPSDestLatitude  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
CG_EXTERN const CFStringRef kCGImagePropertyGPSDestLongitudeRef  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
CG_EXTERN const CFStringRef kCGImagePropertyGPSDestLongitude  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
CG_EXTERN const CFStringRef kCGImagePropertyGPSDestBearingRef  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
CG_EXTERN const CFStringRef kCGImagePropertyGPSDestBearing  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
CG_EXTERN const CFStringRef kCGImagePropertyGPSDestDistanceRef  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
CG_EXTERN const CFStringRef kCGImagePropertyGPSDestDistance  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
CG_EXTERN const CFStringRef kCGImagePropertyGPSProcessingMethod  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
CG_EXTERN const CFStringRef kCGImagePropertyGPSAreaInformation  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
CG_EXTERN const CFStringRef kCGImagePropertyGPSDateStamp  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
CG_EXTERN const CFStringRef kCGImagePropertyGPSDifferental  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/* Possible keys for kCGImagePropertyIPTCDictionary */

CG_EXTERN const CFStringRef kCGImagePropertyIPTCObjectTypeReference  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
CG_EXTERN const CFStringRef kCGImagePropertyIPTCObjectAttributeReference  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
CG_EXTERN const CFStringRef kCGImagePropertyIPTCObjectName  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
CG_EXTERN const CFStringRef kCGImagePropertyIPTCEditStatus  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
CG_EXTERN const CFStringRef kCGImagePropertyIPTCEditorialUpdate  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
CG_EXTERN const CFStringRef kCGImagePropertyIPTCUrgency  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
CG_EXTERN const CFStringRef kCGImagePropertyIPTCSubjectReference  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
CG_EXTERN const CFStringRef kCGImagePropertyIPTCCategory  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
CG_EXTERN const CFStringRef kCGImagePropertyIPTCSupplementalCategory  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
CG_EXTERN const CFStringRef kCGImagePropertyIPTCFixtureIdentifier  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
CG_EXTERN const CFStringRef kCGImagePropertyIPTCKeywords  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
CG_EXTERN const CFStringRef kCGImagePropertyIPTCContentLocationCode  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
CG_EXTERN const CFStringRef kCGImagePropertyIPTCContentLocationName  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
CG_EXTERN const CFStringRef kCGImagePropertyIPTCReleaseDate  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
CG_EXTERN const CFStringRef kCGImagePropertyIPTCReleaseTime  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
CG_EXTERN const CFStringRef kCGImagePropertyIPTCExpirationDate  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
CG_EXTERN const CFStringRef kCGImagePropertyIPTCExpirationTime  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
CG_EXTERN const CFStringRef kCGImagePropertyIPTCSpecialInstructions  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
CG_EXTERN const CFStringRef kCGImagePropertyIPTCActionAdvised  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
CG_EXTERN const CFStringRef kCGImagePropertyIPTCReferenceService  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
CG_EXTERN const CFStringRef kCGImagePropertyIPTCReferenceDate  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
CG_EXTERN const CFStringRef kCGImagePropertyIPTCReferenceNumber  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
CG_EXTERN const CFStringRef kCGImagePropertyIPTCDateCreated  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
CG_EXTERN const CFStringRef kCGImagePropertyIPTCTimeCreated  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
CG_EXTERN const CFStringRef kCGImagePropertyIPTCDigitalCreationDate  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
CG_EXTERN const CFStringRef kCGImagePropertyIPTCDigitalCreationTime  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
CG_EXTERN const CFStringRef kCGImagePropertyIPTCOriginatingProgram  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
CG_EXTERN const CFStringRef kCGImagePropertyIPTCProgramVersion  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
CG_EXTERN const CFStringRef kCGImagePropertyIPTCObjectCycle  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
CG_EXTERN const CFStringRef kCGImagePropertyIPTCByline  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
CG_EXTERN const CFStringRef kCGImagePropertyIPTCBylineTitle  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
CG_EXTERN const CFStringRef kCGImagePropertyIPTCCity  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
CG_EXTERN const CFStringRef kCGImagePropertyIPTCSubLocation  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
CG_EXTERN const CFStringRef kCGImagePropertyIPTCProvinceState  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
CG_EXTERN const CFStringRef kCGImagePropertyIPTCCountryPrimaryLocationCode  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
CG_EXTERN const CFStringRef kCGImagePropertyIPTCCountryPrimaryLocationName  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
CG_EXTERN const CFStringRef kCGImagePropertyIPTCOriginalTransmissionReference  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
CG_EXTERN const CFStringRef kCGImagePropertyIPTCHeadline  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
CG_EXTERN const CFStringRef kCGImagePropertyIPTCCredit  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
CG_EXTERN const CFStringRef kCGImagePropertyIPTCSource  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
CG_EXTERN const CFStringRef kCGImagePropertyIPTCCopyrightNotice  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
CG_EXTERN const CFStringRef kCGImagePropertyIPTCContact  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
CG_EXTERN const CFStringRef kCGImagePropertyIPTCCaptionAbstract  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
CG_EXTERN const CFStringRef kCGImagePropertyIPTCWriterEditor  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
CG_EXTERN const CFStringRef kCGImagePropertyIPTCImageType  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
CG_EXTERN const CFStringRef kCGImagePropertyIPTCImageOrientation  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
CG_EXTERN const CFStringRef kCGImagePropertyIPTCLanguageIdentifier  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
CG_EXTERN const CFStringRef kCGImagePropertyIPTCStarRating  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/* Possible keys for kCGImageProperty8BIMDictionary */

CG_EXTERN const CFStringRef  kCGImageProperty8BIMLayerNames;


/* Possible keys for kCGImagePropertyDNGDictionary */

CG_EXTERN const CFStringRef  kCGImagePropertyDNGVersion;
CG_EXTERN const CFStringRef  kCGImagePropertyDNGBackwardVersion;
CG_EXTERN const CFStringRef  kCGImagePropertyDNGUniqueCameraModel;
CG_EXTERN const CFStringRef  kCGImagePropertyDNGLocalizedCameraModel;
CG_EXTERN const CFStringRef  kCGImagePropertyDNGCameraSerialNumber;
CG_EXTERN const CFStringRef  kCGImagePropertyDNGLensInfo;


/* Possible keys for kCGImagePropertyCIFFDictionary */

CG_EXTERN const CFStringRef  kCGImagePropertyCIFFDescription;
CG_EXTERN const CFStringRef  kCGImagePropertyCIFFFirmware;
CG_EXTERN const CFStringRef  kCGImagePropertyCIFFOwnerName;
CG_EXTERN const CFStringRef  kCGImagePropertyCIFFImageName;
CG_EXTERN const CFStringRef  kCGImagePropertyCIFFImageFileName;
CG_EXTERN const CFStringRef  kCGImagePropertyCIFFReleaseMethod;
CG_EXTERN const CFStringRef  kCGImagePropertyCIFFReleaseTiming;
CG_EXTERN const CFStringRef  kCGImagePropertyCIFFRecordID;
CG_EXTERN const CFStringRef  kCGImagePropertyCIFFSelfTimingTime;
CG_EXTERN const CFStringRef  kCGImagePropertyCIFFCameraSerialNumber;
CG_EXTERN const CFStringRef  kCGImagePropertyCIFFImageSerialNumber;
CG_EXTERN const CFStringRef  kCGImagePropertyCIFFContinuousDrive;
CG_EXTERN const CFStringRef  kCGImagePropertyCIFFFocusMode;
CG_EXTERN const CFStringRef  kCGImagePropertyCIFFMeteringMode;
CG_EXTERN const CFStringRef  kCGImagePropertyCIFFShootingMode;
CG_EXTERN const CFStringRef  kCGImagePropertyCIFFLensModel;
CG_EXTERN const CFStringRef  kCGImagePropertyCIFFLensMaxMM;
CG_EXTERN const CFStringRef  kCGImagePropertyCIFFLensMinMM;
CG_EXTERN const CFStringRef  kCGImagePropertyCIFFWhiteBalanceIndex;
CG_EXTERN const CFStringRef  kCGImagePropertyCIFFFlashExposureComp;
CG_EXTERN const CFStringRef  kCGImagePropertyCIFFMeasuredEV;


/* Possible keys for kCGImagePropertyMakerNikonDictionary */

CG_EXTERN const CFStringRef  kCGImagePropertyMakerNikonISOSetting;
CG_EXTERN const CFStringRef  kCGImagePropertyMakerNikonColorMode;
CG_EXTERN const CFStringRef  kCGImagePropertyMakerNikonQuality;
CG_EXTERN const CFStringRef  kCGImagePropertyMakerNikonWhiteBalanceMode;
CG_EXTERN const CFStringRef  kCGImagePropertyMakerNikonSharpenMode;
CG_EXTERN const CFStringRef  kCGImagePropertyMakerNikonFocusMode;
CG_EXTERN const CFStringRef  kCGImagePropertyMakerNikonFlashSetting;
CG_EXTERN const CFStringRef  kCGImagePropertyMakerNikonISOSelection;
CG_EXTERN const CFStringRef  kCGImagePropertyMakerNikonFlashExposureComp;
CG_EXTERN const CFStringRef  kCGImagePropertyMakerNikonImageAdjustment;
CG_EXTERN const CFStringRef  kCGImagePropertyMakerNikonLensAdapter;
CG_EXTERN const CFStringRef	 kCGImagePropertyMakerNikonLensType;
CG_EXTERN const CFStringRef  kCGImagePropertyMakerNikonLensInfo;
CG_EXTERN const CFStringRef  kCGImagePropertyMakerNikonFocusDistance;
CG_EXTERN const CFStringRef  kCGImagePropertyMakerNikonDigitalZoom;
CG_EXTERN const CFStringRef  kCGImagePropertyMakerNikonShootingMode;
CG_EXTERN const CFStringRef  kCGImagePropertyMakerNikonCameraSerialNumber;
CG_EXTERN const CFStringRef  kCGImagePropertyMakerNikonShutterCount;

/* Possible keys for kCGImagePropertyMakerCanonDictionary */

CG_EXTERN const CFStringRef  kCGImagePropertyMakerCanonOwnerName;
CG_EXTERN const CFStringRef  kCGImagePropertyMakerCanonCameraSerialNumber;
CG_EXTERN const CFStringRef  kCGImagePropertyMakerCanonImageSerialNumber;
CG_EXTERN const CFStringRef  kCGImagePropertyMakerCanonFlashExposureComp;
CG_EXTERN const CFStringRef  kCGImagePropertyMakerCanonContinuousDrive;
CG_EXTERN const CFStringRef  kCGImagePropertyMakerCanonLensModel;
CG_EXTERN const CFStringRef  kCGImagePropertyMakerCanonFirmware	AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
CG_EXTERN const CFStringRef  kCGImagePropertyMakerCanonAspectRatioInfo	AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;


#endif	/* __CGIMAGEPROPERTIES__ */
