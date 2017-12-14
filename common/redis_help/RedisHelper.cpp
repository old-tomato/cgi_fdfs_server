//
// Created by zkl on 12/13/17.
//

#include "RedisHelper.h"

RedisHelper *RedisHelper::helper = nullptr;

RedisHelper *RedisHelper::getInstance() {
    char *ip = "127.0.0.1";
    int port = 6379;

    return getInstance(ip, port);
}

RedisHelper *RedisHelper::getInstance(char *ip, int port) {
    if (helper == nullptr) {
        helper = new RedisHelper;
        helper->context = redisConnect(ip, port);
        if (helper->context == nullptr) {
            LOG("redis", "redis_connect", "redis connect error at %s : %d", ip, port);
            delete helper;
            return nullptr;
        }
    }
    return helper;
}

int RedisHelper::setCommand(char *command) {
    if (command == nullptr) {
        LOG("redis", "redis_command", "set command is null");
        return -1;
    }
    LOG("redis", "redis_command", "set command : %s", command);
    if (this->context == nullptr) {
        LOG("redis", "redis_command", " but redis_context is null");
        return -1;
    }
    reply = static_cast<redisReply *>(redisCommand(this->context, command));
    if (reply->type == REDIS_REPLY_STATUS) {
        // OK
        return 1;
    } else {
        LOG("redis", "redis_command", "command error");
        return -1;
    }
}

int RedisHelper::getStrCommand(char *command, char **result) {
    if (command == nullptr) {
        LOG("redis", "redis_command", "get command is null");
        return -1;
    }

    LOG("redis", "redis_command", "get command : %s", command);

    if (this->context == nullptr) {
        LOG("redis", "redis_command", " but redis_context is null");
        return -1;
    }

    reply = static_cast<redisReply *>(redisCommand(context, command));

        if (reply->type == REDIS_REPLY_STRING) {

            int resultLen = strlen(reply->str);

            char *temp = new char[resultLen + 1];
            memset(temp, 0, resultLen + 1);
            strcpy(temp, reply->str);

            *result = temp;
            // OK
            return 1;
        } else if(reply->type == REDIS_REPLY_ERROR){
            LOG("redis", "redis_command", "command error");
            return -1;
        } else{
            LOG("redis", "redis_command", "command result type error");
            return -1;
        }
}

RedisHelper::~RedisHelper() {
    if (this->context != nullptr) {
        redisFree(this->context);
    }
}