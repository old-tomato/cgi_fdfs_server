#include <stdlib.h>

#include <unistd.h>
#include <pthread.h>
#include <string>
#include <string.h>
#include <cjson/cJSON.h>
#include <vector>
#include "fcgi_stdio.h"
#include <iostream>
#include <unistd.h>
#include <sys/wait.h>

#include "../common/CommonHead.h"
#include "../common/userInfo/UserInfo.h"

int moveFileToFdfs(char * filename , char ** path){
    int fd[2];
    pipe(fd);

    int pid = fork();
    if(pid == 0){
        close(fd[0]);
        dup2(fd[1] , STDOUT_FILENO);

        char * args[4] = {"fdfs_upload_file" , "./conf/client.conf" , filename , 0};

        execvp("fdfs_upload_file" , args);

    }else{
        close(fd[1]);

        waitpid(pid , nullptr , 0);
        char * res = new char[1024];
        memset(res , 0 , 1024);
        read(fd[0] , res , 1024);

        if(strlen(res) == 0){
            LOG("file_upload" , "move_to_fdfs" , "fdfs path failed");
            return -1;
        }
        LOG("file_upload" , "move_to_fdfs" , "fdfs path : %s" , res);

        *path = res;

        return 1;
    }
}

void saveFile(char * data){
    char *part1 = strtok(data , "\r\n");
    LOG("file_upload" , "part" , "part1 ==> %s" , part1);

    char *fileInfo = strtok(NULL , "\r\n");
    LOG("file_upload" , "part" , "part1 ==> %s" , fileInfo);

    //=====================username========================
    char *userStartStr = strchr(fileInfo , '\"') + 1 ;
    char * userEndStr = strchr(userStartStr, '\"');

    int len = userEndStr - userStartStr;
    char username[len + 1] = {0};

    for(int x =0 ; x < len ; ++ x){
        username[x] = userStartStr[x];
    }
    LOG("file_upload" , "part" , "un : %s" , username);

    //filename="login" md5="0d3bd02a98dbfe751275078d04534213" size=62688
    //=====================filename========================
    char * temp = userEndStr + 1;
    char *filenameStartStr = strchr(temp , '\"') + 1 ;
    char *filenameEndStr = strchr(filenameStartStr , '\"');
    int filenameLen = filenameEndStr - filenameStartStr;

    char filename[filenameLen + 1] = {0};
    for(int x =0 ; x < filenameLen ; ++ x){
        filename[x] = filenameStartStr[x];
    }
    LOG("file_upload" , "part" , "filename : %s" , filename);

    //=====================md5========================
    temp = filenameEndStr + 1;
    char * md5StartStr = strchr(temp , '\"') + 1;
    char *md5EndStr = strchr(md5StartStr , '\"');
    int md5Len = md5EndStr - md5StartStr;

    char md5[md5Len + 1] = {0};
    for(int x =0 ; x < md5Len ; ++ x){
        md5[x] = md5StartStr[x];
    }
    LOG("file_upload" , "part" , "md5 : %s" , md5);

    //=====================size========================

    temp = md5EndStr + 1;
    char *sizeStr = strstr(temp , "size=");
    if(sizeStr == nullptr){
        printf(HttpResponse::Error("size is null").getData().c_str());
        return;
    }

    sizeStr = sizeStr + strlen("size=");
    int size = 0;
    sscanf(sizeStr , "%d" , &size);
    LOG("file_upload" , "part" , "size : |%s| : |%d|" , sizeStr , size);

    char *part3 = strtok(NULL , "\r\n");

    char *fileContent = strtok(NULL , "\r\n");

    FILE * file = fopen(filename , "w");
    int current = 0;
    while(1){
        current += fwrite(fileContent , 1 , size , file);
        if(current >= size){
            LOG("file_upload" , "write" , "end current : %d , total : %d" , current , size);
            break;
        }
        LOG("file_upload" , "write" , "current : %d" , current);
    }

    fclose(file);

    // move file to fdfs
    char * path = nullptr;
    moveFileToFdfs(filename , &path);

    // write into sql

    
    printf(HttpResponse::Success().getData().c_str());
}

int main() {
    char **initialEnv = environ;
    int count = 0;

    while (FCGI_Accept() >= 0) {
        char * queryStr = getenv("QUERY_STRING");

        LOG("file_upload" , "security_check" , "queryStr : %s" , queryStr);

        // check
        SecurityCheck sc;
        bool checkFlag = sc.checkToken(queryStr);

        LOG("file_upload" , "security_check" , "check result : %s" , checkFlag ? "OK" : "FAILED");

        if(!checkFlag){
            printf(HttpResponse::Error("token check failed").getData().c_str());
            continue;
        }

        char *contentLength = getenv("CONTENT_LENGTH");
        int len;
        if(contentLength == NULL){
            continue;
        }
        len = atoi(contentLength);

        char * data = (char *)malloc(len + 1);
        memset(data , 0 , len + 1);
        fread(data , 1 , len , stdin);
        saveFile(data);
        free(data);
    }

    return 0;
}