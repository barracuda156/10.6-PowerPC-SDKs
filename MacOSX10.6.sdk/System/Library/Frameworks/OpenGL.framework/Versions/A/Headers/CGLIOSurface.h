/*
	Copyright:  (c) 2008 by Apple Computer, Inc., all rights reserved.
*/

#ifndef _CGLIOSURFACE_H
#define _CGLIOSURFACE_H

#include <OpenGL/CGLTypes.h>
#include <IOSurface/IOSurface.h>
#include <OpenGL/gl.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
** API for IOSurface
*/
extern CGLError CGLTexImageIOSurface2D(CGLContextObj ctx, GLenum target, GLenum internal_format,
						GLsizei width, GLsizei height, GLenum format, GLenum type, IOSurfaceRef ioSurface, GLuint plane);

#ifdef __cplusplus
}
#endif

#endif /* _CGLSURFACE_H */

