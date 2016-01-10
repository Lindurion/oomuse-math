## Copyright 2015 Eric W. Barndollar. All rights reserved.
##
## Licensed under the Apache License, Version 2.0 (the "License");
## you may not use this file except in compliance with the License.
## You may obtain a copy of the License at
##
##     http://www.apache.org/licenses/LICENSE-2.0
##
## Unless required by applicable law or agreed to in writing, software
## distributed under the License is distributed on an "AS IS" BASIS,
## WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
## See the License for the specific language governing permissions and
## limitations under the License.

cmake_minimum_required(VERSION 3.0.2)
project(oomuse-math)


################################################################################
# Build Configuration Options (Set via CMake GUI)
################################################################################

set(OOMUSE_CRT_LINKAGE "dynamic" CACHE STRING
    "'static' or 'dynamic' C runtime library linkage for Visual C++")

# Use OOMUSE_CRT_LINKAGE to determine which gtest lib to link against.
if(OOMUSE_CRT_LINKAGE STREQUAL "static")
  set(GTEST_MSVC_SEARCH "MT" CACHE STRING "" "FORCE")
else()
  set(GTEST_MSVC_SEARCH "MD" CACHE STRING "" "FORCE")
endif()


################################################################################
# Compiler Flags
################################################################################

set(oomuse_compile_flags "")
set(oomuse_compile_definitions "")

if(MSVC)
  # Override CMake defaults.
  set(compiler_flag_lists
      CMAKE_CXX_FLAGS CMAKE_CXX_FLAGS_DEBUG CMAKE_CXX_FLAGS_RELEASE
      CMAKE_C_FLAGS CMAKE_C_FLAGS_DEBUG CMAKE_C_FLAGS_RELEASE)

  foreach(flag_list_name ${compiler_flag_lists})
    # Set C runtime library linkage.
    if(OOMUSE_CRT_LINKAGE STREQUAL "static")
      string(REPLACE "/MD" "/MT" ${flag_list_name} "${${flag_list_name}}")
    else()
      string(REPLACE "/MT" "/MD" ${flag_list_name} "${${flag_list_name}}")
    endif()

    # Use stricter warnings.
    string(REPLACE "/W3" "/W4" ${flag_list_name} "${${flag_list_name}}")
  endforeach()

  list(APPEND oomuse_compile_flags "/GS")  # Use buffer security checks.
  list(APPEND oomuse_compile_flags "/W4" "/WX")  # Treat warnings as errors.

  # Suppress warnings about std::uninitialized_copy().
  list(APPEND oomuse_compile_definitions _SCL_SECURE_NO_WARNINGS)

  # Define standard Unicode Win32 flags.
  list(APPEND oomuse_compile_definitions _WIN32 WIN32 WIN32_LEAN_AND_MEAN)
  list(APPEND oomuse_compile_definitions _UNICODE UNICODE)
elseif((CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    OR (CMAKE_CXX_COMPILER_ID MATCHES "GNU"))
  # Treat warnings as errors.
  list(APPEND oomuse_compile_flags "-Wall" "-Wshadow" "-Werror")
endif()

# Convert list (implicit semicolons) to space-separated string of flags.
string(REPLACE ";" " " oomuse_compile_flags "${oomuse_compile_flags}")


################################################################################
# oomuse-math Library (Header Only)
################################################################################

add_library(oomuse-math INTERFACE)
target_include_directories(oomuse-math INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>)

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/oomuse
    DESTINATION include)


################################################################################
# oomuse-math Tests
################################################################################

enable_testing()
find_package(GTest REQUIRED)

set(OOMUSE_MATH_TEST_FILES
    test/oomuse/math/Constants_test.cpp)

add_executable(oomuse-math_test ${OOMUSE_MATH_TEST_FILES})

set_property(TARGET oomuse-math_test
    APPEND PROPERTY INCLUDE_DIRECTORIES ${GTEST_INCLUDE_DIRS})
set_property(TARGET oomuse-math_test PROPERTY CXX_STANDARD 14)
set_property(TARGET oomuse-math_test
    APPEND PROPERTY COMPILE_FLAGS "${oomuse_compile_flags}")
set_property(TARGET oomuse-math_test
    APPEND PROPERTY COMPILE_DEFINITIONS "${oomuse_compile_definitions}")

target_link_libraries(oomuse-math_test oomuse-math)
target_link_libraries(oomuse-math_test ${GTEST_BOTH_LIBRARIES})

add_test(run_oomuse-math_test oomuse-math_test)