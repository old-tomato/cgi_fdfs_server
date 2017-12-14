#!/usr/bin/env bash

chmod 0777 ./stop_server.sh
chmod 0777 ./start_server.sh

#stop
./stop_server.sh

#start
./start_server.sh

chmod 0777 ./clear.sh
chmod 0777 ./complie.sh
chmod 0777 ./load_mode.sh
chmod 0777 ./kill_mode.sh

# make
./complie.sh

./load_mode.sh