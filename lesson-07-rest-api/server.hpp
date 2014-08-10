#ifndef SERVER_H
#define SERVER_H
/* this simple server will provide a hello message on port 8000
manual testing see result with
curl -vv localhost:8000
note reply type is
Transfer-Encoding: chunked

6
hello

0


6 is number of char in contents
answer end with sequence : "0\r\n" followed "\r\n".

*/
#include <Wt/WServer>
#include <Wt/WResource>
#include <Wt/Http/Response>
#include <Wt/Http/Request>
#include "ressource/api.hpp"
#include <functional>

#include <csignal>


int runServer (int argc, char** argv)
{
     using Wt::WServer;
     try {
          // use argv[0] as the application name to match a suitable entry
          // in the Wt configuration file, and use the default configuration
          // file (which defaults to /etc/wt/wt_config.xml unless the environment
          // variable WT_CONFIG_XML is set)
          API api;
          WServer server(argv[0]);

          // WTHTTP_CONFIGURATION is e.g. "/etc/wt/wthttpd"
          server.setServerConfiguration(argc, argv, WTHTTP_CONFIGURATION);

          // add a single entry point, at the default location (as determined
          // by the server configuration's deploy-path)
          server.addResource(&api, "/");
          if (server.start()) {
               int sig = WServer::waitForShutdown(argv[0]);
               std::cerr << "Shutdown (signal = " << sig << ")" << std::endl;
               server.stop();
               if (sig == SIGHUP)
                    WServer::restart(argc, argv, environ);

          }
     } catch (WServer::Exception& e) {
          std::cerr << e.what() << "\n";
          return 1;
     } catch (std::exception& e) {
          std::cerr << "exception: " << e.what() << "\n";
          return 1;
     }
     return 0;
}

#endif // SERVER_H
