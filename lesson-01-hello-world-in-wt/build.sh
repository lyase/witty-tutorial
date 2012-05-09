#!/bin/sh
echo cleaning up
rm -rvf  build doc

echo Making build dir...
mkdir build
cd build
echo Running cmake...
cmake ..
echo building...
make
make usertest
echo buil documentation
cd ..
doxygen doxy.config 
cd build
echo running...
./hellowt --docroot . --http-address 0.0.0.0 --http-port 8080
echo running test
./usertest --log_level=test_suite --report_level=short
echo checking memory for user class
valgrind ./usertest 
