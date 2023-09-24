cmake_minimum_required (VERSION 3.8)

add_executable("r-type_client")

target_link_libraries("r-type_client"
    PRIVATE asio
)

target_sources("r-type_client"
    PRIVATE ./sources/main.cpp
)
