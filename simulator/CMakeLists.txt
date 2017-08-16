cmake_minimum_required(VERSION 3.8)
project(simulator)

# sources
file(GLOB SRC *.cpp *.h)

# create lib
add_library(${PROJECT_NAME} SHARED ${SRC})

# box2d
find_package(Box2D REQUIRED)
if (BOX2D_FOUND)
    include_directories(${BOX2D_INCLUDE_DIR})
    target_link_libraries(${PROJECT_NAME} ${BOX2D_LIBRARIES})
endif ()

# entity
find_package(EntityX REQUIRED)
if (ENTITYX_FOUND)
    include_directories(${ENTITYX_INCLUDE_DIR})
    target_link_libraries(${PROJECT_NAME} ${ENTITYX_LIBRARIES})
endif ()

# neural networks
add_subdirectory(lib/OpenNN)
target_include_directories(${PROJECT_NAME} PUBLIC lib/OpenNN/opennn)
target_link_libraries(${PROJECT_NAME} opennn)
target_compile_options(opennn PRIVATE "-w")

# logger
include_directories(lib/plog/include)