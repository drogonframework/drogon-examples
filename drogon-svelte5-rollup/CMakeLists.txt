cmake_minimum_required(VERSION 3.15)

project(drogon-svelte5-rollup)

# outputs
# all output should be on .out, so all relative path will be equal
# once we want to release it on alpha/demo/staging/production, we gonna copy all of those to "somewhere"
set(EXECUTABLE_OUTPUT_PATH         "${CMAKE_SOURCE_DIR}/.out")
set(ARCHIVE_OUTPUT_DIRECTORY       "${CMAKE_SOURCE_DIR}/.out")
set(RUNTIME_OUTPUT_DIRECTORY       "${CMAKE_SOURCE_DIR}/.out")
set(LIBRARY_OUTPUT_DIRECTORY       "${CMAKE_SOURCE_DIR}/.out")
set(CMAKE_PDB_OUTPUT_DIRECTORY     "${CMAKE_SOURCE_DIR}/.out")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/.out")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/.out")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/.out")

# create necessary dir/s
## .logs dir for: backend
if(NOT EXISTS "${CMAKE_SOURCE_DIR}/.logs")
    file(MAKE_DIRECTORY "${CMAKE_SOURCE_DIR}/.logs")
endif()

# cxx standard required
if(NOT DEFINED CMAKE_CXX_STANDARD_REQUIRED)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
endif()

# cxx extensions
if(NOT DEFINED CMAKE_CXX_EXTENSIONS)
    set(CMAKE_CXX_EXTENSIONS OFF)
endif()

# cxx standard
if(NOT DEFINED CMAKE_CXX_STANDARD)
    set(CMAKE_CXX_STANDARD 17)
endif()

# cxx flags
if(NOT DEFINED CMAKE_CXX_FLAGS)
    set(CMAKE_CXX_FLAGS)
endif()

# force rules
# c++17 at minimum #1
if(${CMAKE_CXX_STANDARD} LESS 17)
    set(CMAKE_CXX_STANDARD 17)
    message(AUTHOR_WARNING "can't use below than c++17, forcing to c++17 #1")
endif()
# c++17 at minimum #2
if("${CMAKE_CXX_STANDARD}" STRLESS 17)
    set(CMAKE_CXX_STANDARD 17)
    message(AUTHOR_WARNING "can't use below than c++17, forcing to c++17 #2")
endif()

# build type
if(NOT DEFINED CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif()
if(CMAKE_BUILD_TYPE STREQUAL "")
    set(CMAKE_BUILD_TYPE "Debug")
endif()

# add std c++ if cxx flags is not found
set(PROJECT_CXX_STANDARD)
set(PROJECT_CXX_STANDARD_ARGS)
if(MSVC)
    set(PROJECT_CXX_STANDARD_ARGS "/std:c++${CMAKE_CXX_STANDARD}")
else()
    set(PROJECT_CXX_STANDARD_ARGS "-std=c++${CMAKE_CXX_STANDARD}")
endif()
string(FIND "${CMAKE_CXX_FLAGS}" "${PROJECT_CXX_STANDARD_ARGS}" PROJECT_CXX_STANDARD)
if(PROJECT_CXX_STANDARD EQUAL -1)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${PROJECT_CXX_STANDARD_ARGS}")
endif()

# internal variable
set(PROJECT_IS_DEBUG)

# set PROJECT_IS_DEBUG based on CMAKE_BUILD_TYPE
if(CMAKE_BUILD_TYPE STREQUAL "Release" OR CMAKE_BUILD_TYPE STREQUAL "MinSizeRel")
    set(PROJECT_IS_DEBUG false)
else()
    set(PROJECT_IS_DEBUG true)
endif()

include(CheckIncludeFileCXX)
include(GenerateExportHeader)
include(CMakeDependentOption)
include(CMakeFindDependencyMacro)
include(CMakePackageConfigHelpers)
include(FindPackageHandleStandardArgs)

# checking required pacakges
find_package(Drogon CONFIG REQUIRED)

# load lib/s first
add_subdirectory(sources/library/libbackend _deps/libbackend)

# adding executeable
add_subdirectory(sources/backend _exec/backend)

# generate config for libfrontend
configure_file(
    ${CMAKE_SOURCE_DIR}/sources/library/libfrontend/src/config.in.js
    ${CMAKE_SOURCE_DIR}/sources/library/libfrontend/src/config.js
)
