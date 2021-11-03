cmake_minimum_required(VERSION 3.19)

project(Familiar)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_subdirectory (src)

target_link_libraries(Familiar ${CONAN_LIBS})