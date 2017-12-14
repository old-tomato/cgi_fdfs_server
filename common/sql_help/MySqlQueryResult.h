//
// Created by zkl on 12/11/17.
//

#ifndef LOGIN_MYSQLQUERYRESULT_H
#define LOGIN_MYSQLQUERYRESULT_H

#include <vector>
#include <string>

using namespace std;

class MySqlQueryResult {
private:
    vector<vector<string *> * > * result = nullptr;
    int code;
public:
    MySqlQueryResult(){}
    MySqlQueryResult(vector<vector<string *> * > *  data):result(data){}

    void setResult(vector<vector<string *> * > *  data);
    vector<vector<string *> * > * getResult();

    ~MySqlQueryResult();
};


#endif //LOGIN_MYSQLQUERYRESULT_H
