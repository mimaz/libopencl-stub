/*
 * OpenCL stub library
 * Copyright (c) 2020 Mieszko Mazurek <mimaz@gmx.com>
 *
 * Original author: Krishnaraj Bhat (krrishnarraj)
 */

#define CL_TARGET_OPENCL_VERSION 300
#define CL_USE_DEPRECATED_OPENCL_1_0_APIS 1
#include "opencl-stub.h"

#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <dlfcn.h>

#if defined(__APPLE__) || defined(__MACOSX)
static const char *default_so_paths[] = {
	"libOpenCL.so",
	"/System/Library/Frameworks/OpenCL.framework/OpenCL"
};
#elif defined(__ANDROID__)
static const char *default_so_paths[] = {
	"/vendor/lib64/libOpenCL.so",
	"/vendor/lib/libOpenCL.so",
	"/system/lib64/libOpenCL.so",
	"/system/lib/libOpenCL.so",
	"/system/vendor/lib64/libOpenCL.so",
	"/system/vendor/lib/libOpenCL.so",
	"/system/vendor/lib/egl/libGLES_mali.so",
	"/system/vendor/lib/libPVROCL.so",
	"/data/data/org.pocl.libs/files/lib/libpocl.so",
	"libOpenCL.so"
};
#elif defined(_WIN32)
static const char *default_so_paths[] = {
	"OpenCL.dll"
};
#elif defined(__linux__)
static const char *default_so_paths[] = {
	"/usr/lib/x86_64-linux-gnu/libOpenCL.so",
	"/usr/lib/libOpenCL.so",
	"/usr/local/lib/libOpenCL.so",
	"/usr/local/lib/libpocl.so",
	"/usr/lib64/libOpenCL.so",
	"/usr/lib32/libOpenCL.so",
};
#endif

struct stub_desc
{
	struct stub_desc *next;
	const char *fname;
	void *fdefault;
	void **fpointer;
	int api_level;
};

static void *so_handle;
static struct stub_desc *root_desc;

static int
access_file(const char *filename)
{
  struct stat buffer;

  return (stat (filename, &buffer) == 0);
}

static const char *
get_path ()
{
	const char *path;
	int i;

	path = getenv ("OPENCL_STUB_PATH");

	printf ("path: %s\n", path);
	if (access_file (path)) {
		return path;
	}

	printf ("no access\n");

	for (i = 0; i < sizeof (default_so_paths) / sizeof (char *); i++) {
		if (access_file (default_so_paths[i])) {
			return default_so_paths[i];
		}
	}

	return NULL;
}

static int
open_libopencl_so()
{
	const char *path;

	path = get_path ();

	if (path) {
		so_handle = dlopen (path, RTLD_LAZY);
		printf ("loaded %s: %p\n", path, so_handle);
		return 0;
	} else {
		return -1;
	}
}

static int
load_symbols (int api_level)
{
	struct stub_desc *desc;
	void *sym;

	if (api_level < 0) {
		api_level = 300;
	}

	desc = root_desc;

	printf ("so handle %p\n", so_handle);

	while (desc != NULL) {
		if (api_level >= desc->api_level) {
			sym = dlsym (so_handle, desc->fname);
		} else {
			sym = NULL;
		}

		printf ("sym %p %s: %p\n", so_handle, desc->fname, sym);

		if (sym == NULL) {
			sym = desc->fdefault;
		}

		*desc->fpointer = sym;

		desc = desc->next;
	}

	return 0;
}

static int
opencl_stub_load_default ()
{
	if (open_libopencl_so () == 0) {
		return load_symbols (-1);
	}

	return -1;
}

#define __OPENCL_STUB_DEFINE_FULL(name, \
								  global_name, \
								  api_level, \
								  return_type, \
								  default_expr, \
								  arg_names, ...) \
	static return_type \
	d_##name (__VA_ARGS__) \
	{ \
		default_expr; \
	} \
	f_##name s_##name = d_##name; \
	static void init_##name (void) __attribute__((constructor)); \
	static struct stub_desc desc_##name; \
	static void \
	init_##name (void) \
	{ \
		desc_##name.next = root_desc; \
		desc_##name.fname = #name; \
		desc_##name.fdefault = (void *) d_##name; \
		desc_##name.fpointer = (void *) &s_##name; \
		root_desc = &desc_##name; \
	} \
	return_type \
	global_name (__VA_ARGS__) \
	{ \
		return s_##name arg_names; \
	}

#define __OPENCL_STUB_DEFINE(name, \
							 api_level, \
							 return_type, \
							 default_expr, \
							 arg_names, ...) \
	__OPENCL_STUB_DEFINE_FULL(name, \
							  name, \
							  api_level, \
							  return_type, \
							  default_expr, \
							  arg_names, __VA_ARGS__)

static cl_int wrapped_clGetPlatformIDs (cl_uint num_entries,
										cl_platform_id *platforms,
										cl_uint *num_platforms);

cl_int
clGetPlatformIDs (cl_uint num_entries,
				  cl_platform_id *platforms,
				  cl_uint *num_platforms)
{
	opencl_stub_load_default ();

	return wrapped_clGetPlatformIDs (num_entries, platforms, num_platforms);
}

__OPENCL_STUB_DEFINE_FULL (clGetPlatformIDs,
						   static wrapped_clGetPlatformIDs,
						   100, cl_int,
						   return CL_INVALID_PLATFORM,
						   (num_entries, platforms, num_platforms),
						   cl_uint num_entries,
						   cl_platform_id *platforms,
						   cl_uint *num_platforms);
__OPENCL_STUB_DEFINE (clGetPlatformInfo, 100, cl_int,
					  return CL_INVALID_PLATFORM,
					  (platform, param_name, param_value_size,
					   param_value, param_value_size_ret),
					  cl_platform_id platform,
					  cl_platform_info param_name,
					  size_t param_value_size,
					  void *param_value,
					  size_t *param_value_size_ret);
__OPENCL_STUB_DEFINE (clGetDeviceIDs, 100, cl_int,
					  return CL_INVALID_PLATFORM,
					  (platform, device, num_entries,
					   devices, num_devices),
					  cl_platform_id platform,
					  cl_device_type device,
					  cl_uint num_entries,
					  cl_device_id *devices,
					  cl_uint *num_devices);
__OPENCL_STUB_DEFINE (clGetDeviceInfo, 100, cl_int,
					  return CL_INVALID_PLATFORM,
					  (device, param_name, param_value_size,
					   param_value, param_value_size_ret),
					  cl_device_id device,
					  cl_device_info param_name,
					  size_t param_value_size,
					  void *param_value,
					  size_t *param_value_size_ret);
__OPENCL_STUB_DEFINE (clCreateSubDevices, 120, cl_int,
					  return CL_INVALID_PLATFORM,
					  (in_device, properties, num_devices,
					   out_devices, num_devices_ret),
					  cl_device_id in_device,
					  const cl_device_partition_property *properties,
					  cl_uint num_devices,
					  cl_device_id *out_devices,
					  cl_uint *num_devices_ret);
__OPENCL_STUB_DEFINE (clRetainDevice, 120, cl_int,
					  return CL_INVALID_PLATFORM,
					  (device),
					  cl_device_id device);
__OPENCL_STUB_DEFINE (clReleaseDevice, 120, cl_int,
					  return CL_INVALID_PLATFORM,
					  (device),
					  cl_device_id device);
__OPENCL_STUB_DEFINE (clSetDefaultDeviceCommandQueue, 210, cl_int,
					  return CL_INVALID_PLATFORM,
					  (context, device, command_queue),
					  cl_context context,
					  cl_device_id device,
					  cl_command_queue command_queue);
__OPENCL_STUB_DEFINE (clGetDeviceAndHostTimer, 210, cl_int,
					  return CL_INVALID_PLATFORM,
					  (device, device_timestamp, host_timestamp),
					  cl_device_id device,
					  cl_ulong *device_timestamp,
					  cl_ulong *host_timestamp);
__OPENCL_STUB_DEFINE (clGetHostTimer, 210, cl_int,
					  return CL_INVALID_PLATFORM,
					  (device, host_timestamp),
					  cl_device_id device,
					  cl_ulong *host_timestamp);
__OPENCL_STUB_DEFINE (clCreateContext, 100, cl_context,
					  *errcode_ret = CL_INVALID_PLATFORM; return NULL,
					  (properties, num_devices, devices, pfn_notify,
					   user_data, errcode_ret),
					  const cl_context_properties *properties,
					  cl_uint num_devices,
					  const cl_device_id *devices,
					  void (CL_CALLBACK *pfn_notify)(const char *,
													 const void *,
													 size_t,
													 void *),
					  void *user_data,
					  cl_int *errcode_ret);
__OPENCL_STUB_DEFINE (clCreateContextFromType, 100, cl_context,
					  *errcode_ret = CL_INVALID_PLATFORM; return NULL,
					  (properties, device_type, pfn_notify,
					   user_data, errcode_ret),
					  const cl_context_properties *properties,
					  cl_device_type device_type,
					  void (CL_CALLBACK *pfn_notify)(const char *,
													 const void *,
													 size_t,
													 void *),
					  void *user_data,
					  cl_int *errcode_ret);
__OPENCL_STUB_DEFINE (clRetainContext, 100, cl_int,
					  return CL_INVALID_PLATFORM,
					  (context),
					  cl_context context);
__OPENCL_STUB_DEFINE (clReleaseContext, 100, cl_int,
					  return CL_INVALID_PLATFORM,
					  (context),
					  cl_context context);
__OPENCL_STUB_DEFINE (clGetContextInfo, 100, cl_int,
					  return CL_INVALID_PLATFORM,
					  (context, param_name, param_value_size,
					   param_value, param_value_size_ret),
					  cl_context context,
					  cl_context_info param_name,
					  size_t param_value_size,
					  void *param_value,
					  size_t *param_value_size_ret);
__OPENCL_STUB_DEFINE (clSetContextDestructorCallback, 300, cl_int,
					  return CL_INVALID_PLATFORM,
					  (context, pfn_notify, user_data),
					  cl_context context,
					  void (CL_CALLBACK *pfn_notify)(cl_context,
													 void *),
					  void *user_data);
__OPENCL_STUB_DEFINE (clCreateCommandQueueWithProperties, 200, cl_command_queue,
					  *errcode_ret = CL_INVALID_PLATFORM; return NULL,
					  (context, device, properties, errcode_ret),
					  cl_context context,
					  cl_device_id device,
					  const cl_queue_properties *properties,
					  cl_int *errcode_ret);
__OPENCL_STUB_DEFINE (clRetainCommandQueue, 100, cl_int,
					  return CL_INVALID_PLATFORM,
					  (command_queue),
					  cl_command_queue command_queue);
__OPENCL_STUB_DEFINE (clReleaseCommandQueue, 100, cl_int,
					  return CL_INVALID_PLATFORM,
					  (command_queue),
					  cl_command_queue command_queue);
__OPENCL_STUB_DEFINE (clGetCommandQueueInfo, 100, cl_int,
					  return CL_INVALID_PLATFORM,
					  (command_queue, param_name, param_value_size,
					   param_value, param_value_size_ret),
					  cl_command_queue command_queue,
					  cl_command_queue_info param_name,
					  size_t param_value_size,
					  void *param_value,
					  size_t *param_value_size_ret);
__OPENCL_STUB_DEFINE (clCreateBuffer, 100, cl_mem,
					  *errcode_ret = CL_INVALID_PLATFORM; return NULL,
					  (context, flags, size, host_ptr, errcode_ret),
					  cl_context context,
					  cl_mem_flags flags,
					  size_t size,
					  void *host_ptr,
					  cl_int *errcode_ret);
__OPENCL_STUB_DEFINE (clCreateSubBuffer, 110, cl_mem,
					  *errcode_ret = CL_INVALID_PLATFORM; return NULL,
					  (buffer, flags, buffer_create_type,
					   buffer_create_info, errcode_ret),
					  cl_mem buffer,
					  cl_mem_flags flags,
					  cl_buffer_create_type buffer_create_type,
					  const void *buffer_create_info,
					  cl_int *errcode_ret);
__OPENCL_STUB_DEFINE (clCreateImage, 120, cl_mem,
					  *errcode_ret = CL_INVALID_PLATFORM; return NULL,
					  (context, flags, image_format, image_desc,
					   host_ptr, errcode_ret),
					  cl_context context,
					  cl_mem_flags flags,
					  const cl_image_format *image_format,
					  const cl_image_desc *image_desc,
					  void *host_ptr,
					  cl_int *errcode_ret);
__OPENCL_STUB_DEFINE (clCreatePipe, 200, cl_mem,
					  *errcode_ret = CL_INVALID_PLATFORM; return NULL,
					  (context, flags, pipe_packet_size,
					   pipe_max_packets, properties, errcode_ret),
					  cl_context context,
					  cl_mem_flags flags,
					  cl_uint pipe_packet_size,
					  cl_uint pipe_max_packets,
					  const cl_pipe_properties *properties,
					  cl_int *errcode_ret);
__OPENCL_STUB_DEFINE (clCreateBufferWithProperties, 300, cl_mem,
					  *errcode_ret = CL_INVALID_PLATFORM; return NULL,
					  (context, properties, flags,
					   size, host_ptr, errcode_ret),
					  cl_context context,
					  const cl_mem_properties *properties,
					  cl_mem_flags flags,
					  size_t size,
					  void *host_ptr,
					  cl_int *errcode_ret);
__OPENCL_STUB_DEFINE (clCreateImageWithProperties, 300, cl_mem,
					  *errcode_ret = CL_INVALID_PLATFORM; return NULL,
					  (context, properties, flags, image_format,
					   image_desc, host_ptr, errcode_ret),
					  cl_context context,
					  const cl_mem_properties *properties,
					  cl_mem_flags flags,
					  const cl_image_format *image_format,
					  const cl_image_desc *image_desc,
					  void *host_ptr,
					  cl_int *errcode_ret);
__OPENCL_STUB_DEFINE (clRetainMemObject, 100, cl_int,
					  return CL_INVALID_PLATFORM,
					  (memobj),
					  cl_mem memobj);
__OPENCL_STUB_DEFINE (clReleaseMemObject, 100, cl_int,
					  return CL_INVALID_PLATFORM,
					  (memobj),
					  cl_mem memobj);
__OPENCL_STUB_DEFINE (clGetSupportedImageFormats, 100, cl_int,
					  return CL_INVALID_PLATFORM,
					  (context, flags, image_type,
					   num_entries, image_formats, num_image_formats),
					  cl_context context,
					  cl_mem_flags flags,
					  cl_mem_object_type image_type,
					  cl_uint num_entries,
					  cl_image_format *image_formats,
					  cl_uint *num_image_formats);
__OPENCL_STUB_DEFINE (clGetMemObjectInfo, 100, cl_int,
					  return CL_INVALID_PLATFORM,
					  (memobj, param_name, param_value_size,
					   param_value, param_value_size_ret),
					  cl_mem memobj,
					  cl_mem_info param_name,
					  size_t param_value_size,
					  void *param_value,
					  size_t *param_value_size_ret);
__OPENCL_STUB_DEFINE (clGetImageInfo, 100, cl_int,
					  return CL_INVALID_PLATFORM,
					  (image, param_name, param_value_size,
					   param_value, param_value_size_ret),
					  cl_mem image,
					  cl_image_info param_name,
					  size_t param_value_size,
					  void *param_value,
					  size_t *param_value_size_ret);
__OPENCL_STUB_DEFINE (clGetPipeInfo, 200, cl_int,
					  return CL_INVALID_PLATFORM,
					  (pipe, param_name, param_value_size,
					   param_value, param_value_size_ret),
					  cl_mem pipe,
					  cl_pipe_info param_name,
					  size_t param_value_size,
					  void *param_value,
					  size_t *param_value_size_ret);
__OPENCL_STUB_DEFINE (clSetMemObjectDestructorCallback, 110, cl_int,
					  return CL_INVALID_PLATFORM,
					  (memobj, pfn_notify, user_data),
					  cl_mem memobj,
					  void (CL_CALLBACK *pfn_notify)(cl_mem,
													 void *),
					  void *user_data);
__OPENCL_STUB_DEFINE (clSVMAlloc, 200, void *,
					  return NULL,
					  (context, flags, size, alignment),
					  cl_context context,
					  cl_svm_mem_flags flags,
					  size_t size,
					  cl_uint alignment);
__OPENCL_STUB_DEFINE (clSVMFree, 200, void,
					  (void) NULL,
					  (context, svm_pointer),
					  cl_context context,
					  void *svm_pointer);
__OPENCL_STUB_DEFINE (clCreateSamplerWithProperties, 200, cl_sampler,
					  *errcode_ret = CL_INVALID_PLATFORM; return NULL,
					  (context, sampler_properties, errcode_ret),
					  cl_context context,
					  const cl_sampler_properties *sampler_properties,
					  cl_int *errcode_ret);
__OPENCL_STUB_DEFINE (clRetainSampler, 100, cl_int,
					  return CL_INVALID_PLATFORM,
					  (sampler),
					  cl_sampler sampler);
__OPENCL_STUB_DEFINE (clReleaseSampler, 100, cl_int,
					  return CL_INVALID_PLATFORM,
					  (sampler),
					  cl_sampler sampler);
__OPENCL_STUB_DEFINE (clGetSamplerInfo, 100, cl_int,
					  return CL_INVALID_PLATFORM,
					  (sampler, param_name, param_value_size,
					   param_value, param_value_size_ret),
					  cl_sampler sampler,
					  cl_sampler_info param_name,
					  size_t param_value_size,
					  void *param_value,
					  size_t *param_value_size_ret);
__OPENCL_STUB_DEFINE (clCreateProgramWithSource, 100, cl_program,
					  *errcode_ret = CL_INVALID_PLATFORM; return NULL,
					  (context, count, strings, lengths, errcode_ret),
					  cl_context context,
					  cl_uint count,
					  const char **strings,
					  const size_t *lengths,
					  cl_int *errcode_ret);
__OPENCL_STUB_DEFINE (clCreateProgramWithBinary, 100, cl_program,
					  *errcode_ret = CL_INVALID_PLATFORM; return NULL,
					  (context, num_devices, device_list, lengths,
					   binaries, binary_status, errcode_ret),
					  cl_context context,
					  cl_uint num_devices,
					  const cl_device_id *device_list,
					  const size_t *lengths,
					  const unsigned char **binaries,
					  cl_int *binary_status,
					  cl_int *errcode_ret);
__OPENCL_STUB_DEFINE (clCreateProgramWithBuiltInKernels, 120, cl_program,
					  *errcode_ret = CL_INVALID_PLATFORM; return NULL,
					  (context, num_devices, device_list,
					   kernel_names, errcode_ret),
					  cl_context context,
					  cl_uint num_devices,
					  const cl_device_id *device_list,
					  const char *kernel_names,
					  cl_int *errcode_ret);
__OPENCL_STUB_DEFINE (clCreateProgramWithIL, 210, cl_program,
					  *errcode_ret = CL_INVALID_PLATFORM; return NULL,
					  (context, il, length, errcode_ret),
					  cl_context context,
					  const void *il,
					  size_t length,
					  cl_int *errcode_ret);
__OPENCL_STUB_DEFINE (clRetainProgram, 100, cl_int,
					  return CL_INVALID_PLATFORM,
					  (program),
					  cl_program program);
__OPENCL_STUB_DEFINE (clReleaseProgram, 100, cl_int,
					  return CL_INVALID_PLATFORM,
					  (program),
					  cl_program program);
__OPENCL_STUB_DEFINE (clBuildProgram, 100, cl_int,
					  return CL_INVALID_PLATFORM,
					  (program, num_devices, device_list,
					   options, pfn_notify, user_data),
					  cl_program program,
					  cl_uint num_devices,
					  const cl_device_id *device_list,
					  const char *options,
					  void (CL_CALLBACK *pfn_notify)(cl_program,
													 void *),
					  void *user_data);
__OPENCL_STUB_DEFINE (clCompileProgram, 120, cl_int,
					  return CL_INVALID_PLATFORM,
					  (program, num_devices, device_list,
					   options, num_input_headers, input_headers,
					   header_include_names, pfn_notify, user_data),
					  cl_program program,
					  cl_uint num_devices,
					  const cl_device_id *device_list,
					  const char *options,
					  cl_uint num_input_headers,
					  const cl_program *input_headers,
					  const char **header_include_names,
					  void (CL_CALLBACK *pfn_notify)(cl_program,
													 void *),
					  void *user_data);
__OPENCL_STUB_DEFINE (clLinkProgram, 120, cl_program,
					  *errcode_ret = CL_INVALID_PLATFORM; return NULL,
					  (context, num_devices, device_list,
					   options, num_input_programs, input_programs,
					   pfn_notify, user_data, errcode_ret),
					  cl_context context,
					  cl_uint num_devices,
					  const cl_device_id *device_list,
					  const char *options,
					  cl_uint num_input_programs,
					  const cl_program *input_programs,
					  void (CL_CALLBACK *pfn_notify)(cl_program,
													 void *),
					  void *user_data,
					  cl_int *errcode_ret);
__OPENCL_STUB_DEFINE (clSetProgramReleaseCallback, 220, cl_int,
					  return CL_INVALID_PLATFORM,
					  (program, pfn_notify, user_data),
					  cl_program program,
					  void (CL_CALLBACK *pfn_notify)(cl_program,
													 void *),
					  void *user_data);
__OPENCL_STUB_DEFINE (clSetProgramSpecializationConstant, 220, cl_int,
					  return CL_INVALID_PLATFORM,
					  (program, spec_id, spec_size, spec_value),
					  cl_program program,
					  cl_uint spec_id,
					  size_t spec_size,
					  const void *spec_value);
__OPENCL_STUB_DEFINE (clUnloadPlatformCompiler, 120, cl_int,
					  return CL_INVALID_PLATFORM,
					  (platform),
					  cl_platform_id platform);
__OPENCL_STUB_DEFINE (clGetProgramInfo, 100, cl_int,
					  return CL_INVALID_PLATFORM,
					  (program, param_name, param_value_size,
					   param_value, param_value_size_ret),
					  cl_program program,
					  cl_program_info param_name,
					  size_t param_value_size,
					  void *param_value,
					  size_t *param_value_size_ret);
__OPENCL_STUB_DEFINE (clGetProgramBuildInfo, 100, cl_int,
					  return CL_INVALID_PLATFORM,
					  (program, device, param_name, param_value_size,
					   param_value, param_value_size_ret),
					  cl_program program,
					  cl_device_id device,
					  cl_program_build_info param_name,
					  size_t param_value_size,
					  void *param_value,
					  size_t *param_value_size_ret);
__OPENCL_STUB_DEFINE (clCreateKernel, 100, cl_kernel,
					  *errcode_ret = CL_INVALID_PLATFORM; return NULL,
					  (program, kernel_name, errcode_ret),
					  cl_program program,
					  const char *kernel_name,
					  cl_int *errcode_ret);
__OPENCL_STUB_DEFINE (clCreateKernelsInProgram, 100, cl_int,
					  return CL_INVALID_PLATFORM,
					  (program, num_kernels, kernels, num_kernels_ret),
					  cl_program program,
					  cl_uint num_kernels,
					  cl_kernel *kernels,
					  cl_uint *num_kernels_ret);
__OPENCL_STUB_DEFINE (clCloneKernel, 210, cl_kernel,
					  *errcode_ret = CL_INVALID_PLATFORM; return NULL,
					  (source_kernel, errcode_ret),
					  cl_kernel source_kernel,
					  cl_int *errcode_ret);
__OPENCL_STUB_DEFINE (clRetainKernel, 100, cl_int,
					  return CL_INVALID_PLATFORM,
					  (kernel),
					  cl_kernel kernel);
__OPENCL_STUB_DEFINE (clReleaseKernel, 100, cl_int,
					  return CL_INVALID_PLATFORM,
					  (kernel),
					  cl_kernel kernel);
__OPENCL_STUB_DEFINE (clSetKernelArg, 100, cl_int,
					  return CL_INVALID_PLATFORM,
					  (kernel, arg_index, arg_size, arg_value),
					  cl_kernel kernel,
					  cl_uint arg_index,
					  size_t arg_size,
					  const void *arg_value);
__OPENCL_STUB_DEFINE (clSetKernelArgSVMPointer, 200, cl_int,
					  return CL_INVALID_PLATFORM,
					  (kernel, arg_index, arg_value),
					  cl_kernel kernel,
					  cl_uint arg_index,
					  const void *arg_value);
__OPENCL_STUB_DEFINE (clSetKernelExecInfo, 200, cl_int,
					  return CL_INVALID_PLATFORM,
					  (kernel, param_name, param_value_size, param_value),
					  cl_kernel kernel,
					  cl_kernel_exec_info param_name,
					  size_t param_value_size,
					  const void *param_value);
__OPENCL_STUB_DEFINE (clGetKernelInfo, 100, cl_int,
					  return CL_INVALID_PLATFORM,
					  (kernel, param_name, param_value_size,
					   param_value, param_value_size_ret),
					  cl_kernel kernel,
					  cl_kernel_info param_name,
					  size_t param_value_size,
					  void *param_value,
					  size_t *param_value_size_ret);
__OPENCL_STUB_DEFINE (clGetKernelArgInfo, 120, cl_int,
					  return CL_INVALID_PLATFORM,
					  (kernel, arg_index, param_name, param_value_size,
					   param_value, param_value_size_ret),
					  cl_kernel kernel,
					  cl_uint arg_index,
					  cl_kernel_arg_info param_name,
					  size_t param_value_size,
					  void *param_value,
					  size_t *param_value_size_ret);
__OPENCL_STUB_DEFINE (clGetKernelWorkGroupInfo, 100, cl_int,
					  return CL_INVALID_PLATFORM,
					  (kernel, device, param_name, param_value_size,
					   param_value, param_value_size_ret),
					  cl_kernel kernel,
					  cl_device_id device,
					  cl_kernel_work_group_info param_name,
					  size_t param_value_size,
					  void *param_value,
					  size_t *param_value_size_ret);
__OPENCL_STUB_DEFINE (clGetKernelSubGroupInfo, 210, cl_int,
					  return CL_INVALID_PLATFORM,
					  (kernel, device, param_name, input_value_size,
					   input_value, param_value_size,
					   param_value, param_value_size_ret),
					  cl_kernel kernel,
					  cl_device_id device,
					  cl_kernel_sub_group_info param_name,
					  size_t input_value_size,
					  const void *input_value,
					  size_t param_value_size,
					  void *param_value,
					  size_t *param_value_size_ret);
__OPENCL_STUB_DEFINE (clWaitForEvents, 100, cl_int,
					  return CL_INVALID_PLATFORM,
					  (num_events, event_list),
					  cl_uint num_events,
					  const cl_event *event_list);
__OPENCL_STUB_DEFINE (clGetEventInfo, 100, cl_int,
					  return CL_INVALID_PLATFORM,
					  (event, param_name, param_value_size,
					   param_value, param_value_size_ret),
					  cl_event event,
					  cl_event_info param_name,
					  size_t param_value_size,
					  void *param_value,
					  size_t *param_value_size_ret);
__OPENCL_STUB_DEFINE (clCreateUserEvent, 110, cl_event,
					  *errcode_ret = CL_INVALID_PLATFORM; return NULL,
					  (context, errcode_ret),
					  cl_context context,
					  cl_int *errcode_ret);
__OPENCL_STUB_DEFINE (clRetainEvent, 100, cl_int,
					  return CL_INVALID_PLATFORM,
					  (event),
					  cl_event event);
__OPENCL_STUB_DEFINE (clReleaseEvent, 100, cl_int,
					  return CL_INVALID_PLATFORM,
					  (event),
					  cl_event event);
__OPENCL_STUB_DEFINE (clSetUserEventStatus, 110, cl_int,
					  return CL_INVALID_PLATFORM,
					  (event, execution_status),
					  cl_event event,
					  cl_int execution_status);
__OPENCL_STUB_DEFINE (clSetEventCallback, 110, cl_int,
					  return CL_INVALID_PLATFORM,
					  (event, command_exec_callback_type,
					   pfn_notify, user_data),
					  cl_event event,
					  cl_int command_exec_callback_type,
					  void (CL_CALLBACK *pfn_notify)(cl_event,
													 cl_int,
													 void *),
					  void *user_data);
__OPENCL_STUB_DEFINE (clGetEventProfilingInfo, 100, cl_int,
					  return CL_INVALID_PLATFORM,
					  (event, param_name, param_value_size,
					   param_value, param_value_size_ret),
					  cl_event event,
					  cl_profiling_info param_name,
					  size_t param_value_size,
					  void *param_value,
					  size_t *param_value_size_ret);
__OPENCL_STUB_DEFINE (clFlush, 100, cl_int,
					  return CL_INVALID_PLATFORM,
					  (command_queue),
					  cl_command_queue command_queue);
__OPENCL_STUB_DEFINE (clFinish, 100, cl_int,
					  return CL_INVALID_PLATFORM,
					  (command_queue),
					  cl_command_queue command_queue);
__OPENCL_STUB_DEFINE (clEnqueueReadBuffer, 100, cl_int,
					  return CL_INVALID_PLATFORM,
					  (command_queue, buffer, blocking_read,
					   offset, size, ptr, num_events_in_wait_list,
					   event_wait_list, event),
					  cl_command_queue command_queue,
					  cl_mem buffer,
					  cl_bool blocking_read,
					  size_t offset,
					  size_t size,
					  void *ptr,
					  cl_uint num_events_in_wait_list,
					  const cl_event *event_wait_list,
					  cl_event *event);
__OPENCL_STUB_DEFINE (clEnqueueReadBufferRect, 110, cl_int,
					  return CL_INVALID_PLATFORM,
					  (command_queue, buffer, blocking_read,
					   buffer_offset, host_offset, region,
					   buffer_row_pitch, buffer_slice_pitch,
					   host_row_pitch, host_slice_pitch, ptr,
					   num_events_in_wait_list, event_wait_list, event),
					  cl_command_queue command_queue,
					  cl_mem buffer,
					  cl_bool blocking_read,
					  const size_t *buffer_offset,
					  const size_t *host_offset,
					  const size_t *region,
					  size_t buffer_row_pitch,
					  size_t buffer_slice_pitch,
					  size_t host_row_pitch,
					  size_t host_slice_pitch,
					  void *ptr,
					  cl_uint num_events_in_wait_list,
					  const cl_event *event_wait_list,
					  cl_event *event);
__OPENCL_STUB_DEFINE (clEnqueueWriteBuffer, 100, cl_int,
					  return CL_INVALID_PLATFORM,
					  (command_queue, buffer, blocking_write,
					   offset, size, ptr, num_events_in_wait_list,
					   event_wait_list, event),
					  cl_command_queue command_queue,
					  cl_mem buffer,
					  cl_bool blocking_write,
					  size_t offset,
					  size_t size,
					  const void *ptr,
					  cl_uint num_events_in_wait_list,
					  const cl_event *event_wait_list,
					  cl_event *event);
__OPENCL_STUB_DEFINE (clEnqueueWriteBufferRect, 110, cl_int,
					  return CL_INVALID_PLATFORM,
					  (command_queue, buffer, blocking_write,
					   buffer_offset, host_offset, region,
					   buffer_row_pitch, buffer_slice_pitch,
					   host_row_pitch, host_slice_pitch,
					   ptr, num_events_in_wait_list,
					   event_wait_list, event),
					  cl_command_queue command_queue,
					  cl_mem buffer,
					  cl_bool blocking_write,
					  const size_t *buffer_offset,
					  const size_t *host_offset,
					  const size_t *region,
					  size_t buffer_row_pitch,
					  size_t buffer_slice_pitch,
					  size_t host_row_pitch,
					  size_t host_slice_pitch,
					  const void *ptr,
					  cl_uint num_events_in_wait_list,
					  const cl_event *event_wait_list,
					  cl_event *event);
__OPENCL_STUB_DEFINE (clEnqueueFillBuffer, 120, cl_int,
					  return CL_INVALID_PLATFORM,
					  (command_queue, buffer, pattern,
					   pattern_size, offset, size,
					   num_events_in_wait_list, event_wait_list, event),
					  cl_command_queue command_queue,
					  cl_mem buffer,
					  const void *pattern,
					  size_t pattern_size,
					  size_t offset,
					  size_t size,
					  cl_uint num_events_in_wait_list,
					  const cl_event *event_wait_list,
					  cl_event *event);
__OPENCL_STUB_DEFINE (clEnqueueCopyBuffer, 100, cl_int,
					  return CL_INVALID_PLATFORM,
					  (command_queue, src_buffer, dst_buffer,
					   src_offset, dst_offset, size,
					   num_events_in_wait_list,
					   event_wait_list, event),
					  cl_command_queue command_queue,
					  cl_mem src_buffer,
					  cl_mem dst_buffer,
					  size_t src_offset,
					  size_t dst_offset,
					  size_t size,
					  cl_uint num_events_in_wait_list,
					  const cl_event *event_wait_list,
					  cl_event *event);
__OPENCL_STUB_DEFINE (clEnqueueCopyBufferRect, 110, cl_int,
					  return CL_INVALID_PLATFORM,
					  (command_queue, src_buffer, dst_buffer,
					   src_origin, dst_origin, region,
					   src_row_pitch, src_slice_pitch,
					   dst_row_pitch, dst_slice_pitch,
					   num_events_in_wait_list, event_wait_list, event),
					  cl_command_queue command_queue,
					  cl_mem src_buffer,
					  cl_mem dst_buffer,
					  const size_t *src_origin,
					  const size_t *dst_origin,
					  const size_t *region,
					  size_t src_row_pitch,
					  size_t src_slice_pitch,
					  size_t dst_row_pitch,
					  size_t dst_slice_pitch,
					  cl_uint num_events_in_wait_list,
					  const cl_event *event_wait_list,
					  cl_event *event);
__OPENCL_STUB_DEFINE (clEnqueueReadImage, 100, cl_int,
					  return CL_INVALID_PLATFORM,
					  (command_queue, image, blocking_read,
					   origin, region, row_pitch, slice_pitch,
					   ptr, num_events_in_wait_list,
					   event_wait_list, event),
					  cl_command_queue command_queue,
					  cl_mem image,
					  cl_bool blocking_read,
					  const size_t *origin,
					  const size_t *region,
					  size_t row_pitch,
					  size_t slice_pitch,
					  void *ptr,
					  cl_uint num_events_in_wait_list,
					  const cl_event *event_wait_list,
					  cl_event *event);
__OPENCL_STUB_DEFINE (clEnqueueWriteImage, 100, cl_int,
					  return CL_INVALID_PLATFORM,
					  (command_queue, image, blocking_write,
					   origin, region, input_row_pitch, input_slice_pitch,
					   ptr, num_events_in_wait_list,
					   event_wait_list, event),
					  cl_command_queue command_queue,
					  cl_mem image,
					  cl_bool blocking_write,
					  const size_t *origin,
					  const size_t *region,
					  size_t input_row_pitch,
					  size_t input_slice_pitch,
					  const void *ptr,
					  cl_uint num_events_in_wait_list,
					  const cl_event *event_wait_list,
					  cl_event *event);
__OPENCL_STUB_DEFINE (clEnqueueFillImage, 120, cl_int,
					  return CL_INVALID_PLATFORM,
					  (command_queue, image, fill_color,
					   origin, region, num_events_in_wait_list,
					   event_wait_list, event),
					  cl_command_queue command_queue,
					  cl_mem image,
					  const void *fill_color,
					  const size_t *origin,
					  const size_t *region,
					  cl_uint num_events_in_wait_list,
					  const cl_event *event_wait_list,
					  cl_event *event);
__OPENCL_STUB_DEFINE (clEnqueueCopyImage, 100, cl_int,
					  return CL_INVALID_PLATFORM,
					  (command_queue, src_image, dst_image,
					   src_origin, dst_origin, region,
					   num_events_in_wait_list, event_wait_list, event),
					  cl_command_queue command_queue,
					  cl_mem src_image,
					  cl_mem dst_image,
					  const size_t *src_origin,
					  const size_t *dst_origin,
					  const size_t *region,
					  cl_uint num_events_in_wait_list,
					  const cl_event *event_wait_list,
					  cl_event *event);
__OPENCL_STUB_DEFINE (clEnqueueCopyImageToBuffer, 100, cl_int,
					  return CL_INVALID_PLATFORM,
					  (command_queue, src_image, dst_buffer,
					   src_origin, region, dst_offset,
					   num_events_in_wait_list, event_wait_list, event),
					  cl_command_queue command_queue,
					  cl_mem src_image,
					  cl_mem dst_buffer,
					  const size_t *src_origin,
					  const size_t *region,
					  size_t dst_offset,
					  cl_uint num_events_in_wait_list,
					  const cl_event *event_wait_list,
					  cl_event *event);
__OPENCL_STUB_DEFINE (clEnqueueCopyBufferToImage, 100, cl_int,
					  return CL_INVALID_PLATFORM,
					  (command_queue, src_buffer, dst_image,
					   src_offset, dst_origin, region,
					   num_events_in_wait_list, event_wait_list, event),
					  cl_command_queue command_queue,
					  cl_mem src_buffer,
					  cl_mem dst_image,
					  size_t src_offset,
					  const size_t *dst_origin,
					  const size_t *region,
					  cl_uint num_events_in_wait_list,
					  const cl_event *event_wait_list,
					  cl_event *event);
__OPENCL_STUB_DEFINE (clEnqueueMapBuffer, 100, void *,
					  *errcode_ret = CL_INVALID_PLATFORM; return NULL,
					  (command_queue, buffer, blocking_map,
					   map_flags, offset, size,
					   num_events_in_wait_list,
					   event_wait_list, event, errcode_ret),
					  cl_command_queue command_queue,
					  cl_mem buffer,
					  cl_bool blocking_map,
					  cl_map_flags map_flags,
					  size_t offset,
					  size_t size,
					  cl_uint num_events_in_wait_list,
					  const cl_event *event_wait_list,
					  cl_event *event,
					  cl_int *errcode_ret);
__OPENCL_STUB_DEFINE (clEnqueueMapImage, 100, void *,
					  *errcode_ret = CL_INVALID_PLATFORM; return NULL,
					  (command_queue, image, blocking_map,
					   map_flags, origin, region,
					   image_row_pitch, image_slice_pitch,
					   num_events_in_wait_list,
					   event_wait_list, event, errcode_ret),
					  cl_command_queue command_queue,
					  cl_mem image,
					  cl_bool blocking_map,
					  cl_map_flags map_flags,
					  const size_t *origin,
					  const size_t *region,
					  size_t *image_row_pitch,
					  size_t *image_slice_pitch,
					  cl_uint num_events_in_wait_list,
					  const cl_event *event_wait_list,
					  cl_event *event,
					  cl_int *errcode_ret);
__OPENCL_STUB_DEFINE (clEnqueueUnmapMemObject, 100, cl_int,
					  return CL_INVALID_PLATFORM,
					  (command_queue, memobj, mapped_ptr,
					   num_events_in_wait_list, event_wait_list, event),
					  cl_command_queue command_queue,
					  cl_mem memobj,
					  void *mapped_ptr,
					  cl_uint num_events_in_wait_list,
					  const cl_event *event_wait_list,
					  cl_event *event);
__OPENCL_STUB_DEFINE (clEnqueueMigrateMemObjects, 120, cl_int,
					  return CL_INVALID_PLATFORM,
					  (command_queue, num_mem_objects, mem_objects,
					   flags, num_events_in_wait_list,
					   event_wait_list, event),
					  cl_command_queue command_queue,
					  cl_uint num_mem_objects,
					  const cl_mem *mem_objects,
					  cl_mem_migration_flags flags,
					  cl_uint num_events_in_wait_list,
					  const cl_event *event_wait_list,
					  cl_event *event);
__OPENCL_STUB_DEFINE (clEnqueueNDRangeKernel, 100, cl_int,
					  return CL_INVALID_PLATFORM,
					  (command_queue, kernel, work_dim,
					   global_work_offset, global_work_size,
					   local_work_size,
					   num_events_in_wait_list,
					   event_wait_list, event),
					  cl_command_queue command_queue,
					  cl_kernel kernel,
					  cl_uint work_dim,
					  const size_t *global_work_offset,
					  const size_t *global_work_size,
					  const size_t *local_work_size,
					  cl_uint num_events_in_wait_list,
					  const cl_event *event_wait_list,
					  cl_event *event);
__OPENCL_STUB_DEFINE (clEnqueueNativeKernel, 100, cl_int,
					  return CL_INVALID_PLATFORM,
					  (command_queue, user_func, args, cb_args,
					   num_mem_objects, mem_list, args_mem_loc,
					   num_events_in_wait_list, event_wait_list, event),
					  cl_command_queue command_queue,
					  void (CL_CALLBACK *user_func)(void *),
					  void *args,
					  size_t cb_args,
					  cl_uint num_mem_objects,
					  const cl_mem *mem_list,
					  const void **args_mem_loc,
					  cl_uint num_events_in_wait_list,
					  const cl_event *event_wait_list,
					  cl_event *event);
__OPENCL_STUB_DEFINE (clEnqueueMarkerWithWaitList, 120, cl_int,
					  return CL_INVALID_PLATFORM,
					  (command_queue, num_events_in_wait_list,
					   event_wait_list, event),
					  cl_command_queue command_queue,
					  cl_uint num_events_in_wait_list,
					  const cl_event *event_wait_list,
					  cl_event *event);
__OPENCL_STUB_DEFINE (clEnqueueBarrierWithWaitList, 120, cl_int,
					  return CL_INVALID_PLATFORM,
					  (command_queue, num_events_in_wait_list,
					   event_wait_list, event),
					  cl_command_queue command_queue,
					  cl_uint num_events_in_wait_list,
					  const cl_event *event_wait_list,
					  cl_event *event);
__OPENCL_STUB_DEFINE (clEnqueueSVMFree, 200, cl_int,
					  return CL_INVALID_PLATFORM,
					  (command_queue, num_svm_pointers, svm_pointers,
					   pfn_free_func, user_data, num_events_in_wait_list,
					   event_wait_list, event),
					  cl_command_queue command_queue,
					  cl_uint num_svm_pointers,
					  void *svm_pointers[],
					  void (CL_CALLBACK *pfn_free_func)(cl_command_queue,
														cl_uint,
														void *[],
														void *),
					  void *user_data,
					  cl_uint num_events_in_wait_list,
					  const cl_event *event_wait_list,
					  cl_event *event);
__OPENCL_STUB_DEFINE (clEnqueueSVMMemcpy, 200, cl_int,
					  return CL_INVALID_PLATFORM,
					  (command_queue, blocking_copy, dst_ptr,
					   src_ptr, size, num_events_in_wait_list,
					   event_wait_list, event),
					  cl_command_queue command_queue,
					  cl_bool blocking_copy,
					  void *dst_ptr,
					  const void *src_ptr,
					  size_t size,
					  cl_uint num_events_in_wait_list,
					  const cl_event *event_wait_list,
					  cl_event *event);
__OPENCL_STUB_DEFINE (clEnqueueSVMMemFill, 200, cl_int,
					  return CL_INVALID_PLATFORM,
					  (command_queue, svm_ptr, pattern, pattern_size,
					   size, num_events_in_wait_list,
					   event_wait_list, event),
					  cl_command_queue command_queue,
					  void *svm_ptr,
					  const void *pattern,
					  size_t pattern_size,
					  size_t size,
					  cl_uint num_events_in_wait_list,
					  const cl_event *event_wait_list,
					  cl_event *event);
__OPENCL_STUB_DEFINE (clEnqueueSVMMap, 200, cl_int,
					  return CL_INVALID_PLATFORM,
					  (command_queue, blocking_map, flags,
					   svm_ptr, size, num_events_in_wait_list,
					   event_wait_list, event),
					  cl_command_queue command_queue,
					  cl_bool blocking_map,
					  cl_map_flags flags,
					  void *svm_ptr,
					  size_t size,
					  cl_uint num_events_in_wait_list,
					  const cl_event *event_wait_list,
					  cl_event *event);
__OPENCL_STUB_DEFINE (clEnqueueSVMUnmap, 200, cl_int,
					  return CL_INVALID_PLATFORM,
					  (command_queue, svm_ptr, num_events_in_wait_list,
					   event_wait_list, event),
					  cl_command_queue command_queue,
					  void *svm_ptr,
					  cl_uint num_events_in_wait_list,
					  const cl_event *event_wait_list,
					  cl_event *event);
__OPENCL_STUB_DEFINE (clEnqueueSVMMigrateMem, 210, cl_int,
					  return CL_INVALID_PLATFORM,
					  (command_queue, num_svm_pointers, svm_pointers,
					   sizes, flags, num_events_in_wait_list,
					   event_wait_list, event),
					  cl_command_queue command_queue,
					  cl_uint num_svm_pointers,
					  const void **svm_pointers,
					  const size_t *sizes,
					  cl_mem_migration_flags flags,
					  cl_uint num_events_in_wait_list,
					  const cl_event *event_wait_list,
					  cl_event *event);
__OPENCL_STUB_DEFINE (clGetExtensionFunctionAddressForPlatform, 120, void *,
					  return NULL,
					  (platform, func_name),
					  cl_platform_id platform,
					  const char *func_name);
__OPENCL_STUB_DEFINE (clSetCommandQueueProperty, 100, cl_int,
					  return CL_INVALID_PLATFORM,
					  (command_queue, properties,
					   enable, old_properties),
					  cl_command_queue command_queue,
					  cl_command_queue_properties properties,
					  cl_bool enable,
					  cl_command_queue_properties *old_properties);
__OPENCL_STUB_DEFINE (clCreateImage2D, 110, cl_mem,
					  *errcode_ret = CL_INVALID_PLATFORM; return NULL,
					  (context, flags, image_format, image_width,
					   image_height, image_row_pitch,
					   host_ptr, errcode_ret),
					  cl_context context,
					  cl_mem_flags flags,
					  const cl_image_format *image_format,
					  size_t image_width,
					  size_t image_height,
					  size_t image_row_pitch,
					  void *host_ptr,
					  cl_int *errcode_ret);
__OPENCL_STUB_DEFINE (clCreateImage3D, 110, cl_mem,
					  *errcode_ret = CL_INVALID_PLATFORM; return NULL,
					  (context, flags, image_format, image_width,
					   image_height, image_depth, image_row_pitch,
					   image_slice_pitch, host_ptr, errcode_ret),
					  cl_context context,
					  cl_mem_flags flags,
					  const cl_image_format *image_format,
					  size_t image_width,
					  size_t image_height,
					  size_t image_depth,
					  size_t image_row_pitch,
					  size_t image_slice_pitch,
					  void *host_ptr,
					  cl_int *errcode_ret);
__OPENCL_STUB_DEFINE (clEnqueueMarker, 110, cl_int,
					  return CL_INVALID_PLATFORM,
					  (command_queue, event),
					  cl_command_queue command_queue,
					  cl_event *event);
__OPENCL_STUB_DEFINE (clEnqueueWaitForEvents, 110, cl_int,
					  return CL_INVALID_PLATFORM,
					  (command_queue, num_events, event_list),
					  cl_command_queue command_queue,
					  cl_uint num_events,
					  const cl_event *event_list);
__OPENCL_STUB_DEFINE (clEnqueueBarrier, 110, cl_int,
					  return CL_INVALID_PLATFORM,
					  (command_queue),
					  cl_command_queue command_queue);
__OPENCL_STUB_DEFINE (clUnloadCompiler, 110, cl_int,
					  return CL_INVALID_PLATFORM,
					  ());
__OPENCL_STUB_DEFINE (clGetExtensionFunctionAddress, 110, void *,
					  return NULL,
					  (func_name),
					  const char *func_name);
__OPENCL_STUB_DEFINE (clCreateCommandQueue, 120, cl_command_queue,
					  *errcode_ret = CL_INVALID_PLATFORM; return NULL,
					  (context, device, properties, errcode_ret),
					  cl_context context,
					  cl_device_id device,
					  cl_command_queue_properties properties,
					  cl_int *errcode_ret);
__OPENCL_STUB_DEFINE (clCreateSampler, 120, cl_sampler,
					  *errcode_ret = CL_INVALID_PLATFORM; return NULL,
					  (context, normalized_coords, addressing_mode,
					   filter_mode, errcode_ret),
					  cl_context context,
					  cl_bool normalized_coords,
					  cl_addressing_mode addressing_mode,
					  cl_filter_mode filter_mode,
					  cl_int *errcode_ret);
__OPENCL_STUB_DEFINE (clEnqueueTask, 120, cl_int,
					  return CL_INVALID_PLATFORM,
					  (command_queue, kernel, num_events_in_wait_list,
					   event_wait_list, event),
					  cl_command_queue command_queue,
					  cl_kernel kernel,
					  cl_uint num_events_in_wait_list,
					  const cl_event *event_wait_list,
					  cl_event *event);
