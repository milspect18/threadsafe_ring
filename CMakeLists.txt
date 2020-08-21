# TOP-LEVEL CMakeLists for threadsafe_ring
cmake_minimum_required(VERSION 3.1...3.16)

if(${CMAKE_VERSION} VERSION_LESS 3.12)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif()

project(
    pricetec_ringbuffer
    VERSION 0.0.1
    DESCRIPTION "Simple ring buffer with thread safe decorator"
    LANGUAGES CXX
)

# Create a var for the project specific include dir
# then add the dir to the compiler includes path
set(PROJECT_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/inc/ringbuffer)

option(BUILD_EXAMPLE "ON to build the example projects. OFF to omit. (OFF by default" OFF)
option(BUILD_TESTS "ON to build the tests and runner. OFF to omit. (OFF by default" OFF)

if(${BUILD_EXAMPLE})
    add_subdirectory(examples)
endif()

if(${BUILD_TESTS})
    add_subdirectory(test)
endif()
