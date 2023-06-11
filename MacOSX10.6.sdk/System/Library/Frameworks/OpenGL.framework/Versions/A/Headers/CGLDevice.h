/*
	Copyright:	(c) 1999 by Apple Computer, Inc., all rights reserved.
*/

#ifndef _CGLDEVICE_H
#define _CGLDEVICE_H

#include <OpenGL/CGLTypes.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct CGLShareGroupRec	*CGLShareGroup;

CGLError CGLGetCGLContextShareGroup(CGLContextObj ctx, CGLShareGroup *group_ret);

#ifdef __cplusplus
}
#endif

#endif /* _CGLDEVICE_H */

