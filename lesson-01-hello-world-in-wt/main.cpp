/*
 * =====================================================================================
 *
 *       Filename:  main.cpp
 *
 *    Description:  Hello world in c++
 *
 *        Version:  1.0
 *        Created:  01/05/12 10:06:50
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Matthew Sherborne (), msherborne@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */
#include <fstream>
#include <string>
#include <iostream>
#include <ctime>
using namespace std;
#include "HelloApp.hpp"

Wt::WApplication* createApplication(const Wt::WEnvironment& env) {
    return new HelloApp(env);
//return new HelloApp(env,&_aWebPageFactoryHelloWebsite);
}

int main(int argc, char** argv) {
cout<< "\nstarted application with logging to file\n";
ofstream out("outfile.txt");
for (int i=0; i<argc; ++i) {
//   cout << argv[i] << ''<<endl;
   out << argv[i] << ' '<<endl;
   }
out<<"one"<<endl;
out<<"two"<<endl;
out.close();

    return Wt::WRun(argc, argv, &createApplication);
}
