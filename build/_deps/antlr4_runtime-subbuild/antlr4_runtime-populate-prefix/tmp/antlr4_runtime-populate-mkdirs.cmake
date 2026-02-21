# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file LICENSE.rst or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION ${CMAKE_VERSION}) # this file comes with cmake

# If CMAKE_DISABLE_SOURCE_CHANGES is set to true and the source directory is an
# existing directory in our source tree, calling file(MAKE_DIRECTORY) on it
# would cause a fatal error, even though it would be a no-op.
if(NOT EXISTS "/home/dan/Projects/hobbyCAD/build/_deps/antlr4_runtime-src")
  file(MAKE_DIRECTORY "/home/dan/Projects/hobbyCAD/build/_deps/antlr4_runtime-src")
endif()
file(MAKE_DIRECTORY
  "/home/dan/Projects/hobbyCAD/build/_deps/antlr4_runtime-build"
  "/home/dan/Projects/hobbyCAD/build/_deps/antlr4_runtime-subbuild/antlr4_runtime-populate-prefix"
  "/home/dan/Projects/hobbyCAD/build/_deps/antlr4_runtime-subbuild/antlr4_runtime-populate-prefix/tmp"
  "/home/dan/Projects/hobbyCAD/build/_deps/antlr4_runtime-subbuild/antlr4_runtime-populate-prefix/src/antlr4_runtime-populate-stamp"
  "/home/dan/Projects/hobbyCAD/build/_deps/antlr4_runtime-subbuild/antlr4_runtime-populate-prefix/src"
  "/home/dan/Projects/hobbyCAD/build/_deps/antlr4_runtime-subbuild/antlr4_runtime-populate-prefix/src/antlr4_runtime-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/home/dan/Projects/hobbyCAD/build/_deps/antlr4_runtime-subbuild/antlr4_runtime-populate-prefix/src/antlr4_runtime-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/home/dan/Projects/hobbyCAD/build/_deps/antlr4_runtime-subbuild/antlr4_runtime-populate-prefix/src/antlr4_runtime-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
