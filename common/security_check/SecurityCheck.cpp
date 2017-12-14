//
// Created by zkl on 12/13/17.
//

#include "SecurityCheck.h"

bool SecurityCheck::checkToken(char * tokenInfo){

    char *username = strchr(tokenInfo , '&') + 1;
    int tokenLen = (username - 1) - tokenInfo;
    char token[tokenLen + 1] = {0};
    strncpy(token , tokenInfo , tokenLen);

    LOG("securiy_check" , "token_check" , "nickname : %s , token : %s" , username , token);

    char * result = nullptr;
    char command[128] = {0};
    sprintf(command , "get %s" , token);
    int res = RedisHelper::getInstance()->getStrCommand(command , &result);
    if(res < 0 || result == nullptr){
        LOG("securiy_check" , "token_check" , "username : %s , token : %s , res : %d" , username , token , res);
        return false;
    }
    if(strcmp(result , username) == 0){
        LOG("securiy_check" , "token_check" , "check ok");
        return true;
    }else{
        LOG("securiy_check" , "token_check" , "check failed username : %s , token : %s , result : %s" , username , token , result);
        return false;
    }
}