#!/usr/bin/env bash

#kill mode
./kill_mode.sh

#load mode
sudo spawn-fcgi -a 127.0.0.1 -p 8001 -f ./out/regist

#load mode
sudo spawn-fcgi -a 127.0.0.1 -p 8002 -f ./out/login

#load mode
sudo spawn-fcgi -a 127.0.0.1 -p 8003 -f ./out/file_upload

sudo /usr/local/nginx/sbin/nginx -s reload