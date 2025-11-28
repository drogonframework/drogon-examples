cmake_minimum_required(VERSION 3.15)

project(dgkafka)

add_library(${PROJECT_NAME}
    "lib.cc"
    #
    "src/dgkafka/util_helper.cc"
    "src/dgkafka/producer_engine.cc"
)

if (NOT DEFINED DGKAFKA_DELAY)
	set(DGKAFKA_DELAY 500) # in milliseconds
endif()
message(NOTICE "using 500ms as default delay")
if (NOT DEFINED DGKAFKA_STOCK_TRADE_TOPIC)
	set(DGKAFKA_STOCK_TRADE_TOPIC "consume-stock-trade")
endif()

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

target_include_directories(${PROJECT_NAME}
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>/inc
)
target_sources(${PROJECT_NAME}
	PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src/dgkafka
)

configure_file(
	${CMAKE_CURRENT_SOURCE_DIR}/inc/dgkafka/config.in.hh
	${CMAKE_CURRENT_SOURCE_DIR}/inc/dgkafka/config.hh
)

