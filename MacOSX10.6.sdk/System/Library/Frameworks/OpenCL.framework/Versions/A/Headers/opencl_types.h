/*******************************************************************************
 * Copyright:  (c) 2007-2008 by Apple, Inc., All Rights Reserved.
 ******************************************************************************/

#ifndef __OPENCL_TYPES_H
#define __OPENCL_TYPES_H

#include <sys/types.h>
#include <stdbool.h>
#include <OpenGL/CGLDevice.h>

typedef unsigned cl_bitfield;
typedef struct _CLDevice * cl_device;
typedef struct _CLContext * cl_context;
typedef struct _CLEvent * cl_event;
typedef struct _CLGroup * cl_device_group;
typedef struct _CLKernel * cl_kernel;
typedef struct _CLProgram * cl_program;
typedef struct _CLMem * cl_mem;

// FIXME: remove this before shipping? keep for now.
typedef cl_mem cl_stream;

// Error codes that can be returned from OpenCL API calls
typedef enum cl_error {
  CL_SUCCESS              =  0,
  CL_INVALID_VALUE        = -1,
  CL_INVALID_DEVICE       = -2,
  CL_INVALID_CONTEXT      = -3,
  CL_INVALID_MEM_OBJECT   = -4,
  CL_INVALID_PROGRAM      = -5,
  CL_INVALID_BINARY       = -6,
  CL_INVALID_EXECUTABLE   = -7,
  CL_INVALID_KERNEL       = -8,
  CL_INVALID_KERNEL_ARGS  = -9,
  CL_INVALID_EVENT        = -10,
  CL_INVALID_OPERATION    = -11,
  CL_INVALID_ATTACHMENT   = -12,
  CL_BUILD_ERROR          = -13,
  CL_INVALID_OPTIONS      = -14,
  CL_INVALID_DEVICE_ID    = -15,
  CL_INVALID_GLOBAL_WORK_DIM  = -16,
  CL_INVALID_LOCAL_WORK_DIM   = -17,
  CL_INVALID_WORK_DIM_SIZE    = -18,
  CL_INVALID_EVENT_WAIT_LIST  = -19,
  CL_PROFILING_INFO_NOT_AVAILABLE = -20,
  CL_NO_DEVICE_FOUND    = -21,
  CL_INVALID_ARG_VALUE  = -22,
  CL_INVALID_ARG_INDEX  = -23,
  CL_INVALID_ARG_SIZE   = -24,
  CL_INVALID_ARG_ASSOCIATED_DATA = -25
} cl_error;

typedef enum cl_boolean {
  CL_FALSE = 0,
  CL_TRUE = 1
} cl_boolean;

// 3.1 device types used by the clGetComputeDevices API
typedef enum cl_device_type {
  // CL_DEVICE_TYPE_DEFAULT - The default compute device in the system
  CL_DEVICE_TYPE_DEFAULT = 1 << 0,
  
  // CL_DEVICE_TYPE_CPU - A single or multi-core cpu compute device.  Typically
  // this would represent all the general purpose cpus in a system.
  CL_DEVICE_TYPE_CPU = 1 << 1,
  
  // CL_DEVICE_TYPE_GPU - A GPU compute device.
  CL_DEVICE_TYPE_GPU = 1 << 2,
  
  // CL_DEVICE_TYPE_ALL - All compute devices available in the system.
  CL_DEVICE_TYPE_ALL = -1
} cl_device_type;

// 3.1 info types used by the clGetDeviceConfigInfo API
typedef enum cl_device_config_info {
  CL_DEVICE_TYPE,
  CL_DEVICE_ID,
  CL_DEVICE_MAX_COMPUTE_UNITS,
  CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS,
  CL_DEVICE_MAX_WORK_GROUP_SIZE,
  CL_DEVICE_SIMD_GROUP_SIZE,
  CL_DEVICE_MAX_CLOCK_FREQUENCY,
  CL_DEVICE_ADDRESS_BITS,
  CL_DEVICE_MAX_READ_IMAGE_ARGS,
  CL_DEVICE_MAX_WRITE_IMAGE_ARGS,
  CL_DEVICE_MAX_MEM_ALLOC_SIZE,
  CL_DEVICE_IMAGE2D_MAX_WIDTH,
  CL_DEVICE_IMAGE2D_MAX_HEIGHT,
  CL_DEVICE_IMAGE3D_MAX_WIDTH,
  CL_DEVICE_IMAGE3D_MAX_HEIGHT,
  CL_DEVICE_IMAGE3D_MAX_DEPTH,
  CL_DEVICE_MAX_SAMPLERS,
  CL_DEVICE_MAX_PARAMETER_SIZE,
  CL_DEVICE_MEM_BASE_ADDR_ALIGN,
  CL_DEVICE_IMAGE_PITCH_ALIGN,
  CL_DEVICE_IMAGE_MIN_PITCH_SIZE,
  CL_DEVICE_SINGLE_FP_CONFIG,
  CL_DEVICE_GLOBAL_MEM_CACHE_TYPE,
  CL_DEVICE_GLOBAL_MEM_CACHE_SIZE,
  CL_DEVICE_GLOBAL_MEM_CACHELINE_SIZE,
  CL_DEVICE_GLOBAL_MEM_SIZE,
  CL_DEVICE_GLOBAL_GART_MEM_SIZE, // PCIe mem size
  CL_DEVICE_MAX_CONSTANT_BUFFER_SIZE,
  CL_DEVICE_MAX_CONSTANT_ARGS,
  CL_DEVICE_LOCAL_MEM_TYPE,
  CL_DEVICE_LOCAL_MEM_SIZE,
  CL_DEVICE_ERROR_CORRECTION_SUPPORT,
  CL_DEVICE_PROFILING_TIMER_RESOLUTION,
  CL_DEVICE_EXECUTION_CAPABILITIES
} cl_device_config_info;

// 3.1 info types used by the clGetDeviceConfigStrings API
typedef enum cl_device_config_string {
  CL_DEVICE_NAME,
  CL_DEVICE_VENDOR,
  CL_DEVICE_VERSION,
  CL_DRIVER_VERSION,
  CL_VERSION,
  CL_DEVICE_EXTENSIONS
} cl_device_config_string;

// 3.1 bits in CL_DEVICE_SINGLE_FP_CONFIG bitfield
typedef enum cl_fp_config {
  CL_FP_DENORM            = 1 << 0,
  CL_FP_INF_NAN           = 1 << 1,
  CL_FP_ROUND_TO_NEAREST  = 1 << 2,
  CL_FP_ROUND_TO_ZERO     = 1 << 3,
  CL_FP_ROUND_TO_INF      = 1 << 4,
  CL_FP_FMA               = 1 << 5,
} cl_device_fp_config;

// 3.1 bits in CL_DEVICE_GLOBAL_MEM_CACHE_TYPE bitfield 
typedef enum cl_device_global_mem_cache_type {
  CL_NONE,
  CL_READ_ONLY_CACHE,
  CL_READ_WRITE_CACHE,
} cl_device_global_mem_cache_type;

// 3.1 bits in CL_DEVICE_LOCAL_MEM_TYPE bitfield
typedef enum cl_device_local_mem_type {
  CL_LOCAL,
  CL_GLOBAL
} cl_device_local_mem_type;

// 3.1 bits in CL_DEVICE_EXECUTION_CAPABILITIES
typedef enum cl_device_exec_capabilities {
  CL_EXEC_DATA_PARALLEL_KERNEL = 1 << 0,
  CL_EXEC_TASK_PARALLEL_KERNEL = 1 << 1,
  CL_EXEC_NATIVE_FN_AS_KERNEL  = 1 << 2,
} cl_device_exec_capabilities;

// 3.2 info types used by the clGetDeviceGroupInfo API
typedef enum cl_device_group_info {
  CL_DEVICEGROUP_NUM_INSTANCES,
  CL_DEVICES,
} cl_device_group_info;

// 3.3 context properties
typedef enum cl_context_property_type {
  CL_CONTEXT_NULL = 0,
  CL_CONTEXT_EXEC_MODE_ASYNC,
  CL_CONTEXT_PROFILING_ENABLE
} cl_context_property_type;

// 3.3 info types used by the clGetContextInfoAPI
typedef enum cl_context_info {
  CL_CONTEXT_DEVICE,
  CL_CONTEXT_NUM_INSTANCES
} cl_context_info;

typedef enum cl_context_flags {
  CL_CONTEXT_NONE
} cl_context_flags;

// 4.1 flags used by the clCreateArray, and clCreateImage{2D|3D} APIs
typedef enum cl_mem_flags {
  CL_MEM_READ_WRITE              = 1 << 0,
  CL_MEM_WRITE_ONLY              = 1 << 1,
  CL_MEM_READ_ONLY               = 1 << 2,
  CL_MEM_ALLOC_REFERENCE         = 1 << 3,
  CL_MEM_ALLOC_GLOBAL_POOL       = 1 << 4,
  CL_MEM_ALLOC_CONSTANT_POOL     = 1 << 5,
  CL_MEM_USE_HOST_PTR            = 1 << 6,
  CL_MEM_COPY_HOST_PTR           = 1 << 7
} cl_mem_flags;

// 4.1.1 supported image channel orders for use in cl_image_format struct,
// used by various image stream APIs.
typedef enum cl_channel_order {
  CL_R,
  CL_A,
  CL_RG,
  CL_RA,
  CL_RGB,
  CL_RGBA,
  CL_ARGB,
  CL_xRGB
} cl_channel_order;

// 4.1.1 supported image channel data types for use in cl_image_format struct,
// used by various image stream APIs.
typedef enum cl_channel_type {
  CL_SNORM_INT8,
  CL_SNORM_INT16,
  CL_UNORM_INT8,
  CL_UNORM_INT16,
  CL_UNORM_SHORT_565,
  CL_UNORM_SHORT_565_REV,
  CL_UNORM_SHORT_555,
  CL_UNORM_SHORT_555_REV,
  CL_UNORM_INT_8888,
  CL_UNORM_INT_8888_REV,
  CL_UNORM_INT_101010,
  CL_UNORM_INT_101010_REV,
  CL_SIGNED_INT8,
  CL_SIGNED_INT16,
  CL_SIGNED_INT32,
  CL_UNSIGNED_INT8,
  CL_UNSIGNED_INT16,
  CL_UNSIGNED_INT32,
  CL_HALF_FLOAT,
  CL_FLOAT
} cl_channel_type;

// 4.1.1 mem object type returned by clGetMemObjectInfo 
// and clGetSupportedImageFormats API
typedef enum cl_mem_object_type {
  CL_MEM_OBJECT_ARRAY,
  CL_MEM_OBJECT_IMAGE2D,
  CL_MEM_OBJECT_IMAGE3D
} cl_mem_object_type;

// 4.1.4 locking and unlocking mem objects
typedef enum cl_lock_flags {
  CL_LOCK_FLAGS_NONE  // dummy enum, do not use
} cl_lock_flags;

// 4.1.5 info types used by the clGetMemObject API
typedef enum cl_mem_info {
  CL_MEM_OBJECT_TYPE,
  CL_MEM_OBJECT_FLAGS,
  CL_MEM_OBJECT_SIZE,
  CL_MEM_OBJECT_HOST_PTR,
  CL_MEM_OBJECT_LOCK_COUNT,
  CL_MEM_OBJECT_NUM_INSTANCES,
  CL_MEM_OBJECT_DEVICE
} cl_mem_info;

typedef enum cl_array_info {
  CL_ARRAY_ELEMENT_SIZE,
  CL_ARRAY_NUM_ELEMENTS,
} cl_array_info;

typedef enum cl_image_info {
  CL_IMAGE_FORMAT,
  CL_IMAGE_ELEMENT_SIZE,
  CL_IMAGE_ROW_PITCH,
  CL_IMAGE_SLICE_PITCH,
  CL_IMAGE_WIDTH,
  CL_IMAGE_HEIGHT,
  CL_IMAGE_DEPTH,
} cl_image_info;

typedef enum cl_addressing_mode {
  CL_ADDRESS_NONE,
  CL_ADDRESS_REPEAT,
  CL_ADDRESS_CLAMP_TO_EDGE,
  CL_ADDRESS_CLAMP,
} cl_addressing_mode;

typedef enum cl_filter_mode {
  CL_FILTER_NEAREST,
  CL_FILTER_LINEAR,
} cl_filter_mode;

// 4.2.4 info types used by the clGetProgramInfo API
typedef enum cl_program_info {
  CL_PROGRAM_NUM_INSTANCES,
  CL_PROGRAM_DEVICE,
  CL_PROGRAM_BUILD_STATUS
} cl_program_info;

// 4.2.4 status codes possible for cl_program build status
typedef enum cl_build_status {
  CL_BUILD_SUCCESS,
  CL_BUILD_FAILURE,
  CL_BUILD_IN_PROGRESS,
  CL_BUILD_NONE
} cl_build_status;

// 4.3.2 info types used by the clGetKernelInfo API
typedef enum cl_kernel_info {
  CL_KERNEL_FUNCTION_NAME,
  CL_KERNEL_NUM_ARGS,
  CL_KERNEL_NUM_INSTANCES,
  CL_KERNEL_PROGRAM,
  CL_KERNEL_DEVICE
} cl_kernel_info;

// 4.3.2 info types used by clGetKernelWorkGroupInfo API
typedef enum cl_kernel_work_group_info {
  CL_KERNEL_WORK_GROUP_SIZE,
  CL_KERNEL_COMPILE_WORK_GROUP_SIZE
} cl_kernel_work_group_info;

// 4.3.2 argument types used by the clGetKernelArgs API
typedef enum cl_arg_info {
  CL_KERNEL_ARG_NAME,
  CL_KERNEL_ARG_TYPE,
  CL_KERNEL_ARG_VALUE
} cl_arg_info;

// 4.3.5.2 keys used for clGetEventInfo
typedef enum cl_event_command {
  CL_EVENT_COMMAND_EXECUTE_KERNEL,
  CL_EVENT_COMMAND_EXECUTE_DYLIB,
  CL_EVENT_COMMAND_READ,
  CL_EVENT_COMMAND_WRITE,
  CL_EVENT_COMMAND_COPY
} cl_event_command;

// 4.3.6 keys used by event status APIs
typedef enum cl_event_flags {
  CL_EVENT_WAIT_FOR_COMPLETION,
  CL_EVENT_STATUS
} cl_event_flags;

// 4.3.6 event status codes returned from event status APIs
typedef enum cl_event_status {
  CL_COMPLETE,
  CL_RUNNING,
  CL_QUEUED,
  CL_TERMINATED
} cl_event_status;

// 4.3.6.2 event info
typedef enum cl_event_info {
  CL_EVENT_CONTEXT,
  CL_EVENT_DEVICE,
  CL_EVENT_COMMAND,
  CL_EVENT_DEVICE_ID
} cl_event_info;

// 4.3.8 event profiling info
typedef enum cl_profiling_info {
  CL_PROFILING_COMMAND_QUEUE,
  CL_PROFILING_COMMAND_START,
  CL_PROFILING_COMMAND_END
} cl_profiling_info;

// 9.1.4 keys used by clGetGLAttachment API
typedef enum cl_gl_object_type {
  CL_GL_OBJECT_GL_BUFFER,
  CL_GL_OBJECT_GL_TEXTURE2D,
  CL_GL_OBJECT_GL_TEXTURE3D,
  CL_GL_OBJECT_GL_RENDER_BUFFER
} cl_gl_object_type;

// cl_local_arg_desc - description of memory allocation for __local arguments
// when calling compute kernels as "C" functions.
typedef struct _cl_local_arg_desc { 
  // local_ptr - currently can only be set to 0
  void *local_ptr; 
  
  // size_in_bytes - the size in bytes of local memory to be allocated when the
  // kernel is executed.
  unsigned size_in_bytes; 
} cl_local_arg_desc; 

// cl_exec_desc - description of parameters controlling kernel execution when
// a kernel is called as a "C" function.  Similar to the arguments taken by
// clExecuteKernel.
typedef struct _cl_exec_desc { 
  cl_context context; 
  cl_device_group device; 
  unsigned *global_thread_dim;
  unsigned *local_thread_dim; 
  unsigned thread_dim_size;
  cl_event *event_wait_list;
  unsigned event_wait_list_size;
  cl_event *compute_event; 
} cl_exec_desc; 

// cl_image_format - described in section 4.1.1 of the spec, this structure
// allows a client to fully specify a pixel format for use with the image
// streams APIs.
typedef struct _cl_image_format_t {
  unsigned num_channels;
  cl_channel_order channel_order;
  cl_channel_type channel_data_type;
} cl_image_format;

typedef struct _cl_sampler_t {
  cl_addressing_mode addressing_mode;
  cl_filter_mode     filter_mode;
  bool               normalized_coords;
} cl_sampler;

typedef struct cl_context_properties {
  cl_context_property_type type;
  unsigned value;
} cl_context_properties;

typedef struct cl_gl_texture_info {
  unsigned dummy1;
  unsigned dummy2;
} cl_gl_texture_info;

#endif  // __OPENCL_TYPES_H
