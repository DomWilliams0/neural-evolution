cmake_minimum_required(VERSION 3.8)
project(neural-evolution)

set(CMAKE_CXX_STANDARD 11)

# debug
IF(CMAKE_COMPILER_IS_GNUCC)
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -g")
ENDIF(CMAKE_COMPILER_IS_GNUCC)
# version
set(PROJECT_VERSION_MAJOR 1)
set(PROJECT_VERSION_MINOR 0)

# main executable
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")
add_executable(${PROJECT_NAME} main.cpp)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
add_subdirectory(simulator)
include_directories(simulator)
target_link_libraries(${PROJECT_NAME} simulator)

add_subdirectory(renderer)
include_directories(renderer)
target_link_libraries(${PROJECT_NAME} renderer)
