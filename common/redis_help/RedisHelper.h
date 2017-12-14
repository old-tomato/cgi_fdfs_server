//
// Created by zkl on 12/13/17.
//

#ifndef FILE_UPLOAD_REDISHELPER_H
#define FILE_UPLOAD_REDISHELPER_H

#include <hiredis/hiredis.h>
#include <string.h>

extern "C"{
#include "../logger/make_log.h"
};


class RedisHelper {

private:
    redisContext * context;
    redisReply * reply = nullptr;

    static RedisHelper * helper;

    RedisHelper(){};

public:
    static RedisHelper * getInstance();

    static RedisHelper * getInstance(char * ip , int port);

    int setCommand(char * command);

    int getStrCommand(char * command , char ** result);

    ~RedisHelper();
};


#endif //FILE_UPLOAD_REDISHELPER_H
