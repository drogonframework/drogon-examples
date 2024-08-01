cmake_minimum_required(VERSION 3.15)
project(drogon-scylladb-crud-basic)

add_library(${PROJECT_NAME}
    src/drogon_scylladb_crud_basic/coredb.h
    src/drogon_scylladb_crud_basic/coredb.cc
)

set(PREFIX "")
set(CMAKE_STATIC_LIBRARY_PREFIX "")
set(CMAKE_SHARED_LIBRARY_PREFIX "")

target_link_libraries(${PROJECT_NAME} PRIVATE Drogon::Drogon)
target_link_libraries(${PROJECT_NAME} PRIVATE internalcpp)
target_link_libraries(${PROJECT_NAME} PRIVATE scylla-cpp-driver)

aux_source_directory(src/drogon_scylladb_crud_basic/interfaces DROGON_SCYLLADB_CRUD_BASIC_DIR_INTERFACES)
aux_source_directory(src/drogon_scylladb_crud_basic/tables DROGON_SCYLLADB_CRUD_BASIC_DIR_TABLES)
aux_source_directory(src/drogon_scylladb_crud_basic/types DROGON_SCYLLADB_CRUD_BASIC_DIR_TYPES)

target_sources(${PROJECT_NAME}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${DROGON_SCYLLADB_CRUD_BASIC_DIR_INTERFACES}
        ${DROGON_SCYLLADB_CRUD_BASIC_DIR_TABLES}
        ${DROGON_SCYLLADB_CRUD_BASIC_DIR_TYPES}
)

target_include_directories(${PROJECT_NAME}
    PUBLIC
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}>/src
)
