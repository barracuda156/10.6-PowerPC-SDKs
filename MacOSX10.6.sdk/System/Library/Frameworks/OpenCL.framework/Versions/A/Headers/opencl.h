/*******************************************************************************
 * Copyright:  (c) 2007-2008 by Apple, Inc., All Rights Reserved.
 ******************************************************************************/

#ifndef __OPENCL_H
#define __OPENCL_H

#include <AvailabilityMacros.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "opencl_types.h"
  

/*******************************************************************************
 * Device & Context API
 ******************************************************************************/

extern 
int clGetComputeDevices(cl_device_type type, unsigned num_requested,
                        cl_device *device_ids, unsigned *num_device_ids) AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

extern 
int clGetDeviceConfigInfo(cl_device device_id, cl_device_config_info key,
                          void *buffer, size_t buffer_size, size_t *size_out) AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

extern 
const char *clGetDeviceConfigString(cl_device device_id, cl_device_config_string key) AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

extern 
cl_device_group clCreateDeviceGroup(unsigned count, cl_device *device_ids) AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

extern 
cl_device_group clCreateDeviceGroupFromType(cl_device_type type) AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

extern 
void clRetainDeviceGroup(cl_device_group group) AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

extern 
void clReleaseDeviceGroup(cl_device_group group) AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

extern 
int clGetDeviceGroupInfo(cl_device_group group, cl_device_group_info key,
                         void *buffer, size_t buffer_size, size_t *size_out) AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

extern 
cl_context clCreateContext(cl_context_properties *properties, cl_device_group device) AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

extern
void clRetainContext(cl_context context) AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

extern
void clReleaseContext(cl_context context) AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

extern 
int clGetContextInfo(cl_context context, cl_context_info key,
                            void *buffer, size_t buffer_size, size_t *size_out) AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

extern
int clSetContextProperties (cl_context context, cl_context_properties *properties) AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

extern
int clGetContextProperties (cl_context context, cl_context_property_type property, unsigned *property_value) AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

extern
int clFlush(cl_context context) AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

extern
int clFinish(cl_context context) AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

/*******************************************************************************
 * Data API
 ******************************************************************************/

extern 
cl_mem clCreateArray(cl_device_group group, cl_mem_flags flags, 
                     size_t element_size, size_t num_elements, void *host_ptr) AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

extern
cl_mem clCreateImage2D(cl_device_group group, cl_mem_flags flags, 
                       cl_image_format *format, size_t width, size_t height, 
                       size_t pitch, void *host_ptr) AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

extern
cl_mem clCreateImage3D(cl_device_group group, cl_mem_flags flags, 
                       cl_image_format *format, size_t width, size_t height, 
                       size_t depth, size_t row_pitch, size_t slice_pitch,
                       void *host_ptr) AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

extern
void clRetainMemObject(cl_mem memobj) AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

extern
void clReleaseMemObject(cl_mem memobj) AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

extern 
int clGetSupportedImageFormats(cl_device_group group, cl_mem_flags flags,
                               cl_mem_object_type type, unsigned num_entries,
                               cl_image_format *formats, unsigned *num_formats) AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

extern 
int clReadArray(cl_context context, cl_mem array, int async, size_t offset, 
                size_t length, void *dst, cl_event *event) AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

extern
int clWriteArray(cl_context context, cl_mem array, int async, size_t offset, 
                 size_t length, const void *src, cl_event *event) AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

extern 
int clReadImage(cl_context context, cl_mem image, int async, size_t x, size_t y,
                size_t z, size_t w, size_t h, size_t d, size_t dst_row_pitch, 
                size_t dst_slice_pitch, void *dst, cl_event *event) AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

extern 
int clWriteImage(cl_context context, cl_mem image, int async, size_t x, 
                 size_t y, size_t z, size_t w, size_t h, size_t d, 
                 cl_image_format *src_format, size_t src_row_pitch, 
                 size_t src_slice_pitch, const void *src, cl_event *event) AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

extern 
int clCopyArray(cl_context context, cl_mem src, cl_mem dst, size_t dst_offset, 
                size_t src_offset, size_t length, cl_event *event) AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

extern 
int clCopyImage(cl_context context, cl_mem src, cl_mem dst, size_t src_x, 
                size_t src_y, size_t src_z, size_t dst_x, size_t dst_y, 
                size_t dst_z, size_t w, size_t h, size_t z, cl_event *event) AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

extern 
int clCopyImageToArray(cl_context context, cl_mem src_image, cl_mem dst_array,
                       size_t src_x, size_t src_y, size_t src_z, size_t w, 
                       size_t h, size_t z, size_t dst_offset, cl_event *event) AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

extern 
int clCopyArrayToImage(cl_context context, cl_mem src_array, cl_mem dst_image, 
                       size_t src_offset, size_t dst_x, size_t dst_y, 
                       size_t dst_z, size_t w, size_t h, size_t z, cl_event *event) AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

extern 
int clGetMemObjectInfo(cl_mem memobj, cl_mem_info key, void *buffer, 
                       size_t buffer_size, size_t *size_out) AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

extern 
int clGetArrayInfo(cl_mem array, cl_array_info key, void *buffer, 
                   size_t buffer_size, size_t *size_out) AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

extern 
int clGetImageInfo(cl_mem image, cl_image_info key, void *buffer, 
                   size_t buffer_size, size_t *size_out) AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

extern
void *clLockArray(cl_context context, cl_mem array, size_t offset, size_t length,
                  cl_lock_flags flags) AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER; 

extern
void *clLockImage(cl_context context, cl_mem image, size_t x, size_t y, size_t z,
                  size_t width, size_t height, size_t depth, cl_lock_flags flags) AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER; 

extern 
void clUnlockMemObject(cl_context context, cl_mem memobj) AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

/*******************************************************************************
 * Execution API
 ******************************************************************************/

extern 
void clRetainProgram(cl_program program) AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

extern 
void clReleaseProgram(cl_program program) AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

extern 
cl_program clCreateProgramWithSource(cl_device_group device, unsigned count,
                                     const char **strings, size_t *lengths) AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

extern 
cl_program clCreateProgramWithBinary(cl_device_group device, size_t length, void *binary) AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

extern 
int clBuildProgramExecutable(cl_program program, int async, const char *options, 
                             void (*pfn_notify)(cl_program)) AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

extern 
int clGetProgramInfo(cl_program program, cl_program_info key, void *buffer,
                     size_t buffer_size, size_t *size_out) AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

extern 
int clGetProgramSource(cl_program program, size_t buffer_size, size_t *length,
                       char *source) AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

extern 
int clGetProgramBinary(cl_program program, size_t buffer_size, size_t *length,
                       void *binary) AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

extern 
int clGetProgramBuildLog(cl_program program, size_t buffer_size, size_t *length,
                         char *log) AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

extern 
cl_kernel clCreateKernel(cl_program program, const char *kernel_name) AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

extern 
int clCreateKernelsInProgram(cl_program program, unsigned num_kernels,  
                             cl_kernel *kernels, unsigned *num_kernels_ret) AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

extern 
void clRetainKernel(cl_kernel kernel) AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

extern 
void clReleaseKernel(cl_kernel kernel) AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

extern 
int clSetKernelArg(cl_kernel kernel, unsigned index, void *value, size_t size, 
                   void *associated_data) AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

extern 
int clGetKernelInfo(cl_kernel kernel, cl_kernel_info key, void *buffer, 
                    size_t buffer_size, size_t *size_out) AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

extern
int clGetKernelWorkGroupInfo(cl_context context, cl_kernel kernel, 
                             cl_device device, cl_kernel_work_group_info key, 
                             void *buffer, size_t buffer_size, size_t *size_out) AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

extern
int clExecuteKernel(cl_context context, cl_kernel kernel, cl_device id,
                    unsigned *global_dim, unsigned *local_dim, unsigned ndims,
                    cl_event *wait_list, unsigned wait_list_size, cl_event *evt) AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

extern 
int clExecuteDyLibKernel(cl_context context, cl_device_group device, 
                         void (*kernel_func)(void *), void *args,
                         unsigned num_streams, cl_mem *streams,
                         void **args_stream_loc, cl_event *wait_list,
                         unsigned wait_list_size, cl_event *event) AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

extern
int clGetEventStatus(cl_event event, cl_event_flags flags, 
                     cl_event_status *status) AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

extern 
int clGetEventInfo(cl_event event, cl_event_info key, void *buffer, 
                    size_t buffer_size, size_t *size_out) AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

extern 
void clReleaseEvent(cl_event event) AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

extern 
int clWaitForEvents(cl_context context, unsigned count, cl_event *events) AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

extern 
int clWaitBarrier(cl_context context) AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

extern 
int clGetEventProfilingInfo(cl_event event, cl_profiling_info key,
                            void *buffer,  size_t buffer_size, size_t *size_out) AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;
  
#ifdef __cplusplus
}
#endif

#endif  // __OPENCL_H
