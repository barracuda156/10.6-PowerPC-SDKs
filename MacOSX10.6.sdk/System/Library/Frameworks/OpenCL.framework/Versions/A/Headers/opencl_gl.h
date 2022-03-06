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

extern cl_device_group clCreateDeviceGroupFromCGLShareGroup(CGLShareGroup group);
extern cl_device_group clCreateDeviceGroupFromCGLContext(CGLContextObj cgl_ctx);

extern
cl_mem clCreateGLBufferRef(cl_device_group device, cl_mem_flags flags, GLuint bufobj);

extern
cl_mem clCreateGLTexture2DRef(cl_device_group device, cl_mem_flags flags, GLenum target, GLint miplevel, GLuint texture);

extern
cl_mem clCreateGLTexture3DRef(cl_device_group device, cl_mem_flags flags, GLenum target, GLint miplevel, GLuint texture);

extern
cl_mem clCreateGLRenderbufferRef(cl_device_group device, cl_mem_flags flags, GLenum renderbuffer);

extern
int		clAcquireGLMemObjects (cl_device_group device_group, unsigned int num_objects, cl_mem *memobjects);

extern
int		clReleaseGLMemObjects (cl_device_group device_group, unsigned int num_objects, cl_mem *memobjects);

extern 
int clGetGLObjectInfo(cl_mem memobj, cl_gl_object_type *type, GLuint *object, cl_gl_texture_info *info);

#ifdef __cplusplus
}
#endif

#endif  // __OPENCL_GL_H
