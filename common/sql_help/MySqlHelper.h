//
// Created by zkl on 12/11/17.
//

#ifndef CGI_SERVER_TEST_01_SQLHELPER_H
#define CGI_SERVER_TEST_01_SQLHELPER_H

#include "../CommonHead.h"
#include "./MySqlQueryResult.h"
#include <vector>
#include <mysql/mysql.h>

using namespace std;

class MySqlHelper{
private:
    MYSQL * mysql = nullptr;
    static MySqlHelper * helper;
    MySqlHelper(){};
public:
    static MySqlHelper * getInstance();

    int insert(char * sql);

    int query(char * sql , bool insertFLag , MySqlQueryResult * queryResult);

    int processResult();

    void close();

    ~MySqlHelper();
};

#endif //CGI_SERVER_TEST_01_SQLHELPER_H
