# CMakeList.txt : CMake project for R-type, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (R-type "R-type.cpp" "R-type.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET R-type PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
