cmake_minimum_required(VERSION 3.2)
project(google_test_boilterplate)

#
# Building in-tree is not allowed (we take care of your craziness).
#

if(CMAKE_SOURCE_DIR STREQUAL CMAKE_BINARY_DIR)
    message(FATAL_ERROR "Prevented in-tree built. Please create a build directory outside of the source code and call cmake from there. Thank you.")
endif()

#
# Project configuration
#

project(google_test_boilterplate VERSION 0.0.1)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

set(PROJECT_AUTHOR "Stefano Fiorentino")
set(PROJECT_AUTHOR_EMAIL "stefano.fiore84@gmail.com")

message("--")
message("-- ${PROJECT_NAME} v${PROJECT_VERSION} (${CMAKE_BUILD_TYPE})")
message("-- Copyright (c) 2016-2019 ${PROJECT_AUTHOR} <${PROJECT_AUTHOR_EMAIL}>")
message("--")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(NOT MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -g -DDEBUG")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Os -DRELEASE")
endif()

#
# CMake configuration
#

set(PROJECT_CMAKE_IN ${google_test_boilterplate_SOURCE_DIR}/cmake/in)
set(PROJECT_DEPS_DIR ${google_test_boilterplate_SOURCE_DIR}/deps)
set(PROJECT_SRC_DIR ${google_test_boilterplate_SOURCE_DIR}/src)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY bin)

#
# Referenced packages
#

set(THREADS_PREFER_PTHREAD_FLAG ON)

include(FindThreads)
find_package(Doxygen 1.8)

#
# Referenced directories and targets
#

if(DOXYGEN_FOUND)
    add_subdirectory(docs)
endif()

if(BUILD_TESTING)
    set(BUILD_TESTING OFF)

    set(GOOGLETEST_DEPS_DIR ${PROJECT_DEPS_DIR}/googletest)
    set(LIBUV_DEPS_DIR ${PROJECT_DEPS_DIR}/libuv)

    configure_file(${PROJECT_CMAKE_IN}/deps.in ${PROJECT_DEPS_DIR}/CMakeLists.txt)
    execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" . WORKING_DIRECTORY ${PROJECT_DEPS_DIR})
    execute_process(COMMAND ${CMAKE_COMMAND} --build . WORKING_DIRECTORY ${PROJECT_DEPS_DIR})

    # gtest, gtest_main, gmock and gmock_main targets are available from now on
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    add_subdirectory(${GOOGLETEST_DEPS_DIR})

    set(BUILD_TESTING ON)
    enable_testing()

    add_subdirectory(test)
endif()

#
# Install headers
#

INCLUDE(GNUInstallDirs)

IF(NOT DEFINED INCLUDE_INSTALL_DIR)
    SET(INCLUDE_INSTALL_DIR "${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_INCLUDEDIR}")
ENDIF()

file(GLOB HEADERS src/uvw/*.hpp)

install(
        FILES ${HEADERS}
        COMPONENT ${PROJECT_NAME}
        DESTINATION ${INCLUDE_INSTALL_DIR}/uvw
        PERMISSIONS OWNER_READ OWNER_WRITE GROUP_READ WORLD_READ
)

install(
        FILES src/uvw.hpp
        COMPONENT ${PROJECT_NAME}
        DESTINATION ${INCLUDE_INSTALL_DIR}
        PERMISSIONS OWNER_READ OWNER_WRITE GROUP_READ WORLD_READ
)