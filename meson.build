project('opencl-stub', 'c')
add_project_arguments('-DCL_TARGET_OPENCL_VERSION=' +
  get_option('cl_version').to_string(), language: 'c')

cl_inc = include_directories('OpenCL-Headers')

src = [
  'opencl-stub.c',
]

inc = [
  include_directories('.'),
  cl_inc,
]

opencl_stub_lib = shared_library(meson.project_name(),
  src, link_args: [ '-ldl' ],
  include_directories: cl_inc,
  install: true)

opencl_stub_dep = declare_dependency(link_with: opencl_stub_lib,
  include_directories: inc)
