cmake_minimum_required (VERSION 3.8)

project ("R-Type")

enable_language(CXX)

include(FetchContent)

FetchContent_Declare(asio
    GIT_REPOSITORY  https://github.com/chriskohlhoff/asio.git
    GIT_TAG         asio-1-12-2
    GIT_SHALLOW     TRUE
    SOURCE_DIR      ${CMAKE_CURRENT_SOURCE_DIR}/libs/deps/
)

FetchContent_GetProperties(asio)

if(NOT asio_POPULATED)
    message(STATUS "Fetching asio ${ASIO_CMAKE_ASIO_TAG}")

    if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/libs/deps/asio")
        set(FETCHCONTENT_SOURCE_DIR_ASIO "${CMAKE_CURRENT_SOURCE_DIR}/libs/deps/asio")
        message(STATUS "Asio source found at ${CMAKE_CURRENT_SOURCE_DIR}/libs/deps/ skip fetching.")
    endif()

    FetchContent_Populate(asio)
    message(STATUS "Populating Asio done; src at ${asio_SOURCE_DIR}")
endif()

add_library(asio INTERFACE)

target_include_directories(asio
    INTERFACE ${asio_SOURCE_DIR}/asio/include
)

target_include_directories(asio
    INTERFACE ${asio_SOURCE_DIR}/asio/include
)

target_compile_definitions(asio
    INTERFACE
        ASIO_STANDALONE
        ASIO_NO_DEPRECATED
)
target_link_libraries(asio
    INTERFACE pthread
)

add_subdirectory("./client/")
add_subdirectory("./server/")
