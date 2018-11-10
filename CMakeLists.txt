cmake_minimum_required(VERSION 3.11)

project(brute_force_bip38)

set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(jsoncpp CONFIG REQUIRED)

add_executable(brute_force_bip38 main.cpp)
add_subdirectory(third_party/libwally-core)

target_link_libraries(brute_force_bip38 
    PRIVATE 
    jsoncpp_lib_static
    libwally-core
)
