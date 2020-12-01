#define CL_TARGET_OPENCL_VERSION 110
#include <CL/cl.h>
#include <stdio.h>

int main (int argc, char **argv)
{
    cl_platform_id platforms[16];
    cl_uint num_platforms;
    cl_int ret;

    ret = clGetPlatformIDs(16, platforms, &num_platforms);

    if (ret != CL_SUCCESS) {
	fprintf (stderr, "clGetPlatformIDs failed\n");
	return 1;
    }

    printf ("platform count: %d\n", num_platforms);

    return 0;
}
