project('opencl-stub', 'c')

src = [
  'opencl-stub.c',
]

opencl_stub_lib = shared_library(meson.project_name(),
  src, link_args: [ '-ldl' ], install: true)

opencl_stub_dep = declare_dependency(link_with: opencl_stub_lib,
  include_directories: include_directories('.'))
