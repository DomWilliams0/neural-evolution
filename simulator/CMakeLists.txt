cmake_minimum_required(VERSION 3.8)
project(simulator)

add_definitions(-Wall)

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
add_subdirectory(lib/entityx)
include_directories(${ENTITYX_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} ${ENTITYX_LIBRARIES})

# neural networks
#add_definitions(-w)
add_subdirectory(lib/OpenNN/opennn)
add_subdirectory(lib/OpenNN/tinyxml2)
target_include_directories(${PROJECT_NAME} PUBLIC lib/OpenNN/opennn)
target_link_libraries(${PROJECT_NAME} opennn)
message(STATUS "Found OpenNN")

# logger
include_directories(lib/plog/include)
message(STATUS "Found plog")

# noise
add_subdirectory(lib/libnoise)
target_include_directories(${PROJECT_NAME} PUBLIC lib/libnoise/include)
target_link_libraries(${PROJECT_NAME} libnoise)
message(STATUS "Found libnoise")

# events
include_directories(lib/EventBus/src)
file(GLOB EVENTBUS_SRC lib/EventBus/src/event/*)
add_library(EventBus SHARED ${EVENTBUS_SRC})
target_link_libraries(${PROJECT_NAME} EventBus)
message(STATUS "Found EventBus")
