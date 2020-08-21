# threadsafe_ring/test/CMakeLists.txt
cmake_minimum_required(VERSION 3.1...3.16)

if(${CMAKE_VERSION} VERSION_LESS 3.12)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif()

set(
    TEST_SRC
    test_ringbuffer.cpp
)

set(
    TEST_HDR
    catch.hpp
)

find_package(Threads REQUIRED)

add_executable(test_runner ${TEST_SRC} ${TEST_HDR})

target_include_directories(test_runner PUBLIC ${PROJECT_INCLUDE_DIR})
target_link_libraries(example PRIVATE Threads::Threads)
target_compile_features(test_runner PUBLIC cxx_std_17)
