cmake_minimum_required(VERSION 3.15)
project(backend_api)

add_executable(${PROJECT_NAME}
    src/backend_api/main.h
    src/backend_api/main.cc
)

set(PREFIX "")
set(CMAKE_STATIC_LIBRARY_PREFIX "")
set(CMAKE_SHARED_LIBRARY_PREFIX "")

target_link_libraries(${PROJECT_NAME} PRIVATE Drogon::Drogon)
target_link_libraries(${PROJECT_NAME} PRIVATE internalcpp)
target_link_libraries(${PROJECT_NAME} PRIVATE drogon-scylladb-crud-basic)

aux_source_directory(src/backend_api/controllers BACKEND_API_CTL_DIR)
aux_source_directory(src/backend_api/plugins BACKEND_API_CTL_PLUGINS)

target_sources(${PROJECT_NAME}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${BACKEND_API_CTL_DIR}
        ${BACKEND_API_CTL_PLUGINS}
)

target_include_directories(${PROJECT_NAME}
    PUBLIC
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}>/src
)
