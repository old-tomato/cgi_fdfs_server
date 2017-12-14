//
// Created by zkl on 12/13/17.
//

#ifndef FILE_UPLOAD_SECURITYCHECK_H
#define FILE_UPLOAD_SECURITYCHECK_H

#include "../CommonHead.h"
#include "string.h"

class SecurityCheck {

private:
    char * tokenInfo = nullptr;

public:

    bool checkToken(char * tokenInfo);

};


#endif //FILE_UPLOAD_SECURITYCHECK_H
