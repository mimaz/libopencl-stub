project('opencl-stub', 'c')

cl_inc = include_directories('OpenCL-Headers')
pkg = import('pkgconfig')

src = [
  'opencl-stub.c',
]

inc = [
  include_directories('.'),
  cl_inc,
]

if get_option('cl_headers')
  install_subdir('OpenCL-Headers/CL', install_dir: 'include/')
  inc += include_directories('./OpenCL-Headers/CL')
endif

opencl_stub_lib = static_library(meson.project_name(),
  src, link_args: [ '-ldl' ],
  include_directories: cl_inc,
  install: true)

opencl_stub_dep = declare_dependency(link_with: opencl_stub_lib,
  include_directories: inc,
  link_args: [ '-ldl' ])

pkg.generate(libraries: opencl_stub_lib,
  subdirs: 'opencl-stub',
  version: '1.0',
  name: 'opencl-stub',
  description: 'OpenCL stub library')

meson.override_dependency('opencl-stub', opencl_stub_dep)

subdir('test/')
