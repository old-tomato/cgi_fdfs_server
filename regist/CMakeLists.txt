cmake_minimum_required(VERSION 3.4)
project(regist)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/../out)

set(LINK_DIR "/usr/local/lib")
link_directories(${LINK_DIR})

set(INCLUDE_DIR "/usr/local/include")
include_directories(${INCLUDE_DIR})

set(SOURCE_FILES main.cpp
        ../common/sql_help/MySqlHelper.cpp
        ../common/sql_help/MySqlHelper.h
        ../common/http_response/HttpResponse.cpp
        ../common/http_response/HttpResponse.h
        ../common/logger/make_log.h
        ../common/logger/make_log.c
        ../common/CommonHead.h
        ../common/sql_help/MySqlQueryResult.cpp
        ../common/sql_help/MySqlQueryResult.h
        ../common/userInfo/UserInfo.cpp
        ../common/userInfo/UserInfo.h
        )

add_executable(regist ${SOURCE_FILES})

target_link_libraries(regist fcgi pthread cjson mysqlclient)