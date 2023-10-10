#-------------------------------------------------------------------
# This file is part of the CMake build system for R-Type
# For the latest info, see https://github.com/legolas-tek/r-type
#
# The contents of this file are placed in the public domain. Feel
# free to make use of it in any way you like.
#-------------------------------------------------------------------

cmake_minimum_required (VERSION 3.8)

project (R-Type)

enable_language (CXX)
set (CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_STANDARD_REQUIRED ON)

set (CMAKE_MODULE_PATH
  "${PROJECT_SOURCE_DIR}/cmake"
)

include (CPack)
include (dependencies)

add_subdirectory (./client/)
add_subdirectory (./server/)
add_subdirectory (./tests/)

add_subdirectory (./libs/engine/)
add_subdirectory (./libs/networking/)
add_subdirectory (./libs/rendering/)
add_subdirectory (./libs/rtype/)
