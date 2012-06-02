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

#include "HelloApp.hpp"
#include "HelloFactory.hpp"
#include"IWebPageFactory.h"

Wt::WApplication* createApplication(const Wt::WEnvironment& env) {
WebPageFactory* mFactory;
HelloFactory _aWebPageFactoryHelloWebsite();
mFactory=&_aWebPageFactoryHelloWebsite;
    return new HelloApp(env,mFactory);
return new HelloApp(env,&_aWebPageFactoryHelloWebsite);
}

int main(int argc, char** argv) {
    return Wt::WRun(argc, argv, &createApplication);
}
