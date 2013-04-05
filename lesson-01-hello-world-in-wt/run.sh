#!/bin/sh
./hellowt --docroot ".;/doc/html,/resources" --approot .  --http-address=0.0.0.0 --http-port=8000 -c hellowt.xml
