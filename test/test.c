#define CL_TARGET_OPENCL_VERSION 300
#include <opencl-stub.h>
#include <stdio.h>

int main (int argc, char **argv)
{
	opencl_stub_load ("/usr/lib/x86_64-linux-gnu/libOpenCL.so", 300);
	return 0;
}
