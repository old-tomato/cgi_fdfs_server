#!/usr/bin/env bash

#complie
echo 'into regist'
cd regist
cmake .
make
cd ..
echo 'out regist'

echo "into login"
cd login
cmake .
make
cd ..
echo "out login"

echo "into file_upload"
cd file_upload
cmake .
make
cd ..
echo "out file_upload"
