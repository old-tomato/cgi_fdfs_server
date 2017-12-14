//
// Created by zkl on 12/11/17.
//

#include "MySqlHelper.h"

MySqlHelper *MySqlHelper::helper = nullptr;

MySqlHelper *MySqlHelper::getInstance() {
    if(helper == nullptr){
        helper = new MySqlHelper;
    }else if(helper->mysql != nullptr){
        return helper;
    }

    helper->mysql = mysql_init(helper->mysql);
    LOG("mysql" , "init" , "mysql init step 1 over");

    if (helper->mysql == nullptr) {
        LOG("mysql" , "init" , "mysql init error");
        return nullptr;
    } else {
        helper->mysql = mysql_real_connect(helper->mysql, "127.0.0.1", "root", "1111", "dfs", 3306, NULL, 0);
        mysql_query(helper->mysql, "set names utf8");
        LOG("mysql" , "init" , "mysql init success");
        return helper->mysql == nullptr ? nullptr : helper;
    }
}

int MySqlHelper::insert(char *sql) {
    if (mysql == nullptr) {
        LOG("mysql" , "insert" , "insert mysql is null");
        return -1;
    }
    int res = mysql_query(mysql, sql);
    // 0 into success
    // 1 into error
    LOG("mysql" , "insert" , "mysql_query success result : %d" , res);
    return res;
}

int MySqlHelper::query(char * sql , bool insertFLag , MySqlQueryResult * queryResult) {
    if(sql == nullptr || strlen(sql) == 0){
        LOG("mysql" , "query" , "sql length is 0");
        return -2;
    }
    if(insertFLag && queryResult == nullptr){
        LOG("mysql" , "query" , "insertFlag is true but result is null");
        return -1;
    }
    if(mysql == nullptr){
        LOG("mysql" , "query" , "sql is null");
        return -3;
    }
    LOG("mysql" , "query" , "sql is %s" , sql);
    int resCode = mysql_query(mysql , sql);
    if(resCode < 0){
        LOG("mysql" , "query" , "query result error : %d" , resCode);
        return resCode;
    }
    MYSQL_RES *res = mysql_store_result(mysql);
    unsigned int fieldCount = mysql_field_count(mysql);
    MYSQL_ROW row;
    
    if(insertFLag && res->row_count > 0){
        int y = 0;
        vector<vector<string *> *> * totalResult = new vector<vector<string *> *>;
        while((row = mysql_fetch_row(res)) != NULL){
            vector<string *> * vecTemp = new vector<string *>;

            for(int x = 0 ; x < fieldCount ; ++ x){
                LOG("mysql" , "query" , "data : %s" , row[x]);
                string * temp = new string(row[x]);
                vecTemp->push_back(temp);
            }

            totalResult->push_back(vecTemp);
            ++ y;
        }

        queryResult->setResult(totalResult);
    }

    LOG("mysql" , "query" , "query row count %d" , res->row_count);

    return res->row_count;
}

void MySqlHelper::close() {
    if (mysql == nullptr) {
        return;
    } else {
        mysql_close(mysql);
    }
}

MySqlHelper::~MySqlHelper() {
    close();
}