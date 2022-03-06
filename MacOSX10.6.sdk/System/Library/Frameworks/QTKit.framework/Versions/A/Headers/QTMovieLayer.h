/*
	File:		QTMovieLayer.h

	Copyright:	(c)2005-2007 by Apple Inc., all rights reserved.

	
	Revision 1.1.6.2.2.2.4.1  2008/01/10 23:46:21  cad
	Implement image consumer model.
	
	Revision 1.3  2008/01/18 02:18:24  ibarberi
	=== QT74GM => TopOfTree Merge ===
	
	Revision 1.1.6.2.2.2  2007/07/31 04:33:19  dunderwo
	[5364700] QTKit now has its own set of #if guard macros. <jsam, cad, timmon>
	
	Revision 1.1.6.2.2.1  2007/06/19 15:05:11  timmon
	Added comment that initWithMovie: is the designated initializer; part of fixing Radar 5248281.
	
	Revision 1.1.6.2  2007/04/26 00:44:15  duano
	=== Maguro deltas re-applied post QT716 GM rebase ===
	
	Revision 1.1.4.10  2007/03/29 23:30:13  dunderwo
	[5051048] Capture classes now all use _internal ivar. General header cleanup. <simon>
	
	Revision 1.1.4.9  2007/03/08 20:00:33  timmon
	Included QTKitDefines.h rather than QTKit.h; this solves the multiple definition error. Also, since QTKitDefines.h ensures that MAC_OS_X_VERSION_10_5 is defined, we can back out the previous change.
	
	Revision 1.1.4.8  2007/03/08 08:49:46  kudo
	Check if MAC_OS_X_VERSION_10_5 is defined first.
	
	Revision 1.1.4.7  2007/03/08 08:47:10  kudo
	Removed previous workaround now that the real cause of the build failures has been determined. If you see failures on Tiger, make sure you have the proper AvailabilityMacros.h (with no 10_5 stuff); fixes Radar 4943592.
	
	Revision 1.1.4.6  2007/03/06 15:41:41  timmon
	Added temporary workaround for Tiger build failures.
	
	Revision 1.1.4.5  2007/03/03 02:01:58  timmon
	Reenabled availability macros, so that this module builds only under Leopard and later; part of fixing Radar 4943592.
	
	Revision 1.1.4.4  2007/02/27 17:08:37  timmon
	Updated to latest CoreAnimation interfaces; fixes Radar 4921071.
	
	Revision 1.1.4.3  2007/02/01 19:26:14  timmon
	Changed return type of initializers to id; fixes Radar 4934654.
	
	Revision 1.1.4.2  2007/01/25 18:33:53  duano
	=== Maguro deltas re-applied post QT715 GM rebase ===
	
	Revision 1.1.2.5  2007/01/15 18:07:30  timmon
	A few minor tweaks: removed property; fixes Radar 4733201.
	
	Revision 1.1.2.4  2007/01/06 19:32:41  timmon
	Added #if QTKIT_ENABLE_LAYERKIT around entire class declaration.
	
	Revision 1.1.2.3  2007/01/06 03:11:13  timmon
	Changed ENABLE_LAYERKIT to 0 for the time being.
	
	Revision 1.1.2.2  2006/10/05 19:43:36  timmon
	Made QTMovieLayer inherit from NSObject; this is a temporary workaround for Radar 4766676.
	
	Revision 1.1.2.1  2006/09/29 17:00:26  timmon
	First check in, based on code from Frank Doepke.
	
	
*/

/* Note: do not attempt to directly modify the `contents' property of
 * an QTMovieLayer object - doing so will effectively turn it into a
 * regular CALayer. */


#import <Foundation/Foundation.h>
#import <QTKit/QTKitDefines.h>

#if (QTKIT_VERSION_MAX_ALLOWED >= QTKIT_VERSION_7_2) && (MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5)

#import <QuartzCore/QuartzCore.h>

@class QTMovie;

@interface QTMovieLayer : CALayer								// QTMovieLayer is a layer that renders a QTMovie within a layer hierarchy
{
@private
	struct QTMovieLayerPrivate *	_movieLayerPriv;
}

+ (id)layerWithMovie:(QTMovie *)movie;
- (id)initWithMovie:(QTMovie *)movie;							// the designated initializer

- (void)setMovie:(QTMovie *)movie;
- (QTMovie *)movie;

@end

#endif /* (QTKIT_VERSION_MAX_ALLOWED >= QTKIT_VERSION_7_2) && (MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5) */
