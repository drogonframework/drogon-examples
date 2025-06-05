cmake_minimum_required(VERSION 3.15)

project(libbackend)

# this is somehow good and somewhat is not
# in linux environment if not modify the output, output name will have `lib` prefix
set(PREFIX                      "")
set(OUTPUT_NAME                 "")
set(IMPORT_PREFIX               "")
set(CMAKE_STATIC_LIBRARY_PREFIX "")
set(CMAKE_SHARED_LIBRARY_PREFIX "")

set(LIBBACKEND_SOURCES_FILES
    # root
    src/libbackend/lib.cc
    # functions
    src/libbackend/functions/utility_functions.cc
    # interfaces
    src/libbackend/interfaces/idrogon_ctl_helper.cc
)

add_library(libbackend ${LIBBACKEND_SOURCES_FILES})

target_link_libraries(libbackend PRIVATE Drogon::Drogon)

target_include_directories(libbackend
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/src/libbackend/config.in.hh
    ${CMAKE_CURRENT_SOURCE_DIR}/src/libbackend/config.hh
)
