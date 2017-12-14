#!/usr/bin/env bash

echo 'clean into regist'
cd regist
sudo rm -rf ./CMakeCache.txt  ./CMakeFiles  ./cmake_install.cmake ./Makefile ./.idea/
cd ..
echo 'clean out regist'

echo 'clean into login'
cd login
sudo rm -rf ./CMakeCache.txt  ./CMakeFiles  ./cmake_install.cmake ./Makefile ./.idea/
cd ..
echo 'clean out login'

echo 'clean into file_upload'
cd file_upload
sudo rm -rf ./CMakeCache.txt  ./CMakeFiles  ./cmake_install.cmake ./Makefile ./.idea/
cd ..
echo 'clean out file_upload'

echo 'clean into out'
cd out
sudo rm -rf *
cd ..
echo 'clean out out'

echo 'clean logs'
cd logs
sudo rm -rf *
cd ..
echo 'clean logs out'