include(CheckIncludeFileCXX)

if (CMAKE_BUILD_TYPE STREQUAL "")
    set(PROJECT_BUILD_TYPE 1)
elseif(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(PROJECT_BUILD_TYPE 1)
elseif(CMAKE_BUILD_TYPE STREQUAL "Profile")
    set(PROJECT_BUILD_TYPE 2)
elseif(CMAKE_BUILD_TYPE STREQUAL "MinSizeRel")
    set(PROJECT_BUILD_TYPE 3)
elseif(CMAKE_BUILD_TYPE STREQUAL "RelWithDebInfo")
    set(CMAKE_BUILD_TYPE 4)
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    set(CMAKE_BUILD_TYPE 5)
else()
    message(FATAL_ERROR "-DCMAKE_BUILD_TYPE is not recognized")
endif()

set(EXECUTABLE_OUTPUT_PATH          ${CMAKE_CURRENT_SOURCE_DIR}/bin/${PROJECT_BUILD_TAGET_DIRECTORY})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY  ${CMAKE_CURRENT_SOURCE_DIR}/bin/${PROJECT_BUILD_TAGET_DIRECTORY})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY  ${CMAKE_CURRENT_SOURCE_DIR}/bin/${PROJECT_BUILD_TAGET_DIRECTORY})
set(CMAKE_PDB_OUTPUT_DIRECTORY      ${CMAKE_CURRENT_SOURCE_DIR}/bin/${PROJECT_BUILD_TAGET_DIRECTORY})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY  ${CMAKE_CURRENT_SOURCE_DIR}/bin/${PROJECT_BUILD_TAGET_DIRECTORY})
