#!/bin/sh
./server test_conn --docroot . --http-address 0.0.0.0 --http-port 8000 & 
# let server start
sleep 5
./clientfromscratch
RESULT=$?
killall server
return $RESULT
