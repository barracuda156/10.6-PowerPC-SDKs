/*
	File:		QTMovie.h

	Copyright:	(c)2004-2008 by Apple Inc., all rights reserved.

		
		Revision 1.88.20.1.2.1.4.1  2008/01/10 23:46:20  cad
		Implement image consumer model.
	
	Revision 1.90.8.1  2008/04/14 18:14:23  timmon
	Added declarations of QTMovieOpenAsyncRequiredAttribute, QTMovieOpenForPlaybackAttribute, and cancelLoading, for SnowLeopard media slice.
	
	Revision 1.90  2008/01/18 02:18:22  ibarberi
	=== QT74GM => TopOfTree Merge ===
	
	Revision 1.88.20.1.2.1  2007/07/31 04:33:19  dunderwo
	[5364700] QTKit now has its own set of #if guard macros. <jsam, cad, timmon>
	
	Revision 1.88.20.1  2007/04/26 00:44:11  duano
	=== Maguro deltas re-applied post QT716 GM rebase ===
	
	Revision 1.88.12.5  2007/04/02 16:15:42  timmon
	Added declaration of removeTrack:, new public name for existing disposeTrack: (which was made private once again); part of fixing Radar 5079030.
	
	Revision 1.88.12.4  2007/03/29 23:30:13  dunderwo
	[5051048] Capture classes now all use _internal ivar. General header cleanup. <simon>
	
	Revision 1.88.12.3  2007/03/08 01:16:58  timmon
	Added declaration of invalidate method; part of fixing Radar 5027165.
	
	Revision 1.88.12.2  2007/03/08 00:47:40  timmon
	Added declarations of setVisualContext: and visualContext methods; part of fixing Radar 3967754.
	
	Revision 1.88.12.1  2007/01/25 18:33:52  duano
	=== Maguro deltas re-applied post QT715 GM rebase ===
	
	Revision 1.88.10.9  2006/12/04 23:20:27  timmon
	Moved those constants and data types to QTKitDefines.h, which is a better location for them.
	
	Revision 1.88.10.8  2006/12/01 19:23:04  timmon
	Added a number of constants and data types to the 64-bit only header, so that they can be used in 64-bit applications; fixes Radar 4853446.
	
	Revision 1.88.10.7  2006/11/17 20:38:45  timmon
	Added _delegateProxy instance variable to 64-bit QTMovie; part of fixing Radar 4754387.
	
	Revision 1.88.10.6  2006/09/28 22:37:15  timmon
	Added declarations of QTMovieChapters methods; part of fixing Radar 4585314.
	
	Revision 1.88.10.5  2006/09/28 21:44:41  timmon
	Added declaration of disposeTrack: method; part of fixing Radar 4544134.
	
	Revision 1.88.10.4  2006/09/28 21:28:28  timmon
	Added declarations of insertSegmentOfTrack: methods; part of fixing Radar 4461442.
	
	Revision 1.88.10.3  2006/09/28 20:36:52  timmon
	Added declaration of frameImageAtTime:withAttributes:error: and associated constants; also added version tests around other new-in-Leopard APIs; fixes Radar 4272522.
	
	Revision 1.88.10.2  2006/09/27 18:23:08  timmon
	Added new public constants for values returned by QTMovieLoadStateAttribute; fixes Radar 4743442.
	
	Revision 1.88.10.1  2006/09/21 21:38:42  kudo
	=== Maguro deltas re-applied post QT713 GM rebase ===
	
	Revision 1.88.4.13  2006/09/18 22:22:32  timmon
	Fixed duplicate "const" in previous check-in; oops.
	
	Revision 1.88.4.12  2006/09/18 20:32:17  timmon
	Changed "NSString *" to "NSString * const" for exported strings; fixes Radar 4359232.
	
	Revision 1.88.4.11  2006/09/17 19:18:54  timmon
	Added QTIncludeDynamicTypes; fixes Radar 4619855.
	
	Revision 1.88.4.10  2006/07/17 17:58:30  timmon
	Made -setIdling: and -isIdling public; fixes Radar 4630983.
	
	Revision 1.88.4.9  2006/07/09 23:11:31  timmon
	Added declaration of -writeToFile:withAttributes:error:; part of fixing Radar 4519353.
	
	Revision 1.88.4.8  2006/07/09 22:33:45  timmon
	Added declarations of QTMovieThreading methods, which are now public; part of fixing Radar 4594206.
	
	Revision 1.88.4.7  2006/07/09 22:12:06  timmon
	Added declarations of -initToWritable* methods; part of fixing Radar 4102053.
	
	Revision 1.88.4.6  2006/07/09 16:47:45  timmon
	Added declaration of +movieTypesWithOptions:; part of fixing Radar 4369542.
	
	Revision 1.88.4.5  2006/07/09 03:20:10  timmon
	Changed return type of movieWithTimeRange:error: to id; fixes Radar 4159321.
	
	Revision 1.88.4.4  2006/07/08 18:04:19  timmon
	Added "deprecated in 10.5" availability macro to QTMovieActiveSegmentAttribute; fixes Radar 4039530.
	
	Revision 1.88.4.3  2006/07/08 17:47:26  timmon
	Added declaration of -autoplay, which is now public. Part of fixing Radar 4164021.
	
	Revision 1.88.4.2  2006/05/16 21:33:08  timmon
	Made header 64-bit clean.
	
	Revision 1.88.4.1  2006/05/13 03:52:36  timmon
	Cleaned up tabs and spaces in file. Fixes Radar 4361522.
	
	Revision 1.88  2006/05/08 23:43:08  duano
	=== QT71GM => TopOfTree Merge ===
	
	Revision 1.87.6.3  2006/04/10 22:00:04  timmon
	Undid previous change, now that Radar 4508838 is fixed.
	
	Revision 1.87.6.2  2006/04/10 15:47:54  timmon
	Commented out uses of AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER macro, to keep pre-Leopard build environments working for the  moment.
	
	Revision 1.87.6.1  2006/04/08 02:17:12  timmon
	Added declarations of new aperture mode methods and associated constants. Part of fixing Radar 4419737.
	
	Revision 1.87  2005/09/27 19:11:34  bpietsch
	Merge  QT7Branch     (QT7Base0 -> QTMerge33_QT702_to_TOT_QT7) Shipped:   QT702GM
	  ==>  Top Of Tree    PreMerge:   QTMerge33_QT702_to_TOT_TOT  PostMerge: QTMerge33_QT702_to_TOT
	_______________________________________________________________________________________________
	
	Revision 1.86  2005/09/23 02:40:54  bpietsch
	QT702GM to TOT merge -- files added on QT7Branch that were not added to TOT <dkudo>
	
	Revision 1.84.4.3  2005/06/22 15:45:05  timmon
	Add _reserved4 ivar where _equalizerMedia used to be (but was removed by fixes for Radar 4128775. <dss>
	
	Revision 1.84.4.2  2005/06/01 01:11:17  dss
	[4128775] Spectral metering proxying is now done by the MovieAudioFrequencyMetering APIs. <timmon>
	
	Revision 1.84.4.1  2005/03/10 23:10:44  timmon
	Added _seed instance variable; part of fixing Radar 4021601. <jkc>
	
	Revision 1.84  2005/02/15 00:19:41  timmon
	Added _keepInactive instance variable; part of fixing Radar 3976274. <asonone>
	
	Revision 1.83  2005/01/04 22:56:39  timmon
	Add declaration of new public delegate method movieShouldTask:; fixes Radar 3930088. <jkc>
	
	Revision 1.82  2004/12/24 01:08:15  dss
	[3933699] Make QTMovieRateChangesPreservePitchAttribute public <gregc>
	
	Revision 1.81  2004/12/10 19:14:28  timmon
	Added declaration of canUpdateMovieFile method. Radar 3859997 and 3869861.
	
	Revision 1.80  2004/11/19 22:44:10  timmon
	Add NSError parameters to all class and instance initializers. Radar 3860605. <asonone>
	
	Revision 1.79  2004/11/10 19:39:30  timmon
	Added _resourceID instance variable, which will be used to address Radar 3869861, 3859997, and 3871336. <ec>
	
	Revision 1.78  2004/10/21 00:17:02  timmon
	Added comment on meaning of return value for movie:linkToURL delegate method.
	
	Revision 1.77  2004/10/15 16:24:43  timmon
	Changed comment on QTMovieSizeDidChangeNotification declaration from "natural size" to "movie size". <cad>
	
	Revision 1.76  2004/09/21 22:04:08  timmon
	Added _draggable instance variable. Radar 3742451.
	
	Revision 1.75  2004/09/20 23:40:35  timmon
	Update attribute method calls to new APIs. Radar 3798482.
	
	Revision 1.74  2004/09/15 23:17:14  timmon
	Added instance variables for undo-related methods. Radar 37780004.
	
	Revision 1.73  2004/08/31 22:23:50  thaiwey
	Add delegate for handling idle event. <timmon>
	
	Revision 1.72  2004/08/30 18:19:19  timmon
	Added declarations of movieWithAttributes and initWithAttributes, as well as new attributes associated with those methods. Radar 3760825.
	
	Revision 1.71  2004/08/30 17:51:15  timmon
	Moved declarations of QTMovieExportManufacturer, QTAddImageCodecType, and QTAddImageCodecQuality into public header file. Fixes Radar 3746378.
	
	Revision 1.70  2004/08/17 01:28:51  timmon
	Add _delegatePostNetworkDiagnosticUI instance variable.
	
	Revision 1.69  2004/08/13 21:08:15  timmon
	Added _pendingAttributes instance variable.
	
	Revision 1.68  2004/08/12 16:20:01  timmon
	Moved declaration of movie:shouldChangeController: delegate method to QTMovie_Private.h, since it's not a public method.
	
	Revision 1.67  2004/08/10 17:19:07  timmon
	Added declaration of movie:shouldChangeController: delegate method, which is part of the resolution of 3741472 and 3719154.
	
	Revision 1.66  2004/07/28 21:21:38  abaerlocher
	Add (old) equalizer support (radar 3690470).
	
	Revision 1.65  2004/07/27 20:59:06  timmon
	Added addImage declaration from private header. Radar 3726876.
	
	Revision 1.64  2004/07/27 20:16:33  timmon
	Moved QTMovieUneditableException from private header file. Radar 3726889.
	
	Revision 1.63  2004/07/16 03:25:34  timmon
	Added looping state change notification. Added delegate method wrapping movie progress procedure.
	
	Revision 1.62  2004/06/12 20:15:54  timmon
	Changed AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER to AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER. Radar 3691363. <jsam>
	
	Revision 1.61  2004/06/10 16:14:03  timmon
	Added instance variables to support improved asynchronous movie loading. Radar 3684824. <jkc>
	
	Revision 1.60  2004/06/05 17:03:31  timmon
	Added availability macros.
	
	Revision 1.59  2004/06/03 20:52:21  timmon
	Add declaration of insertSegmentOfMovie:fromRange:scaledToRange.
	
	Revision 1.58  2004/05/24 15:31:31  timmon
	Added QTMovieExportSettings key for writeToFile.
	
	Revision 1.57  2004/05/20 22:34:38  timmon
	Changed copyright date to 2004.
	
	Revision 1.56  2004/05/19 17:15:51  timmon
	Added app message notifications and declaration of movieFileTypes.
	
	Revision 1.55  2004/05/18 20:53:57  timmon
	Change copyright symbol to "(c)".
	
	Revision 1.54  2004/05/17 20:38:14  timmon
	Added disposeWhenDone parameter to movieWithQuickTimeMovie and initWithQuickTimeMovie methods.
	
	Revision 1.53  2004/05/10 16:26:36  timmon
	Added declaration of updateMovieFile, which is now public.
	
	Revision 1.52  2004/05/07 16:42:04  timmon
	Moved setMovieAttribute and setMovieAttributes from QTMovie_Private.h.
	
	Revision 1.51  2004/04/22 17:25:19  abaerlocher
	Add chapter did change notification.
	
	Revision 1.50  2004/04/08 19:53:03  timmon
	Tweaked notification handling.
	
	Revision 1.49  2004/03/29 19:39:55  abaerlocher
	Added QTMovieDidEndNotification.
	
	Revision 1.48  2004/03/23 23:03:38  abaerlocher
	Add delegate support.
	
	Revision 1.47  2004/03/11 00:46:58  timmon
	Make canInitWithDataReference, movieWithDataReference, and initWithDataReference public.
	
	Revision 1.46  2004/03/05 19:13:09  bwright
	Make QTMoviePasteboardType public.
	
	Revision 1.45  2004/03/04 00:52:33  timmon
	Removed description declaration; updated a number of method names and parameters as per recent review comments.
	
	Revision 1.44  2004/02/12 23:07:22  timmon
	Added movieNamed: declaration.
	
	Revision 1.43  2004/02/11 23:05:54  timmon
	Added parameter for QTMovieRateDidChangeNotification notification.
	
	Revision 1.42  2004/02/10 03:02:43  asonone
	track delete undo support
	
	Revision 1.41  2004/02/09 21:34:16  timmon
	Removed QTMutableMovie.
	
	Revision 1.40  2004/02/09 18:21:12  timmon
	Added declaration for description method.
	
	Revision 1.39  2004/01/31 01:42:33  asonone
	QTMovieChapterListDidChangeNotification, mcActionChapterListChanged, and chapterList bug fix
	
	Revision 1.38  2004/01/14 00:54:46  abaerlocher
	New notification parameters.
	
	Revision 1.37  2004/01/05 19:26:17  asonone
	QTTimeRange changes
	
	Revision 1.36  2004/01/05 18:09:08  abaerlocher
	Replace trackEnumerator method with tracks.
	
	Revision 1.35  2003/12/19 19:37:41  abaerlocher
	Replace QTMovie with id everywhere.
	
	Revision 1.34  2003/12/17 18:23:30  abaerlocher
	Update the notification parameter comments.
	
	Revision 1.33  2003/12/09 23:25:03  abaerlocher
	Add editable movie attribute.
	
	Revision 1.32  2003/12/08 22:06:55  abaerlocher
	Import QTTimeRange.
	
	Revision 1.31  2003/12/04 21:49:43  abaerlocher
	Latest notification changes.
	
	Revision 1.30  2003/12/04 19:29:57  abaerlocher
	Add some more attributes.
	
	Revision 1.29  2003/12/02 21:35:12  abaerlocher
	Add movieControllerObjectToken, make movieWithMovie: class method an instance method.
	
	Revision 1.28  2003/11/14 19:25:10  asonone
	QTRange to QTTimeRange changes
	
	Revision 1.27  2003/11/13 00:11:14  abaerlocher
	Latest changes.
	
	Revision 1.26  2003/10/29 00:02:34  asonone
	move out dataRefrence stuff to private headers
	
	Revision 1.25  2003/10/21 21:48:57  asonone
	change QTTime class to C struct
	
	Revision 1.24  2003/10/17 21:30:04  abaerlocher
	Make QTDataReference support private.
	
	Revision 1.23  2003/09/19 22:49:45  cad
	Internal/private headers
	
	Revision 1.22  2003/09/19 21:02:15  asonone
	change quickTime* to QuickTime*
	
	Revision 1.21  2003/09/17 16:56:28  asonone
	Quicktime/QuickTime.h => QuickTime/QuickTime.h
	
	Revision 1.20  2003/09/16 23:14:16  asonone
	Enumerator classes are not public, methods now return NSEnumerators
	
	Revision 1.19  2003/09/15 23:57:58  asonone
	revert to previous revision
	
	Revision 1.17  2003/09/12 21:10:41  cad
	Moved is/setEditable to movieview, as it is a function of the UI
	
	Revision 1.16  2003/09/12 01:19:04  asonone
	trackEnumeratorForType implemented
	
	Revision 1.15  2003/09/12 00:30:21  cad
	objectToken is public.
	
	Revision 1.14  2003/09/11 22:22:17  cad
	QTObject base class no longer exists.
	
	Revision 1.13  2003/09/04 18:46:01  abaerlocher
	Move some categories to QTMovie_Private and QTMutableMovie/QTMovieController.
	
	Revision 1.12  2003/09/03 22:46:56  abaerlocher
	Add some reserved fields and use extern NSStrings.
	
	Revision 1.11  2003/08/06 20:18:13  jkc
	Move some time-related methods to inspection category
	
	Revision 1.10  2003/08/03 22:02:39  jkc
	url -> URL, to match the AppKit convention
	
	Revision 1.9  2003/08/03 21:42:49  jkc
	Make QTObjectMgr stuff private; more consistency in naming
	
	Revision 1.8  2003/08/03 19:22:33  jkc
	Categorize QTMovie methods; some name changes too.
	
	Revision 1.7  2003/06/03 00:11:08  abaerlocher
	Update apis.
	
	Revision 1.6  2003/05/29 22:51:22  abaerlocher
	Add canInitWithFile:, canInitWithURL:, canInitWithDataReference:.
	
	Revision 1.5  2003/05/22 16:31:09  abaerlocher
	Add gotoNextSelectionPoint and gotoPreviousSelectionPoint methods.
	
	Revision 1.4  2003/05/14 00:12:33  abaerlocher
	Add movieWithPasteboard: and initWithPasteboard:.
	
	Revision 1.3  2003/05/13 00:17:37  abaerlocher
	Reintroduce track support, imageAtTime:/posterFrameImage, and data reference calls.
	
	Revision 1.2  2003/05/08 17:37:23  abaerlocher
	Add initWithData and editable getter/setter.
	
	Revision 1.1  2003/04/30 16:27:31  abaerlocher
	First checked in.
	
*/

#ifndef QTMOVIE_H
#define QTMOVIE_H

#import <Cocoa/Cocoa.h>

#if !__LP64__
	#import <QuickTime/QuickTime.h>
#endif

#import <QTKit/QTKitDefines.h>
#import <QTKit/QTTime.h>
#import <QTKit/QTTimeRange.h>

@class QTMovie;
@class QTTrack;
@class QTDataReference;
@class QTMovieMediaHelper;

	// pasteboard support
QTKIT_EXTERN NSString * const QTMoviePasteboardType							AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

	// notifications                                                                                                    description									parameter			parameter type
QTKIT_EXTERN NSString * const QTMovieEditabilityDidChangeNotification		AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;	// change in movie editability				-					-
QTKIT_EXTERN NSString * const QTMovieEditedNotification						AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;	// edit was done to the movie				-					-
QTKIT_EXTERN NSString * const QTMovieLoadStateDidChangeNotification			AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;	// change in movie load state				-					-
QTKIT_EXTERN NSString * const QTMovieLoopModeDidChangeNotification			AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;	// change in movie looping mode				-					-
QTKIT_EXTERN NSString * const QTMovieMessageStringPostedNotification		AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;	// message string							message				NSString
QTKIT_EXTERN NSString * const QTMovieRateDidChangeNotification				AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;	// change in movie rate						rate				NSNumber (float)
QTKIT_EXTERN NSString * const QTMovieSelectionDidChangeNotification			AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;	// change in selection start/duration		-					-
QTKIT_EXTERN NSString * const QTMovieSizeDidChangeNotification				AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;	// change in movie size						-					-
QTKIT_EXTERN NSString * const QTMovieStatusStringPostedNotification			AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;	// status string							status				NSString
QTKIT_EXTERN NSString * const QTMovieTimeDidChangeNotification				AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;	// goto time occured						-					-
QTKIT_EXTERN NSString * const QTMovieVolumeDidChangeNotification			AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;	// change in volume							-					-
QTKIT_EXTERN NSString * const QTMovieDidEndNotification						AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;	// movie ended								-					-
QTKIT_EXTERN NSString * const QTMovieChapterDidChangeNotification			AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;	// change in current chapter				-					-
QTKIT_EXTERN NSString * const QTMovieChapterListDidChangeNotification		AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;	// change in chapter list					-					-
QTKIT_EXTERN NSString * const QTMovieEnterFullScreenRequestNotification		AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;	// full screen playback requested			-					-
QTKIT_EXTERN NSString * const QTMovieExitFullScreenRequestNotification		AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;	// normal windowed playback requested		-					-
QTKIT_EXTERN NSString * const QTMovieCloseWindowRequestNotification			AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;	// window close requested					-					-
QTKIT_EXTERN NSString * const QTMovieApertureModeDidChangeNotification		AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;	// change in visual aperture mode			-					-

	// notification parameters
QTKIT_EXTERN NSString * const QTMovieMessageNotificationParameter			AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
QTKIT_EXTERN NSString * const QTMovieRateDidChangeNotificationParameter		AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
QTKIT_EXTERN NSString * const QTMovieStatusFlagsNotificationParameter		AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
QTKIT_EXTERN NSString * const QTMovieStatusCodeNotificationParameter		AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
QTKIT_EXTERN NSString * const QTMovieStatusStringNotificationParameter		AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

QTKIT_EXTERN NSString * const QTMovieTargetIDNotificationParameter			AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
QTKIT_EXTERN NSString * const QTMovieTargetNameNotificationParameter		AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

	// writeToFile: attributes dictionary keys
QTKIT_EXTERN NSString * const QTMovieExport									AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;	// NSNumber (BOOL)
QTKIT_EXTERN NSString * const QTMovieExportType								AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;	// NSNumber (long)
QTKIT_EXTERN NSString * const QTMovieFlatten								AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;	// NSNumber (BOOL)
QTKIT_EXTERN NSString * const QTMovieExportSettings							AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;	// NSData (QTAtomContainer)
QTKIT_EXTERN NSString * const QTMovieExportManufacturer						AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;	// NSNumber (long)

	// addImage: attributes dictionary keys
QTKIT_EXTERN NSString * const QTAddImageCodecType							AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;	// NSString
QTKIT_EXTERN NSString * const QTAddImageCodecQuality						AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;	// NSNumber

	// data locators for movieWithAttributes/initWithAttributes
QTKIT_EXTERN NSString * const QTMovieDataReferenceAttribute					AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;	// QTDataReference
QTKIT_EXTERN NSString * const QTMoviePasteboardAttribute					AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;	// NSPasteboard
QTKIT_EXTERN NSString * const QTMovieDataAttribute							AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;	// NSData

	// movie instantiation options for movieWithAttributes/initWithAttributes
QTKIT_EXTERN NSString * const QTMovieFileOffsetAttribute					AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;	// NSNumber (long long)
QTKIT_EXTERN NSString * const QTMovieResolveDataRefsAttribute				AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;	// NSNumber (BOOL)
QTKIT_EXTERN NSString * const QTMovieAskUnresolvedDataRefsAttribute			AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;	// NSNumber (BOOL)
QTKIT_EXTERN NSString * const QTMovieOpenAsyncOKAttribute					AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;	// NSNumber (BOOL)
QTKIT_EXTERN NSString * const QTMovieDontInteractWithUserAttribute			AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;	// NSNumber (BOOL)

	// movie instantiation options for movieWithAttributes/initWithAttributes
QTKIT_EXTERN NSString * const QTMovieFileOffsetAttribute					AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;	// NSNumber (long long)

/*!
	@constant		QTMovieResolveDataRefsAttribute
	@abstract		Indicates whether external data references in a movie file should be resolved (NSNumber YES) or not resolved (NSNumber NO).
	@discussion		A movie file can contain references to media data in other locations. By default, QTMovie attempts to resolve these references
					at the time that the movie file is opened and a QTMovie object is instantiated. You can prevent that resolution from occurring 
					by passing an NSNumber wrapping the value NO as the value of this attribute.
 */
QTKIT_EXTERN NSString * const QTMovieResolveDataRefsAttribute				AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;	// NSNumber (BOOL) (default = YES)

/*!
	@constant		QTMovieAskUnresolvedDataRefsAttribute
	@abstract		Indicates whether the user should be prompted to help find any unresolved data references (NSNumber YES) or not (NSNumber NO).
	@discussion		When the value of the QTMovieResolveDataRefsAttribute attribute is an NSNumber wrapping the value YES and a movie file contains 
					unresolved data references, this attribute indicates whether the user should be prompted to help find the missing referenced data
					(NSNumber YES) or not (NSNumber NO). Typically QTMovie will display a dialog box that allows the user to navigate to the file or URL
					containing the referenced data. By setting this attribute to NO, you can prevent that dialog box from being displayed and thereby
					speed up the movie opening and initialization process.
 */
QTKIT_EXTERN NSString * const QTMovieAskUnresolvedDataRefsAttribute			AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;	// NSNumber (BOOL) (default = YES)

/*!
	@constant		QTMovieOpenAsyncOKAttribute
	@abstract		Indicates whether a movie file can be opened asynchronously if possible (NSNumber NO) or not (NSNumber YES).
	@discussion		Opening a movie file and initializing a QTMovie object for that file may require a considerable amount of time, perhaps to
					convert the data in the file from one format to another. By setting this attribute to an NSNumber wrapping the value YES, you
					grant QTMovie permission to return a non-nil QTMovie identifier to your application immediately and then to continue processing the
					file data internally. If a movie is opened asynchronously, you must monitor the movie load state and ensure that it has reached the
					appropriate threshold before attempting to perform certain operations on the movie. For instance, you cannot export or copy 
					a QTMovie object until its load state has reached QTMovieLoadStateComplete. 
 */
QTKIT_EXTERN NSString * const QTMovieOpenAsyncOKAttribute					AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;	// NSNumber (BOOL) (default = YES)

/*!
	@constant		QTMovieOpenAsyncRequiredAttribute
	@abstract		Indicates whether the QTMovie must be opened asynchronously (NSNumber YES) or not (NSNumber NO).
	@discussion		Set this attribute to an NSNumber wrapping YES to indicate that all operations necessary to open the movie file (or other container)
					and create a valid QTMovie object must occur asynchronously. That is to say, the methods +movieWithAttributes:error:
					and -initWithAttributes:error: must return almost immediately, performing any lengthy operations on another thread. Your application
					can monitor the movie load state to determine the progress of those operations. 
					
					If you require asynchronous opening but QTMovie is unable to honor your request, then the methods +movieWithAttributes:error:
					and -initWithAttributes:error: return nil with an NSError having the error domain QTKitErrorDomain and code QTErrorMovieOpeningCannotBeAsynchronous. 
 */
QTKIT_EXTERN NSString * const QTMovieOpenAsyncRequiredAttribute				AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;	// NSNumber (BOOL) (default = NO)

/*!
	@constant		QTMovieOpenForPlaybackAttribute
	@abstract		Indicates whether the QTMovie will be used only for playback (NSNumber YES) or not (NSNumber NO).
	@discussion		Set this attribute to an NSNumber wrapping YES to indicate that you intend to use movie playback methods (such as -play or -stop, 
					or corresponding movie view methods such as -play: or -pause:) to control the movie, but do not intend to use other methods that edit,
					export, or in any way modify the movie. Knowing that you need playback services only may allow QTMovie to use more efficient code paths
					for some media files.
 */
QTKIT_EXTERN NSString * const QTMovieOpenForPlaybackAttribute				AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;	// NSNumber (BOOL) (default = NO)

// movie attributes
QTKIT_EXTERN NSString * const QTMovieApertureModeAttribute					AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;	// NSString
QTKIT_EXTERN NSString * const QTMovieActiveSegmentAttribute					AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;
QTKIT_EXTERN NSString * const QTMovieAutoAlternatesAttribute				AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;	// NSNumber (BOOL)
QTKIT_EXTERN NSString * const QTMovieCopyrightAttribute						AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;	// NSString
QTKIT_EXTERN NSString * const QTMovieCreationTimeAttribute					AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;	// NSDate
QTKIT_EXTERN NSString * const QTMovieCurrentSizeAttribute					AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;	// NSValue (NSSize)
QTKIT_EXTERN NSString * const QTMovieCurrentTimeAttribute					AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;	// NSValue (QTTime)
QTKIT_EXTERN NSString * const QTMovieDataSizeAttribute						AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;	// NSNumber (long long)
QTKIT_EXTERN NSString * const QTMovieDelegateAttribute						AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;	// NSObject
QTKIT_EXTERN NSString * const QTMovieDisplayNameAttribute					AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;	// NSString
QTKIT_EXTERN NSString * const QTMovieDurationAttribute						AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;	// NSValue (QTTime)
QTKIT_EXTERN NSString * const QTMovieEditableAttribute						AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;	// NSNumber (BOOL)
QTKIT_EXTERN NSString * const QTMovieFileNameAttribute						AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;	// NSString
QTKIT_EXTERN NSString * const QTMovieHasApertureModeDimensionsAttribute		AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;	// NSNumber (BOOL)
QTKIT_EXTERN NSString * const QTMovieHasAudioAttribute						AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;	// NSNumber (BOOL)
QTKIT_EXTERN NSString * const QTMovieHasDurationAttribute					AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;	// NSNumber (BOOL)
QTKIT_EXTERN NSString * const QTMovieHasVideoAttribute						AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;	// NSNumber (BOOL)
QTKIT_EXTERN NSString * const QTMovieIsActiveAttribute						AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;	// NSNumber (BOOL)
QTKIT_EXTERN NSString * const QTMovieIsInteractiveAttribute					AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;	// NSNumber (BOOL)
QTKIT_EXTERN NSString * const QTMovieIsLinearAttribute						AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;	// NSNumber (BOOL)
QTKIT_EXTERN NSString * const QTMovieIsSteppableAttribute					AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;	// NSNumber (BOOL)
QTKIT_EXTERN NSString * const QTMovieLoadStateAttribute						AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;	// NSNumber (long)
QTKIT_EXTERN NSString * const QTMovieLoopsAttribute							AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;	// NSNumber (BOOL)
QTKIT_EXTERN NSString * const QTMovieLoopsBackAndForthAttribute				AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;	// NSNumber (BOOL)
QTKIT_EXTERN NSString * const QTMovieModificationTimeAttribute				AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;	// NSDate
QTKIT_EXTERN NSString * const QTMovieMutedAttribute							AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;	// NSNumber (BOOL)
QTKIT_EXTERN NSString * const QTMovieNaturalSizeAttribute					AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;	// NSValue (NSSize)
QTKIT_EXTERN NSString * const QTMoviePlaysAllFramesAttribute				AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;	// NSNumber (BOOL)
QTKIT_EXTERN NSString * const QTMoviePlaysSelectionOnlyAttribute			AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;	// NSNumber (BOOL)
QTKIT_EXTERN NSString * const QTMoviePosterTimeAttribute					AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;	// NSValue (QTTime)
QTKIT_EXTERN NSString * const QTMoviePreferredMutedAttribute				AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;	// NSNumber (BOOL)
QTKIT_EXTERN NSString * const QTMoviePreferredRateAttribute					AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;	// NSNumber (float)
QTKIT_EXTERN NSString * const QTMoviePreferredVolumeAttribute				AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;	// NSNumber (float)
QTKIT_EXTERN NSString * const QTMoviePreviewModeAttribute					AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;	// NSNumber (BOOL)
QTKIT_EXTERN NSString * const QTMoviePreviewRangeAttribute					AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;	// NSValue (QTTimeRange)
QTKIT_EXTERN NSString * const QTMovieRateAttribute							AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;	// NSNumber (float)
QTKIT_EXTERN NSString * const QTMovieSelectionAttribute						AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;	// NSValue (QTTimeRange)
QTKIT_EXTERN NSString * const QTMovieTimeScaleAttribute						AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;	// NSNumber (long)
QTKIT_EXTERN NSString * const QTMovieURLAttribute							AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;	// NSURL
QTKIT_EXTERN NSString * const QTMovieVolumeAttribute						AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;	// NSNumber (float)
QTKIT_EXTERN NSString * const QTMovieRateChangesPreservePitchAttribute		AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;	// NSNumber (BOOL)

	// aperture modes
QTKIT_EXTERN NSString * const QTMovieApertureModeClassic					AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
QTKIT_EXTERN NSString * const QTMovieApertureModeClean						AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
QTKIT_EXTERN NSString * const QTMovieApertureModeProduction					AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
QTKIT_EXTERN NSString * const QTMovieApertureModeEncodedPixels				AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

	// movie frame image options for frameImageAtTime:withAttributes:error:
QTKIT_EXTERN NSString * const QTMovieFrameImageSize							AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;	// NSValue (NSSize)
QTKIT_EXTERN NSString * const QTMovieFrameImageType							AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;	// NSString
QTKIT_EXTERN NSString * const QTMovieFrameImageTypeNSImage					AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
QTKIT_EXTERN NSString * const QTMovieFrameImageTypeCGImageRef				AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
QTKIT_EXTERN NSString * const QTMovieFrameImageTypeCIImage					AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
QTKIT_EXTERN NSString * const QTMovieFrameImageTypeCVPixelBufferRef			AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
QTKIT_EXTERN NSString * const QTMovieFrameImageTypeCVOpenGLTextureRef		AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
QTKIT_EXTERN NSString * const QTMovieFrameImageOpenGLContext				AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;	// NSValue (CGLContextObj)
QTKIT_EXTERN NSString * const QTMovieFrameImagePixelFormat					AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;	// NSValue (CGLPixelFormatObj)
QTKIT_EXTERN NSString * const QTMovieFrameImageRepresentationsType			AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;	// NSArray of NSString; strings are, e.g., NSBitmapImageRep
QTKIT_EXTERN NSString * const QTMovieFrameImageDeinterlaceFields			AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;	// NSNumber (BOOL) (default = YES)
QTKIT_EXTERN NSString * const QTMovieFrameImageHighQuality					AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;	// NSNumber (BOOL) (default = YES)
QTKIT_EXTERN NSString * const QTMovieFrameImageSingleField					AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;	// NSNumber (BOOL) (default = YES)

/*!
 @constant		QTMovieFrameImageSessionMode
 @abstract		Indicates that two or more calls to frameImageAtTime:withAttributes:error: will be made on the same QTMovie object.
 @discussion	By adding this key with the associated value that is an NSNumber wrapping the BOOL YES to the dictionary of
				attributes, an application indicates that it will make more than one call to frameImageAtTime:withAttributes:error: on
				the same QTMovie object. This knowledge permits QTMovie to cache certain objects and data structures used to generate
				a frame image, thereby improving performance. When the caller has obtained all the frame images desired from a
				given QTMovie object, the caller should follow those session calls with a call where this value is NO; this is
				a signal to QTMovie to dispose of that cached data.
 */
QTKIT_EXTERN NSString * const QTMovieFrameImageSessionMode					AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;	// NSNumber (BOOL) (default = NO)

	// exceptions
QTKIT_EXTERN NSString * const QTMovieUneditableException					AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

	// keys for dictionaries in -chapters array
QTKIT_EXTERN NSString * const QTMovieChapterName							AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;	// NSString
QTKIT_EXTERN NSString * const QTMovieChapterStartTime						AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;	// NSValue (QTTime)

	// keys for attributes dictionary in -addChapters
QTKIT_EXTERN NSString * const QTMovieChapterTargetTrackAttribute			AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;	// QTTrack

// constants for movieFileTypes method
typedef enum {
	QTIncludeStillImageTypes			= 1 << 0,
	QTIncludeTranslatableTypes			= 1 << 1,
	QTIncludeAggressiveTypes			= 1 << 2,
#if QTKIT_VERSION_MAX_ALLOWED >= QTKIT_VERSION_7_2
	QTIncludeDynamicTypes				= 1 << 3,
#endif
	QTIncludeCommonTypes				= 0,
	QTIncludeAllTypes					= 0xffff
} QTMovieFileTypeOptions;

// constants for movieShouldContinueOp delegate method
typedef enum {
#if __LP64__
	QTMovieOperationBeginPhase			= 0,
	QTMovieOperationUpdatePercentPhase  = 1,
	QTMovieOperationEndPhase			= 2
#else
	QTMovieOperationBeginPhase			= movieProgressOpen,
	QTMovieOperationUpdatePercentPhase  = movieProgressUpdatePercent,
	QTMovieOperationEndPhase			= movieProgressClose
#endif
} QTMovieOperationPhase;

// constants for QTMovieLoadStateAttribute
#if QTKIT_VERSION_MAX_ALLOWED >= QTKIT_VERSION_7_2
enum {
	QTMovieLoadStateError				= -1L,			// an error occurred while loading the movie
	QTMovieLoadStateLoading				= 1000,			// the movie is loading
	QTMovieLoadStateLoaded				= 2000,			// the movie atom has loaded; it's safe to query movie properties
	QTMovieLoadStatePlayable			= 10000,		// the movie has loaded enough media data to begin playing
	QTMovieLoadStatePlaythroughOK		= 20000,		// the movie has loaded enough media data to play through to the end
	QTMovieLoadStateComplete			= 100000L		// the movie has loaded completely
};
typedef NSInteger QTMovieLoadState;
#endif

@interface NSObject (QTMovie_Delegate)
	- (BOOL)movie:(QTMovie *)movie linkToURL:(NSURL *)url;			// return YES if delegate handled link-to-URL request
	- (BOOL)movieShouldLoadData:(id)sender;
	- (BOOL)movieShouldTask:(id)movie;
	- (QTMovie *)externalMovie:(NSDictionary *)dictionary;
	- (BOOL)movie:(QTMovie *)movie shouldContinueOperation:(NSString *)op withPhase:(QTMovieOperationPhase)phase atPercent:(NSNumber *)percent withAttributes:(NSDictionary *)attributes;
@end

@interface QTMovie : NSObject <NSCoding, NSCopying>
{
@private
#if __LP64__
	int32_t					_proxy;
	int32_t					_delegateProxy;
#else
	Movie					_movie;
	MovieController			_movieController;
#endif
	id						_dataReference;
	void *					_objectToken;
	void *					_movieControllerObjectToken;
	long					_reserved1;
	long					_reserved2;
	long					_reserved3;
	QTMovieMediaHelper *	_mediaHelper;
	long					_flags;
#if !__LP64__
	MovieEditState			_editState;
#endif
	NSUndoManager *			_undoManager;
	NSDictionary *			_undoAttributes;
	id						_delegate;
	NSDate *				_lastCheckDate;
	NSDictionary *			_pendingAttributes;
	SInt16					_resourceID;
	long					_seed;
}

- (QTTime)duration;

@end

@interface QTMovie (QTMovie_Initialization)

+ (BOOL)canInitWithPasteboard:(NSPasteboard *)pasteboard;
+ (BOOL)canInitWithFile:(NSString *)fileName;
+ (BOOL)canInitWithURL:(NSURL *)url;
+ (BOOL)canInitWithDataReference:(QTDataReference *)dataReference;

+ (NSArray *)movieFileTypes:(QTMovieFileTypeOptions)types;
+ (NSArray *)movieUnfilteredFileTypes;
+ (NSArray *)movieUnfilteredPasteboardTypes;
#if QTKIT_VERSION_MAX_ALLOWED >= QTKIT_VERSION_7_2
+ (NSArray *)movieTypesWithOptions:(QTMovieFileTypeOptions)types;
#endif

+ (id)movie;
+ (id)movieWithFile:(NSString *)fileName error:(NSError **)errorPtr;
+ (id)movieWithURL:(NSURL *)url error:(NSError **)errorPtr;
+ (id)movieWithDataReference:(QTDataReference *)dataReference error:(NSError **)errorPtr;
+ (id)movieWithPasteboard:(NSPasteboard *)pasteboard error:(NSError **)errorPtr;
+ (id)movieWithData:(NSData *)data error:(NSError **)errorPtr;
#if !__LP64__
+ (id)movieWithQuickTimeMovie:(Movie)movie disposeWhenDone:(BOOL)dispose error:(NSError **)errorPtr;
#endif
+ (id)movieWithAttributes:(NSDictionary *)attributes error:(NSError **)errorPtr;
+ (id)movieNamed:(NSString *)name error:(NSError **)errorPtr;

- (id)initWithFile:(NSString *)fileName error:(NSError **)errorPtr;
- (id)initWithURL:(NSURL *)url error:(NSError **)errorPtr;
- (id)initWithDataReference:(QTDataReference *)dataReference error:(NSError **)errorPtr;
- (id)initWithPasteboard:(NSPasteboard *)pasteboard error:(NSError **)errorPtr;
- (id)initWithData:(NSData *)data error:(NSError **)errorPtr;
- (id)initWithMovie:(QTMovie *)movie timeRange:(QTTimeRange)range error:(NSError **)errorPtr;
#if !__LP64__
- (id)initWithQuickTimeMovie:(Movie)movie disposeWhenDone:(BOOL)dispose error:(NSError **)errorPtr;
#endif
- (id)initWithAttributes:(NSDictionary *)attributes error:(NSError **)errorPtr;

- (id)movieWithTimeRange:(QTTimeRange)range error:(NSError **)errorPtr;

#if QTKIT_VERSION_MAX_ALLOWED >= QTKIT_VERSION_7_2
- (id)initToWritableFile:(NSString *)filename error:(NSError **)errorPtr;
- (id)initToWritableData:(NSMutableData *)data error:(NSError **)errorPtr;
- (id)initToWritableDataReference:(QTDataReference *)dataReference error:(NSError **)errorPtr;

- (void)invalidate;
#endif

#if QTKIT_VERSION_MAX_ALLOWED >= QTKIT_VERSION_7_5_7
/*!
	@method			cancelLoading
	@abstract		Attempt to cancel the loading of a QTMovie object.
	@result			YES if the loading of the receiver was successfully stopped or if the loading of the receiver has already completed; it returns NO if the loading could not be cancelled.
	@discussion		If the receiver was not initialized with QTMovieOpenAsyncRequiredAttribute set to YES,
					then this method is a no-op that returns NO.
*/
- (BOOL)cancelLoading;
#endif

@end

@interface QTMovie (QTMovie_Inspection)

- (QTTime)currentTime;
- (float)rate;
- (float)volume;
- (BOOL)muted;

	// attributes
- (NSDictionary *)movieAttributes;
- (void)setMovieAttributes:(NSDictionary *)attributes;

- (id)attributeForKey:(NSString *)attributeKey;
- (void)setAttribute:(id)value forKey:(NSString *)attributeKey;

- (NSArray *)tracks;
- (NSArray *)tracksOfMediaType:(NSString *)type;

@end

@interface QTMovie (QTMovie_Image)

- (NSImage *)posterImage;
- (NSImage *)currentFrameImage;
- (NSImage *)frameImageAtTime:(QTTime)time;
#if QTKIT_VERSION_MAX_ALLOWED >= QTKIT_VERSION_7_2
- (void *)frameImageAtTime:(QTTime)time withAttributes:(NSDictionary *)attributes error:(NSError **)errorPtr;
#endif

@end

@interface QTMovie (QTMovie_Format)

- (NSData *)movieFormatRepresentation;
- (BOOL)writeToFile:(NSString *)fileName withAttributes:(NSDictionary *)attributes;
#if QTKIT_VERSION_MAX_ALLOWED >= QTKIT_VERSION_7_2
- (BOOL)writeToFile:(NSString *)fileName withAttributes:(NSDictionary *)attributes error:(NSError **)errorPtr;
#endif
- (BOOL)canUpdateMovieFile;
- (BOOL)updateMovieFile;

@end

@interface QTMovie (QTMovie_Time)

#if QTKIT_VERSION_MAX_ALLOWED >= QTKIT_VERSION_7_2
- (void)autoplay;
#endif
- (void)play;
- (void)stop;

- (void)setCurrentTime:(QTTime)time;

- (void)gotoBeginning;
- (void)gotoEnd;
- (void)gotoNextSelectionPoint;
- (void)gotoPreviousSelectionPoint;
- (void)gotoPosterTime;
- (void)stepForward;
- (void)stepBackward;

@end

#if QTKIT_VERSION_MAX_ALLOWED >= QTKIT_VERSION_7_5_7
@interface QTMovie (QTMovie_Stepping)

- (QTTime)frameStartTime:(QTTime)atTime;
- (QTTime)frameEndTime:(QTTime)atTime;
- (QTTime)keyframeStartTime:(QTTime)atTime;

@end
#endif

@interface QTMovie (QTMovie_PlaybackControl)

- (void)setRate:(float)rate;
- (void)setVolume:(float)volume;
- (void)setMuted:(BOOL)mute;

@end

@interface QTMovie (QTMovie_Selection)

- (void)setSelection:(QTTimeRange)selection;
- (QTTime)selectionStart;
- (QTTime)selectionEnd;
- (QTTime)selectionDuration;

@end

@interface QTMovie (QTMovie_Editing)

- (void)replaceSelectionWithSelectionFromMovie:(id)movie;
- (void)appendSelectionFromMovie:(id)movie;

- (void)insertSegmentOfMovie:(QTMovie *)movie timeRange:(QTTimeRange)range atTime:(QTTime)time;
- (void)insertSegmentOfMovie:(QTMovie *)movie fromRange:(QTTimeRange)srcRange scaledToRange:(QTTimeRange)dstRange;
- (void)insertEmptySegmentAt:(QTTimeRange)range;
- (void)deleteSegment:(QTTimeRange)segment;
- (void)scaleSegment:(QTTimeRange)segment newDuration:(QTTime)newDuration;

- (void)addImage:(NSImage *)image forDuration:(QTTime)duration withAttributes:(NSDictionary *)attributes;

#if QTKIT_VERSION_MAX_ALLOWED >= QTKIT_VERSION_7_2
- (QTTrack *)insertSegmentOfTrack:(QTTrack *)track timeRange:(QTTimeRange)range atTime:(QTTime)time;
- (QTTrack *)insertSegmentOfTrack:(QTTrack *)track fromRange:(QTTimeRange)srcRange scaledToRange:(QTTimeRange)dstRange;
- (void)removeTrack:(QTTrack *)track;
#endif

@end

@interface QTMovie (QTMovie_Delegate)

- (id)delegate;
- (void)setDelegate:(id)delegate;

@end

#if !__LP64__
@interface QTMovie (QTMovie_Primitives)

- (Movie)quickTimeMovie;
- (MovieController)quickTimeMovieController;

@end
#endif

@interface QTMovie (QTMovie_VisualSupport)

#if QTKIT_VERSION_MAX_ALLOWED >= QTKIT_VERSION_7_2
- (void)generateApertureModeDimensions;
- (void)removeApertureModeDimensions;
#endif

@end

@interface QTMovie (QTMovie_VisualContext)

#if QTKIT_VERSION_MAX_ALLOWED >= QTKIT_VERSION_7_2
#if !__LP64__
- (void)setVisualContext:(QTVisualContextRef)visualContext;
- (QTVisualContextRef)visualContext;
#endif
#endif

@end

@interface QTMovie (QTMovie_Threading)

#if QTKIT_VERSION_MAX_ALLOWED >= QTKIT_VERSION_7_2
+ (void)enterQTKitOnThread;
+ (void)enterQTKitOnThreadDisablingThreadSafetyProtection;
+ (void)exitQTKitOnThread;
- (BOOL)attachToCurrentThread;
- (BOOL)detachFromCurrentThread;

- (void)setIdling:(BOOL)state;
- (BOOL)isIdling;
#endif

@end

@interface QTMovie (QTMovie_Chapters)

#if QTKIT_VERSION_MAX_ALLOWED >= QTKIT_VERSION_7_2
- (BOOL)hasChapters;
- (NSInteger)chapterCount;
- (NSArray *)chapters;
- (void)addChapters:(NSArray *)chapters withAttributes:(NSDictionary *)attributes error:(NSError **)errorPtr;
- (BOOL)removeChapters;
- (QTTime)startTimeOfChapter:(NSInteger)chapterIndex;		// 0-based index
- (NSInteger)chapterIndexForTime:(QTTime)time;				// 0-based index
#endif

@end

#endif	// QTMOVIE_H
