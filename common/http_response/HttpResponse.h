//
// Created by zkl on 12/11/17.
//

#ifndef CGI_SERVER_TEST_01_HTTPRESPONSE_H
#define CGI_SERVER_TEST_01_HTTPRESPONSE_H

#include <string.h>
#include <string>
#include <cjson/cJSON.h>
#include "../CommonHead.h"

using namespace std;

class HttpResponse{
private:
    string message;
    int code;
    string result;
    cJSON * resultObj = nullptr;
public:
    static const int SUCCESS = 200;
    static const int ERROR = -1;
public:
    HttpResponse(int code , string message , string result);

    static HttpResponse Success();

    static HttpResponse Success(string result);

    static HttpResponse Error(string result);

    static HttpResponse Error();

    HttpResponse * setResultObj(cJSON * obj);

    string getData();

    ~HttpResponse();

};

#endif //CGI_SERVER_TEST_01_HTTPRESPONSE_H