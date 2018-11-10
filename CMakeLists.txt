cmake_minimum_required(VERSION 3.11)

project(brute_force_bip38)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(brute_force_bip38 src/main.cpp)
add_subdirectory(third_party/libwally-core)

target_link_libraries(brute_force_bip38 
    PRIVATE 
    libwally-core
)
