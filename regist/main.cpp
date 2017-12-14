#include "fcgi_config.h"

#include <stdlib.h>

#include <unistd.h>
#include <pthread.h>
#include <string>
#include <string.h>
#include <cjson/cJSON.h>
#include "fcgi_stdio.h"

#include "../common/CommonHead.h"

extern char **environ;

using namespace std;

void toRegist(char * data){
    cJSON *obj = cJSON_Parse(data);

    char * username = cJSON_GetObjectItem(obj , "username")->valuestring;
    char * nickname = cJSON_GetObjectItem(obj , "nickname")->valuestring;
    char * password = cJSON_GetObjectItem(obj , "password")->valuestring;
    char * phone = cJSON_GetObjectItem(obj , "phone")->valuestring;
    char * email = cJSON_GetObjectItem(obj , "email")->valuestring;

    if(username == nullptr || strlen(username) == 0 ||
            nickname == nullptr || strlen(nickname) == 0 ||
            password == nullptr || strlen(password) == 0 ||
            phone == nullptr || strlen(phone) == 0 ||
            email == nullptr || strlen(email) == 0){

        LOG("regist" , "regist" , "param is null");
        printf(HttpResponse::Error("param is null").getData().c_str());
        return;
    }

    MySqlHelper *helper = MySqlHelper::getInstance();
    char sql[1024] = {0};
    sprintf(sql , "insert into user(name , nickname , password , phone , createtime , email) values("
            "\"%s\" , \"%s\" , \"%s\" , \"%s\" , now() , \"%s\")" ,
            username , nickname , password , phone , email);

    LOG("regist" , "regist" , "insert sql ==> %s" , sql);

    int res = helper->insert(sql);

    if(res < 0){
        LOG("regist" , "regist" , "insert error");
        printf(HttpResponse::Error("insert error").getData().c_str());
        return;
    }
    if(res == 0){
        LOG("regist" , "regist" , "insert success");
        printf(HttpResponse::Success("insert success").getData().c_str());
        return;
    }else{
        LOG("regist" , "regist" , "insert error : username or nickname already existed");
        printf(HttpResponse::Error("username or nickname already existed").getData().c_str());
        return;
    }
}

int main ()
{
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

        toRegist(data);
    }

    return 0;

}
