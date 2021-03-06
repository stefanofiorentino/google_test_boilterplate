#
# Doxygen configuration (documentation)
#

set(TARGET_DOCS docs)

set(DOXY_IN_FILE doxy.in)

set(DOXY_SOURCE_DIRECTORY ${PROJECT_SRC_DIR})
set(DOXY_DOCS_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
set(DOXY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
set(DOXY_CFG_FILE doxy.cfg)

configure_file(${DOXY_IN_FILE} ${DOXY_CFG_FILE} @ONLY)

add_custom_target(
        ${TARGET_DOCS}
        COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/${DOXY_CFG_FILE}
        WORKING_DIRECTORY ${google_test_boilterplate_SOURCE_DIR}
        VERBATIM
        SOURCES ${DOXY_IN_FILE}
)

install(
        DIRECTORY ${DOXY_OUTPUT_DIRECTORY}/html
        DESTINATION share/${PROJECT_NAME}-${PROJECT_VERSION}/
)
