#-------------------------------------------------------------------
# This file is part of the CMake build system for R-Type
# For the latest info, see https://github.com/legolas-tek/r-type
#
# The contents of this file are placed in the public domain. Feel
# free to make use of it in any way you like.
#-------------------------------------------------------------------

cmake_minimum_required (VERSION 3.8)

add_library (networking SHARED)

set_target_properties (networking PROPERTIES
    FRAMEWORK TRUE
)

target_link_libraries (networking
    PRIVATE
    asio
    PUBLIC
    engine
)

option (DEBUG_NETWORK "Enable network debug" OFF)

if (DEBUG_NETWORK)
    target_compile_definitions (networking
        PRIVATE
        DEBUG_NETWORK
    )
endif (DEBUG_NETWORK)

target_include_directories (networking
    PUBLIC  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/includes>
            $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/>
)

target_sources (networking
    PRIVATE
    ./sources/TcpNetManager.cpp
    ./sources/UdpNetManager.cpp
    ./sources/CircularBuffer.cpp
    ./sources/Snapshot.cpp
    ./sources/Sync.cpp
    ./sources/NetworkServerSystem.cpp
    ./sources/NetworkClientSystem.cpp
    ./sources/LobbyClient.cpp
    ./sources/TcpServer.cpp
    ./sources/LobbyRemoteClient.cpp
    ./sources/Lobby.cpp
    ./sources/DiffLogger.cpp
)

install(TARGETS networking
        RUNTIME DESTINATION bin
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        FRAMEWORK DESTINATION bin
)
