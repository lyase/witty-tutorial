#!/bin/sh
echo Making build dir...
mkdir build
cd build
echo Running cmake...
cmake ..
echo building...
make
echo running...
#./hellowt --docroot . --http-address 0.0.0.0 --http-port 8080
echo deploying
scp cmdl desafder@debian-witty-prod-srv:
ssh desafder@debian-witty-prod-srv "./cmdl stop" 
scp hellowt desafder@debian-witty-prod-srv:
ssh desafder@debian-witty-prod-srv "./cmdl start" 

