#!/bin/sh
echo cleaning up
rm -rvf generetedStatic build doc

echo Making build dir...
mkdir build  generetedStatic
mkdir generetedStatic/tests
cd build
echo Running cmake...
cmake ..
echo building...
make hellowt
make usertest
echo buil documentation
cd ..
doxygen doxy.config 
mv doc generetedStatic/
cd build
echo runningon build machine...
#./hellowt --docroot . --http-address 0.0.0.0 --http-port 8080
echo build user dbo demo
 make user_dbo_demo
echo running demo dbo functionality class user
 ./user_dbo_demo
echo running functional test for class user
./usertest --log_level=test_suite --report_level=short
echo generate html report for tests
./usertest --report_format=xml --report_level=detailed --log_level=test_suite --log_format=xml  >testresults.xml
xsltproc ../boost_testRes.xsl testresults.xml   >../generetedStatic/tests/processedtestresults.xml


echo checking memory for user class
valgrind ./usertest   --log_level=test_suite --report_level=short
echo loop updating on src change
# while true; do (([[ -z $(git status --porcelain) ]] && echo -n .) || (sleep 0.5;clear; date; ((make 2>&1 | tee make_output.txt) ; git commit -a -q -F make_output.txt))); sleep 1; rm make_output.txt; done
echo deploying
scp ../cmdl desafder@debian-witty-prod-srv:
#using script management
ssh desafder@debian-witty-prod-srv "./cmdl stop" 
# using start stop commands
#ssh desafder@debian-witty-prod-srv "/sbin/start-stop-daemon --stop --signal 15 --retry 5 --quiet --pidfile /var/run/Myscript/hello.pid "
# manual management 
#ssh desafder@debian-witty-prod-srv "killall hellowt " 
scp hellowt desafder@debian-witty-prod-srv:
scp hellowt.xml desafder@debian-witty-prod-srv:
scp -r ../generetedStatic desafder@debian-witty-prod-srv:
scp hellowt.xml desafder@debian-witty-prod-srv:
#using script management
ssh desafder@debian-witty-prod-srv "rm /var/run/Myscript/hellowt.pid ; ./cmdl start" 
# using start stop commands
#ssh desafder@debian-witty-prod-srv "/sbin/start-stop-daemon --start --quiet   --chuid desafder:desafder --pidfile /var/run/Myscript/hello.pid --make-pidfile         --background   --exec  /home/desafder/hellowt --        --docroot=\".;generetedStatic\"    --approot .     --http-address=0.0.0.0 --http-port=8080"
# manual management 
#ssh desafder@debian-witty-prod-srv "screen -d -m /home/desafder/hellowt -c hellowt.xml  --docroot \".;generetedStatic\"    --approot .     --http-address=0.0.0.0 --http-port=8080"
#ssh desafder@debian-witty-prod-srv "/home/desafder/hellowt   --docroot doc/html    --approot .     --http-address=0.0.0.0 --http-port=8080      &"
echo done.

