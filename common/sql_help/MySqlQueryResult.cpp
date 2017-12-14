//
// Created by zkl on 12/11/17.
//

#include "MySqlQueryResult.h"

void MySqlQueryResult::setResult(vector<vector<string *> * > * data){
    this->result = data;
}

vector<vector<string *> * > * MySqlQueryResult::getResult(){
    return this->result;
}

MySqlQueryResult::~MySqlQueryResult(){
    for(auto it = result->begin() ; it != result->end() ; ++ it){

        vector<string *> * temp =  *it;

        for(auto iit = temp->begin() ; iit != temp->end() ; ++ iit){
            string * strTemp = *iit;
            delete strTemp;
        }

        delete temp;
    }
    delete result;
}