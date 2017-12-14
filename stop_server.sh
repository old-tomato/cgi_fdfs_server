#!/usr/bin/env bash

#stop nginx
echo 'stop nginx'
sudo /usr/local/nginx/sbin/nginx -s quit

#stop fdfs
echo 'stop fdfs'
sudo kill -9 `ps aux | grep fdfs__trackerd | grep -v grep | awk '{print $2}'`
sudo kill -9 `ps aux | grep fdfs__storaged | grep -v grep | awk '{print $2}'`

#stop redis
echo 'stop redis'
sudo kill -9 `ps aux | grep redis | grep -v grep | awk '{print $2}'`

#kill mode
./kill_mode.sh
