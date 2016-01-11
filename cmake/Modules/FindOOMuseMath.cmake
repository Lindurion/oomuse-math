## Copyright 2016 Eric W. Barndollar. All rights reserved.
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
##
## =============================================================================
## Usage: Copy this file into your CMake project that uses oomuse-math under
## cmake/Modules/ subfolders.
##
## Set input CMake cache variables using cmake-gui:
##     OOMUSE_ROOT - Set this file path to the dir below the oomuse-math install
##                   dir, e.g. C:/cmakeinstall or
##                   /Users/<your-username>/cmakeinstall
##     OOMUSE_CRT_LINKAGE - For Windows with the Microsoft Visual C++ compiler,
##                          set to 'dynamic' or 'static' (without quotes) to
##                          control C runtime library linkage. These correspond
##                          to the /MD (or /MDd) and /MT (or /MTd) cl compiler
##                          flags.
##
## In your root CMakeLists.txt, add this line before using oomuse-math:
##     set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH}
##         "${CMAKE_SOURCE_DIR}/cmake/Modules/")
##
## Then find the OOMuseMath package:
##     find_package(OOMuseMath REQUIRED)
##
## Add the needed include dirs for this header-only library:
##     set_property(TARGET <your-target>
##         APPEND PROPERTY INCLUDE_DIRECTORIES ${OOMUSEMATH_INCLUDE_DIRS})

set(OOMUSE_ROOT "" CACHE FILEPATH
    "Path of dir below installed oomuse-math, e.g. C:/cmakeinstall")
set(OOMUSE_CRT_LINKAGE "dynamic" CACHE STRING
    "'static' or 'dynamic' C runtime library linkage for Visual C++")


# Find include directory for oomuse-math headers.
find_path(OOMUSEMATH_INCLUDE_DIR oomuse/math/integers.h
    HINTS $ENV{OOMUSE_ROOT}/oomuse-math/include
          ${OOMUSE_ROOT}/oomuse-math/include)
mark_as_advanced(OOMUSEMATH_INCLUDE_DIR)


# Set OOMUSEMATH_FOUND to true if everything above was found.
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(OOMuseMath DEFAULT_MSG
    OOMUSEMATH_INCLUDE_DIR)


# Set output variables.
if(OOMUSEMATH_FOUND)
  set(OOMUSEMATH_INCLUDE_DIRS ${OOMUSEMATH_INCLUDE_DIR})
endif()
