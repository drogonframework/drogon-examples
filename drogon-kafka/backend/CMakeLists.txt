cmake_minimum_required(VERSION 3.20)

project(backend_drogon_kafka)

add_executable(${PROJECT_NAME}
    # core
    "main.cc"
    # plugin
    "plugin_drogon_kafka.cc"
    # controllers
    "ctl_ws_stock_trade.cc"
)

target_link_libraries(${PROJECT_NAME} PRIVATE Drogon::Drogon)
if(SHARED_LIB_LZ4_FILE)
    target_link_libraries(${PROJECT_NAME} PRIVATE "${SHARED_LIB_LZ4_FILE}")
else()
    target_link_libraries(${PROJECT_NAME} PRIVATE lz4)
endif()
if(SHARED_LIB_RDKAFKA_FILE)
    target_link_libraries(${PROJECT_NAME} PRIVATE "${SHARED_LIB_RDKAFKA_FILE}")
    target_link_libraries(${PROJECT_NAME} PRIVATE CppKafka::cppkafka)
else()
    message(FATAL_ERROR "ERROR ${PROJECT_NAME}: can't link rdkafka lib")
endif()
target_link_libraries(${PROJECT_NAME} PRIVATE dgkafka)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/library/dgkafka/inc
)

