#!/usr/bin/env bash

echo 'kill regist'
sudo kill -9 `ps aux | grep ./out/regist | grep -v grep | awk '{print $2}'`
echo 'kill login'
sudo kill -9 `ps aux | grep ./out/login | grep -v grep | awk '{print $2}'`
echo 'kill file_upload'
sudo kill -9 `ps aux | grep ./out/file_upload | grep -v grep | awk '{print $2}'`