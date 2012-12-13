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
#include <signal.h>
#include <fstream>
#include <string>
#include <iostream>
#include <ctime>
#include <stdexcept>
#include <Wt/WEnvironment>
#include <Wt/WConfig.h>
#include "HelloServer.hpp"
#include "HelloApp.hpp"

int main(int argc, char** argv) {
    HelloServer server(argv[0]);
    server.setServerConfiguration(argc, argv, WTHTTP_CONFIGURATION);
    server.addEntryPoint(Wt::Application,
    [](const Wt::WEnvironment& env) {
        return new HelloApp(env);
    });
    if (server.start()) {
        int sig = Wt::WServer::waitForShutdown(argv[0]);
        std::cerr << "Shutdown (signal = " << sig << ")" << std::endl;
        server.stop();
        if (sig == SIGHUP)
            Wt::WServer::restart(argc, argv, environ);
    }
    return 0;
}
