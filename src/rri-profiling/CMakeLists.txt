cmake_minimum_required(VERSION 2.8)
find_package(Qt4 REQUIRED)

project(rri-profiling)

INCLUDE(${QT_USE_FILE})

file(GLOB_RECURSE SRC_FILES ${CMAKE_HOME_DIRECTORY}/src/${PROJECT_NAME}/*.cpp)
set(HEADER_DIR ${CMAKE_HOME_DIRECTORY}/src/${PROJECT_NAME}/headers)
file(GLOB HEADER_FILES ${HEADER_DIR}/*.h)
include_directories(${HEADER_DIR} ${rri-csv_INCLUDE_DIRS} ${rri-core_INCLUDE_DIRS} "${CMAKE_BINARY_DIR}/include")

if(STATIC_OPT)
  add_library(${PROJECT_NAME} STATIC ${SRC_FILES} ${HEADER_FILES})
else()
  add_library(${PROJECT_NAME} SHARED ${SRC_FILES} ${HEADER_FILES})
endif()
add_definitions(-D__BUILD_VERSION__="${RRI_VERSION}")

target_link_libraries(${PROJECT_NAME} ${QT_QTMAIN_LIBRARY} ${QT_LIBRARIES} rri-csv rri-core "${CMAKE_BINARY_DIR}/lib/liblpaggreg.so")

set_target_properties(${PROJECT_NAME} PROPERTIES VERSION ${RRI_VERSION} SOVERSION ${RRI_VERSION_MAJOR})
set_target_properties(${PROJECT_NAME} PROPERTIES POSITION_INDEPENDENT_CODE ON)

set(${PROJECT_NAME}_INCLUDE_DIRS ${HEADER_DIR} CACHE INTERNAL "${PROJECT_NAME}: Include Directories" FORCE)

install(TARGETS ${PROJECT_NAME} DESTINATION lib)
install(FILES ${HEADER_FILES} DESTINATION include)
