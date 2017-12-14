//
// Created by zkl on 12/11/17.
//

#ifndef LOGIN_USERINFO_H
#define LOGIN_USERINFO_H

#include <string.h>

class UserInfo {
private:
    char md5[64] = {0};
    char nickname[128] = {0};
    char username[128] = {0};
    char password[128] = {0};
public:
    UserInfo(){};
    UserInfo(char * md5 , char * nickname);
    UserInfo(char * md5 , char * nickname , char * username , char * password);
    void setNickname(char * nickname);
    void setMd5(char * md5);

    char *getUsername();
    char *getPassword();

    void setUsername(char * username);
    void setPassword(char * password);

    char * getNickname();
    char * getMd5();
};


#endif //LOGIN_USERINFO_H

