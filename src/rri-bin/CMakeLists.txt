cmake_minimum_required(VERSION 2.8)
find_package(Qt4 REQUIRED)

project(rri)

INCLUDE(${QT_USE_FILE})

file(GLOB_RECURSE SRC_FILES ${CMAKE_HOME_DIRECTORY}/src/rri-bin/sources/*.cpp)
set(HEADER_DIR ${CMAKE_HOME_DIRECTORY}/src/rri-bin/headers)
file(GLOB HEADER_FILES ${HEADER_DIR}/*.h)

include_directories(${HEADER_DIR} ${rri-csv_INCLUDE_DIRS} ${rri-core_INCLUDE_DIRS} ${rri-prv_INCLUDE_DIRS} ${rri-profiling_INCLUDE_DIRS} "${CMAKE_BINARY_DIR}/include")

add_executable(${PROJECT_NAME} ${SRC_FILES} ${HEADER_FILES})

add_definitions(-D__BUILD_VERSION__="${RRI_VERSION}")

target_link_libraries(${PROJECT_NAME} ${QT_QTMAIN_LIBRARIES} ${QT_LIBRARIES} rri-csv rri-core rri-prv rri-profiling "${CMAKE_BINARY_DIR}/lib/liblpaggreg.so")

set_target_properties(${PROJECT_NAME} PROPERTIES VERSION ${RRI_VERSION} SOVERSION ${RRI_VERSION_MAJOR})

install(TARGETS ${PROJECT_NAME} DESTINATION bin)
