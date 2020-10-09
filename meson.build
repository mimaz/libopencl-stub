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

opencl_stub_lib = both_libraries(meson.project_name(),
  src, link_args: [ '-ldl' ],
  include_directories: cl_inc,
  install: true)
opencl_stub_lib_static = opencl_stub_lib.get_static_lib()

opencl_stub_dep = declare_dependency(link_with: opencl_stub_lib,
  include_directories: inc)
opencl_stub_dep_static = declare_dependency(link_with: opencl_stub_lib_static,
  include_directories: inc)

pkg.generate(libraries: opencl_stub_lib,
			 subdirs: 'opencl-stub',
			 version: '1.0',
			 name: 'opencl-stub',
			 description: 'OpenCL stub library')

pkg.generate(libraries: opencl_stub_lib_static,
			 subdirs: 'opencl-stub-static',
			 version: '1.0',
			 name: 'opencl-stub',
			 description: 'OpenCL stub library (static)')

subdir('test/')
