cmake_minimum_required(VERSION 3.20)

project(drogon-kafka)

# outputs
# all output should be on out, so all relative path will be equal
# once we want to release it on alpha/demo/staging/production,
# we gonna copy all of those to "somewhere"
set(EXECUTABLE_OUTPUT_PATH         "${CMAKE_SOURCE_DIR}/out")
set(ARCHIVE_OUTPUT_DIRECTORY       "${CMAKE_SOURCE_DIR}/out")
set(RUNTIME_OUTPUT_DIRECTORY       "${CMAKE_SOURCE_DIR}/out")
set(LIBRARY_OUTPUT_DIRECTORY       "${CMAKE_SOURCE_DIR}/out")
set(CMAKE_PDB_OUTPUT_DIRECTORY     "${CMAKE_SOURCE_DIR}/out")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/out")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/out")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/out")

if(NOT DEFINED CMAKE_CXX_STANDARD)
    set(CMAKE_CXX_STANDARD 17)
endif()
if(NOT DEFINED CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif()
if(NOT DEFINED CMAKE_CXX_FLAGS)
    set(CMAKE_CXX_FLAGS "-std=c++17")
endif()

include(CheckIncludeFileCXX)
include(GenerateExportHeader)
include(CMakeDependentOption)
include(CMakeFindDependencyMacro)
include(CMakePackageConfigHelpers)
include(FindPackageHandleStandardArgs)

find_package(Drogon CONFIG REQUIRED)
#[[
NOTE:
- if you could find lz4 by using RdKafka config,
    you can use below code
```cmake
# LZ4
find_package(LZ4 CONFIG)
# RdKafka
find_package(RdKafka CONFIG)
```
===
- in linux, lz4 may not considered found,
    but if you already installed it,
    target_link_libraries for the project may able to detect it
===
"warning will not create error,
I had a bit trouble to find package from cmake file,
so this configuration mostly depend on exported $PATH" - @prothegee
#]]
set(SHARED_LIB_LZ4_FILE)
find_file(SHARED_LIB_LZ4_FILE "liblz4.so")
if(SHARED_LIB_LZ4_FILE)
    message(NOTICE "liblz4 found: ${SHARED_LIB_LZ4_FILE}")
else()
    message(AUTHOR_WARNING "liblz4 not found; program may fail to run")
endif()
# rdkafka
set(SHARED_LIB_RDKAFKA_FILE)
find_file(SHARED_LIB_RDKAFKA_FILE "librdkafka++.so")
if(SHARED_LIB_RDKAFKA_FILE)
    message(NOTICE "librdkafka found: ${SHARED_LIB_RDKAFKA_FILE}")
else()
    message(AUTHOR_WARNING "librdkafka not found; program may fail to run")
endif()
# cppkafka
find_package(CppKafka REQUIRED)

# libs: rdkafka (internal)
add_subdirectory(library/dgkafka dgkafka)

# backend: backend_drogon_kafka
add_subdirectory(backend backend_drogon_kafka)

# tools: producer_ctl
add_subdirectory(tools/producer_ctl producer_ctl)

