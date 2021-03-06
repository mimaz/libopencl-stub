cmake_minimum_required (VERSION 2.8.11)

project(OpenCL_Headers_Tests)

enable_testing()

include_directories(${PROJECT_SOURCE_DIR}/..)

# Add a test for a given source file for each version of OpenCL
function(add_header_test NAME SOURCE)
  foreach(VERSION 100 110 120 200 210 220 300)
    set(TEST_EXE ${NAME}_${VERSION})
    add_executable(${TEST_EXE} ${SOURCE})
    target_compile_definitions(${TEST_EXE}
      PUBLIC
        -DCL_TARGET_OPENCL_VERSION=${VERSION}
    )
    # ICD on Windows uses system headers, which aren't strictly ANSI conformant
    # and trigger warnings 
    if(${NAME} STREQUAL cl_icd_h)
      set(MSVC_COMPILE_DEFS /W4 /WX)
    else()
      set(MSVC_COMPILE_DEFS /W4 /WX /Za)
    endif()
    target_compile_options(${TEST_EXE}
      PUBLIC
        $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Werror -pedantic -Wno-format>
        $<$<CXX_COMPILER_ID:MSVC>:${MSVC_COMPILE_DEFS}>
    )
    add_test(NAME ${TEST_EXE} COMMAND ${TEST_EXE})
  endforeach(VERSION)
endfunction(add_header_test)

# Tests
add_header_test(cl_h test_cl.h.c)
add_header_test(cl_egl_h test_cl_egl.h.c)
add_header_test(cl_ext_h test_cl_ext.h.c)
add_header_test(cl_ext_intel_h test_cl_ext_intel.h.c)
add_header_test(cl_gl_h test_cl_gl.h.c)
add_header_test(cl_gl_ext_h test_cl_gl_ext.h.c)
add_header_test(cl_half_h test_cl_half.h.c)
add_header_test(cl_icd_h test_cl_icd.h.c)
add_header_test(cl_platform_h test_cl_platform.h.c)
add_header_test(cl_opencl_h test_opencl.h.c)
add_header_test(cl_version_h test_cl_version.h.c)
add_header_test(headers test_headers.c)
