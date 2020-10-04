project('opencl-stub', 'c')

src = [
  'opencl-stub.c',
]

libopencl_stub_lib = shared_library(meson.project_name(),
  src, link_args: [ '-ldl' ], install: true)
