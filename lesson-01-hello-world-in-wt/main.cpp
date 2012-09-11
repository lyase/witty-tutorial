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
#include <stdexcept>
#include <Wt/WEnvironment>
#include <Wt/WServer>
#include "HelloApp.hpp"

Wt::WApplication* createApplication(const Wt::WEnvironment& env) {
    Wt::WServer* server = env.server();
    if (!server)
        throw std::logic_error("Couldn't find the server");
    std::string dbConnString;
    server->readConfigurationProperty("dbConnString", dbConnString);
    if (!dbConnString)
        throw std::invalid_argument("Please set the dbConnString in wt_config.xml");
    return new HelloApp(env, dbConnString);
//return new HelloApp(env,&_aWebPageFactoryHelloWebsite);
}

int main(int argc, char** argv) {
    using std::ofstream;
    using std::endl;
    cout<< "\n starting application to  debug comand line parameters  logging command line parameters to file\n";
    ofstream out("ComandLineParameters.txt", fstream::app);
    out<<"<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<"<<endl;
    out<<"I am a app starting parent with pid: "<< getpid()<<endl;
    time_t t = time(0);   // get time now
    struct tm * now = localtime( & t );
    out <<"now year is:"<< (now->tm_year + 1900) << endl\
        <<"month is:" << (now->tm_mon + 1) << endl\
        <<"day is:"<<  now->tm_mday<< endl\
        << "The local date and time is: " << asctime(now) << endl;
    tm* gmtm = gmtime(& t);
    if (gmtm != NULL) {
        out << "The UTC date and time is: " << asctime(gmtm) << endl;
    } else {
        out << "Failed to get the UTC date and time" << endl;
    }
    out <<"here are the comand line parameters passed to app when started:" << endl;
    for (int i=0; i<argc; ++i) {
        out <<"parameter["<<i<<"]:="<< argv[i] << " "<<endl;
    }
    out.close();

    return Wt::WRun(argc, argv, &createApplication);
}
