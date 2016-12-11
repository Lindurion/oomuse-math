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

import conans


class OOMuseMathConan(conans.ConanFile):
  """The conan.io + CMake build configuration for C++ oomuse-math package."""

  #=============================================================================
  # Static configuration data about this package
  #=============================================================================

  name = "oomuse-math"
  version = "0.1.0"

  author = "Eric W. Barndollar (eric@EricWBarndollar.com)"
  build_policy = "missing"  # Automatically build from source when not in cache.
  license = "Apache 2.0"

  # Note: This gets cleared if not in testing mode, since header-only library
  # is not system-depdendent.
  settings = "os", "compiler", "build_type", "arch"
  url = "https://github.com/lindurion/oomuse-math"


  #=============================================================================
  # Configuration options
  #=============================================================================

  options = {
    "testing": [False, True],
  }

  # Note: No configuration option is provided for Windows static C runtime (the
  # /MT or /MTd cl compiler options), so any package that uses this library must
  # use the shared C runtime library on Windows (/MD or /MDd cl options).

  # Note that gtest in shared mode produces compiler warnings, so link against
  # as a static library so this build can treat warnings as errors.
  default_options = "testing=False", "gtest:shared=False"

  def configure(self):
    """Configures things that depend on configuration options."""
    if not self.options.testing:
      self.settings.clear()


  #=============================================================================
  # Dependencies needed to build, run, and (optionally) test this package
  #=============================================================================

  def requirements(self):
    """Defines the conan.io packages required to build & test this package."""
    self.requires("oomuse-core/0.1.1@lindurion/stable")

    if self.options.testing:
      self.requires("gtest/1.8.0@lasote/stable")

  def imports(self):
    """Copies dynamic libs from deps needed to run & test this package."""
    self.copy("*.dll", dst="bin", src="bin")
    self.copy("*.dylib*", dst="bin", src="lib")


  #=============================================================================
  # Building and (optionally) testing this package
  #=============================================================================

  generators = "cmake"  # Generate info needed to build against conan.io deps.

  def build(self):
    """Builds this package and optionally runs tests for it."""
    # Build this package using CMake.
    cmake = conans.CMake(self.settings)

    cmake_test_def = "-DOOMUSE_MATH_TESTING=1" if self.options.testing else ""
    self.run("cmake %s %s %s" % (self.conanfile_directory,
                                 cmake.command_line,
                                 cmake_test_def))
    self.run("cmake --build . %s" % cmake.build_config)

    # If testing, run unit tests to make sure library works before packaging.
    if self.options.testing:
      self.run("ctest -C %s --output-on-failure" % self.settings.build_type)


  #=============================================================================
  # Configuring this built package for clients to depend on and use
  #=============================================================================

  exports = "*"  # Export all files in this dir as part of conan package.

  def package(self):
    """Copies build outputs that client needs to be able to use this library."""

    # Include headers:
    self.copy("*.h", dst="include", src="include", keep_path=True)
