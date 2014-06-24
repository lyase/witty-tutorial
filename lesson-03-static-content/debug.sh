#!/bin/sh

cgdb --args ./lesson-03-static-content --docroot "./static" --approot=.  --http-address=0.0.0.0 --http-port=8000 -c hellowt.xml
