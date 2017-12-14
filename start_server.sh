#!/usr/bin/env bash

#start nginx
echo 'start nginx'
sudo cp ./conf/nginx.conf /usr/local/nginx/conf/
sudo /usr/local/nginx/sbin/nginx

#start fdfs
echo 'start fdfs'
sudo fdfs_trackerd ./conf/tracker.conf
sudo fdfs_storaged ./conf/storage.conf

#start redis
echo 'start redis'
sudo redis-server ./conf/redis.conf
