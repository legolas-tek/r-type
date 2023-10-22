set (CPACK_PACKAGE_NAME "R-Type")
set (CPACK_RESOURCE_FILE_LICENSE
        "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")
set (CPACK_PACKAGE_VERSION ${CMAKE_PROJECT_VERSION})

if (WIN32)
    set (CPACK_GENERATOR "NSIS" CACHE STRING "Semicolon separated list of generators")
else ()
    set (CPACK_GENERATOR "STGZ;ZIP" CACHE STRING "Semicolon separated list of generators")
endif ()

include (CPack)
