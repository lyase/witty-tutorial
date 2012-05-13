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
echo build user dbo demo
 make user_dbo_demo
echo running demo dbo functionality class user
 ./user_dbo_demo
echo running functional test for class user
./usertest --log_level=test_suite --report_level=short
echo checking memory for user class
valgrind ./usertest   --log_level=test_suite --report_level=short
echo loop updating on src change
 while true; do (([[ -z $(git status --porcelain) ]] && echo -n .) || (sleep 0.5;clear; date; ((make 2>&1 | tee make_output.txt) ; git commit -a -q -F make_output.txt))); sleep 1; rm make_output.txt; done
echo deploying
ssh desafder@debian-witty-prod-srv "./cmdl stop" 
scp hellowt desafder@debian-witty-prod-srv:
ssh desafder@debian-witty-prod-srv "./cmdl start" 
echo done.

