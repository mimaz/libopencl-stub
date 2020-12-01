opencl-stub library
===================

A thin wrapper of OpenCL API that loads proper implementation and forwards
calls. Works well on Android.

The library defines function pointers to each supported function and initializes
default dummy implementation. API definition calls the pointers directly
providing no overhead like additional checks or looking for the symbol each
time. The exception is clGetPlatformIDs that additionally
looks for OpenCL implementations and loads proper symbols. It's mandatory to
call clGetPlatformIDs first then.
