#ifndef LIBOPENCL_STUB_H
#define LIBOPENCL_STUB_H

#include <CL/cl.h>
#include <CL/cl_gl.h>

#define __OPENCL_STUB_DECLARE(name, return, ...) \
	typedef return (*f_##name) (__VA_ARGS__); \
	extern f_##name s_##name;

typedef void (*f_pfn_notify)(const char *, const void *, size_t, void *);

__OPENCL_STUB_DECLARE (clGetPlatformIDs, cl_int,
					   cl_uint, cl_platform_id *, cl_uint *);
__OPENCL_STUB_DECLARE (clGetPlatformInfo, cl_int,
					   cl_platform_id, cl_platform_info, size_t, void *, size_t *);
__OPENCL_STUB_DECLARE (clGetDeviceIDs, cl_int,
					   cl_platform_id, cl_device_type, cl_uint, cl_device_id *, cl_uint *);
__OPENCL_STUB_DECLARE (clGetDeviceInfo, cl_int,
					   cl_device_id, cl_device_info, size_t, void *, size_t *);
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
					   cl_ulong *);
#endif
__OPENCL_STUB_DECLARE (clCreateContext, cl_context,
					   const cl_context_properties *, cl_uint, const cl_device_id *,
					   void (CL_CALLBACK *)(const char *, const void *, size_t, void *),
					   void *, cl_int *);
__OPENCL_STUB_DECLARE (clCreateContextFromType, cl_context,
					   const cl_context_properties *,
					   cl_device_type,
					   void (CL_CALLBACK *)(const char *, const void *, size_t, void *),
					   void *, cl_int *);
__OPENCL_STUB_DECLARE (clRetainContext, cl_int,
					   cl_context);
__OPENCL_STUB_DECLARE (clReleaseContext, cl_int,
					   cl_context);
__OPENCL_STUB_DECLARE (clGetContextInfo, cl_int,
					   cl_context, cl_context_info, size_t, void *, size_t *);
#ifdef CL_VERSION_3_0
__OPENCL_STUB_DECLARE (clSetContextDestructorCallback, cl_int,
					   cl_context,
					   void (CL_CALLBACK *)(cl_context, void *),
					   void *);
#endif
#ifdef CL_VERSION_2_0
__OPENCL_STUB_DECLARE (clCreateCommandQueueWithProperties, cl_command_queue,
					   cl_context, cl_device_id, const cl_queue_properties *, cl_int *);
#endif
__OPENCL_STUB_DECLARE (clRetainCommandQueue, cl_int,
					   cl_command_queue);
__OPENCL_STUB_DECLARE (clReleaseCommandQueue, cl_int,
					   cl_command_queue);
__OPENCL_STUB_DECLARE (clGetCommandQueueInfo, cl_int,
					   cl_command_queue, cl_command_queue_info,
					   size_t, void *, size_t *);
__OPENCL_STUB_DECLARE (clCreateBuffer, cl_mem,
					   cl_context, cl_mem_flags, size_t, void *, cl_int *);
#ifdef CL_VERSION_1_1
__OPENCL_STUB_DECLARE (clCreateSubBuffer, cl_mem,
					   cl_mem, cl_mem_flags, cl_buffer_create_type,
					   const void *, cl_int *);
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
					   cl_context, const cl_sampler_properties *, cl_int *);
#endif
__OPENCL_STUB_DECLARE (clRetainSampler, cl_int,
					   cl_sampler);
__OPENCL_STUB_DECLARE (clReleaseSampler, cl_int,
					   cl_sampler);
__OPENCL_STUB_DECLARE (clGetSamplerInfo, cl_int,
					   cl_sampler, cl_sampler_info,
					   size_t, void *, size_t *);
__OPENCL_STUB_DECLARE (clCreateProgramWithSource, cl_program,
					   cl_context, cl_uint, const char **, const size_t *, cl_int *);
__OPENCL_STUB_DECLARE (clCreateProgramWithBinary, cl_program,
					   cl_context, cl_uint, const cl_device_id *,
					   const size_t *, const unsigned char **, cl_int *, cl_int *);
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
					   cl_program, cl_uint, const cl_device_id *, const char *,
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
					   cl_program, cl_program_info, size_t, void *, size_t *);
__OPENCL_STUB_DECLARE (clGetProgramBuildInfo, cl_int,
					   cl_program, cl_device_id, cl_program_build_info,
					   size_t, void *, size_t *);
__OPENCL_STUB_DECLARE (clCreateKernel, cl_kernel,
					   cl_program, const char *, cl_int *);
__OPENCL_STUB_DECLARE (clCreateKernelsInProgram, cl_int,
					   cl_program, cl_uint, cl_kernel *, cl_uint *);
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
					   cl_kernel, cl_kernel_exec_info, size_t, const void *);
#endif
__OPENCL_STUB_DECLARE (clGetKernelInfo, cl_int,
					   cl_kernel, cl_kernel_info, size_t, void *, size_t *);
#ifdef CL_VERSION_1_2
__OPENCL_STUB_DECLARE (clGetKernelArgInfo, cl_int,
					   cl_kernel, cl_uint, cl_kernel_arg_info,
					   size_t, void *, size_t *);
#endif

typedef cl_command_queue (*f_clCreateCommandQueue) (cl_context, cl_device_id, cl_command_queue_properties, cl_int *);

typedef cl_int (*f_clRetainCommandQueue) (cl_command_queue);

typedef cl_int (*f_clReleaseCommandQueue) (cl_command_queue);

typedef cl_int (*f_clGetCommandQueueInfo) (cl_command_queue, cl_command_queue_info, size_t, void *, size_t *);

typedef cl_mem (*f_clCreateSubBuffer) (cl_mem, cl_mem_flags, cl_buffer_create_type, const void *, cl_int *);

typedef cl_mem (*f_clCreateImage) (cl_context, cl_mem_flags, const cl_image_format *, const cl_image_desc *, void *, cl_int *);

typedef cl_int (*f_clRetainMemObject) (cl_mem);

typedef cl_int (*f_clReleaseMemObject) (cl_mem);

typedef cl_int (*f_clGetMemObjectInfo) (cl_mem, cl_mem_info, size_t, void *, size_t *);

typedef cl_int (*f_clGetImageInfo) (cl_mem, cl_image_info, size_t, void *, size_t *);

typedef cl_int (*f_clSetMemObjectDestructorCallback) (cl_mem, void (*pfn_notify)( cl_mem memobj, void* user_data), void *);

typedef cl_int (*f_clGetSupportedImageFormats) (cl_context, cl_mem_flags, cl_mem_object_type, cl_uint, cl_image_format *, cl_uint *);

typedef cl_sampler (*f_clCreateSampler) (cl_context, cl_bool, cl_addressing_mode, cl_filter_mode, cl_int *);

typedef cl_int (*f_clRetainSampler) (cl_sampler);

typedef cl_int (*f_clReleaseSampler) (cl_sampler);

typedef cl_int (*f_clGetSamplerInfo) (cl_sampler, cl_sampler_info, size_t, void *, size_t *);

typedef cl_program (*f_clCreateProgramWithSource) (cl_context, cl_uint, const char **, const size_t *, cl_int *);

typedef cl_program (*f_clCreateProgramWithBuiltInKernels) (cl_context, cl_uint, const cl_device_id *, const char *, cl_int *);

typedef cl_int (*f_clRetainProgram) (cl_program);

typedef cl_int (*f_clReleaseProgram) (cl_program);

typedef cl_int (*f_clBuildProgram) (cl_program, cl_uint, const cl_device_id *, const char *, 
        void (*pfn_notify)(cl_program program, void * user_data), void *);

typedef cl_int (*f_clCompileProgram) (cl_program, cl_uint, const cl_device_id *, const char *, cl_uint, const cl_program *,
        const char **, void (*pfn_notify)(cl_program program, void * user_data), void *);

typedef cl_program (*f_clLinkProgram) (cl_context, cl_uint, const cl_device_id *, const char *, cl_uint, const cl_program *,
                    void (*pfn_notify)(cl_program program, void * user_data), void *, cl_int *);

typedef cl_int (*f_clUnloadPlatformCompiler)(cl_platform_id);

typedef cl_int (*f_clGetProgramInfo) (cl_program, cl_program_info, size_t, void *, size_t *);

typedef cl_int (*f_clGetProgramBuildInfo) (cl_program, cl_device_id, cl_program_build_info, size_t, void *, size_t *);

typedef cl_kernel (*f_clCreateKernel) (cl_program, const char *, cl_int *);

typedef cl_int (*f_clCreateKernelsInProgram) (cl_program, cl_uint, cl_kernel *, cl_uint *);

typedef cl_int (*f_clRetainKernel) (cl_kernel);

typedef cl_int (*f_clReleaseKernel) (cl_kernel);

typedef cl_int (*f_clSetKernelArg) (cl_kernel, cl_uint, size_t,const void *);

typedef cl_int (*f_clGetKernelInfo) (cl_kernel, cl_kernel_info, size_t, void *, size_t *);

typedef cl_int (*f_clGetKernelArgInfo) (cl_kernel, cl_uint, cl_kernel_arg_info, size_t, void *, size_t *);

typedef cl_int (*f_clGetKernelWorkGroupInfo) (cl_kernel, cl_device_id, cl_kernel_work_group_info, size_t, void *, size_t *);

typedef cl_int (*f_clWaitForEvents) (cl_uint, const cl_event *);

typedef cl_int (*f_clGetEventInfo) (cl_event, cl_event_info, size_t, void *, size_t *);

typedef cl_event (*f_clCreateUserEvent) (cl_context, cl_int *);

typedef cl_int (*f_clRetainEvent) (cl_event);

typedef cl_int (*f_clReleaseEvent) (cl_event);

typedef cl_int (*f_clSetUserEventStatus) (cl_event, cl_int);

typedef cl_int (*f_clSetEventCallback) (cl_event, cl_int, void (*pfn_notify)(cl_event, cl_int, void *), void *);

typedef cl_int (*f_clGetEventProfilingInfo) (cl_event, cl_profiling_info, size_t, void *, size_t *);

typedef cl_int (*f_clFlush) (cl_command_queue);

typedef cl_int (*f_clFinish) (cl_command_queue);

typedef cl_int (*f_clEnqueueReadBuffer) (cl_command_queue, cl_mem, cl_bool, size_t, size_t, void *, cl_uint, const cl_event *, cl_event *);

typedef cl_int (*f_clEnqueueReadBufferRect) (cl_command_queue, cl_mem, cl_bool, const size_t *, const size_t *, const size_t *,
                            size_t, size_t, size_t, size_t, void *, cl_uint, const cl_event *, cl_event *);

typedef cl_int (*f_clEnqueueWriteBuffer) (cl_command_queue, cl_mem, cl_bool, size_t, size_t, const void *, cl_uint, const cl_event *, cl_event *);

typedef cl_int (*f_clEnqueueWriteBufferRect) (cl_command_queue, cl_mem, cl_bool, const size_t *, const size_t *, const size_t *,
                            size_t, size_t, size_t, size_t, const void *, cl_uint, const cl_event *, cl_event *);

typedef cl_int (*f_clEnqueueFillBuffer) (cl_command_queue, cl_mem, const void *, size_t, size_t, size_t, cl_uint, const cl_event *, cl_event *);

typedef cl_int (*f_clEnqueueCopyBuffer) (cl_command_queue, cl_mem, cl_mem, size_t, size_t, size_t, cl_uint, const cl_event *, cl_event *);

typedef cl_int (*f_clEnqueueCopyBufferRect) (cl_command_queue, cl_mem, cl_mem, const size_t *, const size_t *, const size_t *,
                            size_t, size_t, size_t, size_t, cl_uint, const cl_event *, cl_event *);

typedef cl_int (*f_clEnqueueReadImage) (cl_command_queue, cl_mem, cl_bool, const size_t *, const size_t *,
							size_t, size_t, void *, cl_uint, const cl_event *, cl_event *);

typedef cl_int (*f_clEnqueueWriteImage) (cl_command_queue, cl_mem, cl_bool, const size_t *, const size_t *,
							size_t, size_t, const void *, cl_uint, const cl_event *, cl_event *);

typedef cl_int (*f_clEnqueueFillImage) (cl_command_queue, cl_mem, const void *, const size_t *, const size_t *, cl_uint, const cl_event *, cl_event *);

typedef cl_int (*f_clEnqueueCopyImage) (cl_command_queue, cl_mem, cl_mem, const size_t *, const size_t *, const size_t *,
          cl_uint, const cl_event *, cl_event *);

typedef cl_int (*f_clEnqueueCopyImageToBuffer) (cl_command_queue, cl_mem, cl_mem, const size_t *, const size_t *, size_t, cl_uint, const cl_event *, cl_event *);

typedef cl_int (*f_clEnqueueCopyBufferToImage) (cl_command_queue, cl_mem, cl_mem, size_t, const size_t *, const size_t *, cl_uint, const cl_event *, cl_event *);

typedef void * (*f_clEnqueueMapBuffer) (cl_command_queue, cl_mem, cl_bool, cl_map_flags, size_t,
						size_t, cl_uint, const cl_event *, cl_event *, cl_int *);

typedef void * (*f_clEnqueueMapImage) (cl_command_queue, cl_mem, cl_bool, cl_map_flags, const size_t *, const size_t *,
                  size_t *, size_t *, cl_uint, const cl_event *, cl_event *, cl_int *);

typedef cl_int (*f_clEnqueueUnmapMemObject) (cl_command_queue, cl_mem, void *, cl_uint, const cl_event *, cl_event *);

typedef cl_int (*f_clEnqueueMigrateMemObjects)(cl_command_queue, cl_uint, const cl_mem *, cl_mem_migration_flags,
						cl_uint, const cl_event *, cl_event *);

typedef cl_int (*f_clEnqueueNDRangeKernel)(cl_command_queue, cl_kernel, cl_uint, const size_t *, const size_t *,
                       const size_t *, cl_uint, const cl_event *, cl_event *);

typedef cl_int (*f_clEnqueueTask)(cl_command_queue, cl_kernel, cl_uint, const cl_event *, cl_event *);

typedef cl_int (*f_clEnqueueNativeKernel)(cl_command_queue, void (*user_func)(void *),  void *, size_t,
                      cl_uint, const cl_mem *, const void **, cl_uint, const cl_event *, cl_event *);

typedef cl_int (*f_clEnqueueMarkerWithWaitList)(cl_command_queue, cl_uint, const cl_event *, cl_event *);

typedef cl_int (*f_clEnqueueBarrierWithWaitList)(cl_command_queue, cl_uint, const cl_event *, cl_event *);

typedef void * (*f_clGetExtensionFunctionAddressForPlatform)(cl_platform_id, const char *);

typedef cl_mem (*f_clCreateImage2D)(cl_context, cl_mem_flags,const cl_image_format *, size_t, size_t,
                				size_t, void *, cl_int *);

typedef cl_mem (*f_clCreateImage3D)(cl_context, cl_mem_flags, const cl_image_format *, size_t,
                		size_t, size_t, size_t, size_t, void *, cl_int *);

typedef cl_int (*f_clEnqueueMarker)(cl_command_queue, cl_event *);

typedef cl_int(*f_clEnqueueWaitForEvents)(cl_command_queue, cl_uint, const cl_event *);

typedef cl_int (*f_clEnqueueBarrier)(cl_command_queue);

typedef cl_int (*f_clUnloadCompiler)(void);

typedef void * (*f_clGetExtensionFunctionAddress)(const char *);

typedef cl_mem (*f_clCreateFromGLBuffer) (cl_context, cl_mem_flags, cl_GLuint, int *);

typedef cl_mem (*f_clCreateFromGLTexture) (cl_context, cl_mem_flags, cl_GLenum, cl_GLint, cl_GLuint, cl_int *);

typedef cl_mem (*f_clCreateFromGLRenderbuffer) (cl_context, cl_mem_flags, cl_GLuint, cl_int *);

typedef cl_int (*f_clGetGLObjectInfo) (cl_mem memobj, cl_gl_object_type *, cl_GLuint *);

typedef cl_int (*f_clGetGLTextureInfo) (cl_mem, cl_gl_texture_info, size_t, void *, size_t *);

typedef cl_int (*f_clEnqueueAcquireGLObjects) (cl_command_queue, cl_uint, const cl_mem *, cl_uint,
                                        const cl_event *, cl_event *);

typedef cl_int (*f_clEnqueueReleaseGLObjects) (cl_command_queue, cl_uint, const cl_mem *, cl_uint,
                                        const cl_event *, cl_event *);

typedef cl_mem (*f_clCreateFromGLTexture2D) (cl_context, cl_mem_flags, cl_GLenum, cl_GLint, cl_GLuint, cl_int *);

typedef cl_mem (*f_clCreateFromGLTexture3D) (cl_context, cl_mem_flags, cl_GLenum, cl_GLint, cl_GLuint, cl_int *);

typedef cl_int (*f_clGetGLContextInfoKHR) (const cl_context_properties *, cl_gl_context_info, size_t,
                                        void *, size_t *);

int opencl_stub_load(const char *path);

// Additional api to reset currently opened opencl shared-object
// Subsequent calls will use newly set environment variables
void stubOpenclReset();

#endif    // LIBOPENCL_STUB_H
