#!/bin/sh
gdb --args ./auth --docroot . --approot . --http-address=0.0.0.0 --http-port=8000 --c wt-config.xml
