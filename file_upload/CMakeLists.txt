cmake_minimum_required(VERSION 3.4)
project(file_upload)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../out)

set(SOURCE_FILES main.cpp
        ../common/sql_help/MySqlQueryResult.cpp
        ../common/sql_help/MySqlQueryResult.h
        ../common/sql_help/MySqlHelper.cpp
        ../common/sql_help/MySqlHelper.h
        ../common/http_response/HttpResponse.cpp
        ../common/http_response/HttpResponse.h
        ../common/logger/make_log.h
        ../common/logger/make_log.c
        ../common/CommonHead.h
        ../common/redis_help/RedisHelper.cpp
        ../common/redis_help/RedisHelper.h
        ../common/security_check/SecurityCheck.cpp
        ../common/security_check/SecurityCheck.h
        )

set(LINK_DIR "/usr/local/lib")
link_directories(${LINK_DIR})

set(INCLUDE_DIR "/usr/local/include")
include_directories(${INCLUDE_DIR})

add_executable(file_upload ${SOURCE_FILES})

target_link_libraries(file_upload fcgi pthread cjson mysqlclient hiredis)