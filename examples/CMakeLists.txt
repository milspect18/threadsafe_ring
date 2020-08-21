# iaaudio/example/CMakeLists.txt
cmake_minimum_required(VERSION 3.1...3.16)

if(${CMAKE_VERSION} VERSION_LESS 3.12)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif()

add_executable(example main.cpp)

target_include_directories(example PUBLIC ${PROJECT_INCLUDE_DIR})
target_compile_features(example PUBLIC cxx_std_17)
