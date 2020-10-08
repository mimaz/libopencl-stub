/*
 *   Stub libopencl that dlsyms into actual library based on environment variable
 *
 *   LIBOPENCL_SO_PATH      -- Path to opencl so that will be searched first
 *   LIBOPENCL_SO_PATH_2    -- Searched second
 *   LIBOPENCL_SO_PATH_3    -- Searched third
 *   LIBOPENCL_SO_PATH_4    -- Searched fourth
 *
 *   If none of these are set, default system paths will be considered
**/

#define CL_TARGET_OPENCL_VERSION 300
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
  "/system/lib/libOpenCL.so",
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
  "/usr/lib/libOpenCL.so",
  "/usr/local/lib/libOpenCL.so",
  "/usr/local/lib/libpocl.so",
  "/usr/lib64/libOpenCL.so",
  "/usr/lib32/libOpenCL.so",
  "libOpenCL.so"
};
#endif

static int access_file(const char *filename)
{
  struct stat buffer;
  return (stat(filename, &buffer) == 0);
}


struct stub_desc
{
	struct stub_desc *next;
	const char *fname;
	void *fdefault;
	void **fpointer;
	int api_level;
};

static struct stub_desc *root_desc;
static void *so_handle;

#define __OPENCL_STUB_DEFINE(name, \
							 api_level, \
							 return_type, \
							 default_expr, \
							 arg_names, ...) \
	static return_type \
	d_##name (__VA_ARGS__) \
	{ \
		default_expr; \
	}\
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
	name (__VA_ARGS__) \
	{ \
		return s_##name arg_names; \
	}

__OPENCL_STUB_DEFINE (clGetPlatformIDs, 100, cl_int,
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
					  void (CL_CALLBACK *)(cl_mem,
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
__OPENCL_STUB_DEFINE (clLinkProgram, 120, cl_int,
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

static int open_libopencl_so()
{
  char *path = NULL, *str = NULL;
  int i;

  if((str=getenv("LIBOPENCL_SO_PATH")) && access_file(str)) {
    path = str;
  }
  else if((str=getenv("LIBOPENCL_SO_PATH_2")) && access_file(str)) {
    path = str;
  }
  else if((str=getenv("LIBOPENCL_SO_PATH_3")) && access_file(str)) {
    path = str;
  }
  else if((str=getenv("LIBOPENCL_SO_PATH_4")) && access_file(str)) {
    path = str;
  }

  if(!path)
  {
    for(i=0; i<(sizeof(default_so_paths) / sizeof(char*)); i++)
    {
      if(access_file(default_so_paths[i]))
      {
        path = (char *) default_so_paths[i];
        break;
      }
    }
  }

  if(path)
  {
    so_handle = dlopen(path, RTLD_LAZY);
    return 0;
  }
  else
  {
    return -1;
  }
}

cl_int
clGetSupportedImageFormats(cl_context           context,
                           cl_mem_flags         flags,
                           cl_mem_object_type   image_type,
                           cl_uint              num_entries,
                           cl_image_format *    image_formats,
                           cl_uint *            num_image_formats)
{
  f_clGetSupportedImageFormats func;

  if(!so_handle)
    open_libopencl_so();

  func = (f_clGetSupportedImageFormats) dlsym(so_handle, "clGetSupportedImageFormats");
  if(func) {
    return func(context, flags, image_type, num_entries,
                image_formats, num_image_formats);
  } else {
    return CL_INVALID_PLATFORM;
  }
}

cl_int
clGetMemObjectInfo(cl_mem           memobj,
                   cl_mem_info      param_name,
                   size_t           param_value_size,
                   void *           param_value,
                   size_t *         param_value_size_ret)
{
  f_clGetMemObjectInfo func;

  if(!so_handle)
    open_libopencl_so();

  func = (f_clGetMemObjectInfo) dlsym(so_handle, "clGetMemObjectInfo");
  if(func) {
    return func(memobj, param_name, param_value_size,
                param_value, param_value_size_ret);
  } else {
    return CL_INVALID_PLATFORM;
  }
}

cl_int
clGetImageInfo(cl_mem           image,
               cl_image_info    param_name,
               size_t           param_value_size,
               void *           param_value,
               size_t *         param_value_size_ret)
{
  f_clGetImageInfo func;

  if(!so_handle)
    open_libopencl_so();

  func = (f_clGetImageInfo) dlsym(so_handle, "clGetImageInfo");
  if(func) {
    return func(image, param_name, param_value_size,
                param_value, param_value_size_ret);
  } else {
    return CL_INVALID_PLATFORM;
  }
}

cl_int
clSetMemObjectDestructorCallback(  cl_mem memobj,
                                   void (*pfn_notify)( cl_mem memobj, void* user_data),
                                   void * user_data )
{
  f_clSetMemObjectDestructorCallback func;

  if(!so_handle)
    open_libopencl_so();

  func = (f_clSetMemObjectDestructorCallback) dlsym(so_handle, "clSetMemObjectDestructorCallback");
  if(func) {
    return func(memobj, pfn_notify, user_data);
  } else {
    return CL_INVALID_PLATFORM;
  }
}

cl_sampler
clCreateSampler(cl_context          context,
                cl_bool             normalized_coords,
                cl_addressing_mode  addressing_mode,
                cl_filter_mode      filter_mode,
                cl_int *            errcode_ret)
{
  f_clCreateSampler func;

  if(!so_handle)
    open_libopencl_so();

  func = (f_clCreateSampler) dlsym(so_handle, "clCreateSampler");
  if(func) {
    return func(context, normalized_coords, addressing_mode, filter_mode, errcode_ret);
  } else {
    return NULL;
  }
}

cl_int
clRetainSampler(cl_sampler sampler)
{
  f_clRetainSampler func;

  if(!so_handle)
    open_libopencl_so();

  func = (f_clRetainSampler) dlsym(so_handle, "clRetainSampler");
  if(func) {
    return func(sampler);
  } else {
    return CL_INVALID_PLATFORM;
  }
}

cl_int
clReleaseSampler(cl_sampler sampler)
{
  f_clReleaseSampler func;

  if(!so_handle)
    open_libopencl_so();

  func = (f_clReleaseSampler) dlsym(so_handle, "clReleaseSampler");
  if(func) {
    return func(sampler);
  } else {
    return CL_INVALID_PLATFORM;
  }
}

cl_int
clGetSamplerInfo(cl_sampler         sampler,
                 cl_sampler_info    param_name,
                 size_t             param_value_size,
                 void *             param_value,
                 size_t *           param_value_size_ret)
{
  f_clGetSamplerInfo func;

  if(!so_handle)
    open_libopencl_so();

  func = (f_clGetSamplerInfo) dlsym(so_handle, "clGetSamplerInfo");
  if(func) {
    return func(sampler, param_name, param_value_size, param_value, param_value_size_ret);
  } else {
    return CL_INVALID_PLATFORM;
  }
}


cl_program
clCreateProgramWithSource(cl_context        context,
                          cl_uint           count,
                          const char **     strings,
                          const size_t *    lengths,
                          cl_int *          errcode_ret)
{
  f_clCreateProgramWithSource func;

  if(!so_handle)
    open_libopencl_so();

  func = (f_clCreateProgramWithSource) dlsym(so_handle, "clCreateProgramWithSource");
  if(func) {
    return func(context, count, strings, lengths, errcode_ret);
  } else {
    return NULL;
  }
}



cl_program
clCreateProgramWithBinary(cl_context                     context,
                          cl_uint                        num_devices,
                          const cl_device_id *           device_list,
                          const size_t *                 lengths,
                          const unsigned char **         binaries,
                          cl_int *                       binary_status,
                          cl_int *                       errcode_ret)
{
  f_clCreateProgramWithBinary func;

  if(!so_handle)
    open_libopencl_so();

  func = (f_clCreateProgramWithBinary) dlsym(so_handle, "clCreateProgramWithBinary");
  if(func) {
    return func(context, num_devices, device_list, lengths, binaries, binary_status, errcode_ret);
  } else {
    return NULL;
  }
}

cl_program
clCreateProgramWithBuiltInKernels(cl_context            context,
                                  cl_uint               num_devices,
                                  const cl_device_id *  device_list,
                                  const char *          kernel_names,
                                  cl_int *              errcode_ret)
{
  f_clCreateProgramWithBuiltInKernels func;

  if(!so_handle)
    open_libopencl_so();

  func = (f_clCreateProgramWithBuiltInKernels) dlsym(so_handle, "clCreateProgramWithBuiltInKernels");
  if(func) {
    return func(context, num_devices, device_list, kernel_names, errcode_ret);
  } else {
    return NULL;
  }
}

cl_int
clRetainProgram(cl_program program)
{
  f_clRetainProgram func;

  if(!so_handle)
    open_libopencl_so();

  func = (f_clRetainProgram) dlsym(so_handle, "clRetainProgram");
  if(func) {
    return func(program);
  } else {
    return CL_INVALID_PLATFORM;
  }
}

cl_int
clReleaseProgram(cl_program program)
{
  f_clReleaseProgram func;

  if(!so_handle)
    open_libopencl_so();

  func = (f_clReleaseProgram) dlsym(so_handle, "clReleaseProgram");
  if(func) {
    return func(program);
  } else {
    return CL_INVALID_PLATFORM;
  }
}

cl_int
clBuildProgram(cl_program           program,
               cl_uint              num_devices,
               const cl_device_id * device_list,
               const char *         options,
               void (*pfn_notify)(cl_program program, void * user_data),
               void *               user_data)
{
  f_clBuildProgram func;

  if(!so_handle)
    open_libopencl_so();

  func = (f_clBuildProgram) dlsym(so_handle, "clBuildProgram");
  if(func) {
    return func(program, num_devices, device_list, options, pfn_notify, user_data);
  } else {
    return CL_INVALID_PLATFORM;
  }
}

cl_int
clCompileProgram(cl_program           program,
                 cl_uint              num_devices,
                 const cl_device_id * device_list,
                 const char *         options,
                 cl_uint              num_input_headers,
                 const cl_program *   input_headers,
                 const char **        header_include_names,
                 void (*pfn_notify)(cl_program program, void * user_data),
                 void *               user_data)
{
  f_clCompileProgram func;

  if(!so_handle)
    open_libopencl_so();

  func = (f_clCompileProgram) dlsym(so_handle, "clCompileProgram");
  if(func) {
    return func(program, num_devices, device_list, options, num_input_headers, input_headers,
                header_include_names, pfn_notify, user_data);
  } else {
    return CL_INVALID_PLATFORM;
  }
}

cl_program
clLinkProgram(cl_context           context,
              cl_uint              num_devices,
              const cl_device_id * device_list,
              const char *         options,
              cl_uint              num_input_programs,
              const cl_program *   input_programs,
              void (*pfn_notify)(cl_program program, void * user_data),
              void *               user_data,
              cl_int *             errcode_ret)
{
  f_clLinkProgram func;

  if(!so_handle)
    open_libopencl_so();

  func = (f_clLinkProgram) dlsym(so_handle, "clLinkProgram");
  if(func) {
    return func(context, num_devices, device_list, options, num_input_programs,
                input_programs, pfn_notify, user_data, errcode_ret);
  } else {
    return NULL;
  }
}


cl_int
clUnloadPlatformCompiler(cl_platform_id platform)
{
  f_clUnloadPlatformCompiler func;

  if(!so_handle)
    open_libopencl_so();

  func = (f_clUnloadPlatformCompiler) dlsym(so_handle, "clUnloadPlatformCompiler");
  if(func) {
    return func(platform);
  } else {
    return CL_INVALID_PLATFORM;
  }
}

cl_int
clGetProgramInfo(cl_program         program,
                 cl_program_info    param_name,
                 size_t             param_value_size,
                 void *             param_value,
                 size_t *           param_value_size_ret)
{
  f_clGetProgramInfo func;

  if(!so_handle)
    open_libopencl_so();

  func = (f_clGetProgramInfo) dlsym(so_handle, "clGetProgramInfo");
  if(func) {
    return func(program, param_name, param_value_size,
                param_value, param_value_size_ret);
  } else {
    return CL_INVALID_PLATFORM;
  }
}

cl_int
clGetProgramBuildInfo(cl_program            program,
                      cl_device_id          device,
                      cl_program_build_info param_name,
                      size_t                param_value_size,
                      void *                param_value,
                      size_t *              param_value_size_ret)
{
  f_clGetProgramBuildInfo func;

  if(!so_handle)
    open_libopencl_so();

  func = (f_clGetProgramBuildInfo) dlsym(so_handle, "clGetProgramBuildInfo");
  if(func) {
    return func(program, device, param_name, param_value_size,
                param_value, param_value_size_ret);
  } else {
    return CL_INVALID_PLATFORM;
  }
}


cl_kernel
clCreateKernel(cl_program      program,
               const char *    kernel_name,
               cl_int *        errcode_ret)
{
  f_clCreateKernel func;

  if(!so_handle)
    open_libopencl_so();

  func = (f_clCreateKernel) dlsym(so_handle, "clCreateKernel");
  if(func) {
    return func(program, kernel_name, errcode_ret);
  } else {
    return NULL;
  }
}

cl_int
clCreateKernelsInProgram(cl_program     program,
                         cl_uint        num_kernels,
                         cl_kernel *    kernels,
                         cl_uint *      num_kernels_ret)
{
  f_clCreateKernelsInProgram func;

  if(!so_handle)
    open_libopencl_so();

  func = (f_clCreateKernelsInProgram) dlsym(so_handle, "clCreateKernelsInProgram");
  if(func) {
    return func(program, num_kernels, kernels, num_kernels_ret);
  } else {
    return CL_INVALID_PLATFORM;
  }
}

cl_int
clRetainKernel(cl_kernel    kernel)
{
  f_clRetainKernel func;

  if(!so_handle)
    open_libopencl_so();

  func = (f_clRetainKernel) dlsym(so_handle, "clRetainKernel");
  if(func) {
    return func(kernel);
  } else {
    return CL_INVALID_PLATFORM;
  }
}

cl_int
clReleaseKernel(cl_kernel   kernel)
{
  f_clReleaseKernel func;

  if(!so_handle)
    open_libopencl_so();

  func = (f_clReleaseKernel) dlsym(so_handle, "clReleaseKernel");
  if(func) {
    return func(kernel);
  } else {
    return CL_INVALID_PLATFORM;
  }
}

cl_int
clSetKernelArg(cl_kernel    kernel,
               cl_uint      arg_index,
               size_t       arg_size,
               const void * arg_value)
{
  f_clSetKernelArg func;

  if(!so_handle)
    open_libopencl_so();

  func = (f_clSetKernelArg) dlsym(so_handle, "clSetKernelArg");
  if(func) {
    return func(kernel, arg_index, arg_size, arg_value);
  } else {
    return CL_INVALID_PLATFORM;
  }
}

cl_int
clGetKernelInfo(cl_kernel       kernel,
                cl_kernel_info  param_name,
                size_t          param_value_size,
                void *          param_value,
                size_t *        param_value_size_ret)
{
  f_clGetKernelInfo func;

  if(!so_handle)
    open_libopencl_so();

  func = (f_clGetKernelInfo) dlsym(so_handle, "clGetKernelInfo");
  if(func) {
    return func(kernel, param_name, param_value_size, param_value, param_value_size_ret);
  } else {
    return CL_INVALID_PLATFORM;
  }
}

cl_int
clGetKernelArgInfo(cl_kernel       kernel,
                   cl_uint         arg_indx,
                   cl_kernel_arg_info  param_name,
                   size_t          param_value_size,
                   void *          param_value,
                   size_t *        param_value_size_ret)
{
  f_clGetKernelArgInfo func;

  if(!so_handle)
    open_libopencl_so();

  func = (f_clGetKernelArgInfo) dlsym(so_handle, "clGetKernelArgInfo");
  if(func) {
    return func(kernel, arg_indx, param_name, param_value_size,
                param_value, param_value_size_ret);
  } else {
    return CL_INVALID_PLATFORM;
  }
}

cl_int
clGetKernelWorkGroupInfo(cl_kernel                  kernel,
                         cl_device_id               device,
                         cl_kernel_work_group_info  param_name,
                         size_t                     param_value_size,
                         void *                     param_value,
                         size_t *                   param_value_size_ret)
{
  f_clGetKernelWorkGroupInfo func;

  if(!so_handle)
    open_libopencl_so();

  func = (f_clGetKernelWorkGroupInfo) dlsym(so_handle, "clGetKernelWorkGroupInfo");
  if(func) {
    return func(kernel, device, param_name, param_value_size, param_value, param_value_size_ret);
  } else {
    return CL_INVALID_PLATFORM;
  }
}


cl_int
clWaitForEvents(cl_uint             num_events,
                const cl_event *    event_list)
{
  f_clWaitForEvents func;

  if(!so_handle)
    open_libopencl_so();

  func = (f_clWaitForEvents) dlsym(so_handle, "clWaitForEvents");
  if(func) {
    return func(num_events, event_list);
  } else {
    return CL_INVALID_PLATFORM;
  }
}


cl_int
clGetEventInfo(cl_event         event,
               cl_event_info    param_name,
               size_t           param_value_size,
               void *           param_value,
               size_t *         param_value_size_ret)
{
  f_clGetEventInfo func;

  if(!so_handle)
    open_libopencl_so();

  func = (f_clGetEventInfo) dlsym(so_handle, "clGetEventInfo");
  if(func) {
    return func(event, param_name, param_value_size, param_value, param_value_size_ret);
  } else {
    return CL_INVALID_PLATFORM;
  }
}

cl_event
clCreateUserEvent(cl_context    context,
                  cl_int *      errcode_ret)
{
  f_clCreateUserEvent func;

  if(!so_handle)
    open_libopencl_so();

  func = (f_clCreateUserEvent) dlsym(so_handle, "clCreateUserEvent");
  if(func) {
    return func(context, errcode_ret);
  } else {
    return NULL;
  }
}

cl_int
clRetainEvent(cl_event event)
{
  f_clRetainEvent func;

  if(!so_handle)
    open_libopencl_so();

  func = (f_clRetainEvent) dlsym(so_handle, "clRetainEvent");
  if(func) {
    return func(event);
  } else {
    return CL_INVALID_PLATFORM;
  }
}

cl_int
clReleaseEvent(cl_event event)
{
  f_clReleaseEvent func;

  if(!so_handle)
    open_libopencl_so();

  func = (f_clReleaseEvent) dlsym(so_handle, "clReleaseEvent");
  if(func) {
    return func(event);
  } else {
    return CL_INVALID_PLATFORM;
  }
}

cl_int
clSetUserEventStatus(cl_event   event,
                     cl_int     execution_status)
{
  f_clSetUserEventStatus func;

  if(!so_handle)
    open_libopencl_so();

  func = (f_clSetUserEventStatus) dlsym(so_handle, "clSetUserEventStatus");
  if(func) {
    return func(event, execution_status);
  } else {
    return CL_INVALID_PLATFORM;
  }
}

cl_int
clSetEventCallback( cl_event    event,
                    cl_int      command_exec_callback_type,
                    void (*pfn_notify)(cl_event, cl_int, void *),
                    void *      user_data)
{
  f_clSetEventCallback func;

  if(!so_handle)
    open_libopencl_so();

  func = (f_clSetEventCallback) dlsym(so_handle, "clSetEventCallback");
  if(func) {
    return func(event, command_exec_callback_type, pfn_notify, user_data);
  } else {
    return CL_INVALID_PLATFORM;
  }
}

cl_int
clGetEventProfilingInfo(cl_event            event,
                        cl_profiling_info   param_name,
                        size_t              param_value_size,
                        void *              param_value,
                        size_t *            param_value_size_ret)
{
  f_clGetEventProfilingInfo func;

  if(!so_handle)
    open_libopencl_so();

  func = (f_clGetEventProfilingInfo) dlsym(so_handle, "clGetEventProfilingInfo");
  if(func) {
    return func(event, param_name, param_value_size, param_value, param_value_size_ret);
  } else {
    return CL_INVALID_PLATFORM;
  }
}

cl_int
clFlush(cl_command_queue command_queue)
{
  f_clFlush func;

  if(!so_handle)
    open_libopencl_so();

  func = (f_clFlush) dlsym(so_handle, "clFlush");
  if(func) {
    return func(command_queue);
  } else {
    return CL_INVALID_PLATFORM;
  }
}

cl_int
clFinish(cl_command_queue command_queue)
{
  f_clFinish func;

  if(!so_handle)
    open_libopencl_so();

  func = (f_clFinish) dlsym(so_handle, "clFinish");
  if(func) {
    return func(command_queue);
  } else {
    return CL_INVALID_PLATFORM;
  }
}


cl_int
clEnqueueReadBuffer(cl_command_queue    command_queue,
                    cl_mem              buffer,
                    cl_bool             blocking_read,
                    size_t              offset,
                    size_t              size,
                    void *              ptr,
                    cl_uint             num_events_in_wait_list,
                    const cl_event *    event_wait_list,
                    cl_event *          event)
{
  f_clEnqueueReadBuffer func;

  if(!so_handle)
    open_libopencl_so();

  func = (f_clEnqueueReadBuffer) dlsym(so_handle, "clEnqueueReadBuffer");
  if(func) {
    return func(command_queue, buffer, blocking_read, offset, size, ptr,
                num_events_in_wait_list, event_wait_list, event);
  } else {
    return CL_INVALID_PLATFORM;
  }
}

cl_int
clEnqueueReadBufferRect(cl_command_queue    command_queue,
                        cl_mem              buffer,
                        cl_bool             blocking_read,
                        const size_t *      buffer_offset,
                        const size_t *      host_offset,
                        const size_t *      region,
                        size_t              buffer_row_pitch,
                        size_t              buffer_slice_pitch,
                        size_t              host_row_pitch,
                        size_t              host_slice_pitch,
                        void *              ptr,
                        cl_uint             num_events_in_wait_list,
                        const cl_event *    event_wait_list,
                        cl_event *          event)
{
  f_clEnqueueReadBufferRect func;

  if(!so_handle)
    open_libopencl_so();

  func = (f_clEnqueueReadBufferRect) dlsym(so_handle, "clEnqueueReadBufferRect");
  if(func) {
    return func(command_queue, buffer, blocking_read, buffer_offset, host_offset, region,
                buffer_row_pitch, buffer_slice_pitch, host_row_pitch, host_slice_pitch, ptr,
                num_events_in_wait_list, event_wait_list, event);
  } else {
    return CL_INVALID_PLATFORM;
  }
}

cl_int
clEnqueueWriteBuffer(cl_command_queue   command_queue,
                     cl_mem             buffer,
                     cl_bool            blocking_write,
                     size_t             offset,
                     size_t             size,
                     const void *       ptr,
                     cl_uint            num_events_in_wait_list,
                     const cl_event *   event_wait_list,
                     cl_event *         event)
{
  f_clEnqueueWriteBuffer func;

  if(!so_handle)
    open_libopencl_so();

  func = (f_clEnqueueWriteBuffer) dlsym(so_handle, "clEnqueueWriteBuffer");
  if(func) {
    return func(command_queue, buffer, blocking_write, offset, size, ptr,
                num_events_in_wait_list, event_wait_list, event);
  } else {
    return CL_INVALID_PLATFORM;
  }
}


cl_int
clEnqueueWriteBufferRect(cl_command_queue    command_queue,
                         cl_mem              buffer,
                         cl_bool             blocking_write,
                         const size_t *      buffer_offset,
                         const size_t *      host_offset,
                         const size_t *      region,
                         size_t              buffer_row_pitch,
                         size_t              buffer_slice_pitch,
                         size_t              host_row_pitch,
                         size_t              host_slice_pitch,
                         const void *        ptr,
                         cl_uint             num_events_in_wait_list,
                         const cl_event *    event_wait_list,
                         cl_event *          event)
{
  f_clEnqueueWriteBufferRect func;

  if(!so_handle)
    open_libopencl_so();

  func = (f_clEnqueueWriteBufferRect) dlsym(so_handle, "clEnqueueWriteBufferRect");
  if(func) {
    return func(command_queue, buffer, blocking_write, buffer_offset, host_offset, region,
                buffer_row_pitch, buffer_slice_pitch, host_row_pitch, host_slice_pitch,
                ptr, num_events_in_wait_list, event_wait_list, event);
  } else {
    return CL_INVALID_PLATFORM;
  }
}


cl_int
clEnqueueFillBuffer(cl_command_queue   command_queue,
                    cl_mem             buffer,
                    const void *       pattern,
                    size_t             pattern_size,
                    size_t             offset,
                    size_t             size,
                    cl_uint            num_events_in_wait_list,
                    const cl_event *   event_wait_list,
                    cl_event *         event)
{
  f_clEnqueueFillBuffer func;

  if(!so_handle)
    open_libopencl_so();

  func = (f_clEnqueueFillBuffer) dlsym(so_handle, "clEnqueueFillBuffer");
  if(func) {
    return func(command_queue, buffer, pattern, pattern_size, offset, size,
                num_events_in_wait_list, event_wait_list, event);
  } else {
    return CL_INVALID_PLATFORM;
  }
}

cl_int
clEnqueueCopyBuffer(cl_command_queue    command_queue,
                    cl_mem              src_buffer,
                    cl_mem              dst_buffer,
                    size_t              src_offset,
                    size_t              dst_offset,
                    size_t              size,
                    cl_uint             num_events_in_wait_list,
                    const cl_event *    event_wait_list,
                    cl_event *          event)
{
  f_clEnqueueCopyBuffer func;

  if(!so_handle)
    open_libopencl_so();

  func = (f_clEnqueueCopyBuffer) dlsym(so_handle, "clEnqueueCopyBuffer");
  if(func) {
    return func(command_queue, src_buffer, dst_buffer, src_offset, dst_offset, size,
                num_events_in_wait_list, event_wait_list, event);
  } else {
    return CL_INVALID_PLATFORM;
  }
}



cl_int
clEnqueueCopyBufferRect(cl_command_queue    command_queue,
                        cl_mem              src_buffer,
                        cl_mem              dst_buffer,
                        const size_t *      src_origin,
                        const size_t *      dst_origin,
                        const size_t *      region,
                        size_t              src_row_pitch,
                        size_t              src_slice_pitch,
                        size_t              dst_row_pitch,
                        size_t              dst_slice_pitch,
                        cl_uint             num_events_in_wait_list,
                        const cl_event *    event_wait_list,
                        cl_event *          event)
{
  f_clEnqueueCopyBufferRect func;

  if(!so_handle)
    open_libopencl_so();

  func = (f_clEnqueueCopyBufferRect) dlsym(so_handle, "clEnqueueCopyBufferRect");
  if(func) {
    return func(command_queue, src_buffer, dst_buffer, src_origin, dst_origin, region, src_row_pitch,
                src_slice_pitch, dst_row_pitch, dst_slice_pitch, num_events_in_wait_list, event_wait_list, event);
  } else {
    return CL_INVALID_PLATFORM;
  }
}

cl_int
clEnqueueReadImage(cl_command_queue     command_queue,
                   cl_mem               image,
                   cl_bool              blocking_read,
                   const size_t *       origin,
                   const size_t *       region,
                   size_t               row_pitch,
                   size_t               slice_pitch,
                   void *               ptr,
                   cl_uint              num_events_in_wait_list,
                   const cl_event *     event_wait_list,
                   cl_event *           event)
{
  f_clEnqueueReadImage func;

  if(!so_handle)
    open_libopencl_so();

  func = (f_clEnqueueReadImage) dlsym(so_handle, "clEnqueueReadImage");
  if(func) {
    return func(command_queue, image, blocking_read, origin, region, row_pitch, slice_pitch,
                ptr, num_events_in_wait_list, event_wait_list, event);
  } else {
    return CL_INVALID_PLATFORM;
  }
}

cl_int
clEnqueueWriteImage(cl_command_queue    command_queue,
                    cl_mem              image,
                    cl_bool             blocking_write,
                    const size_t *      origin,
                    const size_t *      region,
                    size_t              input_row_pitch,
                    size_t              input_slice_pitch,
                    const void *        ptr,
                    cl_uint             num_events_in_wait_list,
                    const cl_event *    event_wait_list,
                    cl_event *          event)
{
  f_clEnqueueWriteImage func;

  if(!so_handle)
    open_libopencl_so();

  func = (f_clEnqueueWriteImage) dlsym(so_handle, "clEnqueueWriteImage");
  if(func) {
    return func(command_queue, image, blocking_write, origin, region, input_row_pitch, input_slice_pitch, ptr,
                num_events_in_wait_list, event_wait_list, event);
  } else {
    return CL_INVALID_PLATFORM;
  }
}


cl_int
clEnqueueFillImage(cl_command_queue   command_queue,
                   cl_mem             image,
                   const void *       fill_color,
                   const size_t *     origin,
                   const size_t *     region,
                   cl_uint            num_events_in_wait_list,
                   const cl_event *   event_wait_list,
                   cl_event *         event)
{
  f_clEnqueueFillImage func;

  if(!so_handle)
    open_libopencl_so();

  func = (f_clEnqueueFillImage) dlsym(so_handle, "clEnqueueFillImage");
  if(func) {
    return func(command_queue, image, fill_color, origin, region, num_events_in_wait_list, event_wait_list, event);
  } else {
    return CL_INVALID_PLATFORM;
  }
}

cl_int
clEnqueueCopyImage(cl_command_queue     command_queue,
                   cl_mem               src_image,
                   cl_mem               dst_image,
                   const size_t *       src_origin,
                   const size_t *       dst_origin,
                   const size_t *       region,
                   cl_uint              num_events_in_wait_list,
                   const cl_event *     event_wait_list,
                   cl_event *           event)
{
  f_clEnqueueCopyImage func;

  if(!so_handle)
    open_libopencl_so();

  func = (f_clEnqueueCopyImage) dlsym(so_handle, "clEnqueueCopyImage");
  if(func) {
    return func(command_queue, src_image, dst_image, src_origin, dst_origin, region,
                num_events_in_wait_list, event_wait_list, event);
  } else {
    return CL_INVALID_PLATFORM;
  }
}

cl_int
clEnqueueCopyImageToBuffer(cl_command_queue command_queue,
                           cl_mem           src_image,
                           cl_mem           dst_buffer,
                           const size_t *   src_origin,
                           const size_t *   region,
                           size_t           dst_offset,
                           cl_uint          num_events_in_wait_list,
                           const cl_event * event_wait_list,
                           cl_event *       event)
{
  f_clEnqueueCopyImageToBuffer func;

  if(!so_handle)
    open_libopencl_so();

  func = (f_clEnqueueCopyImageToBuffer) dlsym(so_handle, "clEnqueueCopyImageToBuffer");
  if(func) {
    return func(command_queue, src_image, dst_buffer, src_origin, region, dst_offset,
                num_events_in_wait_list, event_wait_list, event);
  } else {
    return CL_INVALID_PLATFORM;
  }
}


cl_int
clEnqueueCopyBufferToImage(cl_command_queue command_queue,
                           cl_mem           src_buffer,
                           cl_mem           dst_image,
                           size_t           src_offset,
                           const size_t *   dst_origin,
                           const size_t *   region,
                           cl_uint          num_events_in_wait_list,
                           const cl_event * event_wait_list,
                           cl_event *       event)
{
  f_clEnqueueCopyBufferToImage func;

  if(!so_handle)
    open_libopencl_so();

  func = (f_clEnqueueCopyBufferToImage) dlsym(so_handle, "clEnqueueCopyBufferToImage");
  if(func) {
    return func(command_queue, src_buffer, dst_image, src_offset, dst_origin, region,
                num_events_in_wait_list, event_wait_list, event);
  } else {
    return CL_INVALID_PLATFORM;
  }
}

void *
clEnqueueMapBuffer(cl_command_queue command_queue,
                   cl_mem           buffer,
                   cl_bool          blocking_map,
                   cl_map_flags     map_flags,
                   size_t           offset,
                   size_t           size,
                   cl_uint          num_events_in_wait_list,
                   const cl_event * event_wait_list,
                   cl_event *       event,
                   cl_int *         errcode_ret)
{
  f_clEnqueueMapBuffer func;

  if(!so_handle)
    open_libopencl_so();

  func = (f_clEnqueueMapBuffer) dlsym(so_handle, "clEnqueueMapBuffer");
  if(func) {
    return func(command_queue, buffer, blocking_map, map_flags, offset, size,
                num_events_in_wait_list, event_wait_list, event, errcode_ret);
  } else {
    return NULL;
  }
}

void *
clEnqueueMapImage(cl_command_queue  command_queue,
                  cl_mem            image,
                  cl_bool           blocking_map,
                  cl_map_flags      map_flags,
                  const size_t *    origin,
                  const size_t *    region,
                  size_t *          image_row_pitch,
                  size_t *          image_slice_pitch,
                  cl_uint           num_events_in_wait_list,
                  const cl_event *  event_wait_list,
                  cl_event *        event,
                  cl_int *          errcode_ret)
{
  f_clEnqueueMapImage func;

  if(!so_handle)
    open_libopencl_so();

  func = (f_clEnqueueMapImage) dlsym(so_handle, "clEnqueueMapImage");
  if(func) {
    return func(command_queue, image, blocking_map, map_flags, origin, region, image_row_pitch,
                image_slice_pitch, num_events_in_wait_list, event_wait_list, event, errcode_ret);
  } else {
    return NULL;
  }
}

cl_int
clEnqueueUnmapMemObject(cl_command_queue command_queue,
                        cl_mem           memobj,
                        void *           mapped_ptr,
                        cl_uint          num_events_in_wait_list,
                        const cl_event *  event_wait_list,
                        cl_event *        event)
{
  f_clEnqueueUnmapMemObject func;

  if(!so_handle)
    open_libopencl_so();

  func = (f_clEnqueueUnmapMemObject) dlsym(so_handle, "clEnqueueUnmapMemObject");
  if(func) {
    return func(command_queue, memobj, mapped_ptr, num_events_in_wait_list, event_wait_list, event);
  } else {
    return CL_INVALID_PLATFORM;
  }
}

cl_int
clEnqueueMigrateMemObjects(cl_command_queue       command_queue,
                           cl_uint                num_mem_objects,
                           const cl_mem *         mem_objects,
                           cl_mem_migration_flags flags,
                           cl_uint                num_events_in_wait_list,
                           const cl_event *       event_wait_list,
                           cl_event *             event)
{
  f_clEnqueueMigrateMemObjects func;

  if(!so_handle)
    open_libopencl_so();

  func = (f_clEnqueueMigrateMemObjects) dlsym(so_handle, "clEnqueueMigrateMemObjects");
  if(func) {
    return func(command_queue, num_mem_objects, mem_objects, flags, num_events_in_wait_list, event_wait_list, event);
  } else {
    return CL_INVALID_PLATFORM;
  }
}

cl_int
clEnqueueNDRangeKernel(cl_command_queue command_queue,
                       cl_kernel        kernel,
                       cl_uint          work_dim,
                       const size_t *   global_work_offset,
                       const size_t *   global_work_size,
                       const size_t *   local_work_size,
                       cl_uint          num_events_in_wait_list,
                       const cl_event * event_wait_list,
                       cl_event *       event)
{
  f_clEnqueueNDRangeKernel func;

  if(!so_handle)
    open_libopencl_so();

  func = (f_clEnqueueNDRangeKernel) dlsym(so_handle, "clEnqueueNDRangeKernel");
  if(func) {
    return func(command_queue, kernel, work_dim, global_work_offset, global_work_size, local_work_size,
                num_events_in_wait_list, event_wait_list, event);
  } else {
    return CL_INVALID_PLATFORM;
  }
}

cl_int
clEnqueueTask(cl_command_queue  command_queue,
              cl_kernel         kernel,
              cl_uint           num_events_in_wait_list,
              const cl_event *  event_wait_list,
              cl_event *        event)
{
  f_clEnqueueTask func;

  if(!so_handle)
    open_libopencl_so();

  func = (f_clEnqueueTask) dlsym(so_handle, "clEnqueueTask");
  if(func) {
    return func(command_queue, kernel, num_events_in_wait_list, event_wait_list, event);
  } else {
    return CL_INVALID_PLATFORM;
  }
}

cl_int
clEnqueueNativeKernel(cl_command_queue  command_queue,
                      void (*user_func)(void *),
                      void *            args,
                      size_t            cb_args,
                      cl_uint           num_mem_objects,
                      const cl_mem *    mem_list,
                      const void **     args_mem_loc,
                      cl_uint           num_events_in_wait_list,
                      const cl_event *  event_wait_list,
                      cl_event *        event)
{
  f_clEnqueueNativeKernel func;

  if(!so_handle)
    open_libopencl_so();

  func = (f_clEnqueueNativeKernel) dlsym(so_handle, "clEnqueueNativeKernel");
  if(func) {
    return func(command_queue, user_func, args, cb_args, num_mem_objects, mem_list,
                args_mem_loc, num_events_in_wait_list, event_wait_list, event);
  } else {
    return CL_INVALID_PLATFORM;
  }
}

cl_int
clEnqueueMarkerWithWaitList(cl_command_queue command_queue,
                            cl_uint           num_events_in_wait_list,
                            const cl_event *  event_wait_list,
                            cl_event *        event)
{
  f_clEnqueueMarkerWithWaitList func;

  if(!so_handle)
    open_libopencl_so();

  func = (f_clEnqueueMarkerWithWaitList) dlsym(so_handle, "clEnqueueMarkerWithWaitList");
  if(func) {
    return func(command_queue, num_events_in_wait_list, event_wait_list, event);
  } else {
    return CL_INVALID_PLATFORM;
  }
}

cl_int
clEnqueueBarrierWithWaitList(cl_command_queue command_queue,
                             cl_uint           num_events_in_wait_list,
                             const cl_event *  event_wait_list,
                             cl_event *        event)
{
  f_clEnqueueBarrierWithWaitList func;

  if(!so_handle)
    open_libopencl_so();

  func = (f_clEnqueueBarrierWithWaitList) dlsym(so_handle, "clEnqueueBarrierWithWaitList");
  if(func) {
    return func(command_queue, num_events_in_wait_list, event_wait_list, event);
  } else {
    return CL_INVALID_PLATFORM;
  }
}

void *
clGetExtensionFunctionAddressForPlatform(cl_platform_id platform,
                                         const char *   func_name)
{
  f_clGetExtensionFunctionAddressForPlatform func;

  if(!so_handle)
    open_libopencl_so();

  func = (f_clGetExtensionFunctionAddressForPlatform) dlsym(so_handle, "clGetExtensionFunctionAddressForPlatform");
  if(func) {
    return func(platform, func_name);
  } else {
    return NULL;
  }
}


cl_mem
clCreateImage2D(cl_context              context,
                cl_mem_flags            flags,
                const cl_image_format * image_format,
                size_t                  image_width,
                size_t                  image_height,
                size_t                  image_row_pitch,
                void *                  host_ptr,
                cl_int *                errcode_ret)
{
  f_clCreateImage2D func;

  if(!so_handle)
    open_libopencl_so();

  func = (f_clCreateImage2D) dlsym(so_handle, "clCreateImage2D");
  if(func) {
    return func(context, flags, image_format, image_width, image_height,
                image_row_pitch, host_ptr, errcode_ret);
  } else {
    return NULL;
  }
}

cl_mem
clCreateImage3D(cl_context              context,
                cl_mem_flags            flags,
                const cl_image_format * image_format,
                size_t                  image_width,
                size_t                  image_height,
                size_t                  image_depth,
                size_t                  image_row_pitch,
                size_t                  image_slice_pitch,
                void *                  host_ptr,
                cl_int *                errcode_ret)
{
  f_clCreateImage3D func;

  if(!so_handle)
    open_libopencl_so();

  func = (f_clCreateImage3D) dlsym(so_handle, "clCreateImage3D");
  if(func) {
    return func(context, flags, image_format, image_width, image_height, image_depth,
                image_row_pitch, image_slice_pitch, host_ptr, errcode_ret);
  } else {
    return NULL;
  }
}

cl_int
clEnqueueMarker(cl_command_queue    command_queue,
                cl_event *          event)
{
  f_clEnqueueMarker func;

  if(!so_handle)
    open_libopencl_so();

  func = (f_clEnqueueMarker) dlsym(so_handle, "clEnqueueMarker");
  if(func) {
    return func(command_queue, event);
  } else {
    return CL_INVALID_PLATFORM;
  }
}

cl_int
clEnqueueWaitForEvents(cl_command_queue command_queue,
                       cl_uint          num_events,
                       const cl_event * event_list)
{
  f_clEnqueueWaitForEvents func;

  if(!so_handle)
    open_libopencl_so();

  func = (f_clEnqueueWaitForEvents) dlsym(so_handle, "clEnqueueWaitForEvents");
  if(func) {
    return func(command_queue, num_events, event_list);
  } else {
    return CL_INVALID_PLATFORM;
  }
}

cl_int
clEnqueueBarrier(cl_command_queue command_queue)
{
  f_clEnqueueBarrier func;

  if(!so_handle)
    open_libopencl_so();

  func = (f_clEnqueueBarrier) dlsym(so_handle, "clEnqueueBarrier");
  if(func) {
    return func(command_queue);
  } else {
    return CL_INVALID_PLATFORM;
  }
}

cl_int
clUnloadCompiler(void)
{
  f_clUnloadCompiler func;

  if(!so_handle)
    open_libopencl_so();

  func = (f_clUnloadCompiler) dlsym(so_handle, "clUnloadCompiler");
  if(func) {
    return func();
  } else {
    return CL_INVALID_PLATFORM;
  }
}

void *
clGetExtensionFunctionAddress(const char * func_name)
{
  f_clGetExtensionFunctionAddress func;

  if(!so_handle)
    open_libopencl_so();

  func = (f_clGetExtensionFunctionAddress) dlsym(so_handle, "clGetExtensionFunctionAddress");
  if(func) {
    return func(func_name);
  } else {
    return NULL;
  }
}

static int
load_symbols (int api_level)
{
	struct stub_desc *desc;

	desc = root_desc;

	while (desc != NULL) {
		if (api_level >= desc->api_level) {
			*desc->fpointer = dlsym (so_handle, desc->fname);
		} else {
			*desc->fpointer = desc->fdefault;
		}

		printf ("desc %s\n", desc->fname);

		desc = desc->next;
	}

	return 1;
}

int
opencl_stub_load (const char *path, int api_level)
{
	static int unload_registered;

	if (!unload_registered) {
		atexit (opencl_stub_unload);
		unload_registered = 1;
	}

	opencl_stub_unload ();

	printf ("load stub %s\n", path);

	if (api_level < 0) {
		api_level = 300;
	}

	if (access_file (path)) {
		so_handle = dlopen (path, RTLD_LAZY);

		if (so_handle != NULL) {
			return load_symbols (api_level);
		}
	}

	return 0;
}

void
opencl_stub_unload (void)
{
	if (so_handle != NULL) {
		printf ("unload stub\n");
		dlclose (so_handle);
		so_handle = NULL;
	}
}
