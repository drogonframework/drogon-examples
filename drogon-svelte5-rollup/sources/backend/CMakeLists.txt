cmake_minimum_required(VERSION 3.15)

project(backend)

# BACKEND: www
add_executable(backend_www backend_www/main.cc)

target_link_libraries(backend_www PRIVATE libbackend)
target_link_libraries(backend_www PRIVATE Drogon::Drogon)

drogon_create_views(backend_www
    ${CMAKE_CURRENT_SOURCE_DIR}/backend_www/views
    ${CMAKE_CURRENT_BINARY_DIR}
)

# link & include dir/s
link_directories(   "${CMAKE_SOURCE_DIR}/sources/library/libbackend/src")
include_directories("${CMAKE_SOURCE_DIR}/sources/library/libbackend/src")

target_include_directories(backend_www
    PRIVATE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>/backend_www
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}>/sources/library/libbackend/src
)

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/backend_www BACKEND_WWW_DIR)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/backend_www/controllers BACKEND_WWW_DIR_CTL)

target_sources(backend_www
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${BACKEND_WWW_DIR}
        ${BACKEND_WWW_DIR_CTL}
)
