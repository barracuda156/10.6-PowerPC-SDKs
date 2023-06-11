/*
	File:		QTKitDefines.h

	Copyright:	(c)2004-2007 by Apple Inc., all rights reserved.

	
	Revision 1.7.56.1.2.1.8.1  2007/11/06 02:50:10  simon
	Remove Movies.h redefinitions because these are now exposed to 64-bit clients. Radar 5436331 <dunderwood>
	
	Revision 1.7.56.1.2.1  2007/07/31 04:33:19  dunderwo
	[5364700] QTKit now has its own set of #if guard macros. <jsam, cad, timmon>
	
	Revision 1.7.56.1  2007/04/26 00:44:05  duano
	=== Maguro deltas re-applied post QT716 GM rebase ===
	
		Revision 1.7.48.4  2007/04/04 02:09:03  cad
		Check for presence of each leopard availability macro independently, in case another framework with similar deployment needs only gets AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER. (5110188) <dunderwo>
		
		Revision 1.7.48.3  2007/03/29 23:30:13  dunderwo
		[5051048] Capture classes now all use _internal ivar. General header cleanup. <simon>
		
		Revision 1.7.48.2  2007/03/03 01:58:50  timmon
		Added preprocessor code to define or redefine MAC_OS_X_VERSION_10_5, which is not defined on Tiger; also remove code defining QTKIT_ENABLE_LAYERKIT; part of fixing Radar 4943592.
		
	Revision 1.7.48.1  2007/01/25 18:33:52  duano
	=== Maguro deltas re-applied post QT715 GM rebase ===
		
		Revision 1.7.46.7  2007/01/19 18:46:47  simon
		Removing temporarily QTMovieLayer functionality. Radar 4939842. <dunderwood>
		
		Revision 1.7.46.6  2007/01/06 19:31:46  timmon
		Added definition of QTKIT_ENABLE_LAYERKIT.
		
		Revision 1.7.46.5  2006/12/12 18:23:41  timmon
		Added QTKIT_HIDDEN macro; part of fixing Radar 4875334.
		
		Revision 1.7.46.4  2006/12/05 22:45:47  timmon
		Removed data types CodecQ and CodecType; fixes 64-bit build.
		
		Revision 1.7.46.3  2006/12/04 23:32:50  timmon
		Added a number of constants and data types to the 64-bit target, so that they can be used in 64-bit applications; fixes Radar 4853446.
		
		Revision 1.7.46.2  2006/11/12 00:51:47  kudo
		Fix Maguro SCM build by not relying on a Leopard version of AvailabilityMacros.h.   The redefinitions of the 10_5 macros are moved from QTKit.h into QTKitDefines.h
	
	Revision 1.7.46.1  2006/09/21 21:38:42  kudo
	=== Maguro deltas re-applied post QT713 GM rebase ===
	
		Revision 1.7.40.1  2006/09/15 00:06:30  dunderwo
		Synced up with latest API changes <simon>.
	
	Revision 1.7  2004/05/20 22:33:04  timmon
	Changed copyright date to 2004.
	
	Revision 1.6  2004/05/18 20:52:20  timmon
	Change copyright symbol to "(c)".
	
	Revision 1.5  2003/10/17 21:28:45  abaerlocher
	Add a linefeed.
	
	Revision 1.4  2003/10/17 21:28:17  abaerlocher
	Add a cvs log.
	
*/


#ifndef _QTKITDEFINES_H
#define _QTKITDEFINES_H

#ifndef AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER
#define AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER       WEAK_IMPORT_ATTRIBUTE
#endif
#ifndef AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER
#define AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER       WEAK_IMPORT_ATTRIBUTE
#endif
#ifndef AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5
#define AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER
#endif
#ifndef AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5
#define AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5       AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER
#endif
#ifndef AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5
#define AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5       AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER
#endif
#ifndef AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5
#define AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5       AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER
#endif
#ifndef AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5
#define AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5       AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER
#endif

#ifndef MAC_OS_X_VERSION_10_4
#define MAC_OS_X_VERSION_10_4		1040
#else
#undef MAC_OS_X_VERSION_10_4
#define MAC_OS_X_VERSION_10_4		1040
#endif

#ifndef MAC_OS_X_VERSION_10_5
#define MAC_OS_X_VERSION_10_5		1050
#else
#undef MAC_OS_X_VERSION_10_5
#define MAC_OS_X_VERSION_10_5		1050
#endif

#ifndef MAC_OS_X_VERSION_10_6
#define MAC_OS_X_VERSION_10_6		1060
#else
#undef MAC_OS_X_VERSION_10_6
#define MAC_OS_X_VERSION_10_6		1060
#endif

/*
 QTKit Availability Macros
 
 These macros allow applications to target specific versions of QTKit independently
 of the OS on which the application is built. To target one or more versions of
 QTKit, you can use the QTKIT_VERSION_MIN_REQUIRED and the QTKIT_VERSION_MAX_ALLOWED
 macros in a a way that is analagous to MAC_OS_X_VERSION_MIN_REQUIRED and
 MAC_OS_X_VERSION_MAX_ALLOWED as described in /usr/include/AvailabilityMacros.h. By
 default, the macros are configured to weak-link to symbols as necessary for the
 application to run on all target versions of Max OS X.
 
 IMPORTANT: These macros only properly expose or restrict the available API at
 compile and link time. Since QTKit is released for multiple versions of Mac OS X,
 some of which may not have a given version installed by default, applications must
 also verify whether or not an API exists at run time. It is recommended that
 applications do this by checking which version of QuickTime is installed. Such a
 check also allows applications to ensure they are running against the latest version
 of QTKit in which an API is supported. For example, applications targeting APIs
 introduced for QTKit 7.2 should make sure they are running against QuickTime 7.2.1
 or later, which is the first release for which the QuickTime 7.2 SDK is supported.
 One way to check the QuickTime version is use the Gestalt API. For example, to use
 an API that first became supported in QTKit 7.2, an application would do the
 following:
 
 OSErr err;
 UInt32 qtVersion;
 
 err = Gestalt(gestaltQuickTimeVersion, &qtVersion);
 if ((err == noErr) && (qtVersion >= 0x07210000)) {
     // Use API introduced in QTKit 7.2.1
 }
 
 */

#define QTKIT_VERSION_7_0           70000
#define QTKIT_VERSION_7_2           70200
#define QTKIT_VERSION_7_6           70600

#ifndef QTKIT_VERSION_MIN_REQUIRED
    #if MAC_OS_X_VERSION_MIN_REQUIRED >= MAC_OS_X_VERSION_10_6
        #define QTKIT_VERSION_MIN_REQUIRED QTKIT_VERSION_7_6
    #elif MAC_OS_X_VERSION_MIN_REQUIRED >= MAC_OS_X_VERSION_10_5
        #define QTKIT_VERSION_MIN_REQUIRED QTKIT_VERSION_7_2
    #else
        #define QTKIT_VERSION_MIN_REQUIRED QTKIT_VERSION_7_0
    #endif
#endif

#ifndef QTKIT_VERSION_MAX_ALLOWED
    #define QTKIT_VERSION_MAX_ALLOWED QTKIT_VERSION_7_6
#endif

// error on bad values
#if QTKIT_VERSION_MAX_ALLOWED < QTKIT_VERSION_MIN_REQUIRED
    #error QTKIT_VERSION_MAX_ALLOWED must be >= QTKIT_VERSION_MIN_REQUIRED
#endif
#if QTKIT_VERSION_MIN_REQUIRED < QTKIT_VERSION_7_0
    #error QTKIT_VERSION_MIN_REQUIRED must be >= QTKIT_VERSION_7_0
#endif

#ifdef __cplusplus
#define QTKIT_EXTERN extern "C"
#else
#define QTKIT_EXTERN extern
#endif

#define QTKIT_HIDDEN __attribute__((visibility("hidden")))

#ifndef NSINTEGER_DEFINED

#if __LP64__ || NS_BUILD_32_LIKE_64
typedef long NSInteger;
typedef unsigned long NSUInteger;
#else
typedef int NSInteger;
typedef unsigned int NSUInteger;
#endif


#define NSIntegerMax    LONG_MAX
#define NSIntegerMin    LONG_MIN
#define NSUIntegerMax   ULONG_MAX

#define NSINTEGER_DEFINED 1

#endif	/* NSINTEGER_DEFINED */

#if __LP64__
// constants and data types defined in the 32-bit QuickTime headers that may be required for some QTKit APIs

	// from QuickTimeComponents.h
enum {
	kQTFileTypeAIFF						= 'AIFF',
	kQTFileTypeAIFC						= 'AIFC',
	kQTFileTypeDVC						= 'dvc!',
	kQTFileTypeMIDI						= 'Midi',
	kQTFileTypePicture					= 'PICT',
	kQTFileTypeMovie					= 'MooV',
	kQTFileTypeText						= 'TEXT',
	kQTFileTypeWave						= 'WAVE',
	kQTFileTypeSystemSevenSound			= 'sfil',
	kQTFileTypeMuLaw					= 'ULAW',
	kQTFileTypeAVI						= 'VfW ',
	kQTFileTypeSoundDesignerII			= 'Sd2f',
	kQTFileTypeAudioCDTrack				= 'trak',
	kQTFileTypePICS						= 'PICS',
	kQTFileTypeGIF						= 'GIFf',
	kQTFileTypePNG						= 'PNGf',
	kQTFileTypeTIFF						= 'TIFF',
	kQTFileTypePhotoShop				= '8BPS',
	kQTFileTypeSGIImage					= '.SGI',
	kQTFileTypeBMP						= 'BMPf',
	kQTFileTypeJPEG						= 'JPEG',
	kQTFileTypeJFIF						= 'JPEG',
	kQTFileTypeMacPaint					= 'PNTG',
	kQTFileTypeTargaImage				= 'TPIC',
	kQTFileTypeQuickDrawGXPicture		= 'qdgx',
	kQTFileTypeQuickTimeImage			= 'qtif',
	kQTFileType3DMF						= '3DMF',
	kQTFileTypeFLC						= 'FLC ',
	kQTFileTypeFlash					= 'SWFL',
	kQTFileTypeFlashPix					= 'FPix',
	kQTFileTypeMP4						= 'mpg4',
	kQTFileTypePDF						= 'PDF ',
	kQTFileType3GPP						= '3gpp',
	kQTFileTypeAMR						= 'amr ',
	kQTFileTypeSDV						= 'sdv ',
	kQTFileType3GP2						= '3gp2',
	kQTFileTypeAMC						= 'amc ',
	kQTFileTypeJPEG2000					= 'jp2 '
};

	// from ImageCompression.h
enum {
	codecLosslessQuality				= 0x00000400,
	codecMaxQuality						= 0x000003FF,
	codecMinQuality						= 0x00000000,
	codecLowQuality						= 0x00000100,
	codecNormalQuality					= 0x00000200,
	codecHighQuality					= 0x00000300
};

enum {
	graphicsModeStraightAlpha			= 256,
	graphicsModePreWhiteAlpha			= 257,
	graphicsModePreBlackAlpha			= 258,
	graphicsModeComposition				= 259,
	graphicsModeStraightAlphaBlend		= 260,
	graphicsModePreMulColorAlpha		= 261,
	graphicsModePerComponentAlpha		= 272
};

#endif	/* __LP64__ */


#endif	/* _QTKITDEFINES_H */
