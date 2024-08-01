# drogon framework
find_package(Drogon CONFIG REQUIRED)
if(Drogon_FOUND)
    message(NOTICE "-- ${PROJECT_NAME}:\n   Drogon Framework package found")
else()
    message(FATAL_ERROR "-- ${PROJECT_NAME}:\n   Drogon Framework package not found")
endif()

# SKIPPED: scylladb-cpp-driver (don't know how to find the package)
