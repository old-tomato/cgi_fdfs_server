//
// Created by zkl on 12/11/17.
//

#include "HttpResponse.h"

HttpResponse::HttpResponse(int code , string message , string result){
    this->code = code;
    this->message = message;
    this->result = result;
}

string HttpResponse::getData(){
    string result = "Content-Type: text/html\r\n\r\n";
    cJSON *obj = cJSON_CreateObject();
    cJSON_AddNumberToObject(obj , "code" , this->code);
    if(resultObj == nullptr){
        cJSON_AddStringToObject(obj , "result" , this->result.c_str());
    }else{
        cJSON_AddItemReferenceToObject(obj , "result" , this->resultObj);
    }

    cJSON_AddStringToObject(obj , "message" , this->message.c_str());
    result.append(cJSON_PrintUnformatted(obj));
    return result;
}

HttpResponse * HttpResponse::setResultObj(cJSON * obj){
    this->resultObj = obj;
    return this;
}

HttpResponse::~HttpResponse() {

}

HttpResponse HttpResponse::Success(){
    return HttpResponse(SUCCESS , "success" , "success");
}

HttpResponse HttpResponse::Success(string result){
    return HttpResponse(SUCCESS , "success" , result);
}

HttpResponse HttpResponse::Error(){
    return HttpResponse(ERROR , "error" , "error");
}

HttpResponse HttpResponse::Error(string result){
    return HttpResponse(ERROR , "error" , result);
}
