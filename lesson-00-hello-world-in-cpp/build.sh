#!/bin/sh
echo Making build dir...
mkdir build
cd build
echo Running cmake...
cmake ..
echo building...
make
echo running...
#./hello
echo deploying
ssh desafder@debian-witty-prod-srv "./cmdl stop" 
scp hellowt desafder@debian-witty-prod-srv:
ssh desafder@debian-witty-prod-srv "./cmdl start" 
echo done.
