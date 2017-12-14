//
// Created by zkl on 12/11/17.
//

#ifndef REGIST_COMMONHEAD_H
#define REGIST_COMMONHEAD_H

extern "C"{
#include "./logger/make_log.h"
};

#include "./http_response/HttpResponse.h"
#include "./sql_help/MySqlHelper.h"
#include "./sql_help/MySqlQueryResult.h"
#include "./redis_help/RedisHelper.h"
#include "./security_check/SecurityCheck.h"
#include <vector>

#include <cjson/cJSON.h>

using namespace std;

#endif //REGIST_COMMONHEAD_H
