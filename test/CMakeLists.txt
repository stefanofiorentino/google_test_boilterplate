#
# Tests configuration
#

set(GOOGLE_TEST_BOILERPLATE_SRC_DIR ${PROJECT_SRC_DIR})

if(WIN32)
    set(WINSOCK2 ws2_32)
elseif(NOT APPLE)
    find_library(LIBRT rt)
endif()

set(
        COMMON_LINK_LIBS
        gtest_main
        ${LIBRT}
        Threads::Threads
        ${WINSOCK2}
)

add_library(odr OBJECT odr.cpp)
target_include_directories(odr PRIVATE ${GOOGLE_TEST_BOILERPLATE_SRC_DIR})

macro(ADD_GOOGLE_TEST_BOILERPLATE_TEST TEST_NAME TEST_SOURCE)
    add_executable(${TEST_NAME} $<TARGET_OBJECTS:odr> ${TEST_SOURCE})
    target_include_directories(${TEST_NAME} PRIVATE ${GOOGLE_TEST_BOILERPLATE_SRC_DIR})
    target_link_libraries(${TEST_NAME} PRIVATE ${COMMON_LINK_LIBS})
    add_test(NAME uvw_${TEST_NAME} COMMAND $<TARGET_FILE:${TEST_NAME}>)
endmacro()

macro(ADD_GOOGLE_TEST_BOILERPLATE_DIR_TEST TEST_NAME TEST_SOURCE)
    ADD_GOOGLE_TEST_BOILERPLATE_TEST(${TEST_NAME} ${TEST_SOURCE})
    string(TOUPPER "${TEST_NAME}" TEST_NAME_UPPER)
    set(TEST_DIR_VAR "TARGET_${TEST_NAME_UPPER}_DIR")
    set(TEST_DIR ${CMAKE_CURRENT_BINARY_DIR}/${TEST_NAME})
    file(MAKE_DIRECTORY ${TEST_DIR})
    target_compile_definitions(${TEST_NAME} PRIVATE ${TEST_DIR_VAR}="${TEST_DIR}")
endmacro()

macro(ADD_GOOGLE_TEST_BOILERPLATE_LIB_TEST TEST_NAME TEST_SOURCE)
    ADD_GOOGLE_TEST_BOILERPLATE_TEST(${TEST_NAME} ${TEST_SOURCE})
    target_link_libraries(${TEST_NAME} PRIVATE ${CMAKE_DL_LIBS})
    target_compile_definitions(${TEST_NAME} PRIVATE TARGET_LIB_SO="$<TARGET_FILE:uv>")
endmacro()

# List of available targets

ADD_GOOGLE_TEST_BOILERPLATE_TEST(main main.cpp)
ADD_GOOGLE_TEST_BOILERPLATE_TEST(timer uvw/timer.cpp)
