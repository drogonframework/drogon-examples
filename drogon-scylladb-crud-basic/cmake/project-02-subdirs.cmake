# library directories
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/library/internalcpp)

# db directories
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/db/drogon_scylladb_crud_basic)

# backend directories
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/backend/backend_api)
