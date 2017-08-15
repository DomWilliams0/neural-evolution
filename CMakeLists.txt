cmake_minimum_required(VERSION 3.8)
project(neural-evolution)

set(CMAKE_CXX_STANDARD 11)

# debug
if(CMAKE_BUILD_TYPE STREQUAL "")
    set(CMAKE_BUILD_TYPE Debug)
endif()

# version
set(PROJECT_VERSION_MAJOR 1)
set(PROJECT_VERSION_MINOR 0)

# sources and executable
include_directories(include)
file (GLOB SRC src/*.cpp)
add_executable(${PROJECT_NAME} ${SRC})

# sfml
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
find_package(SFML REQUIRED system window graphics)
if(SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(${PROJECT_NAME} ${SFML_LIBRARIES})
endif()

# box2d
find_package(Box2D REQUIRED)
if(BOX2D_FOUND)
    include_directories(${BOX2D_INCLUDE_DIR})
    target_link_libraries(${PROJECT_NAME} ${BOX2D_LIBRARIES})
endif()

# entity
find_package(EntityX REQUIRED)
if(ENTITYX_FOUND)
    include_directories(${ENTITYX_INCLUDE_DIR})
    target_link_libraries(${PROJECT_NAME} ${ENTITYX_LIBRARIES})
endif()
