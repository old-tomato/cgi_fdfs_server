//
// Created by zkl on 12/11/17.
//

#include "UserInfo.h"

UserInfo::UserInfo(char * md5 , char * nickname){
    strcpy(this->md5 , md5);
    strcpy(this->nickname , nickname);
}

UserInfo::UserInfo(char * md5 , char * nickname , char * username , char * password){
    strcpy(this->md5 , md5);
    strcpy(this->nickname , nickname);

    strcpy(this->username , username);
    strcpy(this->password , password);
}

void UserInfo::setNickname(char * nickname){
    if(nickname == nullptr){
        return;
    }
    strcpy(this->nickname , nickname);
}

void UserInfo::setMd5(char * md5){
    if(md5 == nullptr){
        return;
    }
    strcpy(this->md5 , md5);
}

char * UserInfo::getNickname(){
    return this->nickname;
}

char * UserInfo::getMd5(){
    return this->md5;
}

void UserInfo::setUsername(char * username){
    if(username != nullptr){
        strcpy(this->username , username);
    }
}

void UserInfo::setPassword(char * password){
    if(password != nullptr){
        strcpy(this->password , password);
    }
}

char *UserInfo::getUsername() {
    return username;
}

char *UserInfo::getPassword() {
    return password;
}
