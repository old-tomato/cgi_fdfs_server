#include <stdlib.h>

#include <unistd.h>
#include <pthread.h>
#include <string>
#include <string.h>
#include <cjson/cJSON.h>
#include <vector>
#include "fcgi_stdio.h"
#include <iostream>

#include "../common/CommonHead.h"
#include "../common/userInfo/UserInfo.h"

using namespace std;

int queryUserInfoByNameAndPassword(char * name , char * password , UserInfo * userInfo){
    char sql[1024] = {0};
    sprintf(sql , "select name , nickname , password from user where name = \"%s\" and password = \"%s\"" , name , password);
    LOG("login" , "login sql " , "%s" , sql);
    
    MySqlQueryResult * result = new MySqlQueryResult;
    int ret = MySqlHelper::getInstance()->query(sql , true , result);

    if(ret <= 0){
        return ret;
    }

    if(userInfo != nullptr){
        vector<vector<string *> *> * temp = result->getResult();
        vector<string *> * tt = *(temp->begin());

        int x = 0;
        for(auto it = tt->begin() ; it != tt->end() ; ++it , ++ x){
            if(x == 1){
                userInfo->setNickname(const_cast<char *>((*it)->c_str()));
            }
        }

        userInfo->setMd5("thisisMD5");
    }
    
    delete result;
    return ret;
}

void toLogin(char * data){

    LOG("login" , "login sql " , "data %s" , data);
    if(data == nullptr || strlen(data) == 0){
        printf(HttpResponse::Error("username or password is null").getData().c_str());
        return;
    }
    cJSON *obj = cJSON_Parse(data);
    char * username = cJSON_GetObjectItem(obj , "username")->valuestring;
    char * password = cJSON_GetObjectItem(obj , "password")->valuestring;
    LOG("login" , "login check " , "username %s password %s" , username , password);

    UserInfo userInfo;
    
    int res = queryUserInfoByNameAndPassword(username , password , &userInfo);

    if(res == 0){
        LOG("login" , "login check failed" , "login check failed");
        printf(HttpResponse::Error("login check failed").getData().c_str());

        return;
    }else if(res < 0){
        LOG("login" , "login check failed" , "server error");
        printf(HttpResponse::Error("server error").getData().c_str());
        return;
    }else{
        LOG("login" , "login check success" , "%s login" , username);
        
        // set token alway is hello
        char command[1024] = {0};
        char token[] = "hello";
        sprintf(command , "set %s %s " , token , username);
        int res = RedisHelper::getInstance()->setCommand(command);
        if(res < 0){
            printf(HttpResponse::Error("server error").getData().c_str());
            return;
        }

        cJSON *obj = cJSON_CreateObject();
        cJSON_AddStringToObject(obj , "nickname" , userInfo.getNickname());
        cJSON_AddStringToObject(obj , "token" , token);

        printf(HttpResponse::Success().setResultObj(obj)->getData().c_str());
        return;
    }
}

int main() {
    char **initialEnv = environ;
    int count = 0;

    while (FCGI_Accept() >= 0) {
        char * queryStr = getenv("QUERY_STRING");
        char *contentLength = getenv("CONTENT_LENGTH");
        int len;
        if(contentLength == NULL){
            continue;
        }
        len = atoi(contentLength);

        char data[len + 1] = {0};
        fread(data , 1 , len , stdin);

        toLogin(data);
    }

    return 0;
}