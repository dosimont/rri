#Can be edited


OPTION(BUILD_BIN "Build a static library" ON)
OPTION(BUILD_UI "Build a static library" OFF)

#Should not be modified

project(RRI)
cmake_minimum_required(VERSION 2.8)

set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")

set(RRI_VERSION_MAJOR "0")
set(RRI_VERSION_MINOR "1")
set(RRI_VERSION_PATCH "0")
set(RRI_VERSION "${RRI_VERSION_MAJOR}.${RRI_VERSION_MINOR}.${RRI_VERSION_PATCH}")

add_definitions(-D__BUILD_VERSION__="${RRI_VERSION}")



aux_source_directory(src SRC_LIST)
if(STATIC)
    add_library(${PROJECT_NAME} STATIC ${SRC_LIST})
else(STATIC)
    add_library(${PROJECT_NAME} SHARED ${SRC_LIST})
endif(STATIC)

set_target_properties(${PROJECT_NAME} PROPERTIES VERSION ${RRI_VERSION} SOVERSION ${RRI_VERSION_MAJOR})

install(TARGETS ${PROJECT_NAME} DESTINATION lib)
install(DIRECTORY src/ DESTINATION include/${PROJECT_NAME} FILES_MATCHING PATTERN "*.h")

export(PACKAGE ${PROJECT_NAME})

add_custom_target(uninstall "${CMAKE_COMMAND}" -P "${CMAKE_MODULE_PATH}/uninstall.cmake")
