#!/bin/sh
./server test_conn --docroot . --http-address 0.0.0.0 --http-port 8000 --ssl-certificate server.crt --ssl-private-key server.key --https-port 8443 --https-address 0.0.0.0 --ssl-tmp-dh dh512.pem &
# let server start
sleep 5
./clientfromscratch
RESULT=$?
killall server
return $RESULT
