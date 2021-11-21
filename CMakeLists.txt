cmake_minimum_required(VERSION 3.19)

project(Familiar)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

include_directories(src)
include_directories(src/FamiliarEngine )
include_directories(src/FamiliarGame)

add_subdirectory(src)
