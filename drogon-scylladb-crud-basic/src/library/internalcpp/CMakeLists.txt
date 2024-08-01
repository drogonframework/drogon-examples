cmake_minimum_required(VERSION 3.15)
project(internalcpp)

add_library(${PROJECT_NAME}
    src/internalcpp/base/config.h
    # src/libbackend/base/config.cc
)

set(PREFIX "")
set(CMAKE_STATIC_LIBRARY_PREFIX "")
set(CMAKE_SHARED_LIBRARY_PREFIX "")

target_link_libraries(${PROJECT_NAME} PRIVATE Drogon::Drogon)

include(GenerateExportHeader)

generate_export_header(${PROJECT_NAME}
    EXPORT_FILE_NAME
        ${PROJECT_SOURCE_DIR}/src/internalcpp/base/export.h
)

configure_file(
    ${PROJECT_SOURCE_DIR}/src/internalcpp/base/config.in.h
    ${PROJECT_SOURCE_DIR}/src/internalcpp/base/config.h
)

aux_source_directory(src/internalcpp/base INTERNALCPP_DIR_BASE)
aux_source_directory(src/internalcpp/enums INTERNALCPP_DIR_ENUMS)
aux_source_directory(src/internalcpp/interfaces INTERNALCPP_DIR_INTERFACES)
aux_source_directory(src/internalcpp/modules INTERNALCPP_DIR_MODULES)
aux_source_directory(src/internalcpp/types INTERNALCPP_DIR_TYPES)

target_sources(${PROJECT_NAME}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${INTERNALCPP_DIR_BASE}
        ${INTERNALCPP_DIR_ENUMS}
        ${INTERNALCPP_DIR_INTERFACES}
        ${INTERNALCPP_DIR_MODULES}
        ${INTERNALCPP_DIR_TYPES}
)

target_include_directories(${PROJECT_NAME}
    PUBLIC
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}>/src
)
