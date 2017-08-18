cmake_minimum_required(VERSION 3.8)
project(renderer)

# sources
file(GLOB SRC *.cpp *.h)

# create lib
add_library(${PROJECT_NAME} SHARED ${SRC})

# simulator
include_directories(${simulator_SOURCE_DIR})

# sfml
find_package(SFML REQUIRED system window graphics)
if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(${PROJECT_NAME} ${SFML_LIBRARIES})
endif ()

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

# font
set(FONT_SRC "${PROJECT_SOURCE_DIR}/font.ttf")
set(FONT_DST "${CMAKE_CURRENT_BINARY_DIR}/font.ttf")
add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E create_symlink ${FONT_SRC} ${FONT_DST}
        DEPENDS ${FONT_DST}
)
