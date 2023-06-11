/*
	Copyright:	(c) 2008 by Apple Computer, Inc., all rights reserved.
*/

#ifndef __OPENCL_GL_H
#define __OPENCL_GL_H

#ifdef __cplusplus
extern "C" {
#endif

#include "opencl_types.h"
  
#include <OpenGL/gl.h>

#include <OpenGL/CGLDevice.h>

extern cl_device clCreateDeviceGroupFromCGLShareGroup(CGLShareGroup group);
extern cl_device clCreateDeviceGroupFromCGLContext(CGLContextObj cgl_ctx);

extern int clAttachGLBuffer(cl_context context, cl_mem array, GLuint obj);
extern int clDetachGLBuffer(cl_context context, cl_mem array);

extern int clAttachGLTexture2D(cl_context context, cl_mem image, GLenum textarget, GLuint texture, GLuint miplevel);
extern int clDetachGLTexture2D(cl_context context, cl_mem image);

extern int clAttachGLTexture3D(cl_context context, cl_mem image, GLenum textarget, GLenum texture, GLint miplevel);
extern int clDetachGLTexture3D(cl_context context, cl_mem image);

extern int clAttachGLRenderbuffer(cl_context context, cl_mem image, GLenum renderbuffer);
extern int clDetachGLRenderbuffer(cl_context context, cl_mem image);

extern int clGetGLAttachment(cl_context context, cl_mem memobj, cl_gl_attachment_type type, GLuint *gl_object);


#ifdef __cplusplus
}
#endif

#endif  // __OPENCL_GL_H
