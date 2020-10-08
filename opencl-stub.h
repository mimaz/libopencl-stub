#pragma once
#include <CL/cl.h>

int opencl_stub_load (const char *path, int api_level);
void opencl_stub_unload (void);

#define __OPENCL_STUB_DECLARE(name, return_type, ...) \
	typedef return_type (*f_##name) (__VA_ARGS__); \
	extern f_##name s_##name;

__OPENCL_STUB_DECLARE (clGetPlatformIDs, cl_int,
					   cl_uint, cl_platform_id *, cl_uint *);
__OPENCL_STUB_DECLARE (clGetPlatformInfo, cl_int,
					   cl_platform_id, cl_platform_info,
					   size_t, void *, size_t *);
__OPENCL_STUB_DECLARE (clGetDeviceIDs, cl_int,
					   cl_platform_id, cl_device_type,
					   cl_uint, cl_device_id *, cl_uint *);
__OPENCL_STUB_DECLARE (clGetDeviceInfo, cl_int,
					   cl_device_id, cl_device_info,
					   size_t, void *, size_t *);
#ifdef CL_VERSION_1_2
__OPENCL_STUB_DECLARE (clCreateSubDevices, cl_int,
					   cl_device_id,
					   const cl_device_partition_property *,
					   cl_uint, cl_device_id *, cl_uint *);
__OPENCL_STUB_DECLARE (clRetainDevice, cl_int,
					   cl_device_id);
__OPENCL_STUB_DECLARE (clReleaseDevice, cl_int,
					   cl_device_id);
#endif
#ifdef CL_VERSION_2_1
__OPENCL_STUB_DECLARE (clSetDefaultDeviceCommandQueue, cl_int,
					   cl_context, cl_device_id, cl_command_queue);
__OPENCL_STUB_DECLARE (clGetDeviceAndHostTimer, cl_int,
					   cl_device_id, cl_ulong *, cl_ulong *);
__OPENCL_STUB_DECLARE (clGetHostTimer, cl_int,
					   cl_device_id, cl_ulong *);
#endif
__OPENCL_STUB_DECLARE (clCreateContext, cl_context,
					   const cl_context_properties *,
					   cl_uint, const cl_device_id *,
					   void (CL_CALLBACK *)(const char *,
											const void *,
											size_t, void *),
					   void *, cl_int *);
__OPENCL_STUB_DECLARE (clCreateContextFromType, cl_context,
					   const cl_context_properties *,
					   cl_device_type,
					   void (CL_CALLBACK *)(const char *,
											const void *,
											size_t, void *),
					   void *, cl_int *);
__OPENCL_STUB_DECLARE (clRetainContext, cl_int,
					   cl_context);
__OPENCL_STUB_DECLARE (clReleaseContext, cl_int,
					   cl_context);
__OPENCL_STUB_DECLARE (clGetContextInfo, cl_int,
					   cl_context, cl_context_info,
					   size_t, void *, size_t *);
#ifdef CL_VERSION_3_0
__OPENCL_STUB_DECLARE (clSetContextDestructorCallback, cl_int,
					   cl_context,
					   void (CL_CALLBACK *)(cl_context, void *),
					   void *);
#endif
#ifdef CL_VERSION_2_0
__OPENCL_STUB_DECLARE (clCreateCommandQueueWithProperties, cl_command_queue,
					   cl_context, cl_device_id,
					   const cl_queue_properties *, cl_int *);
#endif
__OPENCL_STUB_DECLARE (clRetainCommandQueue, cl_int,
					   cl_command_queue);
__OPENCL_STUB_DECLARE (clReleaseCommandQueue, cl_int,
					   cl_command_queue);
__OPENCL_STUB_DECLARE (clGetCommandQueueInfo, cl_int,
					   cl_command_queue, cl_command_queue_info,
					   size_t, void *, size_t *);
__OPENCL_STUB_DECLARE (clCreateBuffer, cl_mem,
					   cl_context, cl_mem_flags,
					   size_t, void *, cl_int *);
#ifdef CL_VERSION_1_1
__OPENCL_STUB_DECLARE (clCreateSubBuffer, cl_mem,
					   cl_mem, cl_mem_flags, cl_buffer_create_type,
					   const void *, cl_int *);
#endif
#ifdef CL_VERSION_1_2
__OPENCL_STUB_DECLARE (clCreateImage, cl_mem,
					   cl_context, cl_mem_flags,
					   const cl_image_format *,
					   const cl_image_desc *, void *, cl_int *);
#endif
#ifdef CL_VERSION_2_0
__OPENCL_STUB_DECLARE (clCreatePipe, cl_mem,
					   cl_context, cl_mem_flags, cl_uint, cl_uint,
					   const cl_pipe_properties *, cl_int *);
#endif
#ifdef CL_VERSION_3_0
__OPENCL_STUB_DECLARE (clCreateBufferWithProperties, cl_mem,
					   cl_context, const cl_mem_properties *,
					   cl_mem_flags, size_t, void *, cl_int *);
__OPENCL_STUB_DECLARE (clCreateImageWithProperties, cl_mem,
					   cl_context, const cl_mem_properties *,
					   cl_mem_flags, const cl_image_format *,
					   const cl_image_desc *, void *, cl_int *);
#endif
__OPENCL_STUB_DECLARE (clRetainMemObject, cl_int,
					   cl_mem);
__OPENCL_STUB_DECLARE (clReleaseMemObject, cl_int,
					   cl_mem);
__OPENCL_STUB_DECLARE (clGetSupportedImageFormats, cl_int,
					   cl_context, cl_mem_flags, cl_mem_object_type,
					   cl_uint, cl_image_format *, cl_uint *);
__OPENCL_STUB_DECLARE (clGetMemObjectInfo, cl_int,
					   cl_mem, cl_mem_info, size_t, void *, size_t *);
__OPENCL_STUB_DECLARE (clGetImageInfo, cl_int,
					   cl_mem, cl_image_info, size_t, void *, size_t *);
#ifdef CL_VERSION_2_0
__OPENCL_STUB_DECLARE (clGetPipeInfo, cl_int,
					   cl_mem, cl_pipe_info, size_t, void *, size_t *);
#endif
#ifdef CL_VERSION_1_1
__OPENCL_STUB_DECLARE (clSetMemObjectDestructorCallback, cl_int,
					   cl_mem,
					   void (CL_CALLBACK *)(cl_mem, void *),
					   void *);
#endif
#ifdef CL_VERSION_2_0
__OPENCL_STUB_DECLARE (clCreateSamplerWithProperties, cl_sampler,
					   cl_context, const cl_sampler_properties *,
					   cl_int *);
#endif
__OPENCL_STUB_DECLARE (clRetainSampler, cl_int,
					   cl_sampler);
__OPENCL_STUB_DECLARE (clReleaseSampler, cl_int,
					   cl_sampler);
__OPENCL_STUB_DECLARE (clGetSamplerInfo, cl_int,
					   cl_sampler, cl_sampler_info,
					   size_t, void *, size_t *);
__OPENCL_STUB_DECLARE (clCreateProgramWithSource, cl_program,
					   cl_context, cl_uint, const char **,
					   const size_t *, cl_int *);
__OPENCL_STUB_DECLARE (clCreateProgramWithBinary, cl_program,
					   cl_context, cl_uint, const cl_device_id *,
					   const size_t *, const unsigned char **,
					   cl_int *, cl_int *);
#ifdef CL_VERSION_1_2
__OPENCL_STUB_DECLARE (clCreateProgramWithBuiltInKernels, cl_program,
					   cl_context, cl_uint, const cl_device_id *,
					   const char *, cl_int *);
#endif
#ifdef CL_VERSION_2_1
__OPENCL_STUB_DECLARE (clCreateProgramWithIL, cl_program,
					   cl_context, const void *, size_t, cl_int *);
#endif
__OPENCL_STUB_DECLARE (clRetainProgram, cl_int,
					   cl_program);
__OPENCL_STUB_DECLARE (clReleaseProgram, cl_int,
					   cl_program);
__OPENCL_STUB_DECLARE (clBuildProgram, cl_int,
					   cl_program, cl_uint, const cl_device_id *,
					   const char *,
					   void (CL_CALLBACK *)(cl_program, void *),
					   void *);
#ifdef CL_VERSION_1_2
__OPENCL_STUB_DECLARE (clCompileProgram, cl_int,
					   cl_program, cl_uint, const cl_device_id *,
					   const char *, cl_uint, const cl_program *,
					   const char **,
					   void (CL_CALLBACK *)(cl_program, void *),
					   void *);
__OPENCL_STUB_DECLARE (clLinkProgram, cl_program,
					   cl_context, cl_uint, const cl_device_id *,
					   const char *, cl_uint, const cl_program *,
					   void (CL_CALLBACK *)(cl_program, void *),
					   void *, cl_int *);
#endif
#ifdef CL_VERSION_2_2
__OPENCL_STUB_DECLARE (clSetProgramReleaseCallback, cl_int,
					   cl_program,
					   void (CL_CALLBACK *)(cl_program, void *),
					   void *);
__OPENCL_STUB_DECLARE (clSetProgramSpecializationConstant, cl_int,
					   cl_program, cl_uint, size_t, const void *);
#endif
#ifdef CL_VERSION_1_2
__OPENCL_STUB_DECLARE (clUnloadPlatformCompiler, cl_int,
					   cl_platform_id);
#endif
__OPENCL_STUB_DECLARE (clGetProgramInfo, cl_int,
					   cl_program, cl_program_info,
					   size_t, void *, size_t *);
__OPENCL_STUB_DECLARE (clGetProgramBuildInfo, cl_int,
					   cl_program, cl_device_id,
					   cl_program_build_info,
					   size_t, void *, size_t *);
__OPENCL_STUB_DECLARE (clCreateKernel, cl_kernel,
					   cl_program, const char *, cl_int *);
__OPENCL_STUB_DECLARE (clCreateKernelsInProgram, cl_int,
					   cl_program, cl_uint,
					   cl_kernel *, cl_uint *);
#ifdef CL_VERSION_2_1
__OPENCL_STUB_DECLARE (clCloneKernel, cl_kernel,
					   cl_int *);
#endif
__OPENCL_STUB_DECLARE (clRetainKernel, cl_int,
					   cl_kernel);
__OPENCL_STUB_DECLARE (clReleaseKernel, cl_int,
					   cl_kernel);
__OPENCL_STUB_DECLARE (clSetKernelArg, cl_int,
					   cl_kernel, cl_uint, size_t, const void *);
#ifdef CL_VERSION_2_0
__OPENCL_STUB_DECLARE (clSetKernelArgSVMPointer, cl_int,
					   cl_kernel, cl_uint, const void *);
__OPENCL_STUB_DECLARE (clSetKernelExecInfo, cl_int,
					   cl_kernel, cl_kernel_exec_info,
					   size_t, const void *);
#endif
__OPENCL_STUB_DECLARE (clGetKernelInfo, cl_int,
					   cl_kernel, cl_kernel_info,
					   size_t, void *, size_t *);
#ifdef CL_VERSION_1_2
__OPENCL_STUB_DECLARE (clGetKernelArgInfo, cl_int,
					   cl_kernel, cl_uint, cl_kernel_arg_info,
					   size_t, void *, size_t *);
#endif
__OPENCL_STUB_DECLARE (clGetKernelWorkGroupInfo, cl_int,
					   cl_kernel, cl_device_id,
					   cl_kernel_work_group_info,
					   size_t, void *, size_t *);
#ifdef CL_VERSION_2_1
__OPENCL_STUB_DECLARE (clGetKernelSubGroupInfo, cl_int,
					   cl_kernel, cl_device_id,
					   cl_kernel_sub_group_info,
					   size_t, const void *,
					   size_t, void *, size_t *);
#endif
__OPENCL_STUB_DECLARE (clWaitForEvents, cl_int,
					   cl_uint, const cl_event *);
__OPENCL_STUB_DECLARE (clGetEventInfo, cl_int,
					   cl_event, cl_event_info,
					   size_t, void *, size_t *);
#ifdef CL_VERSION_1_1
__OPENCL_STUB_DECLARE (clCreateUserEvent, cl_event,
					   cl_context, cl_int *);
#endif
__OPENCL_STUB_DECLARE (clRetainEvent, cl_int,
					   cl_event);
__OPENCL_STUB_DECLARE (clReleaseEvent, cl_int,
					   cl_event);
#ifdef CL_VERSION_1_1
__OPENCL_STUB_DECLARE (clSetUserEventStatus, cl_int,
					   cl_event, cl_int);
__OPENCL_STUB_DECLARE (clSetEventCallback, cl_int,
					   cl_event, cl_int,
					   void (CL_CALLBACK *)(cl_event, cl_int, void *),
					   void *);
#endif
__OPENCL_STUB_DECLARE (clGetEventProfilingInfo, cl_int,
					   cl_event, cl_program_info,
					   size_t, void *, size_t *);
__OPENCL_STUB_DECLARE (clFlush, cl_int,
					   cl_command_queue);
__OPENCL_STUB_DECLARE (clFinish, cl_int,
					   cl_command_queue);
__OPENCL_STUB_DECLARE (clEnqueueReadBuffer, cl_int,
					   cl_command_queue, cl_mem,
					   cl_bool, size_t, size_t,
					   void *, cl_uint, const cl_event *, cl_event *);
#ifdef CL_VERSION_1_1
__OPENCL_STUB_DECLARE (clEnqueueReadBufferRect, cl_int,
					   cl_command_queue, cl_mem, cl_bool,
					   const size_t *, const size_t *, const size_t *,
					   size_t, size_t, size_t, size_t, void *,
					   cl_uint, const cl_event *, cl_event *);
#endif
__OPENCL_STUB_DECLARE (clEnqueueWriteBuffer, cl_int,
					   cl_command_queue, cl_mem, cl_bool,
					   size_t, size_t, const void *, cl_uint,
					   const cl_event *, cl_event *);
#ifdef CL_VERSION_1_1
__OPENCL_STUB_DECLARE (clEnqueueWriteBufferRect, cl_int,
					   cl_command_queue, cl_mem, cl_bool,
					   const size_t *, const size_t *, const size_t *,
					   size_t, size_t, size_t, size_t, const void *,
					   cl_uint, const cl_event *, cl_event *);
#endif
#ifdef CL_VERSION_1_2
__OPENCL_STUB_DECLARE (clEnqueueFillBuffer, cl_int,
					   cl_command_queue, cl_mem, const void *,
					   size_t, size_t, size_t,
					   cl_uint, const cl_event *, cl_event *);
#endif
__OPENCL_STUB_DECLARE (clEnqueueCopyBuffer, cl_int,
					   cl_command_queue, cl_mem, cl_mem,
					   size_t, size_t, size_t,
					   cl_uint, const cl_event *, cl_event *);
#ifdef CL_VERSION_1_1
__OPENCL_STUB_DECLARE (clEnqueueCopyBufferRect, cl_int,
					   cl_command_queue, cl_mem, cl_mem,
					   const size_t *, const size_t *, const size_t *,
					   size_t, size_t, size_t, size_t,
					   cl_uint, const cl_event *, cl_event *);
#endif
__OPENCL_STUB_DECLARE (clEnqueueReadImage, cl_int,
					   cl_command_queue, cl_mem, cl_bool,
					   const size_t *, const size_t *,
					   size_t, size_t, void *,
					   cl_uint, const cl_event *, cl_event *);
__OPENCL_STUB_DECLARE (clEnqueueWriteImage, cl_int,
					   cl_command_queue, cl_mem, cl_bool,
					   const size_t *, const size_t *,
					   size_t, size_t, const void *,
					   cl_uint, const cl_event *, cl_event *);
#ifdef CL_VERSION_1_2
__OPENCL_STUB_DECLARE (clEnqueueFillImage, cl_int,
					   cl_command_queue, cl_mem,
					   const void *, const size_t *, const size_t *,
					   cl_uint, const cl_event *, cl_event *);
#endif
__OPENCL_STUB_DECLARE (clEnqueueCopyImage, cl_int,
					   cl_command_queue, cl_mem, cl_mem,
					   const size_t *, const size_t *, const size_t *,
					   cl_uint, const cl_event *, cl_event *);
__OPENCL_STUB_DECLARE (clEnqueueCopyImageToBuffer, cl_int,
					   cl_command_queue, cl_mem, cl_mem,
					   const size_t *, const size_t *, size_t,
					   cl_uint, const cl_event *, cl_event *);
__OPENCL_STUB_DECLARE (clEnqueueCopyBufferToImage, cl_int,
					   cl_command_queue, cl_mem, cl_mem,
					   size_t, const size_t *, const size_t *,
					   cl_uint, const cl_event *, cl_event *);
__OPENCL_STUB_DECLARE (clEnqueueMapBuffer, void *,
					   cl_command_queue, cl_mem, cl_bool, cl_map_flags,
					   size_t, size_t,
					   cl_uint, const cl_event *, cl_event *, cl_int *);
__OPENCL_STUB_DECLARE (clEnqueueMapImage, void *,
					   cl_command_queue, cl_mem, cl_bool, cl_map_flags,
					   const size_t *, const size_t *, size_t *, size_t *,
					   cl_uint, const cl_event *, cl_event *, cl_int *);
__OPENCL_STUB_DECLARE (clEnqueueUnmapMemObject, cl_int,
					   cl_command_queue, cl_mem, void *,
					   cl_uint, const cl_event *, cl_event *);
#ifdef CL_VERSION_1_2
__OPENCL_STUB_DECLARE (clEnqueueMigrateMemObjects, cl_int,
					   cl_command_queue,
					   cl_uint, const cl_mem *, cl_mem_migration_flags,
					   cl_uint, const cl_event *, cl_event *);
#endif
__OPENCL_STUB_DECLARE (clEnqueueNDRangeKernel, cl_int,
					   cl_command_queue, cl_kernel, cl_uint,
					   const size_t *, const size_t *, const size_t *,
					   cl_uint, const cl_event *, cl_event *);
__OPENCL_STUB_DECLARE (clEnqueueNativeKernel, cl_int,
					   cl_command_queue,
					   void (CL_CALLBACK *)(void *),
					   void *, size_t, cl_uint, const cl_mem *, const void **,
					   cl_uint, const cl_event *, cl_event *);
#ifdef CL_VERSION_1_2
__OPENCL_STUB_DECLARE (clEnqueueMarkerWithWaitList, cl_int,
					   cl_command_queue,
					   cl_uint, const cl_event *, cl_event *);
__OPENCL_STUB_DECLARE (clEnqueueBarrierWithWaitList, cl_int,
					   cl_command_queue,
					   cl_uint, const cl_event *, cl_event *);
#endif
#ifdef CL_VERSION_2_0
__OPENCL_STUB_DECLARE (clEnqueueSVMFree, cl_int,
					   cl_command_queue, cl_uint, void *[],
					   void (CL_CALLBACK *)(cl_command_queue, cl_uint,
											void *, void *),
					   void *, cl_uint, const cl_event *, cl_event *);
__OPENCL_STUB_DECLARE (clEnqueueSVMMemcpy, cl_int,
					   cl_command_queue, cl_bool, void *,
					   const void *, size_t,
					   cl_uint, const cl_event *, cl_event *);
__OPENCL_STUB_DECLARE (clEnqueueSVMMemFill, cl_int,
					   cl_command_queue, void *,
					   const void *, size_t, size_t,
					   cl_uint, const cl_event *, cl_event *);
__OPENCL_STUB_DECLARE (clEnqueueSVMMap, cl_int,
					   cl_command_queue, cl_bool,
					   cl_map_flags, void *, size_t,
					   cl_uint, const cl_event *, cl_event *);
__OPENCL_STUB_DECLARE (clEnqueueSVMUnmap, cl_int,
					   cl_command_queue, void *,
					   cl_uint, const cl_event *, cl_event *);
__OPENCL_STUB_DECLARE (clEnqueueSVMMigrateMem, cl_int,
					   cl_command_queue, cl_uint,
					   const void *, const size_t *, cl_mem_migration_flags,
					   cl_uint, const cl_event *, cl_event *);
#endif
#ifdef CL_VERSION_1_2
__OPENCL_STUB_DECLARE (clGetExtensionFunctionAddressForPlatform, void *,
					   cl_platform_id, const char *);
#endif
#ifdef CL_USE_DEPRECATED_OPENCL_1_0_APIS
__OPENCL_STUB_DECLARE (clSetCommandQueueProperty, cl_int,
					   cl_command_queue, cl_command_queue_properties,
					   cl_bool, cl_command_queue_properties *);
#endif
__OPENCL_STUB_DECLARE (clCreateImage2D, cl_mem,
					   cl_context, cl_mem_flags, const cl_image_format *,
					   size_t, size_t, size_t, void *, cl_int *);
__OPENCL_STUB_DECLARE (clCreateImage3D, cl_mem,
					   cl_context, cl_mem_flags, const cl_image_format *,
					   size_t, size_t, size_t, size_t, size_t,
					   void *, cl_int *);
__OPENCL_STUB_DECLARE (clEnqueueMarker, cl_int,
					   cl_command_queue, cl_event *);
__OPENCL_STUB_DECLARE (clEnqueueWaitForEvents, cl_int,
					   cl_command_queue, cl_uint, const cl_event *);
__OPENCL_STUB_DECLARE (clEnqueueBarrier, cl_int,
					   cl_command_queue);
__OPENCL_STUB_DECLARE (clUnloadCompiler, cl_int,
					   void);
__OPENCL_STUB_DECLARE (clGetExtensionFunctionAddress, void *,
					   const char *);
__OPENCL_STUB_DECLARE (clCreateCommandQueue, cl_command_queue,
					   cl_context, cl_device_id,
					   cl_command_queue_properties, cl_int *);
__OPENCL_STUB_DECLARE (clCreateSampler, cl_sampler,
					   cl_context, cl_bool, cl_addressing_mode,
					   cl_filter_mode, cl_int *);
__OPENCL_STUB_DECLARE (clEnqueueTask, cl_int,
					   cl_command_queue, cl_kernel,
					   cl_uint, const cl_event *, cl_event *);
